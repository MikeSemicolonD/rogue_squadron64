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

extern s32 gSaveDataBodySize;
extern s32 D_main_bss_801126E0;
extern s32 D_main_bss_80112720;
void waitForSerialIdle(void);
void releaseSerialLock(void);
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);
extern u32 D_main_bss_801126C8;
typedef struct {
    u32 unk0;
    u32 unk4;
} SaveHdr;
s32 osEepromLongWrite(s32, s32, u8 *, s32);
s32 writeSaveBodyToEeprom(u32, s32, u8 *, u8 *, s32);
s32 saveLoadDispatcher(s32 arg0, u32 arg1, s32 arg2, u8 *arg3, u8 *arg4, s32 arg5) {
    s32 ret;
    u8 *buf;
    u8 *b8;
    u8 *b18;

    if (arg0 == 0) {
        arg0 = D_main_bss_80112720;
    }
    waitForSerialIdle();
    switch (arg0) {
    case 1:
        buf = (u8 *)gSaveDataBuffer;
        rs_memset(buf, 0, gSaveDataBodySize);
        b18 = buf + 0x18;
        memcpy(b18, arg4, arg5);
        b8 = buf + 8;
        memcpy(b8, arg3, 0x10);
        ((SaveHdr *)buf)->unk4 = adler32(adler32(0, 0, 0), b8, 0x10);
        ret = 0;
        ((SaveHdr *)buf)->unk0 = adler32(adler32(0, 0, 0), b18, D_main_bss_801126C8);
        osEepromLongWrite(D_main_bss_801126E0, ((u32)(arg2 * gSaveDataBodySize + 0x20) >> 3) & 0xFF, (u8 *)gSaveDataBuffer, gSaveDataBodySize);
        break;
    case 2:
        if (arg1 >= 4) {
            return 0xA;
        }
        ret = writeSaveBodyToEeprom(arg1, arg2, arg3, arg4, arg5);
        break;
    }
    releaseSerialLock();
    return ret;
}

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
