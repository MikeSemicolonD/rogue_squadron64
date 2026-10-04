#!/usr/bin/env python3
"""Compares a built ROM with the original and names the symbol at the first difference."""
import argparse, re, sys

# (rom_start, rom_end, vram_start, name), copied from SECTIONS in the recomp's tools/make_elf.py.
SEGMENTS = [
    (0x000000, 0x001000, None, "header/ipl3"),
    (0x001000, 0x0A5D30, 0x80000400, "main"),
    (0x0A5D30, 0x10C2D0, 0x800A5130, "mission_overlay"),
    (0x10C2D0, 0x1346C0, 0x800A5130, "menu_overlay"),
    (0x137580, 0x142D90, 0x800A5130, "cinematic_overlay"),
]

def segment_of(off):
    for start, end, vram, name in SEGMENTS:
        if start <= off < end:
            return name, (vram + off - start) if vram is not None else None
    return "data/assets", None

def load_map(path):
    syms = []
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            m = re.match(r"\s+0x([0-9a-fA-F]{8,16})\s+([A-Za-z_][A-Za-z0-9_.]*)\s*$", line)
            if m:
                syms.append((int(m.group(1), 16) & 0xFFFFFFFF, m.group(2)))
    syms.sort()
    return syms

def symbol_at(syms, vram):
    best = None
    for addr, name in syms:
        if addr > vram:
            break
        best = (addr, name)
    return best

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("built")
    ap.add_argument("expected")
    ap.add_argument("--map")
    a = ap.parse_args()
    with open(a.built, "rb") as f:
        b = f.read()
    with open(a.expected, "rb") as f:
        e = f.read()
    if b == e:
        print("MATCH")
        return 0
    if len(b) != len(e):
        print(f"size differs: built 0x{len(b):X}, expected 0x{len(e):X}")
    n = min(len(b), len(e))
    diffs = [i for i in range(n) if b[i] != e[i]]
    if not diffs:
        print(f"common prefix of 0x{n:X} bytes matches")
        return 1
    first = diffs[0]
    seg, vram = segment_of(first)
    word = "byte" if len(diffs) == 1 else "bytes"
    print(f"first difference at ROM 0x{first:X} ({seg}); {len(diffs)} differing {word}")
    if vram is not None:
        print(f"vram 0x{vram:08X}")
        if a.map:
            hit = symbol_at(load_map(a.map), vram)
            if hit:
                print(f"in {hit[1]} +0x{vram - hit[0]:X}")
    return 1

if __name__ == "__main__":
    sys.exit(main())
