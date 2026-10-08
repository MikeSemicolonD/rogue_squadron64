"""alias_conflicts.py FUNC DRAFT OUT : run from the repo root. Inserts DRAFT for FUNC, compiles its file, and for every
"conflicting types for `X'" renames the draft's own declaration of X to an alias (`T X_<tag>(...) __asm__("X");`) and its uses,
until the file compiles. Writes the fixed draft to OUT and restores the source file. Use it when a draft written against an older
copy of the file clashes with declarations added by later matches.
"""
import re
import subprocess
import sys
from pathlib import Path

func, draft, out = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
src = subprocess.run(["bash", "-lc", f"grep -rl 'INCLUDE_ASM(\"[^\"]*\", {func});' src | head -1"], capture_output=True, text=True).stdout.strip()
if not src:
    sys.exit(f"{func} is not an INCLUDE_ASM")
orig = Path(src).read_text()
text = draft.read_text()
tag = re.sub(r"[^a-z]", "", func.lower())[:4] or "dr"
base = src[:-2]
try:
    for _ in range(40):
        Path(draft.parent / "_alias_try.c").write_text(text)
        Path(src).write_text(orig)
        subprocess.run(["python3", "tools/replace_asm.py", func, str(draft.parent / "_alias_try.c")], capture_output=True)
        subprocess.run(["bash", "-lc", f"rm -f build/{base}.o build/{base}.s build/{base}.i"])
        r = subprocess.run(["bash", "-lc", f". ~/opt/rs64env.sh && make -s build/{base}.o 2>&1"], capture_output=True, text=True)
        names = sorted(set(re.findall(r"conflicting types for `(\w+)'", r.stdout)))
        if not names:
            errs = [l for l in r.stdout.splitlines() if re.search(r":\d+: (?!warning)", l)]
            print("compiles" if r.returncode == 0 else "other errors:\n" + "\n".join(errs[:8]))
            break
        for n in names:
            alias = f"{n}_{tag}"
            decl = re.compile(r"^([^\n;{}]*\b)" + re.escape(n) + r"(\s*\([^;{]*\))\s*;", re.M)
            if not decl.search(text):
                print(f"no declaration of {n} in the draft; fix by hand")
                sys.exit(1)
            text = decl.sub(lambda m: f'{m.group(1)}{alias}{m.group(2)} __asm__("{n}");', text, count=1)
            text = re.sub(r"(?<![\w\"])" + re.escape(n) + r"(?=\s*\()", alias, text)
            text = text.replace(f'{alias}{"" }', alias)
            text = re.sub(r'__asm__\("' + re.escape(alias) + r'"\)', f'__asm__("{n}")', text)
            print(f"aliased {n} -> {alias}")
finally:
    Path(src).write_text(orig)
    (draft.parent / "_alias_try.c").unlink(missing_ok=True)
out.write_text(text)
