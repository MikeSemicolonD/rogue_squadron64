#!/usr/bin/env python3
"""Replaces a function's INCLUDE_ASM line in its .c file with the C definition read from another file."""
import argparse, pathlib, re, sys

def read(path):
    with open(path, encoding="utf-8", newline="") as f:
        return f.read()

def find_c(func):
    pat = re.compile(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', re.M)
    for c in sorted(pathlib.Path("src").rglob("*.c")):
        text = read(c)
        m = pat.search(text)
        if m:
            return c, text, m
    sys.exit(f"replace_asm: no INCLUDE_ASM for {func}")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("func")
    ap.add_argument("c_file", help="file holding the function's C definition")
    a = ap.parse_args()
    c, text, m = find_c(a.func)
    nl = "\r\n" if "\r\n" in text else "\n"
    body = read(a.c_file).replace("\r\n", "\n").strip("\n").replace("\n", nl)
    with open(c, "w", encoding="utf-8", newline="") as f:
        f.write(text[:m.start()] + body + text[m.end():])
    print(f"{a.func}: replaced in {c}")

if __name__ == "__main__":
    main()
