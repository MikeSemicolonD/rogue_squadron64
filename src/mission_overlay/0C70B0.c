#include "common.h"
#include "common_types.h"

typedef struct {
    s32 name;
    u8 type;
    u8 pad5[3];
} HangarDisplayItem;

extern HangarDisplayItem *D_mission_overlay_8010A420[];
extern f32 D_mission_overlay_8010A204[][4];
extern s32 findNamedEntryInCurrentObject(s32);
extern void findHudElementExtremes(void *, s32, s32);

typedef struct {
    u8 pad0[0x1C8];
    f32 timers[6];
} HangarDisplayState;

void initHangarDisplayItemTimers(u8 *obj, u8 idx) {
    u8 i;
    s32 e;

    if (D_mission_overlay_8010A420[idx] != NULL) {
        obj[0x1E0] = 0;
        for (i = 0; D_mission_overlay_8010A420[idx][i].name != 0; i++) {
            e = findNamedEntryInCurrentObject(D_mission_overlay_8010A420[idx][i].name);
            if (e != 0) {
                findHudElementExtremes(obj + (obj[0x1E0] * 0x48 + 0x18), e, 1);
                ((HangarDisplayState *)obj)->timers[obj[0x1E0]] = D_mission_overlay_8010A204[D_mission_overlay_8010A420[idx][obj[0x1E0]].type][0];
                *(obj[0x1E0] + obj + 0x1E1) = 0;
                obj[0x1E0]++;
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6880);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A688C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6894);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A689C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68A4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68AC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68B4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68BC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68C4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68CC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68D4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68E4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68EC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68FC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6904);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C70B0", tickHangarDisplayItemAnimations);

typedef struct {
    s32 m[12];
} HvMat;

typedef struct HvLink {
    struct HvLink *next;
    struct HvLink *prev;
} HvLink;

typedef struct {
    u8 pad0[0xC];
    HvLink link;
    u8 pad14[0x28 - 0x14];
    HvMat mtx;
} HvMesh;

typedef struct {
    HvMesh *mesh;
    s32 idx;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
} HvState;

typedef struct {
    u8 pad0[4];
    HvState *state;
} HvNpc;

typedef struct {
    f32 dt;
    u8 pad4[8];
    HvLink **head;
} HvCtx;

typedef struct {
    u8 pad0[6];
    u16 m6;
    u8 pad8[0x20 - 8];
    u16 m20;
    u8 pad22[2];
} HvHud;

typedef struct {
    u8 pad0[0x58];
    f32 f58;
    f32 f5C;
    f32 f60;
    u8 pad64[4];
    f32 f68;
    f32 f6C;
    u8 pad70[0x5D0 - 0x70];
} HvCam;

typedef struct {
    u8 pad0[4];
    u16 *p4;
    u8 pad8[0x144 - 8];
} HvView;

typedef struct {
    u8 pad0[0xC];
    s32 flags[1];
} HvSettings;

typedef struct {
    u8 pad0[0x184];
    u16 flags;
    u8 pad186[0x2A0 - 0x186];
} HvPlayer;

extern s32 D_mission_overlay_8010A0FC[];
extern f32 D_mission_overlay_8010A120[];
extern f32 D_mission_overlay_8010A090[][3];
extern f32 D_mission_overlay_8010A1D4[];
extern f32 D_mission_overlay_8010A1B0[];
extern f32 D_mission_overlay_8010A1F8;
extern f32 D_mission_overlay_8010A1FC;
extern f32 D_mission_overlay_8010A200;
extern s32 *D_mission_overlay_8010C090;
extern u16 D_main_bss_80139574;
extern HvMat D_main_bss_8013800C[] __asm__("D_main_bss_8013800C");
extern HvCam sHvCams[] __asm__("D_main_bss_80138268");
extern HvView sHvViews[] __asm__("D_main_bss_80138D18");
extern HvSettings sHvSettings __asm__("gGameSettings");
extern HvPlayer sHvPlayers[] __asm__("gPlayers");
extern HvHud sHvHud[] __asm__("D_mission_overlay_8010BE18");
extern u16 sHvBtn[][3] __asm__("D_main_bss_80130B88");
extern f32 sHvStick[][2] __asm__("D_mission_overlay_8010BDD8");
extern void *rs_malloc(s32, s32);
extern s32 getPlayerVehicleId(s32);
extern HvMesh *walkMeshdef0List(s32);
extern void clearVec4QuadStruct(void *);
extern void popNpcSlotFromTail(u16, void *);
extern void applyFlagsToMeshTreeOrList(HvMesh *, s32, s32, s32);
extern void releaseMeshAsset(HvMesh *);
extern void scaleVec3ByScalar(f32 *, f32, f32 *);
extern void transformVec3ByMat34(HvMat *, f32 *, f32 *);
extern void initVec4TripletFromArgs(HvMat *, f32, f32, f32);
extern void mat3x4Multiply(HvMat *, HvMat *, HvMat *);
extern s32 func_mission_overlay_800FEECC(void);
extern s32 getHudSecondaryWeponCount(void);
extern void initHangarDisplayItemTimers(u8 *, u8);
extern void tickHangarDisplayItemAnimations(HvState *, u8, f32);

static __inline__ f32 hvAbs(f32 x) {
    f32 r;
    __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(x));
    return r;
}

