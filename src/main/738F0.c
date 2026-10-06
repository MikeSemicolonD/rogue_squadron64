#include "common.h"
#include "common_types.h"

extern u16 spawnNpcOfType(void *, void *, u32, u8);

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
} HeavyBurstArgs;

extern s32 heavyRandomBurstNpcHandler(void *, u16, void *);

__asm__(".section .rodata\n.align 2\nD_main_8003CEF0:\n.asciz \"gnrc_stuff/wtrspray\"\n.align 2\n.section .text");

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF04);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF10);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF20);

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    f32 unk10;
    s32 unk14;
    u8 pad18[8];
    u8 unk20;
    u8 pad21[0xF];
} WaterSprayRec;
typedef struct {
    s16 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s8 unk10;
    union {
        s32 w[4];
        char c[13];
    } name;
} WaterTexDesc;
typedef struct {
    u8 pad[0x1C];
    struct { u8 pad[8]; s32 unk8; } *unk1C;
} MeshdefList;
extern s32 D_main_bss_8013A8B0;
extern s32 D_main_bss_8013A8B4;
extern s32 D_main_bss_8013A8B8;
extern WaterSprayRec D_main_bss_8013A8C0;
extern WaterSprayRec D_main_bss_8013A8F0;
extern WaterSprayRec D_main_bss_8013A920;
extern u8 D_main_bss_8013A944;
extern char D_main_8003CEF0[];
extern char D_main_8003CF04[];
extern s32 D_main_8003CF10[];
extern char D_main_8003CF20[];
extern void load_hmt_and_hob(char *, s32, s32, s32);
extern MeshdefList *walkMeshdef0List(char *);
extern u16 findTextureByName(char *);
extern void releaseTextureLutEntry(s32);
extern void *load_asset(char *);
extern void full_header_image_offset_convert(void *, void *);
extern s32 registerHmtTextureInTable(void *, void *, s32);
extern void rs_free(void *);
extern void setMaterialFlagByIdInMeshTree(s32, s32, s32);
extern void releaseMeshAsset(void *);
extern s32 loadAssetIntoNewSlot(char *, char *);
extern void setPoolEntryPhaseAndMarkActive(u16, f32, s32);

void initWaterSprayParticles(void) {
    WaterTexDesc d;
    MeshdefList *mesh;
    u16 tex;
    void *asset;
    u8 *hdr;
    s32 mat;

    D_main_bss_8013A8B0 = 0;
    D_main_bss_8013A8C0.unk20 = 0;
    D_main_bss_8013A8C0.unkC = 0;
    D_main_bss_8013A8C0.unk14 = 0;
    D_main_bss_8013A8F0.unk20 = 0;
    D_main_bss_8013A8F0.unkC = 0;
    D_main_bss_8013A8F0.unk14 = 0;
    D_main_bss_8013A920.unk20 = 0;
    D_main_bss_8013A920.unkC = 0;
    D_main_bss_8013A920.unk14 = 0;
    D_main_bss_8013A8C0.unk10 = 2.0f;
    D_main_bss_8013A8F0.unk10 = 1.5f;
    D_main_bss_8013A920.unk10 = 0.5f;
    load_hmt_and_hob(D_main_8003CEF0, 0, 0, 0);
    mesh = walkMeshdef0List(D_main_8003CF04);
    tex = findTextureByName((char *)D_main_8003CF10);
    releaseTextureLutEntry(tex);
    asset = load_asset(D_main_8003CF20);
    hdr = (u8 *)asset + 4;
    d.unk0 = 1;
    d.unkC = 0;
    d.unk10 = 1;
    d.unk4 = 1.0f;
    d.unk8 = 1.0f;
    __builtin_memcpy(d.name.c, D_main_8003CF10, 13);
    full_header_image_offset_convert(hdr, hdr);
    mat = registerHmtTextureInTable(&d, hdr, 0);
    rs_free(asset);
    setMaterialFlagByIdInMeshTree(mesh->unk1C->unk8, tex, mat & 0xFFFF);
    releaseMeshAsset(mesh);
    setPoolEntryPhaseAndMarkActive(loadAssetIntoNewSlot((char *)D_main_8003CF10, D_main_8003CF20), 12.0f, 0);
    D_main_bss_8013A944 = 1;
    D_main_bss_8013A8B4 = 0;
    D_main_bss_8013A8B8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcWaterSprayUpdate);

typedef struct { f32 x, y, z; } DbVec3;
typedef struct {
    f32 f10;
    DbVec3 p;
    s32 w20;
    f32 f24;
    s32 w28, w2C, w30, w34;
    f32 f38, f3C;
    s32 w40, w44;
    f32 f48;
    s16 h4C, h4E;
    f32 f50;
    s32 w54, w58;
    f32 f5C;
    s32 w60;
    f32 fq64, f68;
    s32 w6C, w70, w74, w78;
    s8 b7C, b7D;
    s16 pad7E;
    s16 h80, h82, h84;
    s32 w88;
    s16 h8C;
    s16 pad8E;
} DestrBurstParams;
extern s32 D_main_bss_80130C04;
extern s32 gC08 __asm__("D_main_bss_80130C08");
extern s32 spawnRandomBurstNpcVariantWrapper(void *);

extern void assignNpcTargetAndPosition(u16, u16, void *, f32);


u16 spawnDestructionEffectBurst(f32 *pos, u16 id, f32 size, f32 scale, f32 dir, f32 mul) {
    DestrBurstParams d;
    s32 npc;
    f32 a;
    f32 b;

    a = scale * 0.5f;
    b = scale * 3.0f * 0.5f;
    d.f10 = 5.0f;
    d.p = *(DbVec3 *)pos;
    d.w20 = 0;
    d.f24 = -dir;
    d.w28 = 0;
    d.w2C = 0;
    d.w30 = 0;
    d.w34 = 0;
    d.f38 = 1.0f;
    d.f3C = 1.0f;
    d.w40 = 0;
    d.w44 = 0;
    d.f48 = size * 0.1f * 0.25f;
    d.h4C = 0;
    d.h4E = 0;
    d.f50 = size * 4.0f;
    d.w54 = 0;
    d.w58 = 0;
    d.f5C = size / dir;
    d.w60 = 0;
    d.fq64 = 0.8f;
    d.f68 = 1.0f;
    d.w6C = 0;
    d.w74 = gC08 + 0x18;
    d.b7C = 2;
    d.w78 = D_main_bss_80130C04;
    d.b7D = 16;
    d.h80 = (u32)(a * 256.0f + 1.0f);
    d.h82 = (u32)(b * 256.0f + 1.0f);
    d.h84 = (u32)(d.f50 * mul);
    d.w88 = 0x09000000;
    d.h8C = 3;
    npc = spawnRandomBurstNpcVariantWrapper(&d);
    if (id != 0xFFFF) {
        assignNpcTargetAndPosition(npc, id, 0, 0.0f);
    }
    return npc;
}

typedef struct { s32 x, y, z; } BurstV3;
typedef struct {
    f32 f0;
    BurstV3 v4;
    f32 f10, f14, f18, f1C;
    s32 w20, w24;
    f32 f28, f2C;
    s32 w30, w34;
    f32 f38;
    s16 h3C, h3E;
    f32 f40, f44, f48, f4C, f50, f54, f58, f5C;
    s32 w60;
    u8 *w64;
    s32 w68;
    u8 b6C, b6D;
    u8 pad6E[2];
    s16 h70, h72, h74, h76;
    s32 w78;
    u16 h7C;
} BurstCtx;
extern s32 D_main_bss_80130C04;
extern u8 *D_main_bss_80130C08;
extern s32 gCurrentLevel;
f32 distanceFromCameraToPoint(f32 *);
extern s32 spawnRandomBurstNpcVariantWrapper(void *);
extern void attachChildNpcByIndex(s32, void *);

