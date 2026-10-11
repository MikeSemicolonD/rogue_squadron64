#include "common.h"
#include "common_types.h"

#include "crafts.h"
#include "hud.h"
#include "secondary_weapons.h"

#include "mission_overlay/0B4EC0.h"
#include "mission_overlay/0FCA20.h"

static struct hud_struct D_mission_overlay_8010CA30[2];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90B0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90C0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90D0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9100);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A910C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9118);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9124);

extern u32 D_main_bss_80130B4C;
extern u32 D_mission_overlay_8010CA1C;
extern s32 D_mission_overlay_8010B424[];
u16 loadAndRelocateAsset(s32, s32, s32);
u8 isWeaponSlotReady(u8);

typedef struct { u8 pad[0x28]; struct ui_element el[10]; } CsHud;

u8 configurePlayerSecondaryWeaponHud(u8 player, u8 weapon, u8 count, s32 adv) {
    struct hud_struct *h;
    u32 i;
    struct ui_element *e;

    h = &D_mission_overlay_8010CA30[player];
    h->secondaryWeapon = weapon;
    h->secondaryWeaponCount = count;
    h->secondaryWeaponReset = count;
    h->secondaryWeaponIsAdvanced = adv;
    h->crosshairOnOff = (D_main_bss_80130B4C >> 7) & 1;
    h->unknown006 = (D_mission_overlay_8010CA1C >> 10) & 1;
    for (i = 0; i < 10; i++) {
        h->texture_ids[i] = loadAndRelocateAsset(D_mission_overlay_8010B424[i], 0, 0x2000);
    }
    h->outerCrosshairRingElement.texture_count = 1;
    h->outerCrosshairRingElement.unknown0A = 1;
    h->outerCrosshairRingElement.flags = 3;
    h->outerCrosshairRingElement.zero = 0;
    h->outerCrosshairRingElement.texture_id_pointer = &h->texture_ids[0];
    h->innerCrosshairRingElement = h->outerCrosshairRingElement;
    h->innerCrosshairRingElement.texture_id_pointer = &h->texture_ids[1];
    h->seekerCrosshairRing1Element = h->outerCrosshairRingElement;
    h->seekerCrosshairRing1Element.texture_id_pointer = &h->texture_ids[8];
    h->seekerCrosshairRing1Element.rgba.r = 0xFF;
    h->seekerCrosshairRing1Element.rgba.g = 0xD2;
    h->seekerCrosshairRing1Element.rgba.b = 0;
    h->seekerCrosshairRing2Element = h->seekerCrosshairRing1Element;
    h->seekerCrosshairRing2Element.texture_id_pointer = &h->texture_ids[9];
    h->bombCrosshairRingElement.texture_count = 1;
    h->bombCrosshairRingElement.unknown0A = 1;
    h->bombCrosshairRingElement.flags = 3;
    h->bombCrosshairRingElement.rgba.r = 0xFF;
    h->bombCrosshairRingElement.rgba.g = 0xD2;
    h->bombCrosshairRingElement.zero = 0;
    h->bombCrosshairRingElement.rgba.b = 0;
    h->bombCrosshairRingElement.texture_id_pointer = &h->texture_ids[2];
    for (i = 0; i < 5; i++) {
        ((CsHud *)h)->el[i + 3].texture_count = 1;
        ((CsHud *)h)->el[i + 3].unknown0A = 1;
        ((CsHud *)h)->el[i + 3].zero = 0;
        ((CsHud *)h)->el[i + 3].flags = 3;
        ((CsHud *)h)->el[i + 3].rgba.r = 0xFF;
        ((CsHud *)h)->el[i + 3].rgba.g = 0;
        ((CsHud *)h)->el[i + 3].rgba.b = 0;
        ((CsHud *)h)->el[i + 3].rgba.a = 0xBE;
        ((CsHud *)h)->el[i + 3].texture_id_pointer = &h->texture_ids[i + 3];
    }
    switch (h->secondaryWeapon) {
    case 3:
    case 8:
        h->secondaryWeaponState = 0;
        h->unk210 = 0;
        h->unk211 = 0;
        break;
    case 1:
    case 2:
    case 4:
    case 5:
        h->secondaryWeaponState = 0;
        break;
    }
    if (getPlayerVehicleId(0) == 0 && !isWeaponSlotReady(0)) {
        h->alpha_scaling = 0.0f;
    } else {
        h->alpha_scaling = 1.0f;
    }
    for (i = 0; i < 2; i++) {
        D_mission_overlay_8010CA30[i].unk274 = 0;
    }
    return h->secondaryWeapon;
}

