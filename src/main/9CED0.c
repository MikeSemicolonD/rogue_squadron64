#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/9CED0", computeVoicePanCoefficients);

void filterVoiceSampleBlock(s16, s16, u8 *, void *);
void applyVoiceDelayFilter(s32, s16, s16, void *);
void computeVoicePanCoefficients(s32, s32, s32, s32);
void updateVoiceChannelParams(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3, s16 *arg4, s16 *arg5, u8 *arg6, s32 arg7) {
    u8 buf[0x50];
    s32 i;

    for (i = 0; i < 4; i++) {
        filterVoiceSampleBlock(*arg5, *arg4, arg6, buf);
        applyVoiceDelayFilter(arg0, *arg2, *arg3, buf);
        arg3++;
        arg2++;
        arg5++;
        arg4++;
        arg6 += 0x1A;
    }
    computeVoicePanCoefficients(arg0, arg1, arg0, arg7);
}

INCLUDE_ASM("asm/nonmatchings/main/9CED0", updateVoiceChannelParamsLarge);

INCLUDE_ASM("asm/nonmatchings/main/9CED0", decodeAndFillVoiceBlock);

INCLUDE_ASM("asm/nonmatchings/main/9CED0", fake_func_8009D7CC);
