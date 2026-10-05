#!/bin/sh
# Prints m2c's C for one INCLUDE_ASM function, using its .c file (preprocessed with -DM2CTX) as context: tools/m2c_func.sh <function> [m2c flags]
set -e
FUNC="$1"
shift
cd "$(dirname "$0")/.."
S=$(find asm/nonmatchings -name "$FUNC.s" | head -1)
[ -n "$S" ] || { echo "no asm/nonmatchings file for $FUNC (run splat first?)" >&2; exit 1; }
C=$(grep -rl "INCLUDE_ASM(\"[^\"]*\", $FUNC)" src | head -1)
CTX=$(mktemp)
trap 'rm -f "$CTX"' EXIT
if [ -n "$C" ]; then
    mips-linux-gnu-cpp -P -undef -D__GNUC__ -D_LANGUAGE_C -DM2CTX -D_MIPS_SZLONG=32 -D_MIPS_SZINT=32 -I include -I ultralib/include "$C" > "$CTX"
fi
# pycparser cannot read inline asm; m2c only needs the declarations.
sed -i -E "s/(__asm__|asm)[[:space:]]*(volatile[[:space:]]*)?\([^;]*;/;/g" "$CTX"
python3 -m m2c.main -t mips-gcc-c --context "$CTX" --globals=used "$@" "$S"
