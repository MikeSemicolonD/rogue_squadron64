#!/usr/bin/env python3
"""Puts C for a function into its .c file and imports it into decomp-permuter.

Usage (from the repo root): perm_import.py <func> [--snippet file.c] [--sed EXPR ...]
Without --snippet the C comes from m2c (cleaned like auto_decomp); with it, from a hand-written attempt.
Undeclared identifiers are declared the way auto_decomp does; the .c file is restored afterwards.
"""
import argparse, pathlib, re, subprocess, sys
sys.path.insert(0, "tools")
import auto_decomp as a

ap = argparse.ArgumentParser()
ap.add_argument("func")
ap.add_argument("--snippet")
ap.add_argument("--sed", action="append", default=[], help="sed expression applied to the .c file first (repeatable)")
args = ap.parse_args()
func = args.func
c_path = next(c for c in pathlib.Path("src").rglob("*.c") if f", {func});" in a.read(c))
s_path = next(pathlib.Path("asm/nonmatchings").rglob(f"{func}.s"))
original = a.read(c_path)
nl = "\r\n" if "\r\n" in original else "\n"
base = a.with_types(original, nl)
for e in args.sed:
    base = subprocess.run(["sed", e], input=base, capture_output=True, text=True, check=True).stdout
a.write(c_path, base)
if args.snippet:
    code = a.read(args.snippet).replace("\r\n", "\n").strip("\n") + "\n"
    subprocess.run(a.CPP + [str(c_path)], capture_output=True, text=True)
    ctx = subprocess.run(a.CPP + [str(c_path)], capture_output=True, text=True).stdout
    pathlib.Path("/tmp/auto_ctx.c").write_text(ctx)
else:
    code, err = a.m2c(func, s_path, c_path, [])
    if err:
        a.write(c_path, original)
        sys.exit(f"m2c: {err}")
m = re.search(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', base, re.M)
ok, reason = False, ""
for _ in range(40):
    a.write(c_path, base[:m.start()] + code.rstrip("\n").replace("\n", nl) + base[m.end():])
    ok, reason = a.rom_matches()
    und = re.search(r"`(\w+)' undeclared", reason)
    if ok or not reason.startswith("build failed") or not und:
        break
    code = a.declaration_for(und.group(1)) + code
print("build state:", "match" if ok else reason[:160])
if ok:
    print("ALREADY MATCHES")
elif not reason.startswith("build failed"):
    # The permuter must compile with the same compiler the Makefile uses for this file.
    gcc272 = f"build/{str(c_path)[:-2]}.s: N64CC = $(GCC272SN0001)" in a.read("Makefile")
    subprocess.run(["sh", "tools/permuter_setup.sh"] + (["272"] if gcc272 else []), check=True, capture_output=True)
    print("compiler:", "GCC 2.7.2" if gcc272 else "GCC 2.8.1")
    r = subprocess.run([sys.executable, "import.py", f"../../{c_path}", f"../../{s_path}"], cwd="tools/decomp-permuter", capture_output=True, text=True)
    print(r.stdout[-600:], r.stderr[-400:])
    base_c = pathlib.Path("tools/decomp-permuter/nonmatchings", func, "base.c")
    if base_c.exists():
        subprocess.run([sys.executable, "tools/perm_fix_base.py", str(base_c)])
a.write(c_path, original)