void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);

void resetHudInstancesAndUnbindNpcs(void) {
    s32 i;
    struct hud_struct *h;

    i = 0;
    do {
        if ((D_mission_overlay_8010CA30[i & 0xFF].secondaryWeapon == 3 || D_mission_overlay_8010CA30[i & 0xFF].secondaryWeapon == 8) && D_mission_overlay_8010CA30[i & 0xFF].unk210 != 0) {
            destroyNpcSlotChain(D_mission_overlay_8010CA30[i & 0xFF].unk212);
        }
        h = &D_mission_overlay_8010CA30[i & 0xFF];
        if (h->unk274 != 0) {
            factor5RemoveListNode(D_mission_overlay_8010CA30[i & 0xFF].listNode);
            h->unk274 = 0;
        }
        switch (h->secondaryWeapon) {
        case 3:
        case 8:
            h->secondaryWeaponState = 0;
            h->unk210 = 0;
            h->unk211 = 0;
            break;
        case 1:
        case 2:
        case 4:
        case 5:
            h->secondaryWeaponState = 0;
            break;
        }
        if (getPlayerVehicleId(0) == 0 && !isWeaponSlotReady(0)) {
            h->alpha_scaling = 0.0f;
        } else {
            h->alpha_scaling = 1.0f;
        }
        i++;
    } while ((u32)(i & 0xFF) < 2);
}

typedef struct { f32 x, y, z; } FnV3;
extern u16 D_mission_overlay_8010B4B4[];
extern u16 D_main_bss_80139560[];
extern u16 fnFindActive(u16, void *) __asm__("findActiveNpcInSlotChain");
extern u16 fnRevalidate(void *) __asm__("revalidateNpcSlotIterator");
extern u8 *fnGetCtx(u16) __asm__("getNpcContextByIndex");
extern void transformMeshPartIntoWorld(void *, FnV3 *);
extern f32 fnLen(FnV3 *) __asm__("vec3Length");
extern f32 fnDot(FnV3 *, f32 *) __asm__("vec3Dot");

u16 findNearestTargetableNpcInRange(f32 *pos, u16 cur, FnV3 *out, u8 *st, u8 *outIdx, f32 dt) {
    FnV3 d;
    FnV3 p;
    FnV3 curPos;
    FnV3 bestPos;
    u8 iter[8];
    u8 bestIdx;
    u16 best;
    u8 found;
    s32 k;
    u16 n;
    u8 curIdx;
    f32 len;
    f32 bestDist;
    u8 *ctx;

    best = 0xFFFF;
    found = 0;
    k = 0;
    if (D_mission_overlay_8010B4B4[0] != 0xFFFF) {
        do {
            for (n = fnFindActive(D_main_bss_80139560[D_mission_overlay_8010B4B4[k]], iter); n != 0xFFFF; n = fnRevalidate(iter)) {
                ctx = fnGetCtx(n);
                if (*(u16 *)(ctx + 0x14) & 0x100) {
                    continue;
                }
                if (*(void **)(ctx + 0xC) != NULL) {
                    transformMeshPartIntoWorld(*(void **)(ctx + 0xC), &p);
                } else {
                    p = **(FnV3 **)(ctx + 0x8);
                }
                d.x = p.x - pos[0];
                d.y = p.y - pos[1];
                d.z = p.z - pos[2];
                len = fnLen(&d);
                if (0.0f < len && len < 20.0f) {
                    d.x /= len;
                    d.y /= len;
                    d.z /= len;
                    if (fnDot(&d, pos + 3) > 0.985f) {
                        if (n == cur) {
                            found = 1;
                            curPos = p;
                            curIdx = k;
                        }
                        if (best == 0xFFFF || !(bestDist < len)) {
                            best = n;
                            bestDist = len;
                            bestPos = p;
                            bestIdx = k;
                        }
                    }
                }
            }
            k++;
        } while (D_mission_overlay_8010B4B4[k] != 0xFFFF);
    }
    if (found && best != cur) {
        *(f32 *)(st + 0x214) += dt;
        if (*(f32 *)(st + 0x214) < 2.0f) {
            *out = curPos;
            *outIdx = curIdx;
            return cur;
        }
    }
    *(f32 *)(st + 0x214) = 0.0f;
    if (best != 0xFFFF) {
        *out = bestPos;
        *outIdx = bestIdx;
    }
    return best;
}