s32 spawnDistanceScaledDebrisBurstImpl(f32 *arg0, f32 scale, f32 speed) __asm__("spawnDistanceScaledDebrisBurst");
s32 spawnDistanceScaledDebrisBurstImpl(f32 *arg0, f32 scale, f32 speed0)
{
  f32 speed = speed0;
  BurstCtx c;
  s32 id;
  f32 lo;
  f32 hi;
  scale = scale * (distanceFromCameraToPoint(arg0) / 4.5f);
  lo = scale * 0.5f;
  hi = (scale * 3.0f) * 0.5f;
  c.f0 = 5.0f;
  c.v4 = *((BurstV3 *) arg0);
  c.f10 = 0.0f;
  c.f14 = -speed;
  c.f18 = 0.0f;
  c.f1C = 0.0f;
  c.w20 = 0;
  c.w24 = 0;
  c.f28 = 1.0f;
  c.f2C = 1.0f;
  c.w30 = 0;
  c.w34 = 0;
  c.f38 = 0.025f;
  c.h3C = 0x1E;
  c.h3E = 0x1E;
  c.f40 = 60.0f;
  c.f44 = 0.0f;
  c.f48 = 0.0f;
  c.f4C = 0.5f;
  c.f50 = 0.0f;
  c.f54 = 0.05f;
  c.f58 = 1.0f;
  c.f5C = 0.0f;
  c.w64 = D_main_bss_80130C08 + 0x1C;
  c.b6C = 1;
  if (gCurrentLevel == 4)
  {
    c.w68 = D_main_bss_80130C04 + 0xC0;
  }
  else
  {
    c.w68 = D_main_bss_80130C04 + 0x80;
  }
  c.b6D = 0x10;
  c.h70 = (u32) ((lo * 256.0f) + 1.0f);
  c.h72 = (u32) ((hi * 256.0f) + 1.0f);
  c.h74 = 0x14;
  c.w78 = 0x09000000;
  c.h7C = 3;
  id = spawnRandomBurstNpcVariantWrapper(&c) & 0xFFFF;
  attachChildNpcByIndex(id, &D_main_bss_8013A8C0);
  return id;
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDirectionalDebrisBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", distanceAndDopplerNpcHelper);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D088);

typedef struct { f32 x, y, z; } ExpVec;
typedef struct { u8 a, b, c, d; } ExpU4;
typedef struct ExpLink {
    struct ExpLink *next;
    struct ExpLink *prev;
} ExpLink;
typedef struct {
    f32 pos[3];
    f32 dir[3];
    f32 axis[3];
    f32 vel[3];
    ExpLink link;
    s16 h38;
    s16 h3A;
    s16 h3C;
    u8 p3E[2];
    u16 h40;
    u16 h42;
    u8 p44[8];
    f32 f4C;
    f32 f50;
    f32 f54;
    s16 h58;
    s16 h5A;
    ExpU4 w5C;
    ExpU4 w60;
    f32 f64;
    f32 f68;
} ExpNode;
typedef struct {
    ExpVec *pos;
    ExpU4 *p4;
    ExpU4 *p8;
    f32 fC;
} ExpSpawn;
typedef struct {
    f32 dt;
    u8 p4[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 p24[0x24];
    struct { u8 p[0x20]; ExpLink *head; } *unk48;
} ExpTick;
typedef struct {
    f32 *vec;
    void *parent;
    void *p8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    u16 h1C;
    u16 h1E;
    f32 v[3];
} ExpSpray;
typedef struct { u8 p0[4]; ExpNode *unk04; u8 p8[0xE]; u16 unk16; } ExpSelf;
#include "main/192E0.h"
#include "main/1D000.h"
#include "main/5A750.h"
#include "main/700B0.h"
extern void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern u8 transformVec3ToNpcLocalWithScale(void *, s32, void *, f32, s32);
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);
extern void npcWaterSprayUpdate(void);
extern u16 D_main_bss_80139574;
extern u8 *D_main_bss_80138D1C;
extern u8 *D_main_bss_80130C08;
extern u8 D_main_bss_80138058[];
extern ExpVec D_main_8003D088;

s32 explosionEffectNpcHandler(ExpSelf *self, u16 action, void *arg2) {
    ExpNode *n = self->unk04;
    ExpSpawn *sp = arg2;
    ExpTick *tk = arg2;
    f32 s18[3];
    ExpVec s28;
    ExpSpray spray;
    ExpSpray *sprp;
    ExpVec *ps;
    f32 w;
    ExpU4 *pw;
    f32 dt;
    f32 ang;
    f32 *dir;
    f32 *cam;
    ExpLink *head;

    switch (action) {
    case 1:
        n->h40 = 0x201;
        n->w5C = *sp->p4;
        n->h5A = 0;
        n->h58 = 0;
        n->f50 = sp->fC;
        n->f54 = sp->fC;
        n->f4C = 0.0f;
        *(ExpVec *)n->pos = *sp->pos;
        n->f68 = 0.0f;
        n->w60 = *sp->p8;
        composeRandomRotationMatrix(n->axis, n->dir, 0.0f, 0x32, 0, 0);
        n->axis[0] = 1.0f - n->dir[0];
        n->axis[1] = 1.0f - n->dir[1];
        n->axis[2] = 1.0f - n->dir[2];
        orthonormalizeFrame((void *)n);
        *(ExpVec *)n->vel = *(ExpVec *)n->dir;
        scaleVec3ByRandomRange(n->vel, 0.8f, 3.5f);
        *(volatile f32 *)&n->f64 = 0.0f;
        popNpcSlotFromTail(D_main_bss_80139574, self);
        return 1;
    case 2:
        break;
    case 3:
        s28 = D_main_8003D088;
        dt = tk->dt;
        n->pos[0] = n->pos[0] + n->vel[0] * dt;
        n->pos[1] = n->pos[1] + n->vel[1] * dt;
        n->pos[2] = n->pos[2] + n->vel[2] * dt;
        n->vel[1] = n->vel[1] + dt * 5.0f;
        dir = n->dir;
        vec3NormalizeInto(dir, n->vel);
        ang = constMinusSinfApprox(vec3Dot((f32 *)&s28, dir));
        cam = (f32 *)(D_main_bss_80138D1C + 0x28);
        s28.x = n->pos[0] - cam[9];
        s28.y = n->pos[1] - cam[10];
        s28.z = n->pos[2] - cam[11];
        ang = ang * 57.29578f;
        vec3Cross(s18, (f32 *)&s28, dir);
        if (s18[1] >= 0.0f) {
            n->f4C = -ang + 45.0f;
        } else {
            n->f4C = ang + 45.0f;
        }
        if (n->vel[1] > 0.0f) {
            n->f68 = n->f68 + dt * 10.0f;
            if (n->f68 > 5.0f) {
                n->f68 = 5.0f;
            }
        }
        ang = wrapAngleToCyclicRange(n->pos[0], n->pos[2], D_main_bss_80138058, 0);
        if (ang < n->pos[1]) {
            sprp = &spray;
            ps = &s28;
            pw = &n->w60;
            s28.x = n->pos[0];
            s28.y = ang - 0.2f;
            s28.z = n->pos[2];
            w = 0.05f;
            if (D_main_bss_8013A944 != 0) {
                f32 cb = 2.0f; f32 cc = 0.15f; f32 ca = 0.4f; 
                sprp->v[1] = 0.2f;
                sprp->v[0] = w;
                sprp->v[2] = w;
                sprp->h1C = 0xFFFF;
                sprp->h1E = 3;
                sprp->parent = ps;
                spray.vec = spray.v;
                sprp->f18 = ca;
                sprp->f10 = cb;
                sprp->fC = cc;
                spray.p8 = pw;
                spawnNpcOfType(npcWaterSprayUpdate, sprp, 1, 0xF);
            }
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        break;
    case 4:
        if (transformVec3ToNpcLocalWithScale(*(void **)tk, 0, n, 1.0f, 0)) {
            n->h42 = *(u16 *)(D_main_bss_80130C08 + (s32)n->f68 * 2 + 0xC);
            n->h38 = (s32)((n->pos[0] - tk->f18) * 256.0f);
            n->h3A = (s32)((n->pos[1] - tk->f1C) * 256.0f);
            n->h3C = (s32)((n->pos[2] - tk->f20) * 256.0f);
            head = tk->unk48->head;
            n->link.next = head;
            if (head != NULL) {
                head->prev = &n->link;
            }
            n->link.prev = NULL;
            tk->unk48->head = &n->link;
        }
        break;
    default:
        return 1;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0C8);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0CC);

typedef struct ExplColor {
    u8 r, g, b, a;
} ExplColor;
typedef struct ExplosionArgs {
    void *pos;
    void *colorA;
    void *colorB;
    f32 scale;
    u16 id;
} ExplosionArgs;
extern ExplColor D_main_8003D0C8;
extern ExplColor D_main_8003D0CC;
extern u8 *D_main_bss_80138D1C;
extern u8 D_main_bss_80138058[];
extern f32 vec3Length(Vec3f);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern s32 randX(void) __asm__("rand");
extern void spawnOrientedNpcX(s32, f32 *, s32, void *, f32, f32, f32, f32) __asm__("spawnOrientedNpc");
extern void distanceAndDopplerNpcHelper(f32 *, f32, f32);

void triggerDistanceScaledExplosion(s32 i, f32 arg1) {
    ExplosionArgs args;
    ExplColor colA;
    ExplColor colB;
    f32 pos[3];
    Vec3f d;
    u8 *cam;
    f32 dist;
    s32 count;
    f32 x;
    f32 z;
    f32 ground;

    colA = D_main_8003D0C8;
    cam = D_main_bss_80138D1C + 0x28;
    colB = D_main_8003D0CC;
    d[0] = ((f32 *)i)[0] - *(f32 *)(cam + 0x24);
    d[1] = ((f32 *)i)[1] - *(f32 *)(cam + 0x28);
    d[2] = ((f32 *)i)[2] - *(f32 *)(cam + 0x2C);
    dist = vec3Length(d) / 2.5f;
    arg1 = arg1 * dist;
    if (dist > 0.0f) {
        count = 7.0f / dist;
    } else {
        count = 1;
    }
    if (count >= 8) {
        count = 7;
    }
    x = ((f32 *)i)[0];
    pos[0] = x;
    z = ((f32 *)i)[2];
    pos[2] = z;
    i = 0;
    ground = wrapAngleToCyclicRange(x, z, D_main_bss_80138058, 0);
    args.pos = pos;
    args.id = 0xFFFF;
    args.colorA = &colA;
    pos[1] = ground;
    args.colorB = &colB;
    if (count > 0) {
        do {
            args.scale = arg1 + ((f32)(randX() & 0x7F) - 64.0f) / 1280.0f;
            if (args.scale <= 0.0f) {
                args.scale = 0.001f;
            }
            spawnNpcOfType((void *)explosionEffectNpcHandler, &args, 1, 10);
            i++;
        } while (i < count);
    }
    spawnOrientedNpcX(0x8002, pos, 0, &colA, 0.05f, 0.18f, 0.4f, 0.5f);
    distanceAndDopplerNpcHelper(pos, 0.1f, 0.4f);
}

typedef struct { f32 x, y, z; } TodV;
typedef struct { f32 *vec; void *parent; u8 pad8[4]; f32 f24c; f32 f28c; f32 pad2C; f32 f30c; u16 s34; s16 s36; } TodWsArgs;
extern f32 D_tod8013A8B0 __asm__("D_main_bss_8013A8B0");
extern f32 D_main_bss_80130BA4;
extern f32 D_main_bss_80136FA8;
extern u8 D_main_bss_80139920[];
extern u8 D_main_bss_801398C0[];
extern s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
extern void spawnMinimalRandomNpc(f32 *, f32, void *);
extern s32 getPlayerField2(s32);
extern void spawnStubMarkerNpc(f32, f32, f32, f32, s32);
extern s16 todRand(void) __asm__("rand");
extern void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
extern u16 todBurst(f32 *, u16, f32, f32, f32, f32) __asm__("spawnDestructionEffectBurst");
extern void todExplode(f32 *, f32, f32, f32) __asm__("triggerDistanceScaledExplosion");
extern void todDebris(void *, f32, f32) __asm__("spawnDistanceScaledDebrisBurst");

static __inline__ void todSpray(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 kind) {
    TodWsArgs a;
    f32 v[3];
    if (D_main_bss_8013A944 != 0) {
        a.s34 = 0xFFFF;
        a.s36 = kind;
        a.parent = arg0;
        v[0] = arg1;
        v[2] = arg1;
        v[1] = arg3;
        a.vec = v;
        a.f30c = arg4;
        a.f28c = 1.0f / arg5;
        a.f24c = arg2 - arg1;
        spawnNpcOfType(npcWaterSprayUpdate, &a, 1, 0xF);
    }
}

s32 triggerObjectDestructionEffects(f32 *pos, f32 *vel, u16 owner) {
    f32 v[3];
    s32 r;

    r = isTerrainCellBlockedAtWorldXz(pos[0], pos[2], D_main_bss_80138058);
    if (r == 0) {
        spawnMinimalRandomNpc(pos, 0.5f, D_main_bss_80139920);
        if (owner != (u16)getPlayerField2(0)) {
            return 0;
        }
        if (D_tod8013A8B0 + 0.1f < D_main_bss_80130BA4) {
            D_tod8013A8B0 = D_main_bss_80130BA4;
            spawnStubMarkerNpc(((TodV *)pos)->x, ((TodV *)pos)->z, 0.08f, 0.08f, 0xC);
        }
        r = (s16)(todRand() % 100);
        if (r < 2) {
            v[0] = vel[0];
            v[1] = -1.0f;
            v[2] = vel[2];
            spawnDebris1Npc(pos, v, 20.0f, 0.5f, 0.1f);
        } else if (r < 10) {
            todBurst(pos, 0xFFFF, 1.2f, 0.25f, 0.8f, 0.5f);
        }
        if (gCurrentLevel == 13 && pos[1] >= 10.0f) {
            todExplode(pos, 0.1f, 0.4f, 1.0f);
            return 0;
        }
        return 0;
    }
    if (r != 1) {
        return 0;
    }
    v[0] = pos[0];
    v[2] = pos[2];
    v[1] = wrapAngleToCyclicRange(v[0], v[2], D_main_bss_80138058, 0) - D_main_bss_80136FA8;
    if (gCurrentLevel != 13) {
        todDebris(v, 0.1f, 0.4f);
        spawnMinimalRandomNpc(v, 0.5f, D_main_bss_801398C0);
        todSpray(v, 0.05f, 0.4f, 0.3f, 0.3f, 0.3f, 1);
        return 1;
    }
    if (owner == (u16)getPlayerField2(0)) {
        todExplode(pos, 0.1f, 0.4f, 1.0f);
    }
    return 1;
}

#include "main/192E0.h"
#include "main/1D000.h"
#include "main/5A750.h"
extern void *getNpcContextField8(u16);
typedef struct {
    u8 pad0[0x5C];
    Vec3f a;
    Vec3f b;
} LimbAnchors;
typedef struct {
    LimbAnchors *anchors;
    u8 pad4[0x24];
    Mat4x3 m;
} LimbObj;
typedef struct {
    u8 pad[0xC];
    LimbObj *obj;
} LimbCtx;
extern u8 *getNpcContextByIndex(u16);

void transformLimbStrideAnchorsLocal(u16 idx, f32 *out, f32 *out2) {
    Mat4x3 inv;
    Mat4x3 basis;
    Vec3f pa;
    Vec3f pb;
    LimbObj *obj;
    LimbAnchors *an;
    f32 *a;
    f32 *b;
    f32 s;
    f32 (*m)[3];

    obj = ((LimbCtx *)getNpcContextByIndex(idx))->obj;
    an = obj->anchors;
    m = obj->m;
    a = an->a;
    b = an->b;
    transformVec3ByMat34(m, a, pa);
    transformVec3ByMat34(m, b, pb);
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(obj->m[0][0] * obj->m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]));
    out[0] = (an->b[0] - an->a[0]) * s;
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]));
    out[1] = (b[1] - a[1]) * s;
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]));
    out[2] = (b[2] - a[2]) * s;
    if (out2 != NULL) {
        out2[0] = pa[0] + (pb[0] - pa[0]) * 0.5f;
        out2[1] = pa[1] + (pb[1] - pa[1]) * 0.5f;
        out2[2] = pa[2] + (pb[2] - pa[2]) * 0.5f;
        mat34CrossRowsAndCopyPos(basis, getNpcContextField8(idx), 1.0f);
        mat3x3InverseInto(inv, basis);
        transformVec3ByMat34(inv, out2, out2);
    }
}

