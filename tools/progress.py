#!/usr/bin/env python3
"""Byte-based decompilation progress: .text bytes in C subsegments minus INCLUDE_ASM functions, per top-level group.

Handwritten asm (hasm) was never C, so it is left out of the totals.
"""
import argparse, pathlib, re, sys
import yaml

TEXT_TYPES = {"c", "asm", "hasm"}
INSN_RE = re.compile(r"^\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/")
INCLUDE_RE = re.compile(r'INCLUDE_ASM\(\s*"([^"]+)"\s*,\s*([A-Za-z0-9_]+)\s*\)')

def _entries(segments):
    for seg in segments:
        if isinstance(seg, list):
            yield seg
        elif isinstance(seg, dict):
            if "start" in seg:
                yield [seg["start"], seg.get("type"), seg.get("name")]
            yield from _entries(seg.get("subsegments", []))

def text_ranges(yaml_path):
    """[(start, size, type, name)] for every text subsegment; size runs to the next ROM-placed entry."""
    with open(yaml_path) as f:
        cfg = yaml.safe_load(f)
    placed = sorted({(e[0], e[1] if len(e) > 1 else None, e[2] if len(e) > 2 else None) for e in _entries(cfg["segments"]) if isinstance(e[0], int)}, key=lambda t: (t[0], t[1] not in TEXT_TYPES))
    starts = sorted({p[0] for p in placed})
    out = []
    for start, typ, name in placed:
        if typ not in TEXT_TYPES or name is None:
            continue
        nxt = next((s for s in starts if s > start), None)
        if nxt is not None:
            out.append((start, nxt - start, typ, name))
    return out

def insn_bytes(path):
    """Counts instruction lines in .text only; spimdisasm puts jump tables in a .rodata section of the same file."""
    n, in_text = 0, True
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            if line.startswith(".section"):
                in_text = line.split()[1].startswith(".text")
            elif in_text and INSN_RE.match(line):
                n += 1
    return 4 * n

def glabel_count(path):
    with open(path, encoding="utf-8", errors="replace") as f:
        return sum(1 for line in f if line.startswith("glabel "))

def measure(root):
    root = pathlib.Path(root)
    stats = {}
    mk = root / "Makefile"
    ultralib = mk.exists() and "USE_ULTRALIB ?= 1" in mk.read_text()
    for start, size, typ, name in text_ranges(root / "roguesquadron.yaml"):
        if typ == "hasm":
            continue
        group = name.split("/")[0]
        g = stats.setdefault(group, {"total": 0, "asm_bytes": 0, "asm_funcs": 0})
        g["total"] += size
        if typ == "asm" and group == "libultra" and ultralib:
            continue
        if typ == "asm":
            g["asm_bytes"] += size
            s = root / "asm" / f"{name}.s"
            if s.exists():
                g["asm_funcs"] += glabel_count(s)
            continue
        c = root / "src" / f"{name}.c"
        if not c.exists():
            g["asm_bytes"] += size
            continue
        for d, func in dict.fromkeys(INCLUDE_RE.findall(c.read_text(encoding="utf-8", errors="replace"))):
            s = root / d / f"{func}.s"
            if not s.exists():
                sys.exit(f"progress: {c} includes {func} but {s} does not exist (run splat first)")
            g["asm_bytes"] += insn_bytes(s)
            g["asm_funcs"] += 1
    return stats

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=".")
    ap.add_argument("--csv", action="store_true")
    a = ap.parse_args()
    stats = measure(a.root)
    rows = []
    for group in sorted(stats):
        g = stats[group]
        rows.append((group, g["total"] - g["asm_bytes"], g["total"], g["asm_funcs"]))
    rows.append(("total", sum(r[1] for r in rows), sum(r[2] for r in rows), sum(r[3] for r in rows)))
    if a.csv:
        print("group,decompiled_bytes,total_bytes,percent,asm_functions")
    for group, done, total, funcs in rows:
        pct = 100.0 * done / total if total else 0.0
        if a.csv:
            print(f"{group},{done},{total},{pct:.1f},{funcs}")
        else:
            print(f"{group}: {done}/{total} bytes ({pct:.1f}%), {funcs} functions in asm")

if __name__ == "__main__":
    main()
