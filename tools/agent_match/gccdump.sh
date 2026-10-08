#!/bin/bash
# gccdump.sh FUNC DRAFT "FLAGS" [OUTDIR] : run from a worktree root. Compiles DRAFT with the file's own cc1 and flags plus GCC dump FLAGS
# (e.g. "-dl -dg" for allocation priorities, "-dS" for the sched1 ready-list trace, "-dc -dL -dR"), and writes FUNC's section of each
# dump to OUTDIR/FUNC.<pass> (default OUTDIR: ./agent_dumps). -dl prints "Register N used X times across Y insns"; -dg lists "regs to allocate"
# in priority order with each pseudo's conflicts and the final dispositions.
F=$1; D=$2; FL=$3; OUT=${4:-agent_dumps}
. ~/opt/rs64env.sh
src=$(grep -rl "INCLUDE_ASM(\"[^\"]*\", $F);" src | head -1)
[ -n "$src" ] || { echo "$F is not an INCLUDE_ASM in src/"; exit 1; }
b=build/${src%.c}
K=$(mktemp)
cp $src $K
python3 tools/replace_asm.py $F "$D" >/dev/null && touch $src && make -s $b.i
cmd=$(make -n -W $b.i $b.s 2>/dev/null | grep -m1 cc1n64)
mkdir -p $OUT
T=$(mktemp -d)
cp $b.i $T/x.i
cp $K $src; touch $src; rm -f $K
W=$(pwd)
read -r -a parts <<< "$cmd"
args=()
for p in "${parts[@]}"; do
  case $p in
    *.i) args+=("x.i") ;;
    *.s) args+=("x.s") ;;
    ./tools/*) args+=("$W/${p#./}") ;;
    *) args+=("$p") ;;
  esac
done
(cd $T && "${args[@]}" $FL 2>/dev/null)
for f in $T/x.i.*; do
  [ -e "$f" ] || continue
  awk -v F="$F" 'index($0, ";; Function " F) == 1 {p=1; next} /^;; Function /{if(p) exit} p' $f > $OUT/$F.${f##*/x.i.}
done
awk -v F="$F" 'index($0, F ":") == 1 {p=1} p' $T/x.s | sed '/^\s*\.end\s/q' > $OUT/$F.s
rm -rf $T
ls $OUT/$F.*