typedef struct RPLink {
    struct RPLink *next;
    struct RPLink *prev;
} RPLink;
typedef struct {
    f32 pos[3];
    f32 fC;
    RPLink link;
    s32 w18;
    s32 w1C;
    void *p20;
    s32 w24;
    u8 p28[0x34];
    s32 w5C;
    s32 w60;
    s32 w64;
    s32 w68;
    s32 w6C;
    s32 w70;
    s32 w74;
    u8 p78[4];
    void *p7C;
    u8 p80[0x38];
    s32 wB8;
    s32 wBC;
    s16 hC0;
    s16 hC2;
    s16 hC4;
    u8 pC6[2];
    u16 hC8;
    u16 hCA;
    u8 pCC[12];
    f32 fD8;
    f32 fDC;
    u8 pE0[4];
    u8 bE4;
    u8 bE5;
    u8 bE6;
    u8 bE7;
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
    f32 pos2[3];
    u16 h10C;
    u16 h10E;
} RPNode;
typedef struct {
    f32 f0;
    f32 f4;
    u16 h8;
} RPSpawn;
typedef struct { RPLink **headp; } RPLinks;
typedef struct { u8 p0[4]; RPNode *unk04; u8 p8[0xE]; u16 unk16; } RPSelf;
#include "rs_math.h"
#include "main/192E0.h"
#include "main/1D000.h"
#include "main/5A750.h"
extern s16 rand(void);
static __inline__ f32 absf_(f32 v) {
    f32 r;
    __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(v));
    return r;
}
extern void *rs_malloc(u32, u16);
extern void clearStructPair2C30(void *);
extern u16 findFreeNpcSlotByKey(s32, u16);
extern u16 getNextSlotNpcTypeId(u16);
extern void destroyNpcSlotChain(u16);
extern void destroyNpcSlotByIndex(u16);
extern void popNpcSlotFromTail(u16, void *);
extern u8 transformVec3ToNpcLocalWithScale(void *, s32, void *, f32, s32);
extern void forwardToNpcGeneratorSpawn(u16, s32, f32);
extern void *getNpcContextField8(u16);
extern u16 D_main_bss_80139574;
extern u16 D_main_bss_80139910[];

