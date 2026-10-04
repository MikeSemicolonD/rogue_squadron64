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

INCLUDE_ASM("asm/nonmatchings/main/06560", loadOrSaveAllEepromRecords);

INCLUDE_ASM("asm/nonmatchings/main/06560", fake_func_80006BFC);
