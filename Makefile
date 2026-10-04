PYTHON := python3

# provisional.ld is the maintained linker script; splat regenerates roguesquadron.ld on every split.
LDSCRIPT := provisional.ld

TOOLSDIR := ./tools

CROSS   := mips-linux-gnu-
AS      := $(CROSS)as
LD      := $(CROSS)ld
CPP     := $(CROSS)cpp
OBJCOPY := $(CROSS)objcopy

WIBO := ./tools/wibo-x86_64
MODERNASN := $(PYTHON) $(TOOLSDIR)/modern-asn64.py $(AS)

INCLUDE_DIRS := -I ./include/ -I ./ultralib/include/
DEFINES      := -DINCLUDE_ASM_USE_MACRO_INC -D_LANGUAGE_C
CPPFLAGS     := -E -lang-c
CFLAGS       := -quiet -O2 -G0 -mips3 -mhard-float
ASFLAGS      := -EB -mabi=32 -mfp32 -mgp32 -mtune=vr4300 -march=vr4300 -mips3 -G0 -I./include

COMPILERSPATH := $(TOOLSDIR)/compilers
GCC281SN      := $(COMPILERSPATH)/gcc281sn/cc1n64.exe
GCC272SN0001  := $(COMPILERSPATH)/gcc272sn0001/cc1n64.exe

N64CC := $(GCC281SN)

C_DIRS    := $(shell find src -type d)
C_FILES   := $(foreach dir,$(C_DIRS),$(wildcard $(dir)/*.c))
ASM_DIRS  := $(shell find asm -type d -not -path "asm/nonmatchings*")
ASM_FILES := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
BIN_FILES := $(shell find assets -type f -name "*.bin" -not -path "assets/main*")
O_FILES   := $(ASM_FILES:%.s=build/%.o) $(BIN_FILES:%.bin=build/%.o) $(C_FILES:%.c=build/%.o)

BUILD_DIRS := $(C_DIRS:%=build/%) $(ASM_DIRS:%=build/%)

SYMBOL_FILES := undefined_funcs_auto.txt undefined_syms_auto.txt symbol_files/cinematic_overlay.txt symbol_files/libultra.txt symbol_files/main_overlay.txt symbol_files/menu_overlay.txt symbol_files/mission_overlay.txt symbol_files/zlib.txt

.PHONY: clean check

# libultra comes from the ultralib submodule (SDK 2.0I, IDO libultra_rom), which matches the ROM byte for byte.
# It is built in a copy under build/ so the submodule stays clean; set USE_ULTRALIB=0 to assemble asm/libultra instead.
USE_ULTRALIB ?= 1
ULTRALIB_VERSION := I
ULTRALIB_WORK := build/ultralib
ULTRALIB_OBJ_DIR := $(ULTRALIB_WORK)/build/$(ULTRALIB_VERSION)/libultra_rom/src
ULTRALIB_STAMP := $(ULTRALIB_WORK)/.built

ifneq ($(USE_ULTRALIB),0)
O_FILES += $(filter-out $(O_FILES),$(sort $(shell grep -o "build/asm/libultra/[A-Za-z0-9_/]*\.o" $(LDSCRIPT))))

$(ULTRALIB_STAMP):
	rm -rf $(ULTRALIB_WORK)
	mkdir -p build
	cp -rL ultralib $(ULTRALIB_WORK)
	$(MAKE) -C $(ULTRALIB_WORK) VERSION=$(ULTRALIB_VERSION) TARGET=libultra_rom MODERN_LD=1 COMPARE=0 setup
	$(MAKE) -C $(ULTRALIB_WORK) VERSION=$(ULTRALIB_VERSION) TARGET=libultra_rom MODERN_LD=1 COMPARE=0 CROSS=$(CROSS)
	touch $@

build/asm/libultra/%.o: $(ULTRALIB_STAMP)
	@mkdir -p $(@D)
	cp $(ULTRALIB_OBJ_DIR)/$*.o $@
endif

build/tyler.z64: build/tyler.elf
	$(OBJCOPY) $< $@ -O binary

build/tyler.elf: $(O_FILES) $(LDSCRIPT) libultra_aliases.ld
	$(LD) -Map=$@.map -EB -T $(LDSCRIPT) -T undefined_funcs_auto.txt -T undefined_syms_auto.txt -T libultra_aliases.ld -G0 -o $@

$(BUILD_DIRS):
	mkdir -p $@

$(GCC281SN):
	mkdir -p "$(@D)"
	wget "https://github.com/marijnvdwerf/sn64/releases/download/1%2C0%2C0%2C2/cc1n64.exe" -P "$(@D)"
	chmod +x "$@"

$(GCC272SN0001):
	mkdir -p "$(@D)"
	wget "https://github.com/decompme/compilers/releases/download/compilers/n64_sn272_0001.tar.gz" -P "$(@D)"
	tar xzf "$(@D)/n64_sn272_0001.tar.gz" -C "$(@D)"
	chmod +x "$@"

build/src/main/01850.s: N64CC = $(GCC272SN0001)
build/src/main/02420.s: N64CC = $(GCC272SN0001)
build/src/main/031B0.s: N64CC = $(GCC272SN0001)
build/src/main/03290.s: N64CC = $(GCC272SN0001)
build/src/main/04030.s: N64CC = $(GCC272SN0001)
build/src/main/1D000.s: N64CC = $(GCC272SN0001)
build/src/main/1D000.s: CFLAGS += -ffast-math
build/src/mission_overlay/0AEFF0.s: CFLAGS += -fno-strength-reduce
build/src/main/1EE30.s: N64CC = $(GCC272SN0001)
build/src/main/24570.s: N64CC = $(GCC272SN0001)
build/src/main/94F50.s: N64CC = $(GCC272SN0001)
build/src/main/97D20.s: N64CC = $(GCC272SN0001)
build/src/main/9BB60.s: N64CC = $(GCC272SN0001)
build/src/main/98960.s: N64CC = $(GCC272SN0001)
build/src/main/9A850.s: N64CC = $(GCC272SN0001)
build/src/main/07F80.s: N64CC = $(GCC272SN0001)
build/src/main/9CED0.s: N64CC = $(GCC272SN0001)
build/src/zlib/%.s: N64CC = $(GCC272SN0001)
build/src/main/08510.s: N64CC = $(GCC272SN0001)
build/src/zlib/%.s: CFLAGS = -quiet -O3 -G0 -mips3

build/src/%.i: src/%.c | $(BUILD_DIRS)
	$(CPP) $(INCLUDE_DIRS) $(DEFINES) $(CPPFLAGS) $< -o $@

build/src/%.s: build/src/%.i | $(BUILD_DIRS) $(GCC281SN) $(GCC272SN0001)
	$(WIBO) $(N64CC) $(CFLAGS) $< -o $@

build/src/%.o: build/src/%.s | $(BUILD_DIRS)
	$(MODERNASN) $(ASFLAGS) $< -o $@

build/%.o: %.s | $(BUILD_DIRS)
	$(AS) $(ASFLAGS) -o $@ $<

build/%.o: %.bin
	@mkdir -p $(@D)
	$(LD) -r -b binary -o $@ $<

check: build/tyler.z64
	sha1sum -c roguesquadron.sha1 || $(PYTHON) $(TOOLSDIR)/first_diff.py build/tyler.z64 rogue_squadron.z64 --map build/tyler.elf.map

clean:
	rm -rf $(BUILD_DIRS)
