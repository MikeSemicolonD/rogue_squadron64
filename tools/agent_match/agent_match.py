"""Run several Claude Agent SDK agents in parallel, each hand-matching one decomp function in its own worktree.

Setup (once, in WSL):
    curl -LsSf https://astral.sh/uv/install.sh | sh
    uv venv ~/rs64-auto/agentvenv && VIRTUAL_ENV=~/rs64-auto/agentvenv uv pip install claude-agent-sdk

Run (in WSL, from ~/rs64-decomp-build, with the key set only in that shell):
    export ANTHROPIC_API_KEY=sk-ant-...
    ~/rs64-auto/agentvenv/bin/python tools/agent_match/agent_match.py
    ~/rs64-auto/agentvenv/bin/python tools/agent_match/agent_match.py --agents 5 --total-budget 95 --budget 12 mat3x3InverseInto sinfApprox

Each worker takes the next function from the queue, resets its worktree (~/rs64-w<N>) with ~/rs64-auto/tools/reset_w.sh and
runs one agent there. The agent never commits. When it stops, the runner scores its final draft; a 0-line draft is landed in
~/rs64-decomp-build (replace_asm.py, make -j4 check, commit as Michael Frye), one landing at a time. The run stops taking new
functions once the summed cost reaches --total-budget, or after an API error such as exhausted credit.
Everything for a run goes to ~/rs64-auto/agent_runs/<timestamp>/: per-function transcripts, drafts, notes and summary.tsv.
"""
import argparse
import asyncio
import json
import os
import re
import shlex
import subprocess
import sys
import time
from pathlib import Path

from claude_agent_sdk import (
    AssistantMessage,
    ClaudeAgentOptions,
    HookMatcher,
    ResultMessage,
    TextBlock,
    ToolUseBlock,
    query,
)

HOME = Path.home()
MAIN = HOME / "rs64-decomp-build"
SKILL = "/mnt/c/Users/Michael/.claude/skills/matching-rs64-decomp-functions"
MEMORY = "/mnt/c/Users/Michael/.claude/projects/e--Projects-RogueSquadron64Recomp/memory/project_decomp_build_check_2026_10_04.md"
ENV = ". ~/opt/rs64env.sh && "

# Closest near-misses first (permuter units; ~5 per register line). See memory project_decomp_handoff_2026_10_08.
DEFAULT_TARGETS = [
    "resetEffectObjectVecQuads",
    "mat3x3InverseInto",
    "sinfApprox",
    "updateGridLayerScroll",
    "drawTextGlyphRect",
    "popNpcSlotFromTail",
    "scanConvertTriangleToSpanTable",
    "npcSpawnInitTimedEffect",
    "floatMatrixToFixed",
    "startPlayerSlotAnimationChannelLooping",
    "updateEffectObjectTransformPieces",
    "streamTerrainGridCellsByDistance",
    "advanceSongRegion",
    "transformVec3ToNpcLocalWithScale",
    "findSegmentObjectSphereHit",
    "timeSnapshotFiller",
    "samplePlayerAnimChannel",
    "gatherAndSortNearbyNpcViewPoints",
    "loadSongAssetByName",
]

