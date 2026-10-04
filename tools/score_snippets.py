#!/usr/bin/env python3
"""Scores each ~/rs64-auto/snippets/<func>.c draft with asm-differ in this checkout, restoring every file afterwards.

Usage (repo root): score_snippets.py [func ...]   (default: every snippet whose function is still INCLUDE_ASM)
Writes ~/rs64-auto/snippet_scores.tsv: func, score (or failure reason).
"""
import pathlib, re, subprocess, sys
sys.path.insert(0, "tools")
import auto_decomp as a

SNIP = pathlib.Path.home() / "rs64-auto" / "snippets"

def score(func):
    c_path = next((c for c in pathlib.Path("src").rglob("*.c") if f", {func});" in a.read(c)), None)
    if c_path is None:
        return "not-asm"
    original = a.read(c_path)
    nl = "\r\n" if "\r\n" in original else "\n"
    base = a.with_types(original, nl)
    pat = re.compile(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', re.M)
    code = (SNIP / f"{func}.c").read_text().replace("\r\n", "\n").strip("\n") + "\n"
    a.write(c_path, base)
    subprocess.run(a.CPP + [str(c_path)], capture_output=True)
    pathlib.Path("/tmp/auto_ctx.c").write_text(subprocess.run(a.CPP + [str(c_path)], capture_output=True, text=True).stdout)
    result = "build-failed"
    try:
        for _ in range(6):
            m = pat.search(base)
            a.write(c_path, base[:m.start()] + code.rstrip("\n").replace("\n", nl) + base[m.end():])
            ok, reason = a.rom_matches()
            if ok:
                return "MATCH"
            und = re.search(r"`(\w+)' undeclared", reason)
            if not reason.startswith("build failed"):
                break
            if not und:
                return "build-failed: " + reason[14:90]
            code = a.declaration_for(und.group(1)) + code
        else:
            return result
        r = subprocess.run([sys.executable, "tools/asm-differ/diff.py", "--no-pager", "--format", "plain", func], capture_output=True, text=True)
        m = re.search(r"CURRENT \((\d+)\)", r.stdout)
        return m.group(1) if m else "no-score"
    finally:
        a.write(c_path, original)
        pathlib.Path(c_path).touch()

def main():
    funcs = sys.argv[1:] or sorted(p.stem for p in SNIP.glob("*.c"))
    out = pathlib.Path.home() / "rs64-auto" / "snippet_scores.tsv"
    with open(out, "w") as f:
        for func in funcs:
            s = score(func)
            f.write(f"{func}\t{s}\n")
            f.flush()
            print(func, s, flush=True)
    subprocess.run(["make", "-j16", "build/tyler.z64"], capture_output=True)

if __name__ == "__main__":
    main()
