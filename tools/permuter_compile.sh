#!/bin/sh
# Compiles one C file the way the Makefile does, for decomp-permuter: permuter_compile.sh <cc1> [-I.. -D..] <in.c> -o <out.o>
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CC1="$1"
shift
CPPFLAGS=""
while [ $# -gt 0 ]; do
    case "$1" in
        -I*|-D*) CPPFLAGS="$CPPFLAGS $1"; shift ;;
        -o) OUT="$2"; shift 2 ;;
        *) IN="$1"; shift ;;
    esac
done
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
mips-linux-gnu-cpp -I "$ROOT/include" -I "$ROOT/ultralib/include" -DINCLUDE_ASM_USE_MACRO_INC -D_LANGUAGE_C $CPPFLAGS -E -lang-c "$IN" -o "$TMP/in.i"
"$ROOT/tools/wibo-x86_64" "$CC1" -quiet -O2 -G0 -mips3 -mhard-float "$TMP/in.i" -o "$TMP/in.s"
python3 "$ROOT/tools/modern-asn64.py" mips-linux-gnu-as -EB -mabi=32 -mfp32 -mgp32 -mtune=vr4300 -march=vr4300 -mips3 -G0 -I"$ROOT/include" "$TMP/in.s" -o "$OUT"