s32 rpHandler(void *selfp, u16 action, void *arg2) __asm__("randomParticleWithParentNpcHandler");
s32 rpHandler(void *selfp, u16 action, void *arg2) {
    RPSelf *self = selfp;
    RPNode *n = self->unk04;
    RPSpawn *sp = arg2;
    RPLinks *rl = arg2;
    void *s0;
    Mat4x3 m;
    f32 x;
    f32 a;
    f32 dt;
    s32 i;

    switch (action) {
    case 1:
        n = rs_malloc(0x110, 0);
        s0 = &n->w5C;
        __asm__("" :: "r"(s0));
        self->unk04 = n;
        n->w68 = 0x49000000;
        n->p7C = (u8 *)n + 0xB8;
        n->w1C = 0;
        n->w18 = 0;
        n->link.prev = 0;
        n->link.next = 0;
        n->w24 = 0;
        n->p20 = s0;
        n->w64 = 0;
        n->w60 = 0;
        n->w5C = 0;
        n->w6C = 0;
        n->w74 = 0;
        n->w70 = 0;
        n->wBC = 0;
        n->wB8 = 0;
        n->hC4 = 0;
        n->hC2 = 0;
        n->hC0 = 0;
        n->hC8 = 0x300;
        i = rand() & 0x1C00;
        n->bE6 = 0xFF;
        n->bE5 = 0xFF;
        n->bE4 = 0xFF;
        n->bE7 = 0xFF;
        n->hC8 = n->hC8 | i;
        n->fEC = 255.0f;
        n->fF0 = sp->f4;
        n->fF4 = (absf_(((f32)(rand() & 0x7F) - 64.0f) * 0.00390625f) + 0.625f) * n->fF0;
        n->fF8 = 2.0f * n->fF4 - n->fF4;
        n->fD8 = n->fDC = n->fF4 + 0.0001f;
        n->hCA = D_main_bss_80139910[0];
        clearStructPair2C30(s0);
        n->pos[0] = -100.0f;
        n->pos[1] = -100.0f;
        n->pos[2] = -100.0f;
        n->fE8 = absf_(((f32)(rand() & 0x7F) - 64.0f) / 160.0f);
        n->fC = n->fE8 * 16.0f;
        n->fEC = 255.0f - 2.0f * (n->fE8 * 255.0f);
        n->h10C = sp->h8;
        n->h10E = findFreeNpcSlotByKey(0xFFFF, sp->h8);
        if (n->h10E == 0xFFFF) {
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        *(f32 *)((u8 *)n + 0xFC) = sp->f0;
        popNpcSlotFromTail(D_main_bss_80139574, self);
        forwardToNpcGeneratorSpawn(n->h10C, (s32)n->pos2, n->fFC);
        return 1;
    case 2:
        if (n->h10E != 0xFFFF) {
            destroyNpcSlotChain(n->h10E);
        }
        return 1;
    case 3:
        if (getNextSlotNpcTypeId(n->h10E) == 0xFFFF) {
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        n->fE8 = n->fE8 + sp->f0;
        n->fC = n->fE8 * 16.0f;
        n->fEC = 255.0f - 2.0f * (n->fE8 * 255.0f);
        n->fF4 = n->fF4 + 2.0f * (n->fF8 * sp->f0);
        n->fD8 = n->fDC = n->fF0;
        if (n->fE8 <= 0.5f) {
            n->bE7 = (u32)n->fEC;
        } else {
            n->fEC = 255.0f;
            n->fE8 = 0.0f;
            n->fC = 0.0f;
            forwardToNpcGeneratorSpawn(n->h10C, (s32)n->pos2, n->fFC);
            n->fF4 = (absf_(((f32)(rand() & 0x7F) - 64.0f) * 0.00390625f) + 0.625f) * n->fF0;
            n->fF8 = 2.0f * n->fF4 - n->fF4;
            n->fD8 = n->fDC = n->fF4;
        }
        mat34CrossRowsAndCopyPos(m, getNpcContextField8(n->h10C), 1.0f);
        transformVec3ByMat34(m, n->pos2, n->pos);
        return 1;
    case 4:
        setVec3At0x24((void *)((u8 *)n + 0x2C), n->pos[0], n->pos[1], n->pos[2]);
        n->hCA = D_main_bss_80139910[(s32)n->fC % 8];
        if (transformVec3ToNpcLocalWithScale(*(void **)rl, 0, n, 1.0f, 0)) {
            n->link.next = *rl->headp;
            if (n->link.next != 0) {
                (*rl->headp)->prev = &n->link;
            }
            *rl->headp = &n->link;
            n->link.prev = 0;
        }
        break;
    default:
        return 1;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D15C);

extern u8 *D_main_bss_80138D1C;
extern s16 rand(void);
typedef struct { f32 x, y, z; } CamVec3;
extern CamVec3 D_main_8003D15C;

void buildRandomCameraFacingOrientation(Vec3f out, Vec3f dst, f32 scale, s32 range, s32 base, u8 mode) {
    Mat4x3 frame;
    Vec4f q40;
    Vec4f q50;
    Vec4f q60;
    Vec3f v70;
    Vec3f v80;
    Vec3f v90;
    f32 len;
    f32 *axis;
    f32 *tmp;

    extractOrthonormalFrameFromStruct(frame, (void *)(D_main_bss_80138D1C + 0x28));
    if (mode == 0) {
        if (range == 0) {
            quatFromAxisAngle(q40, frame[2], (f32)base);
        } else {
            quatFromAxisAngle(q50, frame[2], (f32)(base + rand() % range));
            quatFromAxisAngle(q60, frame[1], (f32)rand());
            quatMultiply(q60, q50, q40);
        }
        rotateVec3ByQuat(q40, frame[1], dst);
    } else {
        if (range == 0) {
            *(CamVec3 *)v80 = D_main_8003D15C;
            vec3Cross(v70, frame[2], frame[1]);
            vec3Cross(v90, v80, frame[1]);
            len = vec3Length(v90);
            if (len > 0.00001f) {
                v90[0] /= len;
                v90[1] /= len;
                v90[2] /= len;
                vec3Cross(v80, frame[1], v90);
                normalize_vector(v80);
                quatFromAxisAngle(q40, frame[1], -sinfApprox(vec3Dot(v70, v80)) * 57.29578f);
                rotateVec3ByQuat(q40, frame[2], v90);
            }
            vec3Cross(v70, v90, frame[1]);
            if (vec3Length(v70) > 0.00001f) {
                quatFromAxisAngleSafe(q40, v70, (f32)base);
                rotateVec3ByQuat(q40, v90, dst);
            }
        } else {
            quatFromAxisAngle(q50, frame[1], (f32)(base + rand() % range));
            quatFromAxisAngle(q60, frame[2], (f32)rand());
            quatMultiply(q60, q50, q40);
            rotateVec3ByQuat(q40, frame[2], dst);
        }
    }
    if (out != NULL) {
        out[0] = dst[0] * scale;
        out[1] = dst[1] * scale;
        out[2] = dst[2] * scale;
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D170);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnScaledOrientedEffectTriple);

typedef struct { u8 p0[4]; struct HBNode *unk04; u8 p8[0xE]; u16 unk16; } HBSelf;
typedef struct HBNode {
    struct HBNode *next;
    struct HBNode *prev;
    s16 s8;
    s16 sA;
    s16 sC;
    u8 pE[2];
    u16 h10;
    u16 h12;
    u8 p14[8];
    s32 w1C;
    f32 f20;
    f32 f24;
    s16 h28;
    s16 h2A;
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
} HBNode;
typedef struct { f32 x, y, z; } HBVec;
typedef struct {
    HBVec *pos;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
} HBSpawn;
typedef struct {
    f32 dt;
    u8 p4[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 p24[0x24];
    struct { u8 p[0x20]; HBNode *head; } *unk48;
} HBTick;
extern f32 cosf(f32);
extern u8 transformVec3ToNpcLocalWithScale(void *, s32, void *, f32, s32);
extern u16 D_main_bss_80139574;
extern u8 *D_main_bss_80138D1C;
extern u8 *D_main_bss_80130C08;
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);

s32 heavyRandomBurstNpcHandler(void *selfp, u16 action, void *arg2) {
    HBSelf *self = selfp;
    HBNode *n = self->unk04;
    register HBTick *a2 asm("$17");
    HBSpawn *sp = arg2;
    HBTick *tk = arg2;
    f32 dt;
    f32 one;
    f32 pi;
    f32 half;
    f32 v[3];
    f32 *cam;
    f32 *pos;
    f32 m;
    f32 d;

    switch (action) {
    case 1:
        n->h10 = 0x301;
        n->b2C = 0xFF;
        n->b2D = 0xFF;
        n->b2E = 0xFF;
        n->b2F = 0xFF;
        n->sC = 0;
        n->sA = 0;
        n->s8 = 0;
        n->h2A = 0;
        n->h28 = 0;
        n->w1C = 0;
        n->f3C = sp->f4;
        n->f44 = sp->f10;
        n->h12 = *(u16 *)(D_main_bss_80130C08 + 0x20);
        n->f24 = n->f20 = 0.001f;
        *(HBVec *)&n->f30 = *sp->pos;
        n->f60 = 0.0f;
        n->f40 = sp->fC;
        n->f58 = 1.0f;
        n->f5C = 1.0f;
        n->f54 = sp->f8 - sp->f4;
        n->f50 = sp->f1C;
        n->f48 = sp->f14;
        n->f4C = sp->f18;
        d = sp->f20;
        n->f64 = d;
        if (d == 0.0f) {
            n->f64 = 0.033333335f;
        }
        popNpcSlotFromTail(D_main_bss_80139574, self);
        return 1;
    case 2:
        break;
    case 3:
        dt = tk->dt;
        n->f60 = n->f60 + n->f40 * dt;
        one = 1.0f;
        if (n->f60 < one) {
            pi = 3.1415927f;
            half = 0.5f;
            n->f58 = n->f3C + (one - cosf(n->f60 * pi * half)) * n->f54 * (n->f44 * 3.0f) * n->f48;
            n->f5C = n->f3C + (one - cosf(n->f60 * pi * half)) * n->f54 * (n->f44 * 0.25f) * n->f4C;
            n->f20 = n->f58;
            if (n->f20 < 0.001f) n->f20 = 0.001f;
            n->f24 = n->f5C;
            if (n->f24 < 0.001f) n->f24 = 0.001f;
            m = n->f60;
            d = n->f64;
            if (d < m) {
                n->b2F = (u32)((one - m) * (one / d) * 255.0f);
            }
            if (n->f50 > 0.0f) {
                cam = (f32 *)(D_main_bss_80138D1C + 0x28);
                v[0] = cam[9] - n->f30;
                v[1] = cam[10] - n->f34;
                v[2] = cam[11] - n->f38;
                n->f30 = n->f30 + v[0] * n->f50 * dt;
                n->f34 = n->f34 + v[1] * n->f50 * dt;
                n->f38 = n->f38 + v[2] * n->f50 * dt;
            }
        } else {
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        break;
    case 4:
        a2 = arg2;
        __asm__("" : "+r"(a2));
        pos = &n->f30;
        m = n->f5C;
        if (m < n->f58) m = n->f58;
        if (!transformVec3ToNpcLocalWithScale(*(void **)a2, 0, pos, m, 0)) {
            return 1;
        }
        {
            HBNode *head;
            n->s8 = (s32)((n->f30 - a2->f18) * 256.0f);
            n->sA = (s32)((n->f34 - a2->f1C) * 256.0f);
            n->sC = (s32)((n->f38 - a2->f20) * 256.0f);
            head = a2->unk48->head;
            n->next = head;
            if (head != NULL) head->prev = n;
            n->prev = NULL;
            tk->unk48->head = n;
        }
        break;
    default:
        return 1;
    }
    return 1;
}

typedef struct { f32 x, y, z; } BnV3;

void buildNpcAnchoredCameraEffectTransform(u16 id, void *out, s32 dst, f32 scale) {
    Vec3f d;
    Vec3f j;
    Vec3f p;
    Mat4x3 m;
    u8 *cam;
    f32 *ctx;
    f32 len;
    f32 dot2;
    f32 dot3;

    cam = D_main_bss_80138D1C;
    ctx = getNpcContextField8(id);
    d[0] = ctx[0] - *(f32 *)(cam + 0x4C);
    d[1] = ctx[1] - *(f32 *)(cam + 0x50);
    d[2] = ctx[2] - *(f32 *)(cam + 0x54);
    len = vec3Length(d);
    if (len == 0.0f) {
        *(BnV3 *)out = *(BnV3 *)ctx;
        return;
    }
    d[0] /= len;
    d[1] /= len;
    d[2] /= len;
    len = vec3Dot(ctx + 3, d);
    dot2 = vec3Dot(ctx + 6, d);
    vec3Cross(j, ctx + 6, ctx + 3);
    dot3 = vec3Dot(j, d);
    transformLimbStrideAnchorsLocal(id, d, p);
    switch (rand() % 3) {
    case 0:
        j[0] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[0] * 0.5f * scale));
        j[1] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[1] * 0.5f * scale));
        if (len >= 0.0f) {
            j[2] = d[2] * -0.5f * scale;
        } else {
            j[2] = d[2] * 0.5f * scale;
        }
        break;
    case 1:
        j[0] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[0] * 0.5f * scale));
        if (dot2 >= 0.0f) {
            j[1] = d[1] * -0.5f * scale;
        } else {
            j[1] = d[1] * 0.5f * scale;
        }
        j[2] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[2] * 0.5f * scale));
        break;
    case 2:
        if (dot3 >= 0.0f) {
            j[0] = d[0] * -0.5f * scale;
        } else {
            j[0] = d[0] * 0.5f * scale;
        }
        j[1] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[1] * 0.5f * scale));
        j[2] = ((rand() & 0x7F) - 64.0f) / (64.0f / (d[2] * 0.5f * scale));
        break;
    }
    j[0] = p[0] + j[0];
    j[1] = p[1] + j[1];
    j[2] = p[2] + j[2];
    if (dst != 0) {
        *(BnV3 *)dst = *(BnV3 *)j;
    }
    mat34CrossRowsAndCopyPos(m, (void *)ctx, 1.0f);
    transformVec3ByMat34(m, j, out);
}

