#!/usr/bin/env python3
"""Tries m2c output for each INCLUDE_ASM function and keeps it only when the rebuilt ROM still matches byte for byte."""
import argparse, hashlib, pathlib, re, subprocess, sys, time

TARGET_SHA1 = "ed42eed1ee2db646ff7ef94ba8c5421d164a4f0d"
INCLUDE_RE = re.compile(r'^INCLUDE_ASM\("([^"]+)", ([A-Za-z0-9_]+)\);', re.M)
INSN_RE = re.compile(r"^\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/")
CPP = ["mips-linux-gnu-cpp", "-P", "-undef", "-D__GNUC__", "-D_LANGUAGE_C", "-DM2CTX",
       "-D_MIPS_SZLONG=32", "-D_MIPS_SZINT=32", "-I", "include", "-I", "ultralib/include"]

def read(p):
    with open(p, encoding="utf-8", newline="") as f:
        return f.read()

def write(p, text):
    with open(p, "w", encoding="utf-8", newline="") as f:
        f.write(text)

def insn_count(path):
    n, in_text = 0, True
    for line in read(path).splitlines():
        if line.startswith(".section"):
            in_text = line.split()[1].startswith(".text")
        elif in_text and INSN_RE.match(line):
            n += 1
    return n

def candidates(skip):
    out = []
    for c in sorted(pathlib.Path("src").rglob("*.c")):
        for folder, func in INCLUDE_RE.findall(read(c)):
            if func.startswith("fake_func_") or func in skip:
                continue
            s = pathlib.Path(folder) / f"{func}.s"
            if s.exists():
                out.append((insn_count(s), func, c, s))
    out.sort()
    return out

def split_args(s):
    """Splits a macro argument list at top-level commas."""
    args, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            args.append(cur.strip())
            cur = ""
        else:
            cur += ch
    args.append(cur.strip())
    return args

def expand_fields(code):
    """Rewrites M2C_FIELD(expr, T *, off) as a plain pointer cast, innermost first."""
    while True:
        i = code.find("M2C_FIELD(")
        if i < 0:
            return code
        j, depth = i + len("M2C_FIELD("), 1
        start = j
        while depth:
            if code[j] == "(":
                depth += 1
            elif code[j] == ")":
                depth -= 1
            j += 1
        inner = code[start:j - 1]
        if "M2C_FIELD(" in inner:
            inner = expand_fields(inner)
        expr, typ, off = split_args(inner)
        code = code[:i] + f"(*({typ})((u8 *)({expr}) + {off}))" + code[j:]

def m2c(func, s_path, c_path, extra):
    ctx = subprocess.run(CPP + [str(c_path)], capture_output=True, text=True)
    if ctx.returncode:
        return None, "cpp failed"
    pathlib.Path("/tmp/auto_ctx.c").write_text(ctx.stdout)
    r = subprocess.run([sys.executable, "-m", "m2c.main", "-t", "mips-gcc-c", "--valid-syntax",
                        "--context", "/tmp/auto_ctx.c", "--globals=used", *[e for e in extra if e != "no-protos"], str(s_path)],
                       capture_output=True, text=True)
    if r.returncode or not r.stdout.strip():
        return None, "m2c failed"
    code = re.sub(r"\bM2C_UNK(8|16|32|64)?\b", lambda m: {"8": "s8", "16": "s16", "64": "s64"}.get(m.group(1), "s32"), r.stdout)
    code = expand_fields(code)
    bad = re.search(r"M2C_[A-Z_]+", code)
    if bad:
        return None, bad.group(0)
    code = re.sub(r"\s*/\* extern \*/", "", code)
    if "no-protos" in extra:
        code = "\n".join(l for l in code.splitlines() if not re.match(r"^[A-Za-z_][\w \*]*\b\w+\(.*\);$", l) or l.startswith("extern"))
    declared = set(re.findall(r"\b(D_\w+|[a-z]\w*)\b(?=\s*(?:\[.*\])?;)", "\n".join(l for l in code.splitlines() if l.startswith("extern"))))
    context = pathlib.Path("/tmp/auto_ctx.c").read_text()
    missing = sorted({d for d in re.findall(r"\bD_\w+_[0-9A-F]{8}\b", code) if d not in declared and not re.search(r"\b" + d + r"\b", context)})
    if missing:
        code = "".join(f"extern s32 {d};\n" for d in missing) + code
    return code.strip("\n") + "\n", None

