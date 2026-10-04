#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/06560", initMemoryPack);

INCLUDE_ASM("asm/nonmatchings/main/06560", writeSaveBodyToEeprom);

INCLUDE_ASM("asm/nonmatchings/main/06560", writeSaveDataBodyToEeprom);

INCLUDE_ASM("asm/nonmatchings/main/06560", copySaveUnk08);

INCLUDE_ASM("asm/nonmatchings/main/06560", initSaveData);

s32 rs_free(s32);
extern s32 gSaveDataBuffer;

s32 freeSaveDataBuffer(void) {
    rs_free(gSaveDataBuffer);
    return 1;
}

extern s32 D_main_bss_801126F0;

void setSaveDataCallback(s32 arg0) {
    D_main_bss_801126F0 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/06560", saveLoadDispatcher);

INCLUDE_ASM("asm/nonmatchings/main/06560", loadOrSaveEepromRecord);

extern struct {
    u8 pad[0xE];
    u16 count;
} gGamesaveAsset;
extern s32 gSaveDataBodySize;
extern s32 D_main_bss_801126E0;
extern s32 D_main_bss_80112720;
void waitForSerialIdle(void);
void releaseSerialLock(void);
s32 osEepromLongRead(s32, s32, u8 *, s32);
void copySaveUnk08(s32, u8 *);
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);

void loadOrSaveAllEepromRecords(s32 arg0, s32 arg1, u8 *arg2) {
    s32 i;
    s32 addr;
    u8 *buf;

    if (arg0 == 0) {
        arg0 = D_main_bss_80112720;
    }
    waitForSerialIdle();
    switch (arg0) {
    case 1:
        i = 0;
        if (gGamesaveAsset.count != 0) {
            do {
                addr = ((u32)(i * gSaveDataBodySize + 0x20) >> 3) & 0xFF;
                osEepromLongRead(D_main_bss_801126E0, addr, (u8 *)gSaveDataBuffer, 0x18);
                buf = (u8 *)gSaveDataBuffer;
                if (*(u32 *)(buf + 4) != adler32(adler32(0, 0, 0), buf + 8, 0x10)) {
                    rs_memset(arg2, 0, 0x10);
                    arg2 += 0x10;
                } else {
                    memcpy(arg2, buf + 8, 0x10);
                    arg2 += 0x10;
                }
                i++;
            } while (i < gGamesaveAsset.count);
        }
        break;
    case 2:
        copySaveUnk08(arg1, arg2);
        break;
    }
    releaseSerialLock();
}

INCLUDE_ASM("asm/nonmatchings/main/06560", fake_func_80006BFC);
