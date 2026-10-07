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

static __inline__ void uvDecoder(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3, s16 *arg4, s16 *arg5, u8 *arg6, s32 arg7) {
    u8 buf[0x50];
    s32 i;

    for (i = 0; i <= 3; i++, arg5++, arg3++, arg2++, arg4++, arg6 += 0x1A) {
        filterVoiceSampleBlock(*arg5, *arg4, arg6, buf);
        applyVoiceDelayFilter(arg0, *arg2, *arg3, buf);
    }
    computeVoicePanCoefficients(arg0, arg1, arg0, arg7);
}

s32 updateVoiceChannelParamsLarge(s32 S, u8 *c, s32 s) {
    s16 LARc[8], Nc[4], Mc[4], bc[4], xmaxc[4], xmc[13 * 4];
    u8 *p;
    s32 j;

    LARc[0] = (c[1] >> 6) | ((c[0] & 0xF) << 2);
    LARc[1] = c[1] & 0x3F;
    LARc[2] = c[2] >> 3;
    LARc[3] = (c[3] >> 6) | ((c[2] & 7) << 2);
    LARc[4] = (c[3] >> 2) & 0xF;
    LARc[5] = (c[4] >> 6) | ((c[3] & 3) << 2);
    LARc[6] = (c[4] >> 3) & 7;
    LARc[7] = c[4] & 7;
    for (j = 0; j < 4; j++) {
        Nc[j] = (p = c + j * 7)[5] >> 1;
        bc[j] = ((p[5] & 1) << 1) | (p[6] >> 7);
        Mc[j] = (p[6] >> 5) & 3;
        xmaxc[j] = (p[7] >> 7) | ((p[6] & 0x1F) << 1);
        xmc[j * 13 + 0] = (p[7] >> 4) & 7;
        xmc[j * 13 + 1] = (p[7] >> 1) & 7;
        xmc[j * 13 + 2] = ((p[7] & 1) << 2) | (p[8] >> 6);
        xmc[j * 13 + 3] = (p[8] >> 3) & 7;
        xmc[j * 13 + 4] = p[8] & 7;
        xmc[j * 13 + 5] = p[9] >> 5;
        xmc[j * 13 + 6] = (p[9] >> 2) & 7;
        xmc[j * 13 + 7] = (p[10] >> 7) | ((p[9] & 3) << 1);
        xmc[j * 13 + 8] = (p[10] >> 4) & 7;
        xmc[j * 13 + 9] = (p[10] >> 1) & 7;
        xmc[j * 13 + 10] = ((p[10] & 1) << 2) | (p[11] >> 6);
        xmc[j * 13 + 11] = (p[11] >> 3) & 7;
        xmc[j * 13 + 12] = p[11] & 7;
    }
    uvDecoder(S, (s32)LARc, Nc, bc, Mc, xmaxc, (u8 *)xmc, s);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/9CED0", decodeAndFillVoiceBlock);

INCLUDE_ASM("asm/nonmatchings/main/9CED0", fake_func_8009D7CC);