void computeWalkerLimbStrideTargets(u16 id, f32 *base, f32 *outA, f32 *outB, f32 k) {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 m[12];
    mat34CrossRowsAndCopyPos((void *)m, getNpcContextField8(id), 1.0f);
    transformLimbStrideAnchorsLocal(id, a, b);
    c[0] = b[0] - a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] - a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, base);
    c[0] = b[0] + a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] - a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, c);
    outA[0] = c[0] - base[0];
    outA[1] = c[1] - base[1];
    outA[2] = c[2] - base[2];
    c[0] = b[0] - a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] + a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, c);
    outB[0] = c[0] - base[0];
    outB[1] = c[1] - base[1];
    outB[2] = c[2] - base[2];
}

typedef struct {
    f32 x, y, z;
} ExtrapVec3;

extern s32 D_8010CA20;
extern void distanceAndDopplerNpcHelper(f32 *, f32, f32);
extern void spawnNpcType0xAFromTemplate(f32 *, f32);
extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, s32);

static __inline__ void extrapolateVec3Inline(f32 *src, f32 *out, f32 t) {
    out[0] = src[0] - src[3] * t;
    out[1] = src[1] - src[4] * t;
    out[2] = src[2] - src[5] * t;
}

void extrapolateNpcPositionForCurrentMode(u8 *obj) {
    f32 pos[8];
    f32 *src = *(f32 **)(obj + 8);
    f32 *out;
    f32 k;

    if (src != NULL) {
        if (D_8010CA20 == 0) {
            out = pos;
            k = 0.2f;
            pos[0] = src[0] - src[3] * k;
            out[1] = src[1] - src[4] * k;
            out[2] = src[2] - src[5] * k;
        } else {
            *(ExtrapVec3 *)pos = *(ExtrapVec3 *)src;
        }
        switch (*(u16 *)(obj + 4)) {
        case 12:
            spawnRandomScaleColoredEffectFromCaller(pos, 0.4f, 0.8f, 0);
            return;
        case 8:
        case 9:
            return;
        case 10:
        case 11:
        case 13:
        case 14:
            spawnNpcType0xAFromTemplate(pos, 0.6f);
            return;
        default:
            distanceAndDopplerNpcHelper(pos, 0.05f, 0.2f);
            spawnNpcType0xAFromTemplate(pos, 0.2f);
            return;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D220);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D224);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcPowerGeneratorHandleDestruction);

typedef struct {
    f32 f10;
    ExtrapVec3 p;
    s32 w20;
    f32 f24;
    s32 w28, w2C, w30, w34;
    f32 f38, f3C;
    s32 w40, w44;
    f32 f48;
    s16 h4C, h4E;
    f32 f50;
    s32 w54, w58;
    f32 f5C;
    s32 w60;
    f32 f64, f68;
    s32 w6C, w70, w74, w78;
    s8 b7C, b7D;
    s16 h7E;
    s16 h80, h82, h84;
    s32 w88;
    s16 h8C;
    s16 pad8E;
} DebrisBurstParams;
extern s32 D_main_bss_80130C04;
extern u8 *D_main_bss_80130C08;
extern s32 gCurrentLevel;
extern WaterSprayRec D_main_bss_8013A8C0;
extern s32 spawnRandomBurstNpcVariantWrapper(void *);
extern void attachChildNpcByIndex_l(u16, void *) __asm__("attachChildNpcByIndex");
extern void assignNpcTargetAndPosition(u16, u16, void *, f32);

u16 spawnDirectionalDebrisBurstAnchored(u16 id, f32 *pos, void *target, f32 scale, f32 dir, s32 pal) {
    DebrisBurstParams d;
    u16 npc;
    f32 a, b;

    a = scale * 0.5f;
    b = scale * 3.0f * 0.5f;
    d.f10 = 5.0f;
    d.p = *(ExtrapVec3 *)pos;
    d.w20 = 0;
    d.f24 = -dir;
    d.w28 = 0;
    d.w2C = 0;
    d.w30 = 0;
    d.w34 = 0;
    d.f38 = 1.0f;
    d.f3C = 1.0f;
    d.w40 = 0;
    d.w44 = 0;
    d.f48 = 0.025f;
    d.h4C = 30;
    d.h4E = 30;
    d.f50 = 10.0f;
    d.w54 = 0;
    d.w58 = 0;
    d.f5C = 0.5f;
    d.w60 = 0;
    d.f64 = 0.05f;
    d.f68 = 1.0f;
    d.w6C = 0;
    d.w74 = (s32)D_main_bss_80130C08 + 0x1C;
    d.b7C = 1;
    if (pal == 0) {
        if (gCurrentLevel == 4) {
            d.w78 = D_main_bss_80130C04 + 0xC0;
        } else {
            d.w78 = D_main_bss_80130C04 + 0x80;
        }
        d.b7D = 16;
    } else {
        d.w78 = pal;
        d.b7D = 16;
    }
    d.h80 = (u32)(a * 256.0f + 1.0f);
    d.h82 = (u32)(b * 256.0f + 1.0f);
    d.h84 = 5;
    d.w88 = 0x09000000;
    d.h8C = 3;
    npc = spawnRandomBurstNpcVariantWrapper(&d);
    attachChildNpcByIndex_l(npc, &D_main_bss_8013A8C0);
    assignNpcTargetAndPosition(npc, id, target, 0.0f);
    return npc;
}

typedef struct {
    f32 m[12];
} WkMat;

typedef struct {
    f32 v[4];
} WkQ;

typedef struct {
    f32 x, y, z;
} WkV3;

typedef struct {
    f32 x, y, z;
    f32 fwd[3];
    f32 up[3];
    f32 r24[3];
    f32 x2, y2, z2;
    f32 fwd2[3];
    f32 up2[3];
    f32 r54[3];
    WkV3 c60;
    WkV3 c6C;
    u8 *m78;
    u8 *m7C;
    f32 s80[3];
    f32 g8C, g90, g94;
    u8 rgba[4];
    f32 f9C;
    f32 fA0;
    f32 fA4;
} WkObj;

typedef struct {
    WkMat *mat;
    void *target;
    u8 *col;
    s32 pal;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    u16 h2C;
} WkArgs;

u8 *instantiateNamedMeshInstance(char *);
void applyRgbaTintToMeshVertices(u8 *, u8 *);
void wkFlags(void *, s32, s32, s32) __asm__("applyFlagsToMeshTreeOrList");
s32 wkVis(s32, void *, void *, f32) __asm__("addNpcToVisibilityBucket");

s32 wkImpl(u8 *npc, u16 action, void *arg2) __asm__("npcWakeUpdate");
s32 wkImpl(u8 *npc, u16 action, void *arg2) {
    WkObj *d;
    f32 side[4];
    f32 p[4];
    WkQ q38;
    WkQ q48;
    WkQ q58;

    d = *(WkObj **)(npc + 4);
    switch (action) {
    case 1: {
        WkArgs *a = arg2;
        f32 t;
        f32 c;
        d->m78 = instantiateNamedMeshInstance("wake");
        wkFlags(d->m78, 0, 0x09010000, 0);
        d->m7C = instantiateNamedMeshInstance("wake");
        wkFlags(d->m7C, 0, 0x09010000, 0);
        *(WkMat *)d = *a->mat;
        vec3Cross(side, d->up, d->fwd);
        t = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / a->f10);
        p[0] = d->x + side[0] * t;
        p[1] = d->y + side[1] * t;
        p[2] = d->z + side[2] * t;
        spawnDirectionalDebrisBurstAnchored(a->h2C, p, a->target, a->f24, a->f28, a->pal);
        d->c60 = *(WkV3 *)d->fwd;
        d->c6C = *(WkV3 *)d->up;
        d->x -= side[0] * a->f10;
        d->y -= side[1] * a->f10;
        d->z -= side[2] * a->f10;
        quatFromAxisAngle(q38.v, side, 5.0f);
        quatFromAxisAngle(q48.v, d->fwd, a->f1C);
        quatMultiply(q38.v, q48.v, q58.v);
        q48 = q58;
        quatFromAxisAngle(q58.v, d->up, a->f18);
        quatMultiply(q48.v, q58.v, q38.v);
        rotateVec3ByQuat(q38.v, d->fwd, d->fwd);
        rotateVec3ByQuat(q38.v, d->up, d->up);
        *(WkMat *)&d->x2 = *a->mat;
        d->x2 += side[0] * a->f10;
        d->y2 += side[1] * a->f10;
        d->z2 += side[2] * a->f10;
        quatFromAxisAngle(q38.v, side, 5.0f);
        quatFromAxisAngle(q48.v, d->fwd2, -a->f1C);
        quatMultiply(q38.v, q48.v, q58.v);
        q48 = q58;
        quatFromAxisAngle(q58.v, d->up2, -a->f18);
        quatMultiply(q48.v, q58.v, q38.v);
        rotateVec3ByQuat(q38.v, d->fwd2, d->fwd2);
        rotateVec3ByQuat(q38.v, d->up2, d->up2);
        d->rgba[0] = a->col[0];
        d->rgba[1] = a->col[1];
        d->rgba[2] = a->col[2];
        d->rgba[3] = 0xFF;
        applyRgbaTintToMeshVertices(d->m78, d->rgba);
        applyRgbaTintToMeshVertices(d->m7C, d->rgba);
        d->f9C = *(f32 *)(*(u8 **)d->m78 + 0x44);
        c = 0.2f;
        d->s80[0] = c;
        d->s80[1] = c;
        d->s80[2] = a->f14 * c;
        d->g8C = c;
        d->g90 = c;
        c = 0.4f;
        d->g94 = a->f14 * c;
        d->fA4 = 0.0f;
        *(f32 *)((u8 *)d + 0xA0) = a->f20;
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        return 1;
    }
    case 2:
        releaseMeshAsset(d->m78);
        releaseMeshAsset(d->m7C);
        return 1;
    case 3: {
        f32 dt = *(f32 *)arg2;
        f32 t;
        f32 k;
        t = d->fA4 + dt * d->fA0;
        d->fA4 = t;
        if (t < 1.0f) {
            d->rgba[3] = (u32)(255.0f - t * 255.0f);
            applyRgbaTintToMeshVertices(d->m78, d->rgba);
            applyRgbaTintToMeshVertices(d->m7C, d->rgba);
            d->s80[0] += d->g8C * dt * d->fA0;
            d->s80[1] += d->g90 * dt * d->fA0;
            d->s80[2] += d->g94 * dt * d->fA0;
            k = dt * 0.2f;
            d->y += k;
            d->y2 += k;
        } else {
            destroyNpcSlotByIndex(*(u16 *)(npc + 0x16));
            return 1;
        }
        break;
    }
    case 4:
        mat34CrossRowsAndCopyPosPtr((void *)(d->m78 + 0x28), (void *)d, d->s80);
        wkVis(*(s32 *)arg2, d->m78, d, d->f9C);
        mat34CrossRowsAndCopyPosPtr((void *)(d->m7C + 0x28), (void *)&d->x2, d->s80);
        wkVis(*(s32 *)arg2, d->m7C, &d->x2, d->f9C);
        break;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D2D4);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnGatedDistanceEffectPair);

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
} RandomParticleArgs;

extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, s32);
extern void randomParticleWithParentNpcHandler(void);

void spawnRandomParticleWithParent(void *arg0, s32 arg1, f32 arg2, u8 arg3) {
    RandomParticleArgs args;

    if (arg0 != NULL) {
        spawnRandomScaleColoredEffectFromCaller(arg0, arg2, arg2 + arg2, 0);
    }
    if (arg3) {
        args.unk8 = arg1;
        args.unk4 = arg2;
        args.unk0 = 0.6f;
        spawnNpcOfType(randomParticleWithParentNpcHandler, &args, 4, 10);
    }
}

extern f32 vec3Length(Vec3f);
extern u8 *D_main_bss_80138D1C;

f32 distanceFromCameraToPoint(f32 *arg0) {
    Vec3f d;
    u8 *cam = D_main_bss_80138D1C + 0x28;

    d[0] = arg0[0] - *(f32 *)(cam + 0x24);
    d[1] = arg0[1] - *(f32 *)(cam + 0x28);
    d[2] = arg0[2] - *(f32 *)(cam + 0x2C);
    return vec3Length(d);
}

static __inline__ u16 spawnHeavyBurstInline(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

u16 spawnEffectNpcWithRampedScale(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    return spawnHeavyBurstInline(arg0, arg1, arg2, arg3, 1.3333334f, 1.0f, 1.0f, 3.0f, 0.5f, arg4);
}

u16 spawnEffectNpcWithRampedScaleExt(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

void vec3ExtrapolateFirstOrder(f32 *arg0, s32 arg1, f32 *arg2, f32 arg3) {
    arg2[0] = arg0[0] - arg0[3] * arg3;
    arg2[1] = arg0[1] - arg0[4] * arg3;
    arg2[2] = arg0[2] - arg0[5] * arg3;
}

extern void buildNpcAnchoredCameraEffectTransform(u16, void *, s32, f32);

void buildNpcAnchoredCameraEffectTransformWrapper(u16 arg0, void *arg1, f32 arg2) {
    buildNpcAnchoredCameraEffectTransform(arg0, arg1, 0, arg2);
}

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    s16 unk1C;
    s16 unk1E;
} WaterSprayArgs;

extern u8 *getNpcContextByIndex(u16);
extern u8 D_main_bss_8013A944;
extern void npcWaterSprayUpdate(void);

u16 spawnWaterSprayNpc(s32 arg0, s32 arg1) {
    WaterSprayArgs args;
    u16 id = arg0;

    if (D_main_bss_8013A944 != 0) {
        args.unk1C = id;
        args.unk0 = arg1;
        args.unk1E = 0;
        return spawnNpcOfType(npcWaterSprayUpdate, &args, 1, getNpcContextByIndex(id)[0x19] + 1);
    }
    return 0xFFFF;
}

void spawnOrientedEffectIfBudgetOkAlt(f32 *, f32 *, s32, f32, f32, f32);
typedef struct { f32 *vec; void *parent; u8 pad8[4]; f32 f24c; f32 f28c; f32 pad2C; f32 f30c; u16 s34; s16 s36; } WsArgs;
void spawnDistanceScaledDebrisBurst(void *, f32, f32);
extern f32 D_main_bss_80136FA8;
void spawnWaterSprayDebrisAndBurst(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    WsArgs a;
    f32 v[3];
    if (D_main_bss_8013A944 != 0) {
        a.s34 = 0xFFFF;
        v[1] = arg3;
        a.s36 = 2;
        a.parent = arg0;
        v[0] = arg1;
        v[2] = arg1;
        a.vec = v;
        a.f30c = arg4;
        a.f28c = 1.0f / arg5;
        a.f24c = arg2 - arg1;
        spawnNpcOfType(npcWaterSprayUpdate, &a, 1, 0xF);
        spawnDistanceScaledDebrisBurst(arg0, arg2 * 0.75f, arg4 * 0.4f);
        v[0] = arg0[0];
        v[1] = (arg0[1] - D_main_bss_80136FA8) - 0.05f;
        v[2] = arg0[2];
        spawnOrientedEffectIfBudgetOkAlt(v, 0, 0, arg1 * 0.3f, arg2 * 0.6f, arg5 * 2.2f);
    }
}

typedef struct {
    u8 *parent;
    s32 unk4;
    void *unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
} WakeTrailArgs;

extern u8 D_main_800A0D70[];
extern void npcWakeUpdate(void);

void spawnSpeedGatedTrailEffect(s16 arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8) {
    WakeTrailArgs args;

    if (D_main_bss_8013A944 != 0 && arg5 > 0.0f && vec3Length((f32 *)(arg1 + 0x24)) > 0.0f) {
        args.parent = arg1;
        args.unk14 = arg5;
        args.unk18 = arg3;
        args.unk2C = arg0;
        args.unkC = 0;
        args.unk1C = arg4;
        args.unk4 = arg7;
        args.unk24 = arg8;
        args.unk8 = D_main_800A0D70;
        args.unk20 = 1.0f / arg6;
        args.unk28 = 0.3f;
        args.unk10 = arg2 * 0.5f;
        spawnNpcOfType(npcWakeUpdate, &args, 2, 15);
    }
}

void forwardToNpcGeneratorSpawn(u16 arg0, s32 arg1, f32 arg2) {
    Vec3f out;

    buildNpcAnchoredCameraEffectTransform(arg0, out, arg1, arg2);
}

typedef struct { f32 x, y, z; } PgBlk;
typedef struct { f32 f[12]; char name[4]; } PgHs;
typedef struct {
    f32 pos[3];
    f32 rot[6];
    f32 vel[3];
    u8 *mesh;
    f32 mat[12];
    u8 *beam;
    u8 *rec;
    s32 obj;
    u8 *n0;
    u8 *n1;
    u8 *n2;
    u8 *nc[8];
    u8 *m0;
    u8 *m1;
    u8 *m2;
    u8 *mc[8];
    f32 sc[3];
    s32 health[8];
    u16 slot[8];
    u16 fx[2];
    u16 deb[2];
    PgBlk debData[2];
    u8 a124;
    u8 state;
    s16 count;
    f32 radius;
    f32 scale;
    f32 a130;
    f32 a134;
    f32 a138;
    f32 t;
    f32 ease;
    u16 s144;
    u16 s146;
    u16 s148;
    u16 s14A;
    s32 cnt;
    u8 audio[0x88];
    u8 audioOn;
    u8 pad1D9[3];
    u8 dat[0x38];
} PgObj;
extern u16 D_main_bss_80139560[];
extern u8 D_main_bss_80130BA0;
u16 pgPop(u16, void *) __asm__("popNpcSlotFromTail");
u8 *pgWalk(char *) __asm__("walkMeshdef0List");
void *rs_malloc(u32, u16);
void applyFlagsToMeshTreeOrList(void *, s32, s32, s32);
u8 *lookupHmtMaterialByName(void *, char *, void *);
u16 spawnInheritedNpcVariantC(u16, char *, s32);
void pgTex(void *, char *, s32, void *, s32, s32) __asm__("lookupHmtTextureByName");
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void createAndInitObject(void *, s32, void *, void *, s32);
void initSpawnedNpcHealthAndDetail(void *);
void spawnNpcWithRandomRotation(void *);
s32 sprintf(char *, const char *, ...);
u16 spawnHeavyMechSubEffect(void *, void *, char *);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void factor5RemoveListNode(void *);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void walkDatTreeAndCollectSubtypes(void *, void *);
void npcPowerGeneratorHandleDestruction();
f32 quadraticEaseInOut(f32);
f32 floatModulo(f32, f32);
void spawnDebrisBurstFromTemplate(void *, s32);
s32 isNpcWithinActiveReferenceRange(void *);
void walkDatTreeAndScaleLeafByFloat(void *, void *, f32);
void destroyObjectOwnedNpcSlot(s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
s32 getNpcCurrentHealth(s32);
extern u8 D_main_bss_80130B39;
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void spawnOrientedNpc(s32, void *, s32, s32, f32, f32, f32, f32);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void setObjectFlagBit4(void *);
void dispatchSlotAction5IfActive(void *, void *);
#define PG_JOINT_HEAD(mm, nn) \
    m = (mm); \
    n = (nn) + 0x1C; \
    clearVec4QuadStruct((void *)n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24((void *)n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4((void *)n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4((void *)n, (void *)(m + 0x68)); \
    }
#define PG_JOINT_TAIL() \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } }

static __inline__ u8 pgAlive(PgObj *s2) {
    if (D_main_bss_80130B39 == 0) {
        return getNpcCurrentHealth(s2->obj) > 0;
    }
    return 1;
}

s32 func_main_80077AF0(u8 *arg0, u16 action, u8 *arg2) {
    union {
        struct { char nm[12]; s32 pad; PgHs hs; s32 pad2; char buf[16]; } c1;
        struct { char pad[0x10]; f32 v[3]; } c4;
        struct { char pad[0x20]; PgHs hs; s32 pad2; f32 m[12]; char nm[4]; } c5;
    } u;
    PgObj *s2 = *(PgObj **)(arg0 + 4);

    switch (action) {
    case 1:
        {
            u8 *rec = arg2;
            f32 inv;
            s32 i;
            s2 = rs_malloc(0x214, 0);
            *(PgObj **)(arg0 + 4) = s2;
            *(u16 *)(arg0 + 0x14) |= 0x100;
            s2->rec = rec;
            s2->mesh = pgWalk(*(char **)(rec + 0x5C));
            s2->beam = pgWalk("engybeam");
            applyFlagsToMeshTreeOrList(s2->beam, 0, 0x10000, 0);
            s2->pos[0] = *(f32 *)(rec + 0x10);
            s2->pos[1] = *(f32 *)(rec + 0x14);
            s2->pos[2] = *(f32 *)(rec + 0x18);
            composeEulerRotationXYZ((void *)s2, *(f32 *)(rec + 0x1C), *(f32 *)(rec + 0x20), *(f32 *)(rec + 0x24));
            s2->vel[0] = s2->vel[1] = s2->vel[2] = 0.0f;
            inv = 1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34);
            s2->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs((void *)(s2->mesh + 0x28), inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
            composeRotationMatrixSlot0((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x1C));
            composeRotationMatrixSlot1((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x20));
            composeRotationMatrixSlot2((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x24));
            addVec3At0x24((void *)(s2->mesh + 0x28), s2->pos[0], s2->pos[1], s2->pos[2]);
            *(PgObj **)(arg0 + 8) = s2;
            *(u8 **)(arg0 + 0xC) = s2->mesh;
            s2->n0 = lookupHmtMaterialByName(s2->mesh, "base", &s2->m0);
            s2->n1 = lookupHmtMaterialByName(s2->mesh, "maintrns", &s2->m1);
            s2->n2 = lookupHmtMaterialByName(s2->mesh, "top_top", &s2->m2);
            {
                __builtin_memcpy(u.c1.nm, "cb_trns1", 9);
                for (i = 0; i < 8; i++) {
                    s2->nc[i] = lookupHmtMaterialByName(s2->mesh, u.c1.nm, &s2->mc[i]);
                    u.c1.nm[7]++;
                }
            }
            {
                __builtin_memcpy(u.c1.nm, "cb1", 4);
                for (i = 0; i < 8; i++) {
                    s2->slot[i] = spawnInheritedNpcVariantC(*(u16 *)(arg0 + 0x16), u.c1.nm, 0);
                    u.c1.nm[2]++;
                }
            }
            pgTex(s2->mesh, "03", 0, s2->mat, 0, 0);
            s2->mat[6] = -s2->mat[6];
            s2->mat[7] = -s2->mat[7];
            s2->sc[0] = s2->scale * 1.8f;
            s2->mat[8] = -s2->mat[8];
            s2->sc[1] = 1.5f;
            s2->sc[2] = s2->scale * 1.8f;
            { /*B1*/
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o = 0x12;
                if (*(s32 *)(rec + 0x8C) == 1) {
                    o = 0xE;
                }
                s2->s148 = pgPop(*(u16 *)(o + b), arg0);
                if (*(s32 *)(rec + 0x90) != 0) {
                    s32 o2 = 0x18;
                    if (*(s32 *)(rec + 0x8C) == 1) {
                        o2 = 0x1A;
                    }
                    s2->s14A = pgPop(*(u16 *)(o2 + b), arg0);
                } else {
                    s2->s14A = 0xFFFF;
                }
            }
            {
                u8 *b;
                s32 t;
                s32 o;
                __asm__("la %0, D_main_bss_80139560" : "=r"(b));
                s2->s144 = pgPop(*(u16 *)(b + 0x1C), arg0);
                t = *(s32 *)(rec + 0x8C);
                o = (t == 1) ? 0x26 : (t == 0) ? 0x28 : 0x2A;
                s2->s146 = pgPop(*(u16 *)(b + o), arg0);
            } /*B2*/
            s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * s2->scale;
            s2->a130 = 0.0f;
            s2->a134 = 0.0f;
            s2->a138 = 0.0f;
            s2->t = 0.0f;
            s2->ease = 0.0f;
            s2->a124 = 0;
            s2->count = 0;
            s2->cnt = 0;
            s2->deb[0] = s2->deb[1] = s2->fx[0] = s2->fx[1] = 0xFFFF;
            s2->audioOn = 1;
            play3DSoundEventVariant(s2->audio, s2, s2->vel, 14.0f, 0.6f, 7, 0x14, 1, 0x7F, 0x3C);
            if (D_main_bss_80130B39 == 0) {
                createAndInitObject(&s2->obj, 0, arg0, initSpawnedNpcHealthAndDetail, 0);
            } else {
                s2->state = 0;
                if (D_main_bss_80130BA0 != 0) {
                    for (i = 0; i < 7; ) {
                        s32 j;
                        s2->health[i] = -1;
                        u.c1.hs.name[0] = 'c';
                        u.c1.hs.name[1] = 'b';
                        u.c1.hs.name[2] = i + '1';
                        u.c1.hs.name[3] = 0;
                        spawnNpcWithRandomRotation(&u.c1.hs);
                        j = i + 1;
                        u.c1.hs.f[6] = 0.0f;
                        sprintf(u.c1.buf, "cb_trns%d", j);
                        spawnHeavyMechSubEffect(&u.c1.hs, arg0, u.c1.buf);
                        destroyNpcSlotByIndex(s2->slot[i]);
                        s2->slot[i] = 0xFFFF;
                        i = j;
                    }
                    s2->health[7] = 1;
                    s2->count = 7;
                }
            }
            dispatchDatSubtypeByRandomIndex(s2->dat, s2->mesh);
            return 1;
        }
    case 2:
        if (s2->audioOn == 1) {
            s2->audioOn = 0;
            factor5RemoveListNode(s2->audio);
        }
        if (D_main_bss_80130B39 == 0) {
            initActorRenderDescriptorIfUninit(s2->obj, s2->state == 1, s2->rec, 0, s2->rec + 0x70);
            clearPendingAndDestroyChildNpc(&s2->obj);
        }
        walkDatTreeAndCollectSubtypes(s2->dat, s2->mesh);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        {
            f32 dt = *(f32 *)arg2;
            f32 d;
            npcPowerGeneratorHandleDestruction();
            switch (s2->state) {
            case 0:
                d = *(f32 *)(s2->rec + 0x94) * dt * 30.0f;
                s2->a134 = floatModulo(s2->a134 + d, 360.0f);
                s2->a130 = floatModulo(s2->a130 - d, 360.0f);
                s2->a138 = floatModulo(s2->a138 + (d + d), 360.0f);
                break;
            case 1:
                {
                    f32 e;
                    s2->t = s2->t + dt / 1.5f;
                    if (s2->t > 1.0f) {
                        s2->t = 1.0f;
                    }
                    e = quadraticEaseInOut(s2->t);
                    s2->ease = e;
                    d = *(f32 *)(s2->rec + 0x94) * dt * 30.0f * (1.0f - e);
                    s2->a134 = floatModulo(s2->a134 + d, 360.0f);
                    s2->a130 = floatModulo(s2->a130 - d, 360.0f);
                    if (s2->deb[0] != 0xFFFF) {
                        s2->debData[0].y -= 6.0f;
                        spawnDebrisBurstFromTemplate(s2, 0);
                    }
                    if (s2->deb[1] != 0xFFFF) {
                        spawnDebrisBurstFromTemplate(s2, 1);
                    }
                    if (s2->a124 == 2) {
                    destroy:
                        destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                        return 1;
                    }
                }
                break;
            }
            if (*(s32 *)(s2->rec + 0x88) == 0) {
                s2->cnt = 0;
            } else if (isNpcWithinActiveReferenceRange(s2) != 0) {
                s2->cnt = 0;
            } else if (++s2->cnt >= 0x15) {
                goto destroy;
            }
            if (s2->dat[0] != 0xFF) {
                walkDatTreeAndScaleLeafByFloat(s2->dat, s2->mesh, *(f32 *)arg2);
            }
            if (D_main_bss_80130B39 == 0) {
                destroyObjectOwnedNpcSlot(s2->obj);
                return 1;
            }
            return 1;
        }
    case 4:
        {
            u8 *a4 = arg2;
            s32 i;
            u8 *m;
            u8 *n;
            PG_JOINT_HEAD(s2->m0, s2->n0)
            composeRotationMatrixSlot1((void *)n, s2->a134);
            PG_JOINT_TAIL()
            PG_JOINT_HEAD(s2->m1, s2->n1)
            composeRotationMatrixSlot1((void *)n, s2->a130);
            PG_JOINT_TAIL()
            PG_JOINT_HEAD(s2->m2, s2->n2)
            addVec3At0x24((void *)n, 0.0f, s2->ease + s2->ease, 0.0f);
            PG_JOINT_TAIL()
            for (i = 0; i < 8; i++) {
                if (s2->health[i] > 0) {
                    PG_JOINT_HEAD(s2->mc[i], s2->nc[i])
                    composeRotationMatrixSlot1((void *)n, s2->a138);
                    PG_JOINT_TAIL()
                }
            }
            mat34CrossRowsAndCopyPos((void *)(s2->mesh + 0x28), (void *)s2, s2->scale);
            if (addNpcToVisibilityBucket(*(s32 *)a4, s2->mesh, s2, s2->radius) != 0 && s2->dat[0] != 0xFF) {
                walkDatTreeAndVisitChildren(s2->dat, s2->mesh, a4);
            }
            pgTex(s2->mesh, "03", 0, s2->mat, 0, 0);
            s2->mat[6] = -s2->mat[6];
            s2->mat[7] = -s2->mat[7];
            s2->mat[8] = -s2->mat[8];
            u.c4.v[0] = s2->sc[0] * (1.0f - s2->ease);
            u.c4.v[1] = s2->sc[1] * (1.0f - s2->ease);
            u.c4.v[2] = s2->sc[2] * (1.0f - s2->ease);
            if (u.c4.v[1] > 0.0f) {
                mat34CrossRowsAndCopyPosPtr((void *)(s2->beam + 0x28), (void *)s2->mat, u.c4.v);
                addNpcToVisibilityBucket(*(s32 *)a4, s2->beam, s2->mat, s2->radius);
            }
            for (i = 0; i < 2; i++) {
                if (s2->fx[i] != 0xFFFF) {
                    slotDispatcherIter(s2->fx[i], 0xE, arg2);
                }
            }
            if (s2->audioOn != 0) {
                updateActive3DAudioSource(s2->audio, s2, s2->vel, 0x7F);
                return 1;
            }
        }
        break;
    case 5:
        {
            u8 *a5 = arg2;
            s32 idx;
            s32 alive = pgAlive(s2);
            if (alive == 1) {
                u8 *msg;
                u8 *nm;
                u8 c0;
                u8 c1;
                extrapolateNpcPositionForCurrentMode(a5);
                msg = *(u8 **)(a5 + 8);
                if (msg != NULL && (nm = *(u8 **)(msg + 0x24)) != NULL && (c0 = nm[0]) == 'c' && (c1 = nm[1]) == 'b' && nm[2] == '_') {
                    u8 c7 = nm[7];
                    idx = c7 - '1';
                    if (s2->health[idx] > 0) {
                        play3DSoundEvent(0, s2, s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x78, 0x3C);
                        if ((s2->health[idx] -= *(u16 *)(a5 + 6)) <= 0) {
                            u.c5.nm[0] = c0;
                            u.c5.nm[1] = c1;
                            u.c5.nm[2] = c7;
                            u.c5.nm[3] = 0;
                            pgTex(s2->mesh, u.c5.nm, 0, u.c5.m, 0, 0);
                            spawnOrientedNpc(2, u.c5.m, 0, 0, s2->scale * 1.3f, s2->scale * 1.9f, 0.8f, 0.6f);
                            spawnOrientedNpc(2, u.c5.m, 0, 0, s2->scale * 1.1f, s2->scale + s2->scale, 0.8f, 0.5f);
                            spawnOrientedNpc(3, u.c5.m, 0, 0, s2->scale * 0.9f, s2->scale * 2.2f, 0.8f, 0.45f);
                            spawnNpcType0xAFromTemplate(u.c5.m, s2->scale * 4.0f);
                            play3DSoundEvent(0, s2, s2->vel, 24.0f, 0.6f, 0, 0x23, 0x7D, 0x50);
                            if (s2->slot[idx] != 0xFFFF) {
                                destroyNpcSlotByIndex(s2->slot[idx]);
                            }
                            s2->slot[idx] = 0xFFFF;
                            spawnNpcWithRandomRotation(&u.c5.hs);
                            u.c5.hs.f[6] = 0.0f;
                            spawnHeavyMechSubEffect(&u.c5.hs, arg0, (char *)nm);
                            if (++s2->count == 8) {
                                s2->state = alive;
                                spawnNpcWithRandomRotation(&u.c5.hs);
                                u.c5.hs.f[8] = 0.0f;
                                u.c5.hs.f[9] = 0.0f;
                                u.c5.hs.f[10] = 0.0f;
                                u.c5.hs.f[4] = 0.5f;
                                u.c5.hs.f[2] = -0.5f;
                                u.c5.hs.f[3] = -2.8f;
                                u.c5.hs.f[5] = 2.4f;
                                u.c5.hs.f[11] = 5.0f;
                                u.c5.hs.f[6] = 2.5f;
                                s2->fx[0] = spawnHeavyMechSubEffect(&u.c5.hs, arg0, "maintrns");
                                u.c5.hs.f[4] = 0.9f;
                                u.c5.hs.f[5] = 1.3f;
                                u.c5.hs.f[2] = 0.2f;
                                u.c5.hs.f[3] = 0.2f;
                                u.c5.hs.f[11] = 45.0f;
                                u.c5.hs.f[6] = 3.4f;
                                s2->fx[1] = spawnHeavyMechSubEffect(&u.c5.hs, arg0, "base");
                                if (D_main_bss_80130B39 == 0) {
                                    unregisterAndFreeNpcSlot(s2->s146, arg0);
                                    unregisterAndFreeNpcSlot(s2->s148, arg0);
                                    if (s2->s14A != 0xFFFF) {
                                        unregisterAndFreeNpcSlot(s2->s14A, arg0);
                                    }
                                    pgPop(D_main_bss_80139574, arg0);
                                    {
                                        u8 *r = s2->rec;
                                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s2->rec + 0x84));
                                    }
                                    tallyMidDetailObject(arg0);
                                    setObjectFlagBit4(arg0);
                                }
                                if (s2->audioOn == 1) {
                                    s2->audioOn = 0;
                                    factor5RemoveListNode(s2->audio);
                                }
                            }
                        }
                    }
                } else {
                    play3DSoundEvent(0, s2, s2->vel, 18.0f, 0.4f, 0, 0x2A, 0x78, 0x3C);
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
            return 1;
        }
    case 15:
        {
            u16 *msg = (u16 *)arg2;
            s32 i;
            for (i = 0; i < 2; i++) {
                if (s2->fx[i] == msg[0]) {
                    s2->deb[i] = s2->fx[i];
                    s2->debData[i] = *(PgBlk *)(msg + 2);
                    msg[0] = 0xFFFF;
                    return 1;
                }
            }
            return 1;
        }
    case 7:
        if (D_main_bss_80130B39 == 0) {
            dispatchSlotAction5IfActive(arg0, arg2);
        }
        break;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D448);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D454);

#include "main/700B0.h"
typedef struct {
    f32 x, y, z;
} DebrisVec3;
extern char D_main_8003D448[];
extern char D_main_8003D454[];
extern void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
extern void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
extern void spawnOrientedNpc_sdbt(s32, void *, void *, void *, f32, f32, f32, f32) __asm__("spawnOrientedNpc");
extern void spawnNpcType0xAFromTemplate(f32 *, f32);

static __inline__ f32 avabs(f32 x) { f32 r; __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(x)); return r; }
void spawnDebrisBurstFromTemplate_(u8 *base, u8 idx) __asm__("spawnDebrisBurstFromTemplate");
void spawnDebrisBurstFromTemplate_(u8 *base, u8 idx) {
    f32 pos[3];
    f32 vel[3];
    DebrisVec3 v40;
    char name[4];
    u8 i;
    register u8 *e asm("$16");
    f32 *e2;
    u8 *e3;
    f32 *pv;
    f32 a;
    f32 b;
    f32 t;

    i = 0;
    pv = vel;
    {
        register s32 off asm("$2") = idx * 12;
        e = (u8 *)(off + (s32)base);
    }
    e2 = (f32 *)(e + 0x10C);
    v40 = *(DebrisVec3 *)D_main_8003D448;
    __builtin_memcpy(name, D_main_8003D454, 4);
    do {
        composeRandomRotationMatrix(pos, pv, 1.5f, 0x78, 0, 0);
        pos[0] = *(f32 *)(e + 0x10C) + pos[0];
        pos[1] = e2[1] + pos[1];
        pos[2] = e2[2] + pos[2];
        scaleVec3ByRandomRange(pv, 2.0f, 4.0f);
        t = ((f32)(rand() & 0x7F) - 64.0f) / 12.8f;
        a = avabs(t) + 12.0f;
        t = ((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f;
        b = (avabs(t) + 1.0f) * 3.0f + 6.0f;
        t = ((f32)(rand() & 0x7F) - 64.0f) / 320.0f;
        spawnDebris1Npc(pos, pv, a, b, (avabs(t) + 0.6f) * 1.5f);
        if (i & 1) {
            composeRandomRotationMatrix(pos, pv, 5.0f, 0x78, 0, 0);
            scaleVec3ByRandomRange(pos, 0.25f, 1.5f);
            pos[0] = *(f32 *)(e + 0x10C) + pos[0];
            pos[1] = e2[1] + pos[1];
            pos[2] = e2[2] + pos[2];
            spawnNpcType0xAFromTemplate(pos, ((f32)(rand() & 0x7F) - 64.0f) * 0.0625f + 10.0f);
        }
        i++;
    } while (i < 12);
    e3 = base + (idx * 12 + 0x10C);
    spawnOrientedNpc_sdbt(0, e3, &v40, name, 0.5f, 15.0f, 1.5f, 0.5f);
    spawnOrientedNpc_sdbt(0, e3, &v40, name, 0.5f, 14.0f, 1.5f, 1.0f);
    spawnOrientedNpc_sdbt(0, e3, &v40, name, 0.5f, 13.0f, 1.5f, 1.5f);
    spawnOrientedNpc_sdbt(2, e3, &v40, name, 0.5f, 12.0f, 0.75f, 0.25f);
    {
        u8 *b2 = base + idx * 2;
        destroyNpcSlotByIndex(*(u16 *)(b2 + 0x108));
        *(u16 *)(b2 + 0x108) = 0xFFFF;
        *(u16 *)(b2 + 0x104) = 0xFFFF;
    }
    base[0x124]++;
}

typedef struct {
    u8 pad0[0x6C];
    s32 health[8];
    u8 pad8C_[0x8C - 0x6C - 0x20];
} NpcDefHealth;

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern s32 D_main_bss_80137CE4;

void initSpawnedNpcHealthAndDetail(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    s32 i;

    *(u8 *)(npc + 0x125) = 0;
    for (i = 0; i < 8; i++) {
        ((s32 *)(npc + 0xD4))[i] = D_main_bss_80137CE4[(*(NpcDefHealth **)(npc + 0x68))->health];
    }
    setNpcHealth(*(s32 *)(npc + 0x6C), (*(NpcDefHealth **)(npc + 0x68))->health, *(NpcDefHealth **)(npc + 0x68));
    setObjectDetailLevel(*(s32 *)(npc + 0x6C), *(s32 *)(*(u8 **)(npc + 0x68) + 0x8C));
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", fake_func_80079278);
