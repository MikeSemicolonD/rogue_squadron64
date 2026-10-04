#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/3EB20", clearSceneBssRegion);

s32 queueDeferredClearRequest(s32, s32);

void clearDeferredClearRequest(void) {
    queueDeferredClearRequest(0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main/3EB20", fake_func_8003DF98);