SYSTEM = """You are a decompilation matching specialist for the Star Wars: Rogue Squadron N64 decomp. You turn one function's MIPS asm into C that
compiles byte-identical with the original compiler (GCC 2.8.1 SN cc1n64, or 2.7.2 SN0001 for some files; -O2 -G0 -mips3).

Read these before starting, they hold the project's hard-won levers and pitfalls:
- {skill}/SKILL.md, {skill}/asm-patterns.md, {skill}/tricks.md (large: search it for your symptom)
- {memory} (session lessons: allocation priority, scheduling, permuter pitfalls)
The skill mentions ~/sd.sh, ~/cm.sh, land.sh and Windows paths: ignore those. Use only the helpers below.

Your environment: Linux (WSL). Your worktree is {wt} (the current directory); it is a full copy of the repo. Work only inside it and in
your run directory {rundir}. Every shell command needs the toolchain: prefix with `. ~/opt/rs64env.sh && `.

Helpers (run from the worktree root):
- `bash tools/agent_match/score.sh FUNC draft.c [more.c...]`: prints `<draft> <diff lines> <ours>/<target> struct=<N>` and writes draft.diff
  (unified, target vs ours, %hi/%lo normalized). 0 diff lines = matched. struct=0 means only registers differ.
- `bash tools/agent_match/rawasm.sh FUNC draft.c [N]`: your compiled asm with real registers/branch targets. Target: asm/nonmatchings/**/FUNC.s.
- `bash tools/agent_match/gccdump.sh FUNC draft.c "-dl -dg" OUTDIR`: GCC pass dumps for the function (-dl/-dg allocation priorities and
  conflicts, -dS sched1 ready lists, -dc combine, -dL loop). Use these to diagnose register and scheduling residuals instead of guessing.
- `sh tools/m2c_func.sh FUNC` gives an m2c draft if you need a fresh start.
- Starting point: the best previous draft is copied to {rundir}/start.c (may be absent). Previous permuter outputs, if any, are in
  ~/rs64-w*/tools/decomp-permuter/nonmatchings/FUNC*/output-*/source.c (lower number = closer).

Rules:
- A draft is a snippet: any typedefs/externs it needs followed by the function definition. It replaces the INCLUDE_ASM line in the source
  file, so names already declared later in that file may need an alias (`extern T x_l __asm__("x");`).
- Never commit, never push, never `git reset --hard`, never `git checkout -- .`, never edit files outside your worktree and run directory,
  never touch ~/rs64-decomp-build or anything under /mnt/e. Restore single files only. Use `make -j4` or lower. No background processes.
- Write candidate drafts into {rundir}. Keep {rundir}/best.c updated with your lowest-scoring draft at all times, and append one line per
  idea tried to {rundir}/notes.md (what you changed, the score, what it told you).
- Diagnose before mutating: after ~10 variants that do not move a 1-10 line residual, read the dumps and form a hypothesis.
- When you reach 0 diff lines, copy that draft to {rundir}/best.c and confirm the whole ROM: `python3 tools/replace_asm.py FUNC {rundir}/best.c`,
  delete the `// LANDING:` lines it adds, `rm -f build/<src minus .c>.o build/<src minus .c>.s`, `make -j4 check` must print
  `build/tyler.z64: OK`, then `git checkout -- <src>` to restore the file. score.sh compares code only: float literals, jump tables and
  strings go to .rodata in the order the compiler first creates them, so a code match can still fail the ROM check. If it fails,
  `python3 tools/first_diff.py build/tyler.z64 rogue_squadron.z64 --map build/tyler.elf.map` names the differing symbol; fix the source
  order (e.g. if/else vs switch changes literal creation order) and repeat. Stop only after the ROM check passes. The runner lands it.
- If you are out of ideas, stop with best.c holding your best draft. End with a 3-6 line summary: final score, what blocks the match,
  and any lever worth adding to tricks.md.
"""

TASK = """Match `{func}` (source file {src}). Current best known draft: {start_note}.
Score it first, read the diff and the target asm, then work until it matches or you are genuinely stuck."""


def sh(cmd, cwd=None, timeout=1800):
    r = subprocess.run(["bash", "-lc", cmd], cwd=cwd, capture_output=True, text=True, timeout=timeout)
    return r.returncode, r.stdout + r.stderr


def src_of(func, root=MAIN):
    rc, out = sh(f"grep -rl 'INCLUDE_ASM(\"[^\"]*\", {func});' src | head -1", cwd=root)
    return out.strip()


def score(wt, func, draft):
    rc, out = sh(ENV + f"bash tools/agent_match/score.sh {func} {shlex.quote(str(draft))}", cwd=wt, timeout=900)
    m = re.search(r"\s(\d+) \d+/\d+ struct=", out)
    return (int(m.group(1)) if m else None), out.strip()


def best_permuter_output(func):
    best = None
    for d in HOME.glob(f"rs64-w*/tools/decomp-permuter/nonmatchings/{func}*/output-*"):
        m = re.match(r"output-(\d+)", d.name)
        if m and (d / "source.c").exists() and (best is None or int(m.group(1)) < best[0]):
            best = (int(m.group(1)), d / "source.c")
    return best


