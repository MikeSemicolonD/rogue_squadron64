#!/usr/bin/env python3
"""Inserts auto_decomp's cleaned m2c C for a function and imports it into decomp-permuter: perm_import.py <func> (run in the worktree root)."""
import pathlib, re, subprocess, sys
sys.path.insert(0, "tools")
import auto_decomp as a

func = sys.argv[1]
c_path = next(c for c in pathlib.Path("src").rglob("*.c") if f", {func});" in a.read(c))
s_path = next(pathlib.Path("asm/nonmatchings").rglob(f"{func}.s"))
original = a.read(c_path)
nl = "\r\n" if "\r\n" in original else "\n"
base = a.with_types(original, nl)
a.write(c_path, base)
code, err = a.m2c(func, s_path, c_path, [])
if err:
    a.write(c_path, original)
    sys.exit(f"m2c: {err}")
m = re.search(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', base, re.M)
for _ in range(6):
    a.write(c_path, base[:m.start()] + code.rstrip("\n").replace("\n", nl) + base[m.end():])
    ok, reason = a.rom_matches()
    und = re.search(r"`(\w+)' undeclared", reason)
    if ok or not reason.startswith("build failed") or not und:
        break
    code = a.declaration_for(und.group(1)) + code
print("build state:", "match" if ok else reason[:120])
if ok:
    print("m2c output already matches; commit it instead of permuting")
mk = a.read("Makefile")
cc = "gcc272sn0001/cc1n64.exe" if f"build/{str(c_path)[:-2]}.s: N64CC = $(GCC272SN0001)" in mk else "gcc281sn/cc1n64.exe"
print("compiler", cc)
r = subprocess.run([sys.executable, "import.py", f"../../{c_path}", f"../../{s_path}"], cwd="tools/decomp-permuter", capture_output=True, text=True)
print(r.stdout[-1500:], r.stderr[-800:])
a.write(c_path, original)
