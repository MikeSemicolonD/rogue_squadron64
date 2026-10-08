import re
import sys

# normpair.py TARGET_RAW OURS_RAW OUT_T OUT_B : exact normalization when both sides have the same instruction count.
# OURS_RAW is `objdump -dr` of the object; every instruction carrying a relocation gets its immediate masked (X) on both sides,
# and branch/jump targets are masked everywhere. Exits 2 if the instruction counts differ (caller falls back to norm.py).
t_path, b_path, out_t, out_b = sys.argv[1:5]


def parse(path):
    ins, rel = [], set()
    for line in open(path).read().split("\n"):
        if re.match(r"^\s*[0-9a-f]+:\s+R_MIPS_\w+", line):
            if ins:
                rel.add(len(ins) - 1)
            continue
        m = re.match(r"^\s*[0-9a-f]+:\s+(?:[0-9a-f]{8}\s+)?(.*)$", line)
        if m and m.group(1).strip():
            ins.append(re.sub(r"\s+", " ", m.group(1).strip()))
    return ins, rel


t, _ = parse(t_path)
b, rel = parse(b_path)
if len(t) != len(b):
    sys.exit(2)


def mask(s):
    s = re.sub(r"^(jal|j) .*", r"\1 X", s)
    s = re.sub(r"^(lui \w+),.*", r"\1,X", s)
    s = re.sub(r"^(\S+ [^,]+(?:,[^,]+)?),-?(?:0x)?[0-9a-f]+(\(\w+\))$", r"\1,X\2", s)
    s = re.sub(r"^(addiu \w+,\w+),-?\d+$", r"\1,X", s)
    return s


def branch(s):
    return re.sub(r"^(b\w*) (.*?),?(0x)?[0-9a-f]+( <.*>)?$", lambda m: f"{m.group(1)} {m.group(2)},X" if m.group(2) else f"{m.group(1)} X", s)


T, B = [], []
for i, (x, y) in enumerate(zip(t, b)):
    x, y = branch(x), branch(y)
    x = re.sub(r"^(jal|j) .*", r"\1 X", x)
    y = re.sub(r"^(jal|j) .*", r"\1 X", y)
    if i in rel:
        x, y = mask(x), mask(y)
    T.append(x)
    B.append(y)
open(out_t, "w").write("\n".join(T) + "\n")
open(out_b, "w").write("\n".join(B) + "\n")