typedef struct TerrainV3 {
    f32 x;
    f32 y;
    f32 z;
} TerrainV3;

extern u8 D_main_bss_80138058[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, void *, s32);
extern s32 sampleTerrainAtNpcPosition(TerrainV3 *, TerrainV3 *, void *, TerrainV3 *);

s32 projectForwardTerrainImpactPoint(TerrainV3 *out, f32 *arg1, s32 arg2) {
    TerrainV3 hit;
    u8 pad[0x18];
    TerrainV3 pos;
    TerrainV3 next;
    TerrainV3 dir;
    TerrainV3 delta;
    u8 buf[0x30];
    TerrainV3 base;
    u8 pad2[0x20];
    f32 t;

    lookupHmtTextureByName(arg2, "a", 0, &base, buf, 0);
    pos = base;
    dir.x = arg1[3] * 4.0f + arg1[9];
    dir.y = arg1[4] * 4.0f + arg1[10] + 2.0f;
    t = 0.0f;
    dir.z = arg1[5] * 4.0f + arg1[11];
    do {
        next.x = pos.x + dir.x * 0.1f;
        next.y = pos.y + dir.y * 0.1f;
        next.z = pos.z + dir.z * 0.1f;
        dir.y += 1.2f;
        delta.x = next.x - pos.x;
        delta.y = next.y - pos.y;
        delta.z = next.z - pos.z;
        if (!sampleTerrainAtNpcPosition(&pos, &delta, &D_main_bss_80138058, &hit)) {
            t += 0.1f;
            pos = next;
        } else {
            *out = hit;
            return 1;
        }
    } while (t < 5.0f);
    return 0;
}

typedef struct HudInst {
    /* 0x000 */ u8 weapon;
    /* 0x001 */ u8 state;
    /* 0x002 */ u8 count;
    /* 0x003 */ u8 pad3[2];
    /* 0x005 */ u8 crosshair;
    /* 0x006 */ u8 mode;
    /* 0x007 */ u8 latch;
    /* 0x008 */ u8 fade;
    /* 0x009 */ u8 pad9[0x17];
    /* 0x020 */ f32 timer;
    /* 0x024 */ f32 alpha;
    /* 0x028 */ u8 pad28[0x1E0];
    /* 0x208 */ u16 target;
    /* 0x20A */ u16 pad20A;
    /* 0x20C */ f32 lockTimer;
    /* 0x210 */ u8 locked;
    /* 0x211 */ u8 flag211;
    /* 0x212 */ u16 slot;
    /* 0x214 */ u8 pad214[4];
    /* 0x218 */ f32 f218;
    /* 0x21C */ FnV3 pos;
    /* 0x228 */ u8 hit;
    /* 0x229 */ u8 pad229[3];
    /* 0x22C */ f32 f22C;
    /* 0x230 */ u32 node[0x11];
    /* 0x274 */ u8 active;
    /* 0x275 */ u8 pad275[3];
} HudInst;

s32 bsearchFactor5TableByU16Key(s32, s32, s32);
u16 findFreeNpcSlotByKey(u16, u16);
u16 getNextSlotNpcTypeId(u16);
s32 mostlyMusyxFlagGatedHelper(void *);
s32 safeLookup3DSoundEntry(s32, u16);
s32 updateActive3DAudioSource(void *, void *, void *, s32);
extern void fnPlay3D(void *, void *, void *, f32, f32, s32, s32, s32, s32) __asm__("play3DSoundEvent");
extern u8 *fnNpcCtx(u16) __asm__("getNpcContextByIndex");

