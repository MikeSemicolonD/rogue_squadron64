# Build check, 2026-10-04

Tree: `upstream/master` at `c0a6714` ("More matches, mostly concerning demo stuff"), cloned into WSL (Ubuntu 24.04). ROM SHA-1 `ed42eed1ee2db646ff7ef94ba8c5421d164a4f0d` (matches `roguesquadron.yaml`).

## Result

**The decomp builds a byte-identical ROM.** `build/tyler.z64` has SHA-1 `ed42eed1ee2db646ff7ef94ba8c5421d164a4f0d`, and `tools/first_diff.py` reports `MATCH`.

## Workflow

```sh
sh tools/setup_wsl.sh            # once: binutils 2.42, cpp 12.4.0, wibo 1.2.0, splat 0.41.1 into ~/opt (no sudo)
. ~/opt/rs64env.sh
cp /path/to/rogue_squadron.z64 . # the USA 1.0 ROM, not committed
splat split roguesquadron.yaml   # generates asm/ and assets/ (not committed)
make -j$(nproc) check            # build/tyler.z64: OK
```

- **The linker script is `provisional.ld`, not `roguesquadron.ld`.** The maintainer updates `provisional.ld` in every commit. It carries the overlay load symbols (`*_BASEROM_START`, `*_ROM_SIZE`) and the per-file `main_bss` layout. Splat rewrites `roguesquadron.ld` on every split, and that copy doesn't link: it lists files that no longer exist, emits `main_bss` as one blob, and lacks the overlay symbols. The Makefile now uses `LDSCRIPT := provisional.ld`.
- **Splat 0.41.1.** It is the newest release that splits the yaml unchanged. 0.50.0 stops on the overlay/global vram overlap check, and versions up to 0.40.1 fail on the `main_bss` segment.
- **Makefile fix:** the `.bin` rule now creates `build/assets/` itself.
- After a split, `git status` shows `roguesquadron.ld` modified. That's expected; don't commit it.

## Dead ends (for reference)

Building with the regenerated `roguesquadron.ld` fails. Each fix brought it closer, but `provisional.ld` makes all of them unnecessary:
- `extra_syms.ld` for the overlay symbols;
- `auto_link_sections: [".data", ".rodata"]` plus `main_bss` as a `code` group with `start: 0x1000000` and `exclusive_ram_id`;
- `.data` ownership changes for `main/6B8B0` and `mission_overlay/0BF800`.

## Progress (`python3 tools/progress.py`)

These are `.text` bytes in C (yaml text subsegments minus `INCLUDE_ASM` functions). Because the ROM matches, all of it is matching C.

| Group | In C | Total | % | Functions still asm |
|---|---|---|---|---|
| main | 28364 | 535888 | 5.3 | 1069 |
| mission_overlay | 38704 | 391872 | 9.9 | 488 |
| menu_overlay | 3028 | 143728 | 2.1 | 199 |
| cinematic_overlay | 688 | 39216 | 1.8 | 50 |
| libultra | 0 | 55360 | 0.0 | 190 |
| zlib | 11740 | 13168 | 89.2 | 8 |
| entry_point | 0 | 64 | 0.0 | 2 |
| **total** | **82524** | **1179296** | **7.0** | **2006** (121 of them splat `fake_func_*` fragments) |
