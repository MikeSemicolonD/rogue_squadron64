#include "common.h"
#include "common_types.h"

#include "main/5D220.h"

u8 D_main_8009ECF0[] = {
    0x20,
    0x20,
    0x10,
    0x20,
    0x10,
    0x20,
    0x20,
    0x00,
    0x30,
    0x30,
    0x50,
    0x40,
    0x30,
    0x60,
    0x20,
    0x00,
};

char *D_main_8009ED00[] = {
    "red_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "red_laser",
    NULL,
    NULL,
    NULL,
    "i_missile",
    "i_missile",
    "ion_laser",
    "ph_torp",
    "i_missile",
};

f32 D_main_8009ED3C[] ={
    0.7f,
    1.2f,
    2.0f,
    4.0f,
    0.0f,
    1.0f,
    0.0f,
};

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_5D220[] = {
    0xC4400000,
    0xC4620000,
};

INCLUDE_ASM("asm/nonmatchings/main/5D220", checkTrackedNpcProximityForCue);

INCLUDE_ASM("asm/nonmatchings/main/5D220", audioCueDispatcherNpcHandler);

extern u16 D_main_bss_8013957C;
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 revalidateNpcSlotIterator(void *);
void slotDispatcherIter(u16, s32, void *);
void transformMeshPartIntoWorld(s32, f32 *);

