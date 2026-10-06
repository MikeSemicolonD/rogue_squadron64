#include "common.h"
#include "common_types.h"

#include "player.h"

#include "main/6C310.h"

// Interim BSS externs
extern u16 D_main_bss_8013A528[14];

#include "textures.h"
#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/64EA0.h"
extern char D_main_8003C960[];
void rs_free(void *);

__asm__(".section .rodata\n.align 2\n.globl D_main_8003C960\nD_main_8003C960:\n.word 0x706C5F63\n.word 0x72616674\n.word 0x732F7368\n.word 0x61646F77\n.word 0x735F544D\n.word 0x00000000\n.section .text");

void loadCraftShadowTextures(s32 arg0) {
    struct material_entry sp10;
    struct full_image_header *temp_s4;
    struct full_image_header *var_s1;
    s32 var_s2;
    s32 var_v1;

    var_s2 = arg0;
    if (D_main_bss_8013A528[var_s2] == 0xFFFF) {
        temp_s4 = load_asset(D_main_8003C960);
        do {
loop_2:
            var_s1 = temp_s4;
            for (var_v1 = 0; var_v1 < var_s2; var_v1++) {
                var_s1 = (struct full_image_header *)(((u32)var_s1 + var_s1->image_size + 7) & ~3);
            }
            full_header_image_offset_convert(&var_s1->ent, (u32)&var_s1->ent);
            var_s1->ent.flags_type |= 0x2000;
            sp10.material_type = 1;
            sp10.material_name[0] = 0;
            D_main_bss_8013A528[var_s2] = registerHmtTextureInTable(&sp10, &var_s1->ent, 1U);
            var_s2 = 9;
            if (D_main_bss_8013A528[9] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xA;
            if (D_main_bss_8013A528[0xA] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xB;
            if (D_main_bss_8013A528[0xB] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xC;
        } while (D_main_bss_8013A528[0xC] == 0xFFFF);
        rs_free(temp_s4);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/6C310", applyCentripetalBankingToNpcCorners);

extern u8 D_main_800A09C0[];
extern void clearStructPair2C30(void *);
extern void zmemcpy(void *, void *, u32);

u8 *allocateAndInitCraftNpcContext(f32 x, f32 y, u16 craft) {
    u8 *p;
    u16 id;
    u32 k;
    u32 t;
    s32 c;
    u8 *q;
    s32 v;

    p = rs_malloc(0x1E4, 0);
    k = craft & 0xF;
    loadCraftShadowTextures(k);
    c = 0x02960001;
    t = (u32)D_main_bss_8013A528;
    {
        register u32 tm asm("$16") = k * 2;
        k = tm + t;
    }
    id = *(u16 *)k;
    *(s32 *)(p + 0x80) = 9;
    *(u8 **)(p + 0x8C) = p + 0xC8;
    *(s32 *)(p + 0x2C) = 0;
    *(s32 *)(p + 0x28) = 0;
    *(s32 *)(p + 0x24) = 0;
    *(s32 *)(p + 0x20) = 0;
    *(u8 **)(p + 0x30) = p + 0x6C;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x70) = 0;
    *(s32 *)(p + 0x6C) = 0;
    *(s32 *)(p + 0x74) = 0;
    *(s32 *)(p + 0x78) = c;
    *(s32 *)(p + 0x88) = 0;
    *(s32 *)(p + 0x7C) = 0;
    *(s32 *)(p + 0x84) = 0;
    *(u8 **)(p + 0x90) = p + 0x178;
    *(s32 *)(p + 0x94) = 0;
    clearStructPair2C30(p + 0x6C);
    *(s32 *)(p + 0xCC) = 0;
    *(s32 *)(p + 0xC8) = 0;
    *(u8 **)(p + 0xD0) = p + 0xD8;
    *(s32 *)(p + 0xD4) = 4;
    zmemcpy(p + 0xD8, D_main_800A09C0, 0xA0);
    v = id << 16;
    *(s32 *)(p + 0x158) = v;
    *(s32 *)(p + 0x130) = v;
    *(s32 *)(p + 0x108) = v;
    *(s32 *)(p + 0xE0) = v;
    if (id == D_main_bss_8013A528[5] || id == D_main_bss_8013A528[0xC]) {
        *(u16 *)(p + 0x168) = 0x800;
        *(u16 *)(p + 0x164) = 0x800;
        *(u16 *)(p + 0x148) = 0x800;
        *(u16 *)(p + 0x144) = 0x800;
        *(u16 *)(p + 0x118) = 0x800;
        *(u16 *)(p + 0x114) = 0x800;
        *(u16 *)(p + 0xF8) = 0x800;
        *(u16 *)(p + 0xF4) = 0x800;
        *(u16 *)(p + 0x170) = 0x1000;
        *(u16 *)(p + 0x16C) = 0x1000;
        *(u16 *)(p + 0x120) = 0x1000;
        *(u16 *)(p + 0x11C) = 0x1000;
    }
    q = p;
    *(f32 *)(q + 8) = x;
    *(f32 *)(q + 0xC) = y;
    *(u16 *)(q + 0x1C) = 0;
    *(u16 *)(q + 0x1E) = 0xFF;
    *(f32 *)(q + 0) = *(f32 *)(q + 4) = 0.0f;
    *(f32 *)(q + 0x14) = 2.0f;
    *(f32 *)(q + 0x18) = 1.0f;
    *(f32 *)(q + 0x10) = 0.5f;
    return q;
}

extern u8 D_main_bss_80138058[];
extern u8 *D_main_bss_80136E08;
extern u8 *D_main_bss_80138D1C;
extern s32 D_main_bss_8013A524;
extern s32 D_main_bss_8013889C;
extern u16 D_main_bss_8013A520;
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
s32 transformVec3ToNpcLocalWithScale(s32, s32, f32 *, f32, s32);
s32 sampleTerrainAtNpcPosition(f32 *, f32 *, void *, s32);
void setVec3At0x24(void *, f32, f32, f32);
s32 rand(void);
void acbCall(f32 *, u8 *, f32 *, f32, f32) __asm__("applyCentripetalBankingToNpcCorners");

static __inline__ void anSetB27(u8 *l, s32 v) {
    register s32 vv asm("$6") = v;
    u8 *e = *(u8 **)(l + 8);
    u32 i;

    for (i = 0; i < *(u32 *)(l + 0xC); i++) {
        e[0x27] = vv;
        e += 0x28;
    }
}

void anocV(u8 **list, s32 obj, f32 *m, u8 *npc) __asm__("advanceNpcOnCurvedPath");
void anocV(u8 **list, s32 obj, f32 *m, u8 *npc) {
    f32 v[3];
    f32 d[3];
    f32 t;
    f32 r;
    s16 h;
    register s32 a asm("$3");
    u8 *l;
    u8 *e;
    u32 i;

    if (m != NULL) {
        v[0] = m[0] + m[3] * ((f32 *)npc)[1] + (m[7] * m[5] - m[8] * m[4]) * ((f32 *)npc)[0];
        v[2] = m[2] + m[5] * ((f32 *)npc)[1] + (m[6] * m[4] - m[7] * m[3]) * ((f32 *)npc)[0];
        v[1] = wrapAngleToCyclicRange(v[0], v[2], D_main_bss_80138058, 0);
        t = (v[1] - m[1]) * ((f32 *)npc)[4];
        v[0] += *(f32 *)(D_main_bss_80136E08 + 0x10) * t;
        v[2] += *(f32 *)(D_main_bss_80136E08 + 0x18) * t;
        v[1] = wrapAngleToCyclicRange(v[0], v[2], D_main_bss_80138058, 0);
    } else {
        v[0] = *(f32 *)(npc + 0x60);
        v[1] = *(f32 *)(npc + 0x64);
        v[2] = *(f32 *)(npc + 0x68);
    }
    if (list == NULL || (u8)transformVec3ToNpcLocalWithScale(obj, 0, v, 1.0f, 0)) {
        if ((s16)--*(s16 *)(npc + 0x1C) <= 0) {
            if (D_main_bss_8013A524 != D_main_bss_8013889C) {
                D_main_bss_8013A524 = D_main_bss_8013889C;
                D_main_bss_8013A520 = 0;
            }
            if (D_main_bss_8013A520 < 3) {
                d[0] = *(f32 *)(D_main_bss_80138D1C + 0x4C) - v[0];
                d[1] = *(f32 *)(D_main_bss_80138D1C + 0x50) - v[1];
                d[2] = *(f32 *)(D_main_bss_80138D1C + 0x54) - v[2];
                D_main_bss_8013A520++;
                if (sampleTerrainAtNpcPosition(v, d, D_main_bss_80138058, 0)) {
                    s32 x = *(s16 *)(npc + 0x1E);
                    if (x < 0) {
                        x = -x;
                    }
                    *(s16 *)(npc + 0x1E) = -x;
                } else if (*(s16 *)(npc + 0x1E) <= 0) {
                    if (*(s16 *)(npc + 0x1E) != 0) {
                        *(s16 *)(npc + 0x1E) = -*(s16 *)(npc + 0x1E);
                    } else {
                        *(s16 *)(npc + 0x1E) = 1;
                    }
                }
                *(s16 *)(npc + 0x1C) = (rand() & 7) + 4;
            } else {
                *(s16 *)(npc + 0x1C) = rand() & 7;
            }
        }
        if (*(s16 *)(npc + 0x1E) != 0) {
            if (*(s16 *)(npc + 0x1E) < 0) {
                *(s16 *)(npc + 0x1E) += 0x20;
                if (*(s16 *)(npc + 0x1E) >= 0) {
                    *(s16 *)(npc + 0x1E) = 0;
                }
            } else {
                *(s16 *)(npc + 0x1E) += 0x20;
                if (*(s16 *)(npc + 0x1E) >= 0x100) {
                    *(s16 *)(npc + 0x1E) = 0xFF;
                }
            }
            if (m == NULL) {
                h = *(s16 *)(npc + 0x1E);
                t = *(f32 *)(npc + 0x18);
                if (h >= 0) {
                    a = (u32)(t * (f32)h);
                } else {
                    a = (u32)(t * (f32)-h);
                }
                anSetB27(npc + 0xC8, a);
            } else {
                r = 1.0f - (v[1] - m[1]) / *(f32 *)(npc + 0x14);
                if (r < 0.0f) {
                    return;
                }
                if (1.0f < r) {
                    r = 1.0f;
                }
                h = *(s16 *)(npc + 0x1E);
                r = r * *(f32 *)(npc + 0x18);
                if (h >= 0) {
                    a = (u32)(r * (f32)h);
                } else {
                    a = (u32)(r * (f32)-h);
                }
                anSetB27(npc + 0xC8, a);
                acbCall(v, npc, m, 0.5f, 0.5f);
                setVec3At0x24(npc + 0x3C, v[0], v[1], v[2]);
            }
            if (list != NULL) {
                e = *list;
                *(u8 **)(npc + 0x20) = e;
                if (e != NULL) {
                    *(u8 **)(e + 4) = npc + 0x20;
                }
                *list = npc + 0x20;
                *(s32 *)(npc + 0x24) = 0;
            }
        }
    }
}

extern u16 D_main_bss_80139594;
u8 *allocateAndInitCraftNpcContext(f32, f32, u16);
void advanceNpcOnCurvedPath(s32, s32, s32, u8 *);
s32 destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(u8 *);
s32 popNpcSlotFromTail(u16, void *);

s32 splineWalkerCraftNpcHandler(u8 *arg0, u16 arg1, u8 *arg2) {
    u8 *npc;
    u8 *ctx;
    f32 c;

    npc = *(u8 **)(arg0 + 4);
    switch (arg1) {
    case 1:
        ctx = allocateAndInitCraftNpcContext(*(f32 *)(arg2 + 4), *(f32 *)(arg2 + 8), *(u16 *)(arg2 + 0xC));
        *(u8 **)(npc + 0xC) = ctx;
        if (ctx == NULL) {
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        c = 100.0f;
        *(s32 *)(ctx + 0x10) = 0;
        *(f32 *)(ctx + 0x14) = c;
        advanceNpcOnCurvedPath(0, 0, *(s32 *)arg2, ctx);
        *(s32 *)(ctx + 0x78) = (*(s32 *)(ctx + 0x78) & 0xF1FFFFFF) | 0x08000000;
        *(f32 *)(npc + 0) = *(f32 *)(ctx + 0x60);
        *(f32 *)(npc + 4) = *(f32 *)(ctx + 0x64);
        *(f32 *)(npc + 8) = *(f32 *)(ctx + 0x68);
        popNpcSlotFromTail(D_main_bss_80139594, arg0);
        return 1;
    case 2:
        rs_free(*(s32 *)(npc + 0xC));
        return 1;
    case 4:
        if (isNpcWithinActiveReferenceRange(npc) == 0) {
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        advanceNpcOnCurvedPath(*(s32 *)(arg2 + 8), *(s32 *)arg2, 0, *(u8 **)(npc + 0xC));
        break;
    }
    return 1;
}

typedef struct {
    f32 x;
    s32 pad04;
    f32 y;
    s32 pad0C;
    s32 pad10;
    f32 scaleX;
    s32 pad18;
    f32 scaleY;
    s32 pad20;
    s32 pad24;
    s32 pad28;
} StubPathPoint;

extern u16 D_main_bss_80139574;

s32 stubNpcHandler(u8 *arg0, u16 arg1, u8 *arg2) {
    StubPathPoint pt;
    u8 *npc;
    u8 *ctx;
    f32 one;
    f32 f;

    npc = *(u8 **)(arg0 + 4);
    switch (arg1) {
    case 1:
        one = 1.0f;
        *(f32 *)(npc + 0x10) = one;
        ctx = allocateAndInitCraftNpcContext(*(f32 *)(arg2 + 8), *(f32 *)(arg2 + 0xC), *(u16 *)(arg2 + 0x10));
        *(u8 **)(npc + 0xC) = ctx;
        if (ctx == NULL) {
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        *(f32 *)(ctx + 0x18) = *(f32 *)(npc + 0x10);
        *(s32 *)(ctx + 0x10) = 0;
        *(f32 *)(ctx + 0x14) = 100.0f;
        pt.x = *(f32 *)(arg2 + 0);
        pt.pad04 = 0;
        pt.y = *(f32 *)(arg2 + 4);
        pt.pad0C = 0;
        pt.pad10 = 0;
        pt.scaleX = one;
        pt.pad18 = 0;
        pt.scaleY = one;
        pt.pad20 = 0;
        advanceNpcOnCurvedPath(0, 0, (s32)&pt, ctx);
        *(s32 *)(ctx + 0x78) = (*(s32 *)(ctx + 0x78) & 0xF1FFFFFF) | 0x08000000;
        *(f32 *)(npc + 0) = *(f32 *)(ctx + 0x60);
        *(f32 *)(npc + 4) = *(f32 *)(ctx + 0x64);
        *(f32 *)(npc + 8) = *(f32 *)(ctx + 0x68);
        popNpcSlotFromTail(D_main_bss_80139574, arg0);
        return 1;
    case 2:
        rs_free(*(s32 *)(npc + 0xC));
        return 1;
    case 3:
        f = *(f32 *)(npc + 0x10) - *(f32 *)(arg2 + 0) * 0.5f;
        *(f32 *)(npc + 0x10) = f;
        if (f <= 0.0f) {
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        *(f32 *)(*(u8 **)(npc + 0xC) + 0x18) = f;
        break;
    case 4:
        advanceNpcOnCurvedPath(*(s32 *)(arg2 + 8), *(s32 *)arg2, 0, *(u8 **)(npc + 0xC));
        break;
    }
    return 1;
}

void clearTrackedNpcSlots(void) {
    s32 i;
    u16 v = 0xFFFF;

    for (i = 13; i >= 0; i--) {
        D_main_bss_8013A528[i] = v;
    }
}

s32 splineWalkerCraftNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s16 d;
} SplineWalkerSpawnArgs;
void spawnSplineWalkerCraft(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    SplineWalkerSpawnArgs args;

    args.a = arg0;
    args.b = arg1;
    args.c = arg2;
    args.d = arg3;
    spawnNpcOfType(splineWalkerCraftNpcHandler, &args, 1, 10);
}

s32 stubNpcHandler();
typedef struct {
    f32 x;
    f32 y;
    s32 a;
    s32 b;
    s16 c;
} StubMarkerArgs;
u16 spawnStubMarkerNpc(f32 x, f32 y, s32 a, s32 b, s16 c) {
    StubMarkerArgs args;

    args.a = a;
    args.b = b;
    args.x = x;
    args.y = y;
    args.c = c;
    return spawnNpcOfType(stubNpcHandler, &args, 1, 10);
}

extern u32 get_asset_size_extra(s32, char *);
extern s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
extern void setupAssetDma(s32, s32, s32, s32, u32, void *);
extern void teardownAssetDma(s32, s32);
extern char D_main_8003C9B0[];
extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;

__asm__(".section .rodata\n.align 2\n.globl D_main_8003C9B0\nD_main_8003C9B0:\n.word 0x706C5F63\n.word 0x72616674\n.word 0x732F6B6F\n.word 0x656C7363\n.word 0x685F484D\n.word 0x54008005\n.word 0x45010004\n.word 0x00000000\n.section .text");

u32 load_naboo_starfighter(u32 arg0) {
    u32 buf;
    u32 size;
    u32 off;
    u32 ret;
    u32 v;
    s32 idx;
    u16 count;
    u16 i;
    u32 *q;

    size = get_asset_size_extra(D_main_bss_80137CFC, D_main_8003C9B0);
    buf = (u32)rs_malloc(size, 0);
    idx = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, D_main_8003C9B0, 0);
    setupAssetDma(D_main_bss_80138920, 0, idx, 0, size, (void *)buf);
    teardownAssetDma(D_main_bss_80138920, idx);
    decrypt_ns_hmt((u8 *)buf, size, arg0);
    off = *(u32 *)(buf + 4);
    ret = 0;
    if (size >= off && (off & 3) == 0) {
        count = *(u16 *)(buf + off);
        if (count < 0x29) {
            i = 0;
            for (; i < count; i++, off += 0x34) {
                if (off >= size) {
                    break;
                }
                q = (u32 *)(off + buf) + 1;
                v = *q;
                if (v == 0 || (v & 3) != 0 || v > size) {
                    break;
                }
                v = q[9];
                if (v == 0 || (v & 3) != 0 || v > size) {
                    break;
                }
            }
            if (i == count) {
                ret = arg0;
            }
        }
    }
    rs_free((void *)buf);
    return ret;
}

#if 0
void *getCraftRecordByIdx(s32 arg0) {
    return &gPlayers[arg0].inner.posX; // While this matches its obviously wrong, there's another struct inside player.inner (most likely)
}
#else
extern u8 D_main_bss_80137DBC[][0x2A0];
void *getCraftRecordByIdx(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 4;
}
#endif

void *getPlayerCraftRecordByIdx(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 4;
}

enum PlayerCraft getPlayerVehicleId(s32 playerId) {
    return gPlayers[playerId].inner.vehicleId;
}

void *getPlayerRecordTargetBuffer(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 0x34;
}

u16 getPlayerField2(s32 arg0) {
    return gPlayers[arg0].unk002;
}

extern u16 D_main_bss_80139574;
void releaseMeshAsset(void *);
void *walkMeshdef0List(char *);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, s32, s32, s32);
s32 popNpcSlotFromTail(u16, void *);

s32 attachDebrisModelVariant(u8 *arg0, u8 *arg1) {
    f32 fs0;
    u8 *a;
    u8 *t;
    char *name;
    f32 x;
    f32 y;
    f32 z;
    f32 f;
    u8 *m;
    u8 *mp;

    a = *(u8 **)(arg1 + 0x30);
    fs0 = *(f32 *)(*(u8 **)a + 0x34);
    releaseMeshAsset(a);
    t = *(u8 **)(arg1 + 0x34);
    switch (*(s32 *)(t + 0x90)) {
        default:
            name = *(char **)(t + 0x5C);
            break;
        case 1:
            name = "bld_a_dst";
            break;
        case 2:
            name = "bld_b_dst";
            break;
        case 3:
            name = "bld_c_dst";
            break;
        case 4:
            name = "fueltnk_dst";
            break;
        case 5:
            *(u8 **)(arg1 + 0x30) = NULL;
            return 0;
    }
    *(s32 *)(arg0 + 0xC) = 0;
    m = walkMeshdef0List(name);
    *(void **)(arg1 + 0x30) = m;
    mp = m + 0x28;
    f = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x94);
    if (f != 0.0f) {
        x = f * 0.25f;
    } else {
        x = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x28) * fs0;
    }
    f = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x98);
    if (f != 0.0f) {
        y = f * 0.25f;
    } else {
        y = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x2C) * fs0;
    }
    f = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x9C);
    if (f != 0.0f) {
        z = f * 0.25f;
    } else {
        z = *(f32 *)(*(u8 **)(arg1 + 0x34) + 0x30) * fs0;
    }
    initVec4TripletFromArgs(mp, x, y, z);
    composeRotationMatrixSlot0(*(u8 **)(arg1 + 0x30) + 0x28, *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x1C));
    composeRotationMatrixSlot1(*(u8 **)(arg1 + 0x30) + 0x28, *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x20));
    composeRotationMatrixSlot2(*(u8 **)(arg1 + 0x30) + 0x28, *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x24));
    addVec3At0x24(*(u8 **)(arg1 + 0x30) + 0x28, *(s32 *)(arg1 + 0), *(s32 *)(arg1 + 4), *(s32 *)(arg1 + 8));
    popNpcSlotFromTail(D_main_bss_80139574, arg0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/6C310", updateDestructionDebrisNpc);
__asm__(".section .rodata\n.globl D_main_8003CAE4\nD_main_8003CAE4:\n.word 0x3F4CCCCD\n.word 0x3C01003F\n.word 0x01415824\n.section .text");


INCLUDE_ASM("asm/nonmatchings/main/6C310", fake_func_8006D8FC);
