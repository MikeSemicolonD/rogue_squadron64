#include "common.h"
#include "common_types.h"

typedef struct {
    s16 v0, v1, v2, v3, v4, v5, v6, v7;
} VoicePanBlock;

typedef struct {
    u8 pad[0x168];
    VoicePanBlock blocks[2];
    s16 cur;
} VoicePanState;

s32 renderVoiceAudioBlock(s32, s32, s32);

void computeVoicePanCoefficients(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    VoicePanState *st = (VoicePanState *)arg0;
    const VoicePanBlock *in = (const VoicePanBlock *)arg1;
    VoicePanBlock *out;

    out = &st->blocks[st->cur];
    out->v0 = (((((in->v0 - 0x20) << 10) * 0x3333) + 0x4000) >> 15) * 2;
    out->v1 = (((((in->v1 - 0x20) << 10) * 0x3333) + 0x4000) >> 15) * 2;
    out->v2 = (((((in->v2 << 10) - 0x5000) * 0x3333) + 0x4000) >> 15) * 2;
    out->v3 = (((((in->v3 << 10) - 0x2C00) * 0x3333) + 0x4000) >> 15) * 2;
    out->v4 = (((((in->v4 << 10) - 0x20BC) * 0x4B17) + 0x4000) >> 15) * 2;
    out->v5 = (((((in->v5 << 10) - 0x1200) * 0x4444) + 0x4000) >> 15) * 2;
    out->v6 = ((((((in->v6 - 4) << 10) + 0x2AA) * 0x7ADE) + 0x4000) >> 15) * 2;
    out->v7 = (((((in->v7 << 10) - 0x710) * 0x740C) + 0x4000) >> 15) * 2;
    renderVoiceAudioBlock(arg0, arg2, arg3);
    st->cur ^= 1;
}

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