def rom_matches():
    b = subprocess.run(["make", "-j16", "build/tyler.z64"], capture_output=True, text=True)
    if b.returncode:
        lines = (b.stdout + b.stderr).splitlines()
        err = next((l for l in lines if re.search(r"\.c:\d+: (?!warning)", l) or re.search(r"undefined reference|multiple definition|Error:", l)), "")
        return False, "build failed: " + err[:160]
    h = hashlib.sha1(pathlib.Path("build/tyler.z64").read_bytes()).hexdigest()
    return h == TARGET_SHA1, "rom differs" if h != TARGET_SHA1 else "match"

def with_types(text, nl):
    """Files that only include common.h have no s32 etc.; the header adds no code."""
    if "common_types.h" in text or "ultratypes.h" in text:
        return text
    anchor = '#include "common.h"' + nl
    if anchor in text:
        return text.replace(anchor, anchor + '#include "common_types.h"' + nl, 1)
    return '#include "common_types.h"' + nl + text

def try_func(func, c_path, s_path, variants):
    original = read(c_path)
    nl = "\r\n" if "\r\n" in original else "\n"
    pat = re.compile(r'^INCLUDE_ASM\("[^"]+", ' + re.escape(func) + r'\);', re.M)
    reason = "no variant"
    base = with_types(original, nl)
    for extra in variants:
        write(c_path, base)
        code, err = m2c(func, s_path, c_path, extra)
        if err:
            reason = err
            write(c_path, original)
            continue
        m = pat.search(base)
        write(c_path, base[:m.start()] + code.rstrip("\n").replace("\n", nl) + base[m.end():])
        ok, reason = rom_matches()
        if ok:
            return True, "match " + " ".join(extra)
        write(c_path, original)
    pathlib.Path(c_path).touch()
    return False, reason

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--skip", default=str(pathlib.Path.home() / "rs64-skip-tmcg2.txt"))
    ap.add_argument("--log", default=str(pathlib.Path.home() / "rs64-auto" / "auto_decomp.tsv"))
    ap.add_argument("--max-insns", type=int, default=10**9)
    ap.add_argument("--limit", type=int, default=10**9)
    ap.add_argument("--commit-every", type=int, default=25)
    a = ap.parse_args()
    skip = set(pathlib.Path(a.skip).read_text().split()) if pathlib.Path(a.skip).exists() else set()
    done = set()
    if pathlib.Path(a.log).exists():
        done = {line.split("\t")[0] for line in pathlib.Path(a.log).read_text().splitlines() if line}
    ok, _ = rom_matches()
    if not ok:
        sys.exit("auto_decomp: baseline ROM does not match; fix that first")
    variants = [[], ["--no-andor"], ["--no-casts"], ["no-protos"]]
    matched_since_commit, tried = [], 0
    with open(a.log, "a") as log:
        for n, func, c_path, s_path in candidates(skip):
            if n > a.max_insns or tried >= a.limit:
                break
            if func in done:
                continue
            tried += 1
            t0 = time.time()
            ok, reason = try_func(func, c_path, s_path, variants)
            log.write(f"{func}\t{n}\t{c_path}\t{'OK' if ok else 'FAIL'}\t{reason}\t{time.time() - t0:.1f}\n")
            log.flush()
            if ok:
                matched_since_commit.append(func)
                print(f"MATCH {func} ({n} insns)", flush=True)
                if len(matched_since_commit) >= a.commit_every:
                    commit(matched_since_commit)
                    matched_since_commit = []
        if matched_since_commit:
            commit(matched_since_commit)
    ok, _ = rom_matches()
    print("final ROM", "OK" if ok else "MISMATCH", flush=True)

def commit(funcs):
    subprocess.run(["git", "add", "src"], check=True)
    msg = f"Match {len(funcs)} functions\n\n" + "\n".join(funcs) + "\n"
    subprocess.run(["git", "-c", "user.name=Michael Frye", "-c", "user.email=legoguy217@gmail.com",
                    "commit", "-q", "-m", msg], check=True)

if __name__ == "__main__":
    main()
