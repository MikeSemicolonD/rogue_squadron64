"""Rewrites m2c stack locals whose address is passed to a callee into one struct, so GCC keeps the stores to the other slots."""
import re

SIZES = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "s32": 4, "u32": 4, "f32": 4, "s64": 8, "u64": 8, "f64": 8}
DECL = re.compile(r"^(\s*)([A-Za-z_][\w ]*?)\s*(\*+)?\s*sp([0-9A-F]+)(?:\[(\d+)\])?;[ \t]*\n?", re.M)

def _size(base, ptr, count):
    if ptr:
        size = 4
    elif base.strip() in SIZES:
        size = SIZES[base.strip()]
    else:
        return None
    return size * (int(count) if count else 1)

def struct_args(code, max_gap=None):
    """Returns rewritten code, or None when there is nothing to rewrite or a local's size is unknown.

    max_gap stops collecting members at the first gap larger than that many bytes (None = take every local above).
    Stack slots m2c references without declaring are treated as s32.
    """
    taken = sorted({int(m, 16) for m in re.findall(r"&sp([0-9A-F]+)\b", code)})
    if not taken:
        return None
    decls = {}
    for m in DECL.finditer(code):
        off = int(m.group(4), 16)
        size = _size(m.group(2), m.group(3), m.group(5))
        if size is None:
            return None
        decls[off] = {"text": m.group(0), "base": m.group(2).strip(), "ptr": m.group(3) or "", "count": m.group(5), "size": size}
    for ref in {int(r, 16) for r in re.findall(r"\bsp([0-9A-F]+)\b", code)}:
        if ref not in decls:
            decls[ref] = {"text": None, "base": "s32", "ptr": "", "count": None, "size": 4}
    start = taken[0]
    members = sorted(o for o in decls if o >= start)
    if max_gap is not None:
        kept, end = [], start
        for o in members:
            if o - end > max_gap and o not in taken:
                break
            kept.append(o)
            end = o + decls[o]["size"]
        members = kept
    if len(members) < 2:
        return None
    fields, pos = [], start
    for o in members:
        d = decls[o]
        if o < pos:
            return None
        if o > pos:
            fields.append(f"u8 pad{pos:X}[0x{o - pos:X}];")
        fields.append(f"{d['base']} {d['ptr']}f{o:X}{'[' + d['count'] + ']' if d['count'] else ''};")
        pos = o + d["size"]
    out = code
    for o in members:
        if decls[o]["text"]:
            out = out.replace(decls[o]["text"], "", 1)
    extra = "".join(f"    s32 sp{o:X};\n" for o in sorted(decls) if o not in members and decls[o]["text"] is None)
    fn = re.search(r"^[A-Za-z_][\w \*]*\b\w+\([^;{]*\)\s*\{\n", out, re.M)
    if fn is None:
        return None
    body_start = fn.end()
    out = out[:body_start] + f"    struct {{ {' '.join(fields)} }} sa;\n" + extra + out[body_start:]
    for o in members:
        out = re.sub(r"\bsp" + f"{o:X}" + r"\b", f"sa.f{o:X}", out)
    return out