u8 tickHudInstanceTargetingAndSpawns(u8 idx, f32 dt, f32 *aim, s32 arg3, u8 fire, u16 *outTarget, u16 key) {
    HudInst *h;
    FnV3 sp28;
    u8 sp38;
    u8 ret;
    u8 dis;
    u16 n;
    u8 *ctx;
    u8 cnt;
    f32 x;

    ret = 0;
    h = &((HudInst *)D_mission_overlay_8010CA30)[idx];
    h->crosshair = (D_main_bss_80130B4C >> 7) & 1;
    if (getPlayerVehicleId(0) == 0 && !isWeaponSlotReady(0)) {
        dis = 1;
        if (0.0f < h->alpha) {
            x = h->alpha - dt * 4.0f;
            h->alpha = x;
            if (x < 0.0f) {
                h->alpha = 0.0f;
            }
        }
    } else {
        if (h->alpha < 1.0f) {
            x = h->alpha + dt * 4.0f;
            h->alpha = x;
            if (1.0f < x) {
                h->alpha = 1.0f;
            }
        }
        dis = 0;
    }
    switch (h->weapon) {
    case 3:
    case 8:
        switch (h->state) {
        case 0:
            if (fire) {
                if (h->count != 0 && !dis) {
                    h->state = 1;
                    h->fade = 0;
                    h->latch = 0;
                    h->f218 = 0.0f;
                    h->timer = 0.5f;
                } else {
                    bsearchFactor5TableByU16Key(0x67, 0x5A, 0x40);
                    h->state = 4;
                }
            }
            break;
        case 1:
            if (!dis) {
                h->f218 = h->f218 + dt;
                h->timer = h->timer - dt;
                if (0.0f < h->timer) {
                    h->fade = 190 - (u32)(h->timer * 190.0f * 2.0f);
                    if (h->mode == 0) {
                        if (!fire) {
                            h->latch = 1;
                            break;
                        }
                        if (h->latch == 0) {
                            break;
                        }
                        if (h->f218 < 0.42f) {
                            h->latch = 0;
                            ret = 1;
                            h->flag211 = 1;
                        } else {
                            h->latch = 0;
                        }
                    } else {
                        if (fire) {
                            break;
                        }
                        h->latch = 1;
                    }
                } else {
                    h->fade = 190;
                    h->state = 2;
                    h->target = 0xFFFF;
                    h->locked = 0;
                    h->slot = 0xFFFF;
                    break;
                }
            }
            h->timer = 0.5f - h->timer;
            h->state = 3;
            break;
        case 2:
            if (dis) {
                if (h->locked) {
                    destroyNpcSlotChain(h->slot);
                }
                h->target = 0xFFFF;
                h->locked = 0;
                h->timer = 0.5f;
                h->state = 3;
                break;
            }
            n = findNearestTargetableNpcInRange(aim, h->target, &sp28, (u8 *)h, &sp38, dt);
            if (h->locked == 0) {
                if (n != 0xFFFF && n == h->target) {
                    h->lockTimer = h->lockTimer - dt;
                    if (h->lockTimer < 0.0f) {
                        h->locked = 1;
                        h->pos = sp28;
                        h->lockTimer = 2.5f;
                        h->slot = findFreeNpcSlotByKey(key, h->target);
                        if (sp38 >= 4) {
                            bsearchFactor5TableByU16Key(0x69, 0x6E, 0xFF);
                        } else {
                            bsearchFactor5TableByU16Key(0x68, 0x6E, 0xFF);
                        }
                    }
                } else {
                    h->target = n;
                    h->lockTimer = 0.8f;
                }
            } else if (n != h->target) {
                h->lockTimer = h->lockTimer - dt;
                if (0.0f <= h->lockTimer) {
                    if (getNextSlotNpcTypeId(h->slot) != 0xFFFF) {
                        ctx = fnNpcCtx(h->target);
                        if (ctx) {
                            if (*(void **)(ctx + 0xC) != NULL) {
                                transformMeshPartIntoWorld(*(void **)(ctx + 0xC), &h->pos);
                            } else {
                                h->pos = **(FnV3 **)(ctx + 0x8);
                            }
                        }
                    } else {
                    shortDrop:
                        h->lockTimer = 0.8f;
                        goto drop;
                    }
                } else {
                drop:
                    h->locked = 0;
                    h->target = 0xFFFF;
                    destroyNpcSlotChain(h->slot);
                }
            } else {
                h->pos = sp28;
                h->lockTimer = 2.5f;
                if (getNextSlotNpcTypeId(h->slot) == 0xFFFF) {
                    goto shortDrop;
                }
            }
            if (h->mode == 0) {
                if (!fire) {
                    h->latch = 1;
                    break;
                }
                if (h->latch == 0) {
                    break;
                }
                h->latch = 0;
            } else if (fire) {
                break;
            }
            if (h->locked) {
                *outTarget = h->target;
                destroyNpcSlotChain(h->slot);
                ret = 1;
            }
            h->target = 0xFFFF;
            h->locked = 0;
            h->timer = 0.5f;
            h->state = 3;
            break;
        case 3:
            h->timer = h->timer - dt;
            if (0.0f < h->timer) {
                h->fade = (u32)(h->timer * 190.0f * 2.0f);
                if (dis) {
                    break;
                }
                if (h->mode == 0) {
                    if (!fire) {
                        h->latch = 1;
                        break;
                    }
                    if (h->latch == 0) {
                        break;
                    }
                    h->latch = 0;
                } else if (!fire) {
                    break;
                }
                if (h->count == 0) {
                    break;
                }
                h->timer = 0.5f;
                h->state = 1;
            } else {
                h->fade = 0;
                h->state = 0;
            }
            break;
        case 4:
            if (!fire) {
                h->state = 0;
            }
            break;
        }
        break;
    case 4:
        switch (h->state) {
        case 0:
            if (fire) {
                if (h->count != 0 && !dis) {
                    if (0.0f < aim[7]) {
                        h->state = 1;
                        h->fade = 0;
                        h->latch = 0;
                        h->timer = 0.5f;
                    }
                } else {
                    bsearchFactor5TableByU16Key(0x67, 0x5A, 0x40);
                    h->state = 4;
                }
            }
            break;
        case 1:
            if (!dis) {
                h->timer = h->timer - dt;
                if (0.0f < h->timer) {
                    h->fade = 200 - (u32)(h->timer * 200.0f * 2.0f);
                } else {
                    h->fade = 200;
                    h->state = 2;
                }
                h->hit = projectForwardTerrainImpactPoint(&h->pos, aim, arg3);
                if (h->mode == 0) {
                    if (!fire) {
                        h->latch = 1;
                    } else if (h->latch != 0) {
                        h->latch = 0;
                        ret = 1;
                        goto c4s1tail;
                    }
                } else if (!fire) {
                    ret = 1;
                    goto c4s1tail;
                }
                if (!(aim[7] <= 0.0f)) {
                    break;
                }
            }
        c4s1tail:
            h->timer = 0.5f - h->timer;
            h->state = 3;
            break;
        case 2:
            h->hit = projectForwardTerrainImpactPoint(&h->pos, aim, arg3);
            if (!dis) {
                if (h->mode != 0) {
                    if (!fire) {
                        ret = 1;
                        goto c4s2tail;
                    }
                } else if (!fire) {
                    h->latch = 1;
                } else if (h->latch != 0) {
                    h->latch = 0;
                    ret = 1;
                    goto c4s2tail;
                }
                if (!(aim[7] <= 0.0f)) {
                    break;
                }
            }
        c4s2tail:
            h->timer = 0.5f;
            h->state = 3;
            break;
        case 3:
            h->timer = h->timer - dt;
            if (0.0f < h->timer) {
                h->fade = (u32)(h->timer * 200.0f * 2.0f);
            } else {
                h->fade = 0;
                if (fire) {
                    h->state = 4;
                } else {
                    h->state = 0;
                }
            }
            h->hit = projectForwardTerrainImpactPoint(&h->pos, aim, arg3);
            if (dis) {
                break;
            }
            if (h->count == 0) {
                break;
            }
            if (!(0.0f < aim[7])) {
                break;
            }
            if (h->mode == 0) {
                if (!fire) {
                    h->latch = 1;
                    break;
                }
                if (h->latch == 0) {
                    break;
                }
                h->latch = 0;
            } else if (!fire) {
                break;
            }
            h->timer = 0.5f;
            h->state = 1;
            break;
        case 4:
            if (!fire) {
                h->state = 0;
            }
            break;
        }
        break;
    case 2:
    case 5:
    case 7:
    case 9:
        switch (h->state) {
        case 0:
            if (fire) {
                if (h->count != 0 && !dis) {
                    ret = 1;
                } else {
                    bsearchFactor5TableByU16Key(0x67, 0x5A, 0x40);
                }
                h->state = 1;
            }
            break;
        case 1:
            if (!fire) {
                h->state = 0;
            }
            break;
        }
        break;
    case 1:
        switch (h->state) {
        case 0:
            if (fire) {
                if (h->count != 0 && !dis) {
                    h->state = 1;
                    h->f22C = 0.0f;
                    fnPlay3D(h->node, aim, aim + 9, 18.0f, 0.2f, 7, 0x3A, 0x64, 0x3C);
                    safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(h->node), 0);
                    h->active = 1;
                } else {
                    bsearchFactor5TableByU16Key(0x67, 0x5A, 0x40);
                    h->state = 2;
                }
            }
            break;
        case 1:
            h->f22C = h->f22C + dt;
            dt = h->f22C / 3.0f + 0.1f;
            if (1.0f < dt) {
                dt = 1.0f;
            }
            if (!fire || dis) {
                factor5RemoveListNode(h->node);
                h->active = 0;
                if (dis) {
                    h->state = 2;
                } else {
                    h->state = 0;
                    if (0.0f < h->f22C) {
                        ret = 1;
                    }
                }
            } else {
                updateActive3DAudioSource(h->node, aim, aim + 9, 0x64);
                safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(h->node), (u32)(dt * 16383.0f));
            }
            break;
        case 2:
            if (!fire) {
                h->state = 0;
            }
            break;
        }
        break;
    }
    cnt = h->count;
    if (cnt != 0xFF && ret && cnt != 0) {
        h->count = cnt - 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", updatePlayerHudFrame);

void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);
void releaseTextureLutEntry(u16);

