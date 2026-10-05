#include "common.h"
#include "common_types.h"

#include "main/04030.h"
#include "main/3F160.h"
#include "main/700B0.h"

typedef struct DebrisSpawnArgs {
    u8 pad00[0x10];
    f32 f10, f14, f18;
    u8 pad1C[0x38 - 0x1C];
    f32 f38;
    s16 h3C, h3E;
    f32 f40;
    u8 pad44[0x4C - 0x44];
    f32 f4C;
    u8 pad50[0x54 - 0x50];
    f32 f54, f58;
    u8 pad5C[0x64 - 0x5C];
    void *p64;
    s32 i68;
    s8 b6C, b6D;
    s16 h6E, h70, h72;
    s32 pad74;
    s32 i74;
    u16 h78;
} DebrisSpawnArgs;
extern s32 D_main_bss_80130C04;
extern u8 D_main_bss_80139870[];
extern void initNpcContextFromTransform(void *, s32, s32);
extern s32 spawnRandomBurstNpcVariantWrapper(void *);
extern void assignNpcTargetAndPosition(s32, s32, void *, f32);

s32 spawnDestructionDebris(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    DebrisSpawnArgs s;
    f32 vec[3];
    s32 r;

    initNpcContextFromTransform(&s, arg1, 0);
    s.p64 = D_main_bss_80139870;
    s.b6C = 0xB;
    s.h6E = 0x1E00;
    s.b6D = 0x10;
    s.i68 = D_main_bss_80130C04 + 0x40;
    s.h78 |= 0x18;
    if (arg2 < 0.0f) {
        s.b6C = 0x14;
        arg2 = -arg2;
        s.h6E = 0;
        s.i68 = 0;
        s.b6D = 0;
        s.h78 &= 0xFFEF;
    }
    s.h70 = (u32)(arg4 * 0.125f * 256.0f);
    s.h72 = (u32)(arg4 / 6.0f * 256.0f);
    s.h3C = 0;
    s.h3E = 0;
    s.f40 = arg3;
    s.f4C = arg2;
    s.f58 = 1.0f;
    s.f38 = s.f14 = s.f10 = s.f18 = 0.0f;
    s.f54 = 0.8f;
    s.i74 |= 0x09000000;
    r = spawnRandomBurstNpcVariantWrapper(&s);
    if ((u16)arg0 != 0xFFFF) {
        vec[1] = vec[2] = vec[0] = 0.0f;
        assignNpcTargetAndPosition((u16)r, (u16)arg0, vec, 0.0f);
    }
    return (u16)r;
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", npcDebris1Update);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSph);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockBig);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSml);

INCLUDE_ASM("asm/nonmatchings/main/700B0", orientedNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", multiEventTemplateNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndAllocSubtypeBuffers);

INCLUDE_ASM("asm/nonmatchings/main/700B0", dispatchDatSubtypeByRandomIndex);

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndVisitChildren);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strProbeDroid);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVCrsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRTrPillar);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBThcapHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRBlkHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTspHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTrpHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRaptor);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRebTransport);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWrldDvstr);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVHlsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWaveskimmer);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBPwrtranHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMedHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMe5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strIRfcHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strITrd2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm5newHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm3Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTecHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strB20sbHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr8Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBLrsp);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strImpShuttle);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILndHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILtsrcHi);

INCLUDE_ASM("asm/nonmatchings/main/700B0", loadSfxAsset);

void buildRotationMatrixSlot0(f32 *, f32);
void composeRotationMatrixSlot0(f32 *, f32);
void composeRotationMatrixSlot1(f32 *, f32);

void composeRandomRotationMatrix(f32 *arg0, f32 *arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 m[12];
    f32 v;
    f32 t;

    if (arg3 != 0) {
        v = (f32)((s16)rand() % arg3);
    } else {
        v = 0.0f;
    }
    buildRotationMatrixSlot0(m, v);
    composeRotationMatrixSlot1(m, (f32)(s16)rand());
    if (arg4 != 0) {
        composeRotationMatrixSlot0(m, (f32)arg4);
    }
    if (arg5 != 0) {
        composeRotationMatrixSlot1(m, (f32)arg5);
    }
    t = -m[1];
    arg1[0] = t;
    arg1[1] = -m[4];
    arg1[2] = -m[7];
    arg0[0] = arg1[0] * arg2;
    arg0[1] = arg1[1] * arg2;
    arg0[2] = arg1[2] * arg2;
}

