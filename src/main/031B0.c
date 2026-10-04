#include "common.h"
#include "common_types.h"

extern u8 osAppNMIBuffer[];

inline s32 getResetVectorRegion(u8 **start, u32 *size) {
    *start = osAppNMIBuffer;
    *size = 0x80000400 - (u32)osAppNMIBuffer;
    return 1;
}

s32 sprintf(char *, const char *, ...);

void fatalErrorHalt(char *file, char *msg, s32 line) {
    char buf[0x200];
    u8 *start;
    u32 size;
    u32 len;

    len = sprintf(buf, "%s\n%d\n%s\n", file, line, msg) + 1;
    getResetVectorRegion(&start, &size);
    rs_memset(start, 0, len < size ? len : size);
    rs_strncpy(start, buf, len);
    while (1) {
    }
}

__asm__(".section .rodata\n    .byte 0x32, 0x8C, 0x80, 0x00, 0x32, 0xB4\n.section .text");

extern s32 D_80000318;
extern u8 *D_main_bss_8010FCB0;

s32 getUsableRdramSize(void) {
    if (*(u32 *)(D_main_bss_8010FCB0 + 0x44) & 0x2000) {
        return 0x400000;
    }
    return D_80000318;
}

INCLUDE_ASM("asm/nonmatchings/main/031B0", fake_func_8000268C);