void collectNearbyNpcsForEffect(u8 *arg0, u16 arg1) {
    u8 sp10[8];
    struct {
        u16 a;
        u16 b;
        s16 c;
        s16 d;
        s32 e;
    } ev;
    f32 v[3];
    s32 idx;
    s32 mesh;
    u32 cur;
    f32 dist2;
    f32 r;
    f32 t;
    f32 sq;
    f32 sq2;
    f32 val;
    f32 two31;
    u32 sign;
    s32 w;

    ev.a = 0xFFFF;
    ev.b = 0xFFFF;
    ev.c = 9;
    ev.e = 0;
    idx = findActiveNpcInSlotChain(D_main_bss_8013957C, sp10);
    if ((idx & 0xFFFF) != 0xFFFF) {
        sign = 0x80000000;
        two31 = 2147483648.0f;
        do {
            cur = idx & 0xFFFF;
            if (cur != (arg1 & 0xFFFF)) {
                mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
                if (mesh != 0) {
                    transformMeshPartIntoWorld(mesh, v);
                    v[0] = v[0] - *(f32 *)(arg0 + 0x90);
                    v[1] = v[1] - *(f32 *)(arg0 + 0x94);
                    v[2] = v[2] - *(f32 *)(arg0 + 0x98);
                    r = *(f32 *)(arg0 + 0xD0);
                    dist2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
                    if (dist2 <= r * r) {
                        __asm__("sqrt.s %0, %1" : "=f"(sq) : "f"(dist2));
                        t = (r - sq) / r;
                        __asm__ volatile("sqrt.s %0, %1" : "=f"(sq2) : "f"(t));
                        val = (f32)*(u16 *)(arg0 + 0xD6) * sq2;
                        if (!(two31 <= val)) {
                            ev.d = (s32)val;
                        } else {
                            w = (s32)(val - two31);
                            __asm__("or %0, %1, %2" : "=r"(w) : "r"(w), "r"(sign));
                            ev.d = w;
                        }
                        slotDispatcherIter(idx & 0xFFFF, 5, &ev);
                    }
                }
            }
            idx = revalidateNpcSlotIterator(sp10);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/5D220", sprayEffectEmitterNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/5D220", dispatchCueByCategory);

INCLUDE_RODATA("asm/nonmatchings/main/5D220", D_main_8003B168);

extern s32 D_main_8003B168;
extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_8013961C;
extern s32 D_main_bss_80139740;
extern u8 *D_main_bss_801395E0[];
extern s16 D_main_bss_80139738;
extern s8 D_main_bss_80139730;
extern s8 D_main_bss_80139734[];
extern s8 D_main_bss_8013973A;
extern f32 D_main_bss_8013973C;
void load_hmt_and_hob(char *, s32, s32, s32);
u8 *getHobObjectByName(char *);
s16 loadAndRelocateAsset(s32 *, s32, s32);
void loadExplosionTextures(void);
s32 rs_malloc(s32, s32);
s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
void setupAssetDma(s32, s32, s32, s32, s32, s32);
void teardownAssetDma(s32, s32);
void initWeaponSlotIndexTable(void);
s32 load_asset(char *);

void loadWeaponsHobObjects(void) {
    s32 i;
    u8 **s0;
    char **s1;
    u8 *obj;
    char *name;
    u8 *p;
    s8 *q;
    s32 h;
    u32 flag;

    load_hmt_and_hob("weapons", 0, 0, 0);
    i = 0;
    flag = 0x10000;
    s0 = D_main_bss_801395E0;
    s1 = D_main_8009ED00;
    do {
        name = *s1;
        if (name != NULL) {
            obj = getHobObjectByName(name);
            *s0 = obj;
            p = *(u8 **)(*(u8 **)(obj + 0x10) + 0x10);
            *(u32 *)(p + 0xC) |= flag;
        } else {
            *s0 = NULL;
        }
        s0++;
        i++;
        s1++;
    } while (i < 0xF);
    D_main_bss_80139738 = loadAndRelocateAsset(&D_main_8003B168, 0, 0);
    loadExplosionTextures();
    D_main_bss_80139740 = rs_malloc(0x400, 0);
    h = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, "lights_PAL", 1);
    i = 3;
    setupAssetDma(D_main_bss_80138920, 0, h, 0, 0x400, D_main_bss_80139740);
    teardownAssetDma(D_main_bss_80138920, h);
    q = D_main_bss_80139734 + i;
    do {
        *q = i;
        i -= 1;
        q -= 1;
    } while (i >= 0);
    i = 4;
    D_main_bss_80139730 = i;
    initWeaponSlotIndexTable();
    D_main_bss_8013961C = load_asset("weapon_info");
    D_main_bss_8013973A = 0;
    D_main_bss_8013973C = 0.5f;
}

s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 findNpcInScaledBoxRegion(u8 *arg0, f32 scale, u16 ex, u16 slot, f32 *out) {
    u8 it[8];
    f32 box[3];
    s32 idx;
    s32 mesh;
    u16 best;
    f32 bestDist;

    box[0] = *(f32 *)(arg0 + 0x24) * scale;
    box[1] = *(f32 *)(arg0 + 0x28) * scale;
    best = 0xFFFF;
    (void)0;
    bestDist = 2.0f;
    box[2] = *(f32 *)(arg0 + 0x2C) * scale;
    idx = findActiveNpcInSlotChain(slot, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            if (ex == 0xFFFF || ex != (idx & 0xFFFF)) {
                mesh = *(s32 *)(getNpcContextByIndex(idx & 0xFFFF) + 0xC);
                if (mesh != 0) {
                    if (findSegmentObjectSphereHit(mesh, arg0, box, out) != 0) {
                        if (out[6] < bestDist) {
                            bestDist = out[6];
                            best = idx;
                        }
                    }
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return best;
}

s32 findSegmentObjectSphereHit(s32, void *, void *, void *);

u16 findNpcInScaledBoxRegionExcludingPair(u8 *arg0, u16 ex1, f32 scale, u16 ex2, u16 slot, void *out) {
    u8 it[8];
    f32 box[3];
    u16 cur;
    s32 idx;
    s32 mesh;

    box[0] = *(f32 *)(arg0 + 0x24) * scale;
    box[1] = *(f32 *)(arg0 + 0x28) * scale;
    box[2] = *(f32 *)(arg0 + 0x2C) * scale;
    idx = findActiveNpcInSlotChain(slot, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            cur = idx & 0xFFFF;
            if (cur != ex1) {
                if (ex2 == 0xFFFF || ex2 != cur) {
                    mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
                    if (mesh != 0) {
                        if (findSegmentObjectSphereHit(mesh, arg0, box, out) != 0) {
                            return cur;
                        }
                    }
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0xFFFF;
}

s32 rs_free(s32);
extern s32 D_main_bss_8013961C;
extern s32 D_main_bss_80139740;

void freeEffectAssetBuffers(void) {
    rs_free(D_main_bss_8013961C);
    rs_free(D_main_bss_80139740);
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 unk1C;
    s16 unk20;
    s32 unk24;
    u8 unk28;
    u8 unk29;
    f32 unk2C;
} ByteAnimDebrisArgs;
void byteAnimatedDebrisNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
void spawnByteAnimDebrisDefault(f32 *pos) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = 0;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

void spawnByteAnimDebrisWithParam(f32 *pos, u8 arg1) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = arg1;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = arg1 + 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

s16 loadAndRelocateAsset(s32 *, s32, s32);
extern s32 D_main_8003B168;
extern s16 D_main_bss_80139738;

void loadTieBomberSprite(void) {
    D_main_bss_80139738 = loadAndRelocateAsset(&D_main_8003B168, 0, 0);
}

typedef struct {
    f32 x, y, z;
} NpcRayDir;

typedef struct {
    u8 pad0[0xC];
    f32 hx, hy, hz;
} NpcRayHit;

extern NpcRayDir D_main_bss_801395A0;
extern NpcRayHit D_main_bss_801395B0;
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 revalidateNpcSlotIterator(void *);

s32 findNpcAlongDirectionRay(u8 *arg0, s32 arg1, f32 *arg2, u16 arg3) {
    u8 sp10[8];
    f32 x;
    f32 y;
    f32 z;
    s32 idx;
    s32 ctx;

    x = *(f32 *)(arg0 + 0x10) * 0.5f;
    D_main_bss_801395A0.x = x;
    y = *(f32 *)(arg0 + 0x14) * 0.5f;
    D_main_bss_801395A0.y = y;
    z = *(f32 *)(arg0 + 0x18) * 0.5f;
    D_main_bss_801395A0.z = z;
    if (x == 0.0f && y == 0.0f && z == 0.0f) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(arg3, sp10);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            idx &= 0xFFFF;
            if (*(u16 *)(arg0 + 0xB6) != idx) {
                ctx = *(s32 *)(getNpcContextByIndex(idx) + 0xC);
                if (ctx != 0) {
                    if (findSegmentObjectSphereHit(ctx, arg0 + 4, &D_main_bss_801395A0, &D_main_bss_801395B0) != 0) {
                        arg2[0] = D_main_bss_801395B0.hx;
                        arg2[1] = D_main_bss_801395B0.hy;
                        arg2[2] = D_main_bss_801395B0.hz;
                        return 1;
                    }
                }
            }
            idx = revalidateNpcSlotIterator(sp10);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/5D220", fake_func_8005EE64);
