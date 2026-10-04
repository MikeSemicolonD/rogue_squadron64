#!/usr/bin/env python3
"""Compiles variants of a text region in a permuter base.c and reports the instruction diff count vs target.o.

Usage (inside nonmatchings/<func>): try_variants.py <func> <variants.txt>
variants.txt: the original region, then each replacement, separated by lines of '----'.
"""
import pathlib, subprocess, sys

def disasm(obj, func):
    out = subprocess.run(["mips-linux-gnu-objdump", "-d", "--no-show-raw-insn", obj], capture_output=True, text=True).stdout
    lines, on = [], False
    for l in out.splitlines():
        if l.endswith(f"<{func}>:"):
            on = True
            continue
        if on:
            if not l.strip() or l.endswith(">:"):
                break
            lines.append(l.split("\t", 1)[-1].split("<")[0].strip())
    return lines

func = sys.argv[1]
parts = pathlib.Path(sys.argv[2]).read_text().split("\n----\n")
original, variants = parts[0], parts[1:]
base = pathlib.Path("base.c").read_text()
assert original in base, "original region not in base.c"
target = disasm("target.o", func)
for i, v in enumerate(variants):
    pathlib.Path("/tmp/variant.c").write_text(base.replace(original, v, 1))
    r = subprocess.run(["bash", "compile.sh", "/tmp/variant.c", "-o", "/tmp/variant.o"], capture_output=True, text=True)
    if r.returncode:
        err = next((l for l in r.stderr.splitlines() if "variant.c:" in l and "warning" not in l), "?")
        print(f"variant {i}: compile error {err[:100]}")
        continue
    got = disasm("/tmp/variant.o", func)
    diff = sum(1 for a, b in zip(got, target) if a != b) + abs(len(got) - len(target))
    print(f"variant {i}: {diff} differing instructions (len {len(got)} vs {len(target)})")
    if diff == 0:
        print("MATCH:\n" + v)
