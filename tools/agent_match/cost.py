"""Live spend estimate for an agent_match run, from the Agent SDK session logs (~/.claude/projects/-home-michael-rs64-w*/).

    python3 tools/agent_match/cost.py [RUN_DIR]   (default: newest ~/rs64-auto/agent_runs/*)

Counts every assistant message written after the run started, once per message id. Prices are USD per million tokens.
The runner's summary.tsv holds the exact per-function cost once each agent finishes; this is the running estimate.
"""
import json
import sys
from pathlib import Path

PRICES = {
    "claude-opus-5-5": {"in": 4.00, "out": 20.00, "cache_read": 0.20, "cache_write_5m": 5.00, "cache_write_1h": 8.00},
    "claude-sonnet-5-5": {"in": 2.00, "out": 10.00, "cache_read": 0.20, "cache_write_5m": 2.50, "cache_write_1h": 4.00},
}

runs = sorted((Path.home() / "rs64-auto" / "agent_runs").iterdir())
run = Path(sys.argv[1]) if len(sys.argv) > 1 else runs[-1]
start = (run / "runner.log").stat().st_ctime if (run / "runner.log").exists() else run.stat().st_ctime

seen = set()
per_wt = {}
for proj in (Path.home() / ".claude" / "projects").glob("-home-michael-rs64-w*"):
    wt = proj.name.split("-")[-1]
    for f in proj.glob("*.jsonl"):
        if f.stat().st_mtime < start:
            continue
        for line in open(f, errors="replace"):
            try:
                d = json.loads(line)
            except ValueError:
                continue
            m = d.get("message")
            if d.get("type") != "assistant" or not isinstance(m, dict) or not m.get("usage"):
                continue
            key = m.get("id") or d.get("uuid")
            if key in seen:
                continue
            seen.add(key)
            p = PRICES.get(m.get("model"))
            if not p:
                continue
            u = m["usage"]
            cc = u.get("cache_creation") or {}
            w5 = cc.get("ephemeral_5m_input_tokens", u.get("cache_creation_input_tokens", 0))
            w1 = cc.get("ephemeral_1h_input_tokens", 0)
            cost = (u.get("input_tokens", 0) * p["in"] + u.get("output_tokens", 0) * p["out"]
                    + u.get("cache_read_input_tokens", 0) * p["cache_read"] + w5 * p["cache_write_5m"] + w1 * p["cache_write_1h"]) / 1e6
            s = per_wt.setdefault(wt, [0.0, 0])
            s[0] += cost
            s[1] += 1

total = sum(v[0] for v in per_wt.values())
for wt, (c, n) in sorted(per_wt.items(), key=lambda kv: int(kv[0][1:])):
    print(f"rs64-{wt}: ${c:6.2f}  ({n} API calls)")
print(f"total:    ${total:6.2f}  (run {run.name})")
