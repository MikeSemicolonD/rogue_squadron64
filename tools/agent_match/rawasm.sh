#!/bin/bash
# rawasm.sh FUNC DRAFT [N] : run from a worktree root. Compiles DRAFT in place of FUNC and prints its first N (default 400) instructions
# with real registers and branch targets. The target is asm/nonmatchings/**/FUNC.s.
F=$1; D=$2; N=${3:-400}
. ~/opt/rs64env.sh
src=$(grep -rl "INCLUDE_ASM(\"[^\"]*\", $F);" src | head -1)
[ -n "$src" ] || { echo "$F is not an INCLUDE_ASM in src/"; exit 1; }
K=$(mktemp)
cp $src $K
python3 tools/replace_asm.py $F $D >/dev/null 2>&1 && touch $src && make -s build/${src%.c}.o 2>&1 | grep -m3 -E ':[0-9]+: [^w]'
mips-linux-gnu-objdump -d --no-show-raw-insn build/${src%.c}.o | awk -v f="<$F>:" '$2==f{p=1;next} p&&/^$/{exit} p' | head -$N
cp $K $src; touch $src
rm -f $K
