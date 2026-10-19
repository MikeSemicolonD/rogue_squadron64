#include "common.h"
#include "common_types.h"

typedef struct {
    u8 *unk0;
    u8 *unk4;
    u16 *npcs[2];
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
} CraftAnimSlot;

extern CraftAnimSlot D_mission_overlay_8010CF20[];

void despawnCraftAnimationSlotNpcs(u8);
void rs_free(void *);

typedef struct {
    s16 x, y, z, w;
} CaPt;

typedef struct {
    u8 **nodes[2];
    u8 pad8[8];
    u8 count;
    u8 idx;
    u8 pad12[2];
    CaPt *pts[4][4];
    CaPt copies[4][4];
    s16 avg[4][4];
    f32 unkF4;
    f32 unkF8;
} CraftAnimState;

extern CraftAnimState gCraftAnimState __asm__("D_mission_overlay_8010CF38");
u8 **caFindNode(u8 *, char *) __asm__("findModelChildNodeByName");

void resolveCraftAnimationNodeHandles(u8 *arg0) {
    u8 i;
    u32 j;
    u8 *n;
    u8 *rec;
    u16 *ix;

    switch (*(u16 *)(arg0 + 0xB4)) {
    case 0:
        gCraftAnimState.nodes[0] = caFindNode(*(u8 **)arg0, "glw_a");
        gCraftAnimState.nodes[1] = caFindNode(*(u8 **)arg0, "glw_b");
        gCraftAnimState.count = 2;
        break;
    case 1:
    case 2:
    case 3:
    case 7:
        gCraftAnimState.nodes[0] = caFindNode(*(u8 **)arg0, "glw_a");
        gCraftAnimState.count = 1;
        break;
    default:
        gCraftAnimState.count = 0;
        break;
    }
    gCraftAnimState.idx = 0;
    for (i = 0; i < gCraftAnimState.count; i++) {
        n = *gCraftAnimState.nodes[i];
        *(s32 *)(n + 0xC) &= ~8;
        rec = *(u8 **)(*(u8 **)(n + 0x20) + 8);
        for (j = 0; j < *(u32 *)(*(u8 **)(n + 0x20) + 0xC); j++) {
            ix = (u16 *)(rec + (*(u16 *)(rec + 4) & 0xFC));
            gCraftAnimState.pts[gCraftAnimState.idx][0] = (CaPt *)*(u8 **)(n + 0x24) + ix[0];
            gCraftAnimState.copies[gCraftAnimState.idx][0] = ((CaPt *)*(u8 **)(n + 0x24))[ix[0]];
            gCraftAnimState.pts[gCraftAnimState.idx][1] = (CaPt *)*(u8 **)(n + 0x24) + ix[1];
            gCraftAnimState.copies[gCraftAnimState.idx][1] = ((CaPt *)*(u8 **)(n + 0x24))[ix[1]];
            gCraftAnimState.pts[gCraftAnimState.idx][2] = (CaPt *)*(u8 **)(n + 0x24) + ix[2];
            gCraftAnimState.copies[gCraftAnimState.idx][2] = ((CaPt *)*(u8 **)(n + 0x24))[ix[2]];
            gCraftAnimState.pts[gCraftAnimState.idx][3] = (CaPt *)*(u8 **)(n + 0x24) + ix[3];
            gCraftAnimState.copies[gCraftAnimState.idx][3] = ((CaPt *)*(u8 **)(n + 0x24))[ix[3]];
            gCraftAnimState.avg[gCraftAnimState.idx][0] = (u32)(gCraftAnimState.pts[gCraftAnimState.idx][0]->x + gCraftAnimState.pts[gCraftAnimState.idx][1]->x + gCraftAnimState.pts[gCraftAnimState.idx][2]->x + gCraftAnimState.pts[gCraftAnimState.idx][3]->x) >> 2;
            gCraftAnimState.avg[gCraftAnimState.idx][1] = (u32)(gCraftAnimState.pts[gCraftAnimState.idx][0]->y + gCraftAnimState.pts[gCraftAnimState.idx][1]->y + gCraftAnimState.pts[gCraftAnimState.idx][2]->y + gCraftAnimState.pts[gCraftAnimState.idx][3]->y) >> 2;
            gCraftAnimState.avg[gCraftAnimState.idx][2] = (u32)(gCraftAnimState.pts[gCraftAnimState.idx][0]->z + gCraftAnimState.pts[gCraftAnimState.idx][1]->z + gCraftAnimState.pts[gCraftAnimState.idx][2]->z + gCraftAnimState.pts[gCraftAnimState.idx][3]->z) >> 2;
            rec += (rec[4] & 0x3F) * 4;
            gCraftAnimState.idx++;
        }
    }
    gCraftAnimState.unkF4 = *(f32 *)(arg0 + 0xE8);
    gCraftAnimState.unkF8 = 1.0f;
}