s32 hangarVehicleDisplayNpcHandler(HvNpc *npc, u16 msg, HvCtx *ctx) {
    f32 v10[3];
    f32 v20[3];
    f32 v30[3];
    HvMat m;
    HvMat sc;
    HvState *s;
    f32 scale;
    f32 stick;
    f32 t;
    f32 lim;
    HvCam *cam;
    s32 idx;
    u16 btn;
    HvHud *hud;
    HvCtx *c3 = ctx;
    HvCtx *c4;

    s = npc->state;
    switch (msg) {
    case 1:
        s = rs_malloc(0x1E8, 0);
        npc->state = s;
        s->idx = ctx->dt;
        s->mesh = walkMeshdef0List(D_mission_overlay_8010A0FC[getPlayerVehicleId(s->idx)]);
        clearVec4QuadStruct(&s->mesh->mtx);
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        applyFlagsToMeshTreeOrList(s->mesh, 0, 0x10008, 0);
        s->f14 = 0.0f;
        D_mission_overlay_8010C090 = (s32 *)s;
        s->f8 = 0.0f;
        s->fC = 0.0f;
        s->f10 = 0.0f;
        D_mission_overlay_8010A200 = s->f14;
        clearVec4QuadStruct(&s->mesh->mtx);
        initHangarDisplayItemTimers((u8 *)s, getPlayerVehicleId(s->idx));
        break;
    case 2:
        releaseMeshAsset(s->mesh);
        break;
    case 3:
        D_mission_overlay_8010A200 = s->f14;
        scale = D_mission_overlay_8010A120[getPlayerVehicleId(s->idx)];
        scaleVec3ByScalar(v10, scale, D_mission_overlay_8010A090[getPlayerVehicleId(s->idx)]);
        m = D_main_bss_8013800C[s->idx * 14];
        switch (getPlayerVehicleId(s->idx)) {
        case 1:
            break;
        case 5:
            v20[0] = v10[0];
            v20[1] = 0.0f;
            v20[2] = 0.0f;
            transformVec3ByMat34(&m, v20, v30);
            ((f32 *)&m)[9] = v30[0];
            ((f32 *)&m)[10] = v30[1];
            ((f32 *)&m)[11] = v30[2];
            break;
        }
        idx = s->idx;
        if (sHvPlayers[idx].flags & 1) {
            btn = sHvBtn[idx][0];
            { HvHud *h = sHvHud; hud = &h[idx]; }
            if (!(btn & hud->m20) && !(btn & hud->m6) && (stick = sHvStick[idx][0], hvAbs(stick) > 0.1f)) {
                t = s->f8;
                if (hvAbs(t) < 0.024999998f) {
                    t += stick * -0.005f;
                    s->f8 = t;
                    if (hvAbs(t) > 0.024999998f) {
                        lim = -0.024999998f;
                        if (t > 0.0f) {
                            lim = 0.024999998f;
                        }
                        s->f8 = lim;
                    }
                }
                t = s->fC + sHvStick[s->idx][1] * 0.005f;
                s->fC = t;
                if (hvAbs(t) > 0.015f) {
                    lim = -0.015f;
                    if (t > 0.0f) {
                        lim = 0.015f;
                    }
                    s->fC = lim;
                }
            }
            s->f10 = sHvStick[s->idx][1] * 0.005f;
            if (s->f8 > 0.0f) {
                s->f8 = s->f8 - 0.00125f;
                if (s->f8 < 0.0f) {
                    s->f8 = 0.0f;
                }
            } else {
                s->f8 = s->f8 + 0.00125f;
                if (s->f8 > 0.0f) {
                    s->f8 = 0.0f;
                }
            }
            if (s->fC > 0.0f) {
                s->fC = s->fC - 0.00125f;
                if (s->fC < 0.0f) {
                    s->fC = 0.0f;
                }
            } else {
                s->fC = s->fC + 0.00125f;
                if (s->fC > 0.0f) {
                    s->fC = 0.0f;
                }
            }
            s->f14 = s->f14 - c3->dt;
            if (s->f14 < 0.0f) {
                s->f14 = 0.0f;
            }
        } else {
            s->f14 = 0.0f;
        }
        D_mission_overlay_8010A200 = s->f14;
        { s32 *pi = &s->idx; cam = &sHvCams[*pi]; }
        cam->f58 = v10[0];
        cam->f5C = cam->f68 - v10[1];
        cam->f60 = cam->f6C - v10[2];
        v10[0] = s->f8;
        v10[1] = s->fC;
        v10[2] = s->f10;
        transformVec3ByMat34(&m, v10, v20);
        initVec4TripletFromArgs(&sc, scale, scale, scale);
        mat3x4Multiply(&m, &sc, &m);
        ((f32 *)&m)[9] = v20[0];
        ((f32 *)&m)[10] = v20[1];
        ((f32 *)&m)[11] = v20[2];
        s->mesh->mtx = m;
        tickHangarDisplayItemAnimations(s, getPlayerVehicleId(s->idx), c3->dt);
        break;
    case 4:
        c4 = ctx;
        if (sHvViews[s->idx].p4[2] == 3 && (sHvSettings.flags[s->idx] & 0x10) && !(sHvPlayers[s->idx].flags & 0x100) && s->f14 == 0.0f
            && (!(u8)func_mission_overlay_800FEECC() || !(u8)getHudSecondaryWeponCount() || !(sHvPlayers[s->idx].flags & 1))) {
            D_mission_overlay_8010A1FC = D_mission_overlay_8010A1D4[getPlayerVehicleId(s->idx)];
            D_mission_overlay_8010A1F8 = D_mission_overlay_8010A1B0[getPlayerVehicleId(s->idx)];
            if ((s->mesh->link.next = *c4->head) != NULL) {
                s->mesh->link.next->prev = &s->mesh->link;
            }
            *c4->head = &s->mesh->link;
        }
        break;
    }
    return 1;
}