void composeRandomRotationMatrixVariant(f32 *arg0, f32 *arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 m[12];
    f32 v;
    f32 t;

    if (arg3 != 0) {
        v = (f32)(arg4 + (s16)rand() % arg3);
    } else {
        v = (f32)arg4;
    }
    buildRotationMatrixSlot0(m, v);
    composeRotationMatrixSlot1(m, (f32)(s16)rand());
    if (arg5 != 0) {
        composeRotationMatrixSlot0(m, (f32)arg5);
    }
    if (arg6 != 0) {
        composeRotationMatrixSlot1(m, (f32)arg6);
    }
    t = -m[1];
    arg1[0] = t;
    arg1[1] = -m[4];
    arg1[2] = -m[7];
    arg0[0] = arg1[0] * arg2;
    arg0[1] = arg1[1] * arg2;
    arg0[2] = arg1[2] * arg2;
}

void scaleVec3ByRandomRange(Vec3f arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;

    temp_fv0 = (((rand() % 4096) * (arg2 - arg1)) / 4095.0f) + arg1;
    arg0[0] *= temp_fv0;
    arg0[1] *= temp_fv0;
    arg0[2] *= temp_fv0;
}

extern u8 D_main_bss_80130B63;
s32 npcDebris1Update(struct D_80130BB8_type *self, u16 arg1, void *arg2);

typedef struct { s32 a; s32 b; f32 c; f32 d; f32 e; } Debris1Args;

void spawnDebris1Npc(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Debris1Args args;

    if ((D_main_bss_80130B63 != 0) || (findLargestFreeHeapChunk() >= 0x3A98U)) {
        args.a = arg0;
        args.b = arg1;
        args.e = arg3;
        args.d = arg2;
        args.c = arg4;
        spawnNpcOfType(npcDebris1Update, &args, 1U, 0xFU);
    }
}

s32 orientedNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2);
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3I;

typedef struct {
    f32 pos[3];
    f32 inv[3];
    f32 dir[3];
    f32 one[3];
} OrientedFrame;

typedef struct {
    OrientedFrame *frame;
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
} OrientedSpawnArgs;

void orthonormalizeFrame(OrientedFrame *);

void spawnOrientedEffectIfBudgetOk(f32 *pos, f32 *dir, s32 arg2, f32 arg3, f32 arg4)
{
  OrientedFrame fr;
  OrientedSpawnArgs args;
  OrientedFrame *fp;
  float new_var;
  *((V3I *) fr.pos) = *((V3I *) pos);
  if (dir != 0)
  {
    *((V3I *) fr.dir) = *((V3I *) dir);
  }
  else
  {
    fr.dir[0] = 0.0f;
    fr.dir[2] = 0.0f;
    fr.dir[1] = 1.0f;
  }
  fr.inv[0] = 1.0f - fr.dir[0];
  (&fr)->inv[1] = 1.0f - fr.dir[1];
  fr.inv[2] = 1.0f - fr.dir[2];
  fr.one[2] = 1.0f;
  fr.one[1] = 1.0f;
  fr.one[0] = 1.0f;
  orthonormalizeFrame(&fr);
  fp = &fr;
  new_var = 0.0001f;
  if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20)))
  {
    args.c = new_var;
    args.frame = fp;
    args.a = arg2;
    args.b = 0;
    args.d = arg3;
    args.e = arg4;
    spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
  }
}