def guard_hook(wt, rundir):
    allowed = (str(wt), str(rundir), "/tmp")
    bad = re.compile(r"git\s+(push|reset\s+--hard|checkout\s+--\s+\.)|rs64-decomp-build|/mnt/e/|git\s+commit")

    async def hook(input_data, tool_use_id, context):
        name = input_data.get("tool_name", "")
        tin = input_data.get("tool_input", {}) or {}
        reason = None
        if name == "Bash" and bad.search(tin.get("command", "")):
            reason = "Blocked: no commits/pushes/hard resets, and no access to ~/rs64-decomp-build or /mnt/e. The runner lands matches."
        if name in ("Write", "Edit", "MultiEdit", "NotebookEdit"):
            p = Path(tin.get("file_path", "")).expanduser()
            p = str(p if p.is_absolute() else wt / p)
            if not p.startswith(allowed):
                reason = f"Blocked: write outside the worktree {wt} and run directory {rundir}."
        if reason:
            return {"hookSpecificOutput": {"hookEventName": "PreToolUse", "permissionDecision": "deny", "permissionDecisionReason": reason}}
        return {}

    return hook


class Run:
    def __init__(self, args):
        self.args = args
        self.dir = HOME / "rs64-auto" / "agent_runs" / time.strftime("%Y%m%d_%H%M%S")
        self.dir.mkdir(parents=True)
        self.queue = asyncio.Queue()
        for f in args.functions or DEFAULT_TARGETS:
            self.queue.put_nowait(f)
        self.spent = 0.0
        self.stop = False
        self.land_lock = asyncio.Lock()
        self.summary = self.dir / "summary.tsv"
        self.summary.write_text("func\tworktree\tresult\tscore\tcost_usd\tturns\tminutes\n")

    def log(self, msg):
        line = f"[{time.strftime('%H:%M:%S')}] {msg}"
        print(line, flush=True)
        with open(self.dir / "runner.log", "a") as fh:
            fh.write(line + "\n")

    async def land(self, func, draft):
        async with self.land_lock:
            src = src_of(func)
            if not src:
                return "already-landed"
            loop = asyncio.get_running_loop()
            cmd = (ENV + f"python3 tools/replace_asm.py {func} {shlex.quote(str(draft))} && sed -i '/\\/\\/ LANDING:/d' {src} && "
                   f"rm -f build/{src[:-2]}.o build/{src[:-2]}.s build/{src[:-2]}.i && make -j4 check 2>&1 | tail -3")
            rc, out = await loop.run_in_executor(None, lambda: sh(cmd, cwd=MAIN, timeout=3600))
            if "tyler.z64: OK" not in out:
                await loop.run_in_executor(None, lambda: sh(f"git checkout -q -- {src}", cwd=MAIN))
                self.log(f"LAND FAILED {func}: {out[-400:]}")
                return "land-failed"
            commit = (f"git add {src} && git -c user.name='Michael Frye' -c user.email=legoguy217@gmail.com "
                      f"commit -q -m 'Match {func}' && git log --oneline -1")
            rc, out = await loop.run_in_executor(None, lambda: sh(commit, cwd=MAIN))
            self.log(f"LANDED {func}: {out.strip()}")
            return "landed"

    async def run_agent(self, wtn, func):
        args = self.args
        wt = HOME / f"rs64-w{wtn}"
        rundir = self.dir / func
        rundir.mkdir(exist_ok=True)
        loop = asyncio.get_running_loop()
        rc, out = await loop.run_in_executor(None, lambda: sh(f"bash ~/rs64-auto/tools/reset_w.sh {wtn} && mkdir -p tools/agent_match && "
                                                              f"cp {MAIN}/tools/agent_match/*.sh {MAIN}/tools/agent_match/*.py tools/agent_match/", cwd=wt, timeout=900))
        src = src_of(func, wt)
        if not src:
            self.log(f"skip {func}: not an INCLUDE_ASM (already matched?)")
            return
        snippet = HOME / "rs64-auto" / "best_snippets" / f"{func}.c"
        start_note = "none; start from m2c (sh tools/m2c_func.sh FUNC)"
        if snippet.exists():
            (rundir / "start.c").write_text(snippet.read_text())
            start_note = f"{rundir}/start.c"
        pb = best_permuter_output(func)
        if pb:
            start_note += f"; best permuter output (score {pb[0]}) at {pb[1]} (a whole file: copy just the function and what it needs)"

        opts = ClaudeAgentOptions(
            model=args.model,
            effort=args.effort,
            thinking={"type": "adaptive"} if args.thinking else {"type": "disabled"},
            cwd=str(wt),
            system_prompt=SYSTEM.format(skill=SKILL, memory=MEMORY, wt=wt, rundir=rundir),
            allowed_tools=["Bash", "Read", "Write", "Edit", "Grep", "Glob"],
            disallowed_tools=["WebFetch", "WebSearch", "Agent", "Task"],
            permission_mode="bypassPermissions",
            max_turns=args.max_turns,
            max_budget_usd=args.budget,
            add_dirs=[str(rundir), SKILL, str(Path(MEMORY).parent)],
            hooks={"PreToolUse": [HookMatcher(hooks=[guard_hook(wt, rundir)])]},
            setting_sources=[],
        )
        t0 = time.time()
        cost, turns, result, err = 0.0, 0, "stopped", None
        transcript = open(rundir / "transcript.md", "a")
        self.log(f"start {func} in rs64-w{wtn} ({args.model}, ${args.budget} cap)")
        try:
            async for msg in query(prompt=TASK.format(func=func, src=src, start_note=start_note), options=opts):
                if isinstance(msg, AssistantMessage):
                    for b in msg.content:
                        if isinstance(b, TextBlock):
                            transcript.write(b.text + "\n\n")
                        elif isinstance(b, ToolUseBlock):
                            transcript.write(f"> {b.name}: {json.dumps(b.input)[:600]}\n\n")
                    transcript.flush()
                elif isinstance(msg, ResultMessage):
                    cost = msg.total_cost_usd or 0.0
                    turns = msg.num_turns
                    if msg.is_error:
                        err = f"{msg.subtype} {msg.api_error_status or ''} {msg.errors or ''}"
                    if msg.result:
                        transcript.write("## Result\n\n" + msg.result + "\n")
        except Exception as e:
            err = f"{type(e).__name__}: {e}"
        transcript.close()
        self.spent += cost

        if err:
            self.log(f"{func}: agent error: {err[:300]}")
            if re.search(r"credit|billing|quota|rate.?limit|overloaded|40[123]|429|529", err, re.I) and "budget" not in err.lower():
                self.stop = True
                self.log("API error looks like a credit/rate problem: no new functions will start.")

        best = rundir / "best.c"
        n = None
        if best.exists():
            n, out = await loop.run_in_executor(None, lambda: score(wt, func, best))
            if n == 0:
                result = await self.land(func, best)
            else:
                result = "not-matched"
        mins = (time.time() - t0) / 60
        self.log(f"done {func}: {result} score={n} ${cost:.2f} turns={turns} {mins:.0f}min (run total ${self.spent:.2f})")
        with open(self.summary, "a") as fh:
            fh.write(f"{func}\trs64-w{wtn}\t{result}\t{n}\t{cost:.2f}\t{turns}\t{mins:.0f}\n")
        if self.spent >= args.total_budget:
            self.stop = True
            self.log(f"Total budget ${args.total_budget} reached: no new functions will start.")

    async def worker(self, wtn):
        while not self.stop and not self.queue.empty():
            func = self.queue.get_nowait()
            await self.run_agent(wtn, func)

    async def main(self):
        self.log(f"run dir {self.dir}; {self.queue.qsize()} functions; {self.args.agents} agents on rs64-w{self.args.first_worktree}..")
        await asyncio.gather(*(self.worker(self.args.first_worktree + i) for i in range(self.args.agents)))
        self.log(f"finished: ${self.spent:.2f} spent; summary in {self.summary}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("functions", nargs="*", help="functions to match, in order (default: the near-miss list)")
    ap.add_argument("--agents", type=int, default=5, help="parallel agents (default 5)")
    ap.add_argument("--model", default="claude-opus-5-5")
    ap.add_argument("--effort", default="medium", choices=["low", "medium", "high", "xhigh", "max"])
    ap.add_argument("--no-thinking", dest="thinking", action="store_false", help="disable thinking (default: adaptive thinking on)")
    ap.add_argument("--budget", type=float, default=12.0, help="max USD per function (default 12)")
    ap.add_argument("--total-budget", type=float, default=95.0, help="stop starting new functions after this much USD (default 95)")
    ap.add_argument("--max-turns", type=int, default=200)
    ap.add_argument("--first-worktree", type=int, default=1, help="agents use ~/rs64-w<first>..; keep clear of running permuters")
    args = ap.parse_args()
    if not os.environ.get("ANTHROPIC_API_KEY"):
        sys.exit("Set ANTHROPIC_API_KEY in this shell first.")
    asyncio.run(Run(args).main())


if __name__ == "__main__":
    main()
