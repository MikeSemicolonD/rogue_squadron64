#!/bin/sh
# Writes permuter_settings.toml for this checkout (decomp-permuter needs absolute paths; GCC 2.8.1 SN by default, pass 272 for GCC 2.7.2 files).
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CC1="$ROOT/tools/compilers/gcc281sn/cc1n64.exe"
[ "$1" = "272" ] && CC1="$ROOT/tools/compilers/gcc272sn0001/cc1n64.exe"
cat > "$ROOT/permuter_settings.toml" <<TOML
compiler_type = "gcc"
compiler_command = "$ROOT/tools/permuter_compile.sh $CC1 -I$ROOT/include -I$ROOT/ultralib/include -DINCLUDE_ASM_USE_MACRO_INC -D_LANGUAGE_C"
assembler_command = "mips-linux-gnu-as -EB -mabi=32 -mfp32 -mgp32 -march=vr4300 -mips3 -G0 -I $ROOT/include"
asm_prelude_file = "tools/permuter_prelude.inc"
TOML
echo "wrote $ROOT/permuter_settings.toml"
