#!/usr/bin/env python3
"""Writes C for thin wrapper functions (argument setup, one jal, return) straight from their splat asm."""
import pathlib, re, sys

INSN = re.compile(r"^\s*/\* [0-9A-Fa-f]+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/\s+(\S+)\s*(.*)$")
AREGS = ["$a0", "$a1", "$a2", "$a3"]

def parse(path):
    insns, in_text = [], True
    for line in pathlib.Path(path).read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith(".section"):
            in_text = line.split()[1].startswith(".text")
            continue
        m = INSN.match(line)
        if m and in_text:
            ops = [o.strip() for o in m.group(2).split(",")] if m.group(2) else []
            insns.append((m.group(1), ops))
    return insns

def imm(s):
    return int(s, 0)

def synth(func, path):
    """Returns C text, or None when the function isn't a plain wrapper."""
    ins = parse(path)
    if len(ins) < 5 or ins[0][0] != "addiu" or ins[0][1][0] != "$sp":
        return None
    if [i[0] for i in ins[-3:]] != ["lw", "jr", "addiu"] or ins[-3][1][0] != "$ra":
        return None
    body = [i for i in ins[1:-3] if not (i[0] == "sw" and i[1] and i[1][0] == "$ra")]
    if len(body) != len(ins) - 5:
        return None
    jals = [i for i, (op, _) in enumerate(body) if op == "jal"]
    if len(jals) != 1 or jals[0] != len(body) - 2:
        return None
    callee = body[jals[0]][1][0]
    setup = body[:jals[0]] + body[jals[0] + 1:]
    vals = {}
    params = {}
    for op, ops in setup:
        if not ops or ops[0] not in AREGS:
            return None
        dst = ops[0]
        def src(r):
            if r == "$zero":
                return "0"
            if r in vals:
                return vals[r]
            if r in AREGS:
                params.setdefault(r, "s32")
                return f"arg{AREGS.index(r)}"
            raise ValueError(r)
        try:
            if op == "addu" and ops[2] == "$zero":
                vals[dst] = src(ops[1])
            elif op == "addiu" and ops[1] == "$zero":
                vals[dst] = hex(imm(ops[2])) if imm(ops[2]) >= 10 else str(imm(ops[2]))
            elif op == "lui" and ops[1].startswith("%hi("):
                vals[dst] = "&" + ops[1][4:-1]
            elif op == "addiu" and ops[2].startswith("%lo(") and ops[1] == dst and vals.get(dst, "").startswith("&"):
                pass
            elif op == "lui":
                vals[dst] = hex(imm(ops[1]) << 16)
            elif op == "ori" and ops[1] == dst and dst in vals:
                vals[dst] = hex(int(vals[dst], 0) | imm(ops[2]))
            elif op == "andi" and ops[2] in ("0xFF", "0xFFFF") and ops[1] in AREGS and ops[1] not in vals:
                params[ops[1]] = "u8" if ops[2] == "0xFF" else "u16"
                vals[dst] = f"arg{AREGS.index(ops[1])}"
            else:
                return None
        except (ValueError, IndexError):
            return None
    written = [AREGS.index(r) for r in vals]
    n_args = max(written + [AREGS.index(p) for p in params], default=-1) + 1
    args, arg_types = [], []
    for k in range(n_args):
        r = AREGS[k]
        if r in vals:
            args.append(vals[r])
            arg_types.append(params.get(r, "s32") if vals[r] == f"arg{k}" else ("void*" if vals[r].startswith("&") else "s32"))
        else:
            params.setdefault(r, "s32")
            args.append(f"arg{k}")
            arg_types.append(params[r])
    n_params = max([AREGS.index(p) for p in params], default=-1) + 1
    plist = ", ".join(f"{params.get(AREGS[k], 's32')} arg{k}" for k in range(n_params)) or "void"
    externs = sorted({a[1:] for a in args if a.startswith("&")})
    out = "".join(f"extern s32 {e};\n" for e in externs)
    out += f"void {callee}({', '.join(arg_types) or 'void'});\n\n"
    out += f"void {func}({plist}) {{\n    {callee}({', '.join(args)});\n}}\n"
    return out

if __name__ == "__main__":
    for p in sys.argv[1:]:
        f = pathlib.Path(p).stem
        c = synth(f, p)
        print(f"// {f}: {'wrapper' if c else 'not a wrapper'}")
        if c:
            print(c)