#include "player.h"

extern u8 *getNpcContextByIndex(u16);
extern f32 vec3Dot(f32 *, f32 *);

void applyNpcPositionDrift(u8 *obj, f32 *dir) {
    u8 *npc = *(u8 **)(getNpcContextByIndex(gPlayers[*(s32 *)(obj + 0xB8)].inner.unk28A) + 4);

    if (vec3Dot(dir, (f32 *)(obj + 0x10)) > 0.0f) {
        *(f32 *)(npc + 8) -= 0.005f;
    } else {
        *(f32 *)(npc + 8) += 0.005f;
    }
    if ((dir[1] > 0.0f && *(f32 *)(obj + 0x20) > 0.0f) || (dir[1] < 0.0f && *(f32 *)(obj + 0x20) < 0.0f)) {
        *(f32 *)(npc + 0xC) += 0.005f;
    } else {
        *(f32 *)(npc + 0xC) -= 0.005f;
    }
}

extern f32 D_mission_overlay_8010A1F8;
extern f32 D_mission_overlay_8010A1FC;

void getConfigFloatPair(f32 *arg0, f32 *arg1) {
    *arg0 = D_mission_overlay_8010A1F8;
    *arg1 = D_mission_overlay_8010A1FC;
}

extern void vec3Cross(f32 *out, f32 *a, f32 *b);
void accumulateVectorInObjectFrame(f32 *a, f32 *b, f32 *c) {
    f32 t[3];
    vec3Cross(t, c + 7, c + 4);
    a[0] = a[0] + (t[0] * b[0] + c[7] * b[1] + c[4] * b[2]);
    a[1] = a[1] + (t[1] * b[0] + c[8] * b[1] + c[5] * b[2]);
    a[2] = a[2] + (t[2] * b[0] + c[9] * b[1] + c[6] * b[2]);
}

extern f32 D_mission_overlay_8010A200;

f32 getConfigFloatValue(void) {
    return D_mission_overlay_8010A200;
}

s32 findModelChildNodeByName(s32, s32);
extern s32 *D_mission_overlay_8010C090;

s32 findNamedEntryInCurrentObject(s32 arg0) {
    return findModelChildNodeByName(*D_mission_overlay_8010C090, arg0);
}

typedef struct {
    s32 m[12];
} ObjMatrix3x4;

void copyCurrentObjectMatrix(ObjMatrix3x4 *out) {
    *out = *(ObjMatrix3x4 *)(*D_mission_overlay_8010C090 + 0x28);
}

static u32 D_mission_overlay_800A695C[] __attribute__((section(".rodata"))) = { 0x8FC30014 };
