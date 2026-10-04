# Build check, 2026-10-04

Tree: `upstream/master` at `c0a6714` ("More matches, mostly concerning demo stuff"), cloned into WSL (Ubuntu 24.04). ROM SHA-1 `ed42eed1ee2db646ff7ef94ba8c5421d164a4f0d` (matches `roguesquadron.yaml`).

Toolchain: `tools/setup_wsl.sh` (no sudo): binutils/cpp 2.42 from the Ubuntu `mips-linux-gnu` cross packages, wibo 1.2.0, splat in a venv. SN compilers come from the Makefile's own download rules.

## Result

**The ROM could not be built, so whether the decomp matches is still unknown.** Every C and asm file compiles and assembles. The link fails under every configuration tried. The failures are configuration drift between `roguesquadron.yaml`, the committed `roguesquadron.ld`, and `src/`. They are not compiler problems.

## Failures, in the order hit

1. **Makefile: `build/assets/` is never created.** The `build/%.o: %.bin` rule has no directory dependency and `BUILD_DIRS` doesn't cover `assets/`. Fixed on this branch with `@mkdir -p $(@D)` in that rule.
2. **`asm/` isn't committed, so splat must run first, and the splat version is unpinned.**
   - splat 0.50.0 refuses the yaml: the overlay segments overlap the global vram range because `main_bss` (vram 0x8010D200) is global and sits above the overlays. Adding `exclusive_ram_id: main_bss` to the `main_bss` segment, as splat suggests, makes it split.
   - splat 0.36.4, 0.38.1 and 0.39.1 crash in `bss.py` (`get_next_subsegment_for_ram` on `None`). 0.40.1 rejects `main_bss`'s subsegments as out of vram order.
   - splat 0.41.1 splits as-is. Its generated linker script is identical to 0.50.0's (with the tag).
3. **The committed `roguesquadron.ld` is stale and hand-edited.** Splat regenerates it on every split. Compared with the regenerated one, the committed script:
   - links `build/src/main/02490.o`, but `src/main/02490.c` no longer exists (moved in `fb6cd1b`);
   - names 10 data objects splat no longer emits (`asm/data/main/38160.data.o`, `3BDC0.rodata.o`, `mission_overlay/0B4EC0.bss.o`, ...);
   - omits `build/src/main/01850.o(.text)` and `02420.o(.text)`;
   - contains 6 hand-added lines that `src/main/01720.c` needs: `<overlay>_BASEROM_START = <overlay>_ROM_START + 0xB0000000` and `<overlay>_ROM_SIZE = SIZEOF(.<overlay>)` for the mission, menu and cinematic overlays.

   **Fix on this branch:** those six lines now live in `extra_syms.ld`, which the Makefile passes to ld, so regenerating `roguesquadron.ld` no longer loses them.
4. **`main_bss` is emitted twice.** With the regenerated script, splat writes the whole `main_bss` segment as one blob, `asm/data/main_bss.bss.s`, and the main segment also links each C file's `.bss`. The result is 89 duplicate symbols (in `04080`, `033C0`, `02420`, `1EE30`, `3F160`, `562A0` and others). The yaml's `main_bss` subsegment list isn't honoured by either splat version. Neither workaround links:
   - splicing in the committed script's per-subsegment `.bss` list leaves `D_main_bss_8010FCB0`, `D_main_bss_801126E4` and others undefined;
   - dropping the per-file `.bss` leaves about 5000 undefined references.
5. **`mission_overlay/0BF800` data is defined twice.** The latest upstream commit moved `D_mission_overlay_80109AD0`, `demoStep` and `D_mission_overlay_80109AE4` into `src/mission_overlay/0BF800.c`. The yaml still lists `[0x0010A6D0, data, "mission_overlay/0BF800"]` as asm data. That gives 3 duplicate symbols. The likely fix is changing that entry to `.data`, but only if the C defines the whole range.

## What's needed from upstream

Ask the maintainer how they build:
- their splat version;
- whether they regenerate `roguesquadron.ld` or keep it by hand;
- how `main_bss` is meant to split;
- whether `make` currently links for them.

With that, items 4 and 5 are probably small yaml fixes. Items 1 and 3 are fixed on `build-check`.
