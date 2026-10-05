#!/usr/bin/env python3
"""Makes base.c parseable when the source file uses GCC asm labels (`T x __asm__("sym");`) or top-level __asm__ blocks.

decomp-permuter's import leaves its `_permuter_ignore_line` marker in such lines, and pycparser rejects asm labels.
This strips the marker and wraps each top-level line that contains __asm__ in PERM_IGNORE(...).
Usage: perm_fix_base.py <nonmatchings/func/base.c>
"""
import re, sys

p = sys.argv[1]
lines = open(p).read().replace("_permuter_ignore_line ", "").split("\n")
out, depth, n = [], 0, 0
for l in lines:
    if depth == 0 and re.search(r"\b(__asm__|asm)\s*\(", l) and l.rstrip().endswith(";") and not l.startswith("PERM_IGNORE("):
        out.append("PERM_IGNORE(" + l.rstrip() + ")")
        n += 1
    else:
        out.append(l)
    depth += l.count("{") - l.count("}")
open(p, "w").write("\n".join(out))
print("wrapped", n)