void teardownHudInstancesAndUnbindNpcs(void) {
    u32 i;

    for (i = 0; i < 10; i++) {
        releaseTextureLutEntry(D_mission_overlay_8010CA30[0].texture_ids[i]);
    }
    for (i = 0; i < 2; i++) {
        if ((D_mission_overlay_8010CA30[i].secondaryWeapon == 3 || D_mission_overlay_8010CA30[i].secondaryWeapon == 8) && D_mission_overlay_8010CA30[i].unk210 != 0) {
            destroyNpcSlotChain(D_mission_overlay_8010CA30[i].unk212);
        }
        if (D_mission_overlay_8010CA30[i].unk274 != 0) {
            factor5RemoveListNode(D_mission_overlay_8010CA30[i].listNode);
        }
    }
}

typedef struct {
    s16 hB8;
    u16 hBA;
    s32 wBC;
    f32 fC0;
    f32 fC4;
    f32 fC8;
    u8 bCC;
    u8 padCD[0xB];
} DhSlotArgs;
typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x13C];
} DhCam;
extern DhCam D_main_bss_80138D18[];
extern u8 gPlayers[];
extern f32 D_mission_overlay_8010B44C[];
extern f32 D_mission_overlay_8010B454[];
extern f32 D_mission_overlay_8010B45C[];
extern f32 D_mission_overlay_8010B464[];
extern f32 D_mission_overlay_8010B46C[];
extern f32 D_mission_overlay_8010B474[];
extern f32 D_mission_overlay_8010B47C[];
extern f32 D_mission_overlay_8010B484[];
extern f32 D_mission_overlay_8010B48C[];
extern f32 D_mission_overlay_8010B494[];
extern f32 D_mission_overlay_8010B49C[];
extern f32 D_mission_overlay_8010B4A4[];
extern f32 D_mission_overlay_8010B4AC[];
extern f32 D_mission_overlay_8010B4C0[];
extern f32 D_mission_overlay_8010B4CC[];
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void accumulateVectorInObjectFrame(void *, void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);

