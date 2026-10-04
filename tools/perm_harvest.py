#!/usr/bin/env python3
"""Applies permuter score-0 results to the main clone, keeping each only if the ROM still matches; run from the repo root.

Looks in the given worktrees' tools/decomp-permuter/nonmatchings/<func>/output-0-*/source.c.
"""
import pathlib, re, subprocess, sys
sys.path.insert(0, "tools")
import auto_decomp as a

def function_text(src, func):
    m = re.search(r"^[A-Za-z_][\w \*]*\b" + re.escape(func) + r"\s*\([^;{]*\)\s*\{", src, re.M)
    if not m:
        return None
    i, depth = src.index("{", m.start()), 0
    for j in range(i, len(src)):
        if src[j] == "{":
            depth += 1
        elif src[j] == "}":
            depth -= 1
            if depth == 0:
                return src[m.start():j + 1]
    return None

def snippet_decls(func):
    p = pathlib.Path.home() / "rs64-auto" / "snippets" / f"{func}.c"
    if not p.exists():
        return ""
    t = p.read_text()
    body = function_text(t, func)
    return t[:t.index(body)] if body else ""

def main():
    applied = []
    for wt in sys.argv[1:]:
        for d in sorted(pathlib.Path(wt, "tools/decomp-permuter/nonmatchings").glob("*")):
            outs = sorted(d.glob("output-0-*/source.c"))
            if not outs:
                continue
            func = d.name
            src = outs[0].read_text()
            body = function_text(src, func)
            c_path = next((c for c in pathlib.Path("src").rglob("*.c") if f", {func});" in a.read(c)), None)
            if not body or c_path is None:
                print(f"{func}: skipped (body={bool(body)} still-asm={c_path is not None})")
                continue
            snip = pathlib.Path("/tmp/harvest_snip.c")
            snip.write_text(snippet_decls(func) + body + "\n")
            original = a.read(c_path)
            ok, reason = False, ""
            nl = "\r\n" if "\r\n" in original else "\n"
            base = a.with_types(original, nl)
            pat = re.compile(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', re.M)
            code = snip.read_text()
            for _ in range(6):
                m = pat.search(base)
                a.write(c_path, base[:m.start()] + code.rstrip("\n").replace("\n", nl) + base[m.end():])
                ok, reason = a.rom_matches()
                und = re.search(r"`(\w+)' undeclared", reason)
                if ok or not und:
                    break
                code = a.declaration_for(und.group(1)) + code
            if ok:
                subprocess.run(["git", "add", str(c_path)], check=True)
                subprocess.run(["git", "-c", "user.name=Michael Frye", "-c", "user.email=legoguy217@gmail.com",
                                "commit", "-q", "-m", f"Match {func}"], check=True)
                applied.append(func)
                print(f"{func}: MATCH, committed")
            else:
                a.write(c_path, original)
                pathlib.Path(c_path).touch()
                print(f"{func}: score 0 in permuter but ROM differs here ({reason[:80]})")
    print("applied:", len(applied))

if __name__ == "__main__":
    main()