void spawnOrientedEffectIfBudgetOkAlt(f32 *pos, f32 *dir, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    OrientedFrame fr;
    OrientedSpawnArgs args;
    OrientedFrame *fp;

    *(V3I *)fr.pos = *(V3I *)pos;
    if (dir != NULL) {
        *(V3I *)fr.dir = *(V3I *)dir;
    } else {
        fr.dir[0] = 0.0f;
        fr.dir[2] = 0.0f;
        fr.dir[1] = 1.0f;
    }
    fr.inv[0] = 1.0f - fr.dir[0];
    fr.inv[1] = 1.0f - fr.dir[1];
    fr.inv[2] = 1.0f - fr.dir[2];
    fr.one[2] = 1.0f;
    fr.one[1] = 1.0f;
    fr.one[0] = 1.0f;
    orthonormalizeFrame(&fr);
    fp = &fr;
    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.d = arg4;
        args.frame = fp;
        args.a = arg2;
        args.b = 0;
        args.c = arg3;
        args.e = arg5;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

void spawnOrientedNpc(s32 arg0, f32 *pos, f32 *dir, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    OrientedFrame fr;
    OrientedSpawnArgs args;
    OrientedFrame *fp;

    *(V3I *)fr.pos = *(V3I *)pos;
    if (dir != NULL) {
        *(V3I *)fr.dir = *(V3I *)dir;
    } else {
        fr.dir[0] = 0.0f;
        fr.dir[2] = 0.0f;
        fr.dir[1] = 1.0f;
    }
    fr.inv[0] = 1.0f - fr.dir[0];
    fr.inv[1] = 1.0f - fr.dir[1];
    fr.inv[2] = 1.0f - fr.dir[2];
    fr.one[1] = arg6;
    fr.one[0] = 1.0f;
    fr.one[2] = 1.0f;
    orthonormalizeFrame(&fr);
    fp = &fr;
    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.c = arg4;
        args.d = arg5;
        args.frame = fp;
        args.a = arg3;
        args.b = arg0;
        args.e = arg7;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

extern u8 D_main_bss_80130B63;
s32 orientedNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2);

typedef struct { s32 a; s32 b; s32 c; f32 d; f32 e; f32 f; } OrientedNpcArgs;

void gameStateByteGatedNpcHelper(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    OrientedNpcArgs args;

    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.e = arg4;
        args.a = arg1;
        args.b = arg2;
        args.c = arg0;
        args.d = arg3;
        args.f = arg5;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnMultiEventNpcWrapper);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnNpcChildForActivePlayerCell);

void sendSlotActionTwelve(u16 arg0) {
    if (arg0 != 0xFFFF) {
        slotDispatcherIter(arg0, 0xC, NULL);
    }
}

typedef struct DatTreeNode {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u8 unk6;
    u8 pad7;
    struct DatTreeNode *unk8;
    u8 padC[0x2C];
} DatTreeNode;
extern u8 D_main_bss_8013A898;
extern u8 *D_main_bss_8013A89C;
void rs_free(void *);
void walkDatTreeAndCollectSubtypes(DatTreeNode *n) {
    s32 i;

    if (n->unk0 == 0xFF) {
        return;
    }
    if (n->unk0 & 0x80) {
        for (i = 0; i < n->unk4; i++) {
            if (n->unk8[i].unk6 != 0) {
                D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk8[i].unk6;
            }
        }
        rs_free(n->unk8);
        n->unk0 = 0xFF;
    } else if (n->unk6 != 0) {
        D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk6;
    }
}

extern u16 D_main_800A0AA0[][4];
void walkDatTreeAndScaleLeafByFloat(DatTreeNode *n, s32 arg1, f32 scale) {
    s32 i;

    if (n->unk0 & 0x80) {
        for (i = 0; i < n->unk4; i++) {
            walkDatTreeAndScaleLeafByFloat(&n->unk8[i], arg1, scale);
        }
    } else {
        n->unk2 = n->unk2 + D_main_800A0AA0[n->unk0 & 0x1F][n->unk1] * scale;
        if (n->unk2 > 0x100) {
            n->unk2 = 0;
            n->unk1 = (n->unk1 + 1) & 3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", fake_func_80072CE8);

static u32 D_main_8003CEE4[] __attribute__((section(".rodata"))) = { 0x152A00C3, 0x00000000, 0x03688024 };
