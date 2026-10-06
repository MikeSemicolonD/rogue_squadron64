#include "common.h"

#include "main/04080.h"
#include "zlib/zutil.h"

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_junk_zutil[] = {
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B14,
    0x80000B10,
    0xAC92001C,
    0x8E820000,
};

void *zcalloc(void *opaque, u32 arg1, u32 arg2) {
    return rs_zcalloc(arg1, arg2);
}

void zcfree(void *arg0, void *arg1) {
    rs_zcfree(arg1);
}

__asm__(".word 0xC4221D2C, 0x46001001, 0xE4400010");