void dispatchHudInstanceWeaponEffect(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 arg6) {
    f32 mtx[12];
    u8 buf[0x30];
    f32 mtx2[12];
    DhSlotArgs sa;
    f32 scale[3];
    struct hud_struct *h;
    register u8 *p2 asm("$19") = arg2;
    register s32 tex asm("$7") = arg3;
    u16 r;
    f32 one;
    f32 t;
    f32 u;

    switch (arg4) {
    case 3:
    case 8:
        {
            struct hud_struct *hb = D_mission_overlay_8010CA30;
            h = &hb[arg0 & 0xFF];
        }
        if (h->unk211 != 0) {
            h->unk211 = 0;
            goto case2;
        }
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        if (arg4 == 3) {
            r = dispatchCueByCategory(0xA, arg1, mtx, D_mission_overlay_8010B4C0, 1, 4.0f, D_mission_overlay_8010B47C[h->secondaryWeaponIsAdvanced]);
            sa.fC4 = D_mission_overlay_8010B46C[h->secondaryWeaponIsAdvanced];
            sa.fC8 = D_mission_overlay_8010B474[h->secondaryWeaponIsAdvanced];
        } else {
            r = dispatchCueByCategory(0xD, arg1, mtx, D_mission_overlay_8010B4C0, 1, 4.0f, D_mission_overlay_8010B494[h->secondaryWeaponIsAdvanced]);
            sa.fC4 = D_mission_overlay_8010B484[h->secondaryWeaponIsAdvanced];
            sa.fC8 = D_mission_overlay_8010B48C[h->secondaryWeaponIsAdvanced];
        }
        sa.hB8 = 0;
        sa.hBA = arg6;
        sa.wBC = 0;
        sa.bCC = 0;
        sa.fC0 = 10.0f;
        slotDispatcherIter(r, 0xA, &sa);
        if (arg4 == 3) {
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        } else {
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        }
        break;
    case 4:
        lookupHmtTextureByName(tex, "zb", 0, mtx, buf, 0);
        mtx[9] = *(f32 *)(p2 + 0xC) * 4.0f + *(f32 *)(p2 + 0x24);
        mtx[10] = *(f32 *)(p2 + 0x10) * 4.0f + *(f32 *)(p2 + 0x28) + 2.0f;
        mtx[11] = *(f32 *)(p2 + 0x14) * 4.0f + *(f32 *)(p2 + 0x2C);
        dispatchCueByCategory(8, arg1, mtx, NULL, 0, 0.0f, D_mission_overlay_8010B4AC[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
        play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x47, 0x78, 0);
        break;
    case 2:
    case 5:
    case2:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        if (arg4 == 2) {
            dispatchCueByCategory(0xA, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B44C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B454[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        } else {
            dispatchCueByCategory(0xD, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B45C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B464[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        }
        break;
    case 7:
    case 9:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        r = dispatchCueByCategory(0xE, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B49C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B4A4[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
        if (arg4 == 9) {
            sa.hB8 = 0;
            slotDispatcherIter(r, 0xA, &sa);
        }
        play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        break;
    case 1:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        {
            DhCam *cams = D_main_bss_80138D18;
            u8 *pl = (u8 *)gPlayers;
            if (*(u16 *)(cams[*(s32 *)(pl + 0xBC)].p4 + 4) == 3 && *(u16 *)(pl + 0xB8) == 1) {
                accumulateVectorInObjectFrame(mtx, D_mission_overlay_8010B4CC, pl + 4);
            }
        }
        one = 1.0f;
        mat34CrossRowsAndCopyPos(mtx2, mtx, one);
        { struct hud_struct *hh = D_mission_overlay_8010CA30; t = *(f32 *)&hh[arg0 & 0xFF].unknown_words214[6] / 3.0f; }
        if (one < t) {
            t = one;
        }
        u = t;
        if (t < 0.25f) {
            u = 0.25f;
        }
        scale[0] = u * 3.0f;
        scale[1] = u * 3.0f;
        scale[2] = u * 5.0f;
        t = t + 0.1f;
        if (one < t) {
            t = one;
        }
        dispatchCueByCategory(0xC, arg1, mtx, scale, 1, 10.0f, t * 4.0f);
        play3DSoundEvent(0, p2, p2 + 0x24, 20.0f, 0.2f, 0, 0x34, 0x78, 0x3C);
        break;
    }
}

u8 configurePlayerSecondaryWeaponHud(u8, u8, u8, s32);
extern u8 D_main_bss_80130B12;
extern u32 D_main_bss_80130B4C;
extern u8 gMissionState[];

u8 refreshPlayerSecondaryWeaponHud(u8 arg0) {
    s32 flag;

    if (arg0 == 0) {
        switch (D_main_bss_80130B12) {
            case 2:
            case 3:
                flag = (D_main_bss_80130B4C >> 10) & 1;
                break;
            case 5:
            case 8:
                flag = (D_main_bss_80130B4C >> 12) & 1;
                break;
            case 4:
                flag = (D_main_bss_80130B4C >> 15) & 1;
                break;
            default:
                flag = 0;
                break;
        }
    } else {
        flag = 0;
    }
    return configurePlayerSecondaryWeaponHud(arg0, gMissionState[2], gMissionState[3], flag);
}

void resetTransientPlayerStateFlags(void) {
    u8 var_s1;
    struct hud_struct *temp_s0;

    for (var_s1 = 0; var_s1 < 2;  var_s1++) {
        temp_s0 = &D_mission_overlay_8010CA30[var_s1];
        switch (temp_s0->secondaryWeapon) {
        case SECONDARY_WEAPON_SEEKER_MISSILES:
        case SECONDARY_WEAPON_SEEKER_TORPEDOS:
            temp_s0->secondaryWeaponState = 0;
            temp_s0->unk210 = 0;
            temp_s0->unk211 = 0;
            break;
        case SECONDARY_WEAPON_ION_CANNON:
        case SECONDARY_WEAPON_MISSLES:
        case SECONDARY_WEAPON_BOMBS:
        case SECONDARY_WEAPON_PROTON_TORPEDOS:
            temp_s0->secondaryWeaponState = 0;
            break;
        }
        if (getPlayerVehicleId(0) != CRAFT_XWING) {
            temp_s0->alpha_scaling = 1.0f;
        } else if (!isWeaponSlotReady(0U)) {
            temp_s0->alpha_scaling = 0.0f;
        } else {
            temp_s0->alpha_scaling = 1.0f;
        }
    }
}

void resetSecondaryWeaponCount(void) {
    u8 var_a0;

    for (var_a0 = 0; var_a0 < 2; var_a0++) {
        D_mission_overlay_8010CA30[var_a0].secondaryWeaponCount = D_mission_overlay_8010CA30[var_a0].secondaryWeaponReset;
    }
}

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} HudTargetPos;

s32 getActiveHudInstanceTargetPosition(HudTargetPos *arg0) {
    if (D_mission_overlay_8010CA30[0].secondaryWeapon == 4 && D_mission_overlay_8010CA30[0].secondaryWeaponState != 0 && *(u8 *)&D_mission_overlay_8010CA30[0].unknown_words214[5] != 0) {
        *arg0 = *(HudTargetPos *)&D_mission_overlay_8010CA30[0].unknown_words214[2];
        return 1;
    }
    return 0;
}

s32 func_mission_overlay_800FEECC(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_mission_overlay_8010CA30[0].secondaryWeapon == SECONDARY_WEAPON_BOMBS) {
        var_a0 = D_mission_overlay_8010CA30[0].secondaryWeaponState > 0U;
    }
    return var_a0;
}

u8 getHudSecondaryWeponCount(void) {
    return D_mission_overlay_8010CA30[0].secondaryWeaponCount;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", fake_func_800FEF04);

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodata_pad_0FCA20[] = {
    0x00000000,
    0x8FC20024,
};
