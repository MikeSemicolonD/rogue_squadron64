"""rodata_trim.py SRC BLOCK N : replace `INCLUDE_RODATA(..., BLOCK);` in SRC with a one-line inline rodata block that drops the
first N words of asm/nonmatchings/**/BLOCK.s. Use it when a newly matched function emits its own literals that splat had put at the
start of the following rodata block (the ROM check then fails with everything after it shifted).
"""
import re
import sys
from pathlib import Path

src, block, n = sys.argv[1], sys.argv[2], int(sys.argv[3])
asm = next(Path("asm/nonmatchings").rglob(f"{block}.s"))
words = []
for line in asm.read_text().splitlines():
    m = re.match(r"^\s*/\*\s+[0-9A-F]+\s+[0-9A-F]+\s+([0-9A-F]+)\s+\*/", line)
    if m:
        h = m.group(1)
        words += [h[i:i + 8] for i in range(0, len(h), 8)]
keep = words[n:]
text = Path(src).read_text()
pat = re.compile(r'^INCLUDE_RODATA\("[^"]*", ' + re.escape(block) + r'\);$', re.M)
if not pat.search(text):
    sys.exit(f"no INCLUDE_RODATA for {block} in {src}")
body = "".join(f"\\n.word 0x{w}" for w in keep)
new = f'__asm__(".section .rodata{body}\\n.section .text");' if keep else ""
Path(src).write_text(pat.sub(lambda m: new, text))
print(new or "(block removed)")
