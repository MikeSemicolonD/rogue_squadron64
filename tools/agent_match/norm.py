import re
import sys

# norm.py rom|obj FILE : normalize objdump output (ROM disassembly, or .o disassembly with -r) so %hi/%lo and call targets compare equal
mode, path = sys.argv[1], sys.argv[2]
raw = open(path).read().split("\n")
ins = []
lo_next = set()
for line in raw:
    m = re.match(r"^\s*[0-9a-f]+:\s+(R_MIPS_\w+)", line)
    if m:
        if ins and m.group(1) == "R_MIPS_LO16":
            lo_next.add(len(ins) - 1)
        continue
    m = re.match(r"^\s*[0-9a-f]+:\s+(?:[0-9a-f]{8}\s+)?(.*)$", line)
    if not m or not m.group(1).strip():
        continue
    ins.append(re.sub(r"\s+", " ", m.group(1).strip()))

MEM = re.compile(r"^(lw|sw|lh|lhu|lb|lbu|sh|sb|lwc1|swc1|ldc1|sdc1|addiu) ([^,]+),(-?\d+)\((\w+)\)$")
ADDIU = re.compile(r"^addiu (\w+),(\w+),(-?\d+)$")
out = []
luireg = {}
for i, s in enumerate(ins):
    s = re.sub(r"^(jal|j) .*", r"\1 X", s)
    s = re.sub(r"^(b\w*) (.*?),?(0x)?[0-9a-f]+( <.*>)?$", lambda m: f"{m.group(1)} {m.group(2)},X" if m.group(2) else f"{m.group(1)} X", s)
    m = re.match(r"^lui (\w+),", s)
    if m:
        s = f"lui {m.group(1)},X"
        luireg[m.group(1)] = i
    mm = MEM.match(s)
    am = ADDIU.match(s)
    if mm:
        base = mm.group(4)
        if (mode == "obj" and i in lo_next) or (mode == "rom" and base in luireg):
            s = f"{mm.group(1)} {mm.group(2)},X({base})"
    elif am and ((mode == "obj" and i in lo_next) or (mode == "rom" and am.group(2) in luireg)):
        s = f"addiu {am.group(1)},{am.group(2)},X"
    # a write to a register ends its lui tracking; a move copies it
    w = re.match(r"^\w+(?:\.\w+)* (\$?\w+),", s)
    mv = re.match(r"^move (\w+),(\w+)$", s)
    if mv and mv.group(2) in luireg:
        luireg[mv.group(1)] = i
    elif w and not s.startswith("lui ") and not re.match(r"^(sw|sh|sb|swc1|sdc1|b)", s):
        luireg.pop(w.group(1), None)
    out.append(s)
print("\n".join(out))
