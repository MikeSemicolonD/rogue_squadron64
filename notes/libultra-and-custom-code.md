# libultra and Factor 5's custom low-level code

Findings from 2026-10-04, made against the matching build (`make check` OK).

## libultra is stock SDK 2.0I, IDO-compiled (`libultra_rom`)

The ultralib submodule was built for each candidate version (`make VERSION=<v> TARGET=libultra_rom COMPARE=0`, in a separate copy of `ultralib/`). Each built object's `.text` was compared with the ROM, ignoring relocated fields (jump targets and `%hi`/`%lo` immediates, including `ldc1`/`sdc1`).

| Version | Whole objects matching the ROM |
|---|---|
| 2.0I | 109 of 116 compared, and the 7 "differences" are explained below |
| 2.0J, 2.0K, 2.0L | 41 |
| GCC `libgultra_rom` (any version) | about 2 functions |

- **The 7 non-matching 2.0I objects aren't real differences:**
  - Five are `mgu/*.o`, ultralib's alternative assembly versions of `guMtxF2L`, `guMtxIdent`, `guMtxIdentF`, `guMtxL2F` and `guScaleF`. The game uses the C versions in `gu/mtxutil.c` and `gu/scale.c`, which match.
  - `guPerspective` and `_Ldtob` differ only in `ldc1` relocation fields.
- **Files that looked missing are renames.** `sinf`/`cosf` are ultralib's `__sinf`/`__cosf`; `bcopy`/`bzero`/`bcmp` are `_bcopy`/`_bzero`/`_bcmp`; `__osEPiRawReadIo`/`__osEPiRawWriteIo` are `osEPiRawReadIo`/`osEPiRawWriteIo`. Every one has the same size and identical bytes.
- **Odd labels** (`func_main_8002BB34`, `noopHandler_80036B88`, `viMgrMain`, `_MakeMotorData`, ...) are splat labels or `static` helpers inside objects that already match as a whole.

**Conclusion:** all 190 libultra functions are unmodified 2.0I. The yaml's comment "libultra version < J" agrees. The next step is to link the IDO 2.0I objects instead of `asm/libultra`. That needs the IDO 5.3 recompiled toolchain (`ultralib/tools`), Makefile rules that build `build/asm/libultra/**.o` from ultralib sources, and the symbol renames above (or aliases) so `provisional.ld` and the game's references still resolve.

## Where Factor 5's custom code actually is

The "different math functions" and "different storage" are game code, not libultra changes.

- **Math library `src/main/1D000.c`:** built with GCC 2.7.2 SN0001 and `-ffast-math`.
  - Fast approximations: `sinfApprox`, `constMinusSinfApprox`, `atan2Approx`.
  - Quaternion and matrix routines: `quatFromAxisAngle`, `slerpQuaternions`, `quatToRotationMatrix`, `mat3x3InverseInto`, `floatMatrixToFixed` and others.
  - Vector helpers that use the FPU `sqrt.s` instruction directly instead of libultra's `sqrtf` (match with `__asm__("sqrt.s %0, %1" ...)`). About 41 game functions use inline `sqrt.s`.
  - The game still calls stock `sinf` (185 call sites) and `cosf` (64) from libultra. `sqrtf` has only 3 call sites.
- **Compression `src/zlib`:** a very old zlib inflate (the decomp notes point at zlib v0.8). It decompresses assets from the data blob, about 89% matched.
- **Encryption `decrypt_ns_hmt` (0x8006AFC0, `main/6B8B0`):** decrypts "ns" HMT texture files. Its register use (a0–a2 copied into t0–t2, only t-registers) looks hand-written assembly, so it likely stays asm.
- **Checksums:** Factor 5's CRC32 uses initial value `0xFAC5FAC5` (`rs_crc32`, used for cheat-code hashes). `adler32` is zlib's.
- **Other replacements:** MusyX replaces the libultra audio library entirely (`src/main/9xxxx` files, several built with GCC 2.7.2). Factor 5's own mutex/sync primitives sit around 0x80092010.
