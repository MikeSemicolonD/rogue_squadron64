#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcInitSimpleModel);

typedef struct { f32 m[12]; } TickMtx;
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void resolveNpcAttachmentPos(s32, TickMtx *, f32, f32);
extern u8 tickProgressChannel(s32, TickMtx *, s32, f32 *);
extern u16 triggerCueWithSlotEffect(s32, s32, TickMtx *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void slotDispatcherIter(s32, s32, s16 *);
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010A890[];
extern u8 D_mission_overlay_8010A89C[];

s32 npcTickEffectChannelShared(s32 arg0, s32 arg1, s32 arg2) {
    TickMtx mtx;
    struct { s16 h58; u8 pad5A[0x16]; f32 f70; s8 b74; } p;
    f32 prog;
    f32 fv;
    u8 r;
    u8 *npc = *(u8 **)(arg0 + 4);

    if (arg2 == 0) {
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "a", 0, &mtx, 0, 0);
        r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 0, &prog);
        if (r == 1) {
            fv = ((f32 *)(*(u8 **)(npc + 0x34) + 0xC0))[D_main_bss_80137CE4];
            fv = (fv + 10.0f) * 0.25f;
            p.b74 = 0;
            p.f70 = fv;
            if (fv > 50.0f) {
                p.f70 = 50.0f;
            }
            p.h58 = 2;
            *(s32 *)(npc + 0xF8) = 0;
            slotDispatcherIter(triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, D_mission_overlay_8010A890, r, 10.0f, prog), 0xA, (s16 *)&p);
            play3DSoundEvent(0, npc, npc + 0x24, 10.0f, 0.3f, 0, 0xD, 0x7D, 0x28);
        }
    } else {
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "b", 0, &mtx, 0, 0);
        fv = ((f32 *)(*(u8 **)(npc + 0x34) + 0xD4))[D_main_bss_80137CE4];
        if (fv != 0.0f) {
            resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, 10.0f, fv);
        }
        r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 1, &prog);
        if (r == 1) {
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, D_mission_overlay_8010A89C, r, 10.0f, prog);
            play3DSoundEvent(0, npc, npc + 0x24, 10.0f, 0.1f, 0, 0x1D, 0x78, 0x28);
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTankDroidComputeAimMotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTankDroidUpdate);

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode0(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 0);
}

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode1(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 1);
}