typedef struct {
    f32 f0, f4, f8, fC, f10, f14, f18, f1C, f20;
} CaKey;

extern CaKey D_mission_overlay_8010B534[];
extern f32 D_mission_overlay_8010B678[];
extern f32 D_mission_overlay_8010D02C;
f32 vec3Dot(void *, void *);
void vec3Cross(void *, void *, void *);
void quatFromAxisAngleSafe(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);

void applyCraftAnimationKeyframePose(u8 *arg0, f32 dt) {
    f32 q[4];
    f32 v[4][3];
    f32 out[3];
    CaKey *k;
    f32 cur;
    f32 t;
    f32 prev;
    f32 r;
    f32 w;
    f32 base;
    f32 ang;
    s16 *a;
    u32 i;
    u32 j;

    if (gCraftAnimState.idx == 0) {
        return;
    }
    cur = *(f32 *)(arg0 + 0xE8);
    k = &D_mission_overlay_8010B534[*(u16 *)(arg0 + 0xB4)];
    base = k->f8 + k->fC * (cur - k->f0) / (k->f4 - k->f0);
    prev = gCraftAnimState.unkF4;
    if (prev < cur) {
        r = (cur - prev) / dt;
        if (k->f20 < r) {
            r = k->f20;
        }
        t = base + r * (k->f10 / k->f20);
    } else if (cur < prev) {
        r = (prev - cur) / dt;
        if (k->f20 < r) {
            r = k->f20;
        }
        t = base - r * (k->f14 / k->f20);
    } else {
        t = base;
    }
    w = gCraftAnimState.unkF8;
    if (w < t) {
        gCraftAnimState.unkF8 = w + k->f18 * dt;
        if (t < gCraftAnimState.unkF8) {
            gCraftAnimState.unkF8 = t;
        }
    } else {
        gCraftAnimState.unkF8 = w - k->f1C * dt;
        if (gCraftAnimState.unkF8 < t) {
            gCraftAnimState.unkF8 = t;
        }
    }
    t = (gCraftAnimState.unkF8 < 2.2f) ? gCraftAnimState.unkF8 : 2.2f;
    for (i = 0; i < gCraftAnimState.idx; i++) {
        a = gCraftAnimState.avg[i];
        for (j = 0; j < 4; j++) {
            v[j][0] = (gCraftAnimState.copies[i][j].x - a[0]) * t;
            v[j][1] = (gCraftAnimState.copies[i][j].y - a[1]) * t;
            v[j][2] = (gCraftAnimState.copies[i][j].z - a[2]) * t;
        }
        ang = vec3Dot(D_mission_overlay_8010B678, arg0 + 0x1C) * 90.0f;
        vec3Cross(out, v[0], v[1]);
        quatFromAxisAngleSafe(q, out, ang);
        for (j = 0; j < 4; j++) {
            rotateVec3ByQuat(q, v[j], out);
            gCraftAnimState.pts[i][j]->x = a[0] + (u32)out[0];
            gCraftAnimState.pts[i][j]->y = a[1] + (u32)out[1];
            gCraftAnimState.pts[i][j]->z = a[2] + (u32)out[2];
        }
    }
    D_mission_overlay_8010D02C = *(f32 *)(arg0 + 0xE8);
}

void destroyNpcSlotByIndex(u16);

void despawnCraftAnimationSlotNpcs(u8 slot) {
    u8 i;
    u8 j;

    D_mission_overlay_8010CF20[slot].unk10 = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < *D_mission_overlay_8010CF20[slot].unk4; j++) {
            if (D_mission_overlay_8010CF20[slot].npcs[i][j] != 0xFFFF) {
                destroyNpcSlotByIndex(D_mission_overlay_8010CF20[slot].npcs[i][j]);
                D_mission_overlay_8010CF20[slot].npcs[i][j] = 0xFFFF;
            }
        }
    }
}

