#!/bin/bash
# score.sh FUNC DRAFT... : run from a worktree root. Compiles each DRAFT (a C snippet defining FUNC) in place of FUNC's INCLUDE_ASM,
# prints "<draft> <diff lines> <ours>/<target> insns struct=<diff lines ignoring register names>", and writes <draft>.diff (unified diff).
# 0 diff lines means the function matches. The source file is restored afterwards.
H=$(cd "$(dirname "$0")" && pwd)
FUNC=$1; shift
. ~/opt/rs64env.sh
src=$(grep -rl "INCLUDE_ASM(\"[^\"]*\", $FUNC);" src | head -1)
[ -n "$src" ] || { echo "$FUNC is not an INCLUDE_ASM in src/ (already matched?)"; exit 1; }
o=build/${src%.c}.o
s=$(find asm/nonmatchings -name "$FUNC.s" | head -1)
rom=$(( 0x$(awk -v f="$FUNC" '$0 ~ ("glabel " f "$"){g=1;next} g && /\/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*\//{print $2; exit}' $s) ))
size=$(grep -oE "nonmatching $FUNC, 0x[0-9A-Fa-f]+" $s | grep -oE "0x[0-9A-Fa-f]+$")
T=$(mktemp -d)
mips-linux-gnu-objdump -D -b binary -m mips:4300 -EB --start-address=$rom --stop-address=$((rom+size)) rogue_squadron.z64 | grep -E "^ +[0-9a-f]+:" > $T/t.raw
python3 $H/norm.py rom $T/t.raw > $T/t.txt
cp $src $T/src.c
for d in "$@"; do
  cp $T/src.c $src
  python3 tools/replace_asm.py "$FUNC" "$d" >/dev/null 2>&1 || { echo "$(basename $d) replace-failed"; continue; }
  touch $src
  if ! make -s $o >$T/log 2>&1; then echo "$(basename $d) compile-failed $(grep -m1 -E ':[0-9]+: [^w]' $T/log)"; continue; fi
  mips-linux-gnu-objdump -dr --no-show-raw-insn $o | awk -v f="<$FUNC>:" '$2==f{p=1;next} p&&/^$/{exit} p' > $T/b.raw
  python3 $H/norm.py obj $T/b.raw > $T/b.txt
  n=$(diff $T/t.txt $T/b.txt | grep -c '^[<>]')
  R='s/(\$f[0-9]+|\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|fp|ra)\b)/R/g'
  sn=$(diff <(sed -E "$R" $T/t.txt) <(sed -E "$R" $T/b.txt) | grep -c '^[<>]')
  echo "$(basename $d) $n $(wc -l < $T/b.txt)/$(wc -l < $T/t.txt) struct=$sn"
  diff -U3 --label target --label ours $T/t.txt $T/b.txt > ${d%.c}.diff
done
cp $T/src.c $src; touch $src
rm -rf $T
