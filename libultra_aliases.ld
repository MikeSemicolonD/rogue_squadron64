/* Names the game's symbol files use for libultra 2.0I functions that ultralib names differently. */
__osEPiRawReadIo = osEPiRawReadIo;
__osEPiRawWriteIo = osEPiRawWriteIo;
/* GCC emits __udivdi3 for 64-bit unsigned division; the game names it u64DivU64. */
__udivdi3 = u64DivU64;