void despawnCraftAnimationSlotNpcsAndMarkStopping(u8 slot) {
    u8 i;
    u8 j;

    D_mission_overlay_8010CF20[slot].unk10 = 2;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < *D_mission_overlay_8010CF20[slot].unk4; j++) {
            if (D_mission_overlay_8010CF20[slot].npcs[i][j] != 0xFFFF) {
                destroyNpcSlotByIndex(D_mission_overlay_8010CF20[slot].npcs[i][j]);
                D_mission_overlay_8010CF20[slot].npcs[i][j] = 0xFFFF;
            }
        }
    }
}

void *rs_malloc(s32, s32);
typedef struct {
    u8 pad[0xF4];
    f32 unkF4;
    f32 unkF8;
} CaCam;
extern CaCam caCam __asm__("D_mission_overlay_8010CF38");

static __inline__ void caReset(u8 index) {
    u8 *obj;

    despawnCraftAnimationSlotNpcs(index);
    obj = D_mission_overlay_8010CF20[index].unk0;
    D_mission_overlay_8010CF20[index].unk10 = 0;
    D_mission_overlay_8010CF20[index].unk11 = 0;
    D_mission_overlay_8010CF20[index].unk12 = 0;
    D_mission_overlay_8010CF20[index].unk13 = 0;
    caCam.unkF4 = *(f32 *)(obj + 0xE8);
    caCam.unkF8 = 1.0f;
}

void allocateCraftAnimationStateForSlot(u8 *arg0, u8 slot, u8 *arg2)
{
  CraftAnimSlot *s;
  u8 i;
  u8 j;
  D_mission_overlay_8010CF20[slot].unk4 = arg2;
  D_mission_overlay_8010CF20[slot].unk0 = arg0;
  if ((*arg2) != 0)
  {
    D_mission_overlay_8010CF20[slot].npcs[0] = rs_malloc((*arg2) * 2, 0);
    D_mission_overlay_8010CF20[slot].npcs[1] = rs_malloc((*arg2) * 2, 0);
    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < (*D_mission_overlay_8010CF20[slot].unk4); j++)
      {
        D_mission_overlay_8010CF20[slot].npcs[i][j] = 0xFFFF;
      }

    }

    caReset(slot);
  }
  resolveCraftAnimationNodeHandles(arg0);
}

typedef struct {
    s32 w0;
    u8 b4;
    u8 b5;
    u8 pad6[2];
    f32 f8;
    f32 fC;
} CaEnt;

typedef struct {
    u8 count;
    u8 pad1[3];
    CaEnt *ents;
} CaList;

#define CA_LIST(s) ((CaList *)(s)->unk4)

extern s32 gCurrentLevel;
extern s32 D_mission_overlay_8010B510[];
extern s32 D_mission_overlay_8010B514[];
extern s32 D_mission_overlay_8010B524[];
u16 spawnNpcChildForActivePlayerCell(u16, f32, u8, s32, s32, void *, s32);
void sendSlotActionTwelve(u16);
u8 isWeaponSlotReady(s32);
void applyCraftAnimationKeyframePose(u8 *, f32);

void tickCraftAnimationSlot(u8 slot, f32 dt) {
    u8 n;
    CraftAnimSlot *s;
    u8 en;
    u8 i;
    u8 ok;

    if (gCurrentLevel == 5 || gCurrentLevel == 0x11) {
        en = 0;
    } else {
        en = 1;
    }
    s = &D_mission_overlay_8010CF20[slot];
    if (CA_LIST(s)->count != 0) {
        switch (s->unk10) {
        case 0:
            if (s->unk12 != 0) {
                for (i = 0; i < CA_LIST(s)->count; i++) {
                    if ((CA_LIST(s)->ents[i].b5 & 1) && (en || (CA_LIST(s)->ents[i].b5 & 0xF0))) {
                        if (s->unk12 == 1) {
                            s->npcs[0][i] = spawnNpcChildForActivePlayerCell(*(u16 *)(s->unk0 + 0xB6), CA_LIST(s)->ents[i].f8 * 0.0035f, (u32)(CA_LIST(s)->ents[i].fC * 6.0f), CA_LIST(s)->ents[i].w0, CA_LIST(s)->ents[i].b4, &D_mission_overlay_8010B514[CA_LIST(s)->ents[i].b5 >> 4], 1);
                        } else {
                            s->npcs[0][i] = spawnNpcChildForActivePlayerCell(*(u16 *)(s->unk0 + 0xB6), CA_LIST(s)->ents[i].f8 * 0.0035f, (u32)(CA_LIST(s)->ents[i].fC * 7.0f), CA_LIST(s)->ents[i].w0, CA_LIST(s)->ents[i].b4, &D_mission_overlay_8010B524[CA_LIST(s)->ents[i].b5 >> 4], 1);
                        }
                    }
                }
                s->unk10 = 1;
                s->unk13 = s->unk12;
            }
            break;
        case 1:
            if (s->unk14 != 0.0f) {
                s->unk14 -= dt;
                if (s->unk14 <= 0.0f) {
                    s->unk12 = 0;
                    goto despawn;
                }
            }
            if (s->unk12 != s->unk13) {
            despawn:
                for (i = 0; i < CA_LIST(s)->count; i++) {
                    if ((CA_LIST(s)->ents[i].b5 & 1) && s->npcs[0][i] != 0xFFFF) {
                        sendSlotActionTwelve(s->npcs[0][i]);
                        s->npcs[0][i] = 0xFFFF;
                    }
                }
                s->unk13 = 0;
                s->unk10 = 0;
            }
            break;
        case 2:
        default:
            break;
        }
        if (en) {
            switch (*(u16 *)(s->unk0 + 0xB4)) {
            case 0:
                ok = !isWeaponSlotReady(0);
                break;
            case 2:
                ok = 4.5f < *(f32 *)(s->unk0 + 0xE8);
                break;
            case 3:
                ok = 3.6000001f < *(f32 *)(s->unk0 + 0xE8);
                break;
            case 7:
                ok = 3.8999999f < *(f32 *)(s->unk0 + 0xE8);
                break;
            case 8:
                ok = 4.8f < *(f32 *)(s->unk0 + 0xE8);
                break;
            default:
                ok = 0;
                break;
            }
            if (ok) {
                if (s->unk11 == 0) {
                    n = 0;
                    for (i = 0; i < CA_LIST(s)->count; i++) {
                        if (CA_LIST(s)->ents[i].b5 & 2) {
                            s->npcs[1][i] = spawnNpcChildForActivePlayerCell(*(u16 *)(s->unk0 + 0xB6), CA_LIST(s)->ents[i].f8 * 0.008f, (u32)(CA_LIST(s)->ents[i].fC * 3.0f), CA_LIST(s)->ents[i].w0, CA_LIST(s)->ents[i].b4, D_mission_overlay_8010B510, 1);
                            n++;
                        }
                    }
                    s->unk11 = 1;
                }
            } else if (s->unk11 != 0) {
                for (i = 0; i < CA_LIST(s)->count; i++) {
                    if ((CA_LIST(s)->ents[i].b5 & 2) && s->npcs[1][i] != 0xFFFF) {
                        sendSlotActionTwelve(s->npcs[1][i]);
                        s->npcs[1][i] = 0xFFFF;
                    }
                }
                s->unk11 = 0;
            }
        }
    }
    applyCraftAnimationKeyframePose(s->unk0, dt);
}

void freePlayerAuxBuffersIfActive(u8 index) {
    if (*D_mission_overlay_8010CF20[index].unk4 != 0) {
        despawnCraftAnimationSlotNpcs(index);
        rs_free(D_mission_overlay_8010CF20[index].npcs[0]);
        rs_free(D_mission_overlay_8010CF20[index].npcs[1]);
    }
}

typedef struct {
    u8 pad[0xF4];
    f32 unkF4;
    f32 unkF8;
} CraftAnimCamera;

extern CraftAnimCamera D_mission_overlay_8010CF38;

void resetCraftAnimationStateForSlot(u8 index) {
    u8 *obj;

    despawnCraftAnimationSlotNpcs(index);
    obj = D_mission_overlay_8010CF20[index].unk0;
    D_mission_overlay_8010CF20[index].unk10 = 0;
    D_mission_overlay_8010CF20[index].unk11 = 0;
    D_mission_overlay_8010CF20[index].unk12 = 0;
    D_mission_overlay_8010CF20[index].unk13 = 0;
    D_mission_overlay_8010CF38.unkF4 = *(f32 *)(obj + 0xE8);
    D_mission_overlay_8010CF38.unkF8 = 1.0f;
}

void setCraftAnimationSlotParams(u8 slot, u8 flag, f32 value) {
    D_mission_overlay_8010CF20[slot].unk12 = flag;
    D_mission_overlay_8010CF20[slot].unk14 = value;
}

u8 getCraftAnimationSlotFlag(u8 slot) {
    return D_mission_overlay_8010CF20[slot].unk13;
}

f32 getCraftAnimationSlotValue(u8 slot) {
    return D_mission_overlay_8010CF20[slot].unk14;
}

__asm__(".section .rodata\n    .word 0xB8480003\n.section .text");
