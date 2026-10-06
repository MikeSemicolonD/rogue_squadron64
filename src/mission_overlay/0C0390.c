#include "common.h"
#include "common_types.h"

#include "PR/gu.h"

#include "game_settings.h"
#include "levels.h"
#include "mission_state.h"
#include "player.h"
#include "secondary_weapons.h"

#include "main/3F160.h"
#include "mission_overlay/0C0390.h"

u16 D_mission_overlay_8010BFD0;
u16 bss_pad0_0C0390;
u32 bss_pad1_0C0390;
struct rgba D_mission_overlay_8010BFD8;
f32 D_mission_overlay_8010BFDC;

// Interim Data externs
// These might actually be one big array, based on the access pattern in `updateHudHealthIndicator`
extern struct healthIndicatorColors advancedShieldColors;
extern struct healthIndicatorColors standardHealthColors[2];
extern struct healthIndicatorColors criticalHealthColors[3];
extern u8 missionObjectiveTextIds[0x14][4];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A6250);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A6260);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A626C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A627C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A628C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A6298);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62A4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62B0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62BC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62C8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62D0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62D8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A62E0);

void updateHudHealthIndicator(struct func_800C0084_type *arg0, f32 arg1) {
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fs0;
    f32 permuter;
    f32 magic;
    s32 temp_ft2;
    struct healthIndicatorColors *var_a1;

    temp_fv0 = getPlayerHealthPercentage(arg0->unk234);
    if (temp_fv0 < 0.25f) {
        var_fs0 = (0.25f - temp_fv0) * 4.0f;
        var_a1 = criticalHealthColors;
    } else {
        temp_fv1 = gPlayers[arg0->unk234].inner.advancedShieldTimer;
        if (temp_fv1 > 0.0f) {
            var_a1 = &advancedShieldColors;
            arg0->playerHealthPercentage = temp_fv0;
            var_fs0 = 1.0f - temp_fv1;
        } else {
            var_fs0 = (1.0f - temp_fv0) * 4.0f;
            temp_ft2 = (s32) var_fs0;
            var_a1 = &standardHealthColors[temp_ft2];
            var_fs0 -= (f32) temp_ft2;
        }
    }
    if (temp_fv0 < arg0->playerHealthPercentage) {
        arg0->unk23C = 1.0f;
    }
    arg0->playerHealthPercentage = temp_fv0;
    arg0->upperHealthIndicatorColor.r = var_a1->upper.r + ((var_a1[1].upper.r - var_a1->upper.r) * var_fs0);
    arg0->upperHealthIndicatorColor.g = var_a1->upper.g + ((var_a1[1].upper.g - var_a1->upper.g) * var_fs0);
    arg0->upperHealthIndicatorColor.b = var_a1->upper.b + ((var_a1[1].upper.b - var_a1->upper.b) * var_fs0);
    arg0->upperHealthIndicatorColor.a = 0xB9;
    arg0->lowerHealthIndicatorColor.r = var_a1->lower.r + ((var_a1[1].lower.r - var_a1->lower.r) * var_fs0);
    arg0->lowerHealthIndicatorColor.g = var_a1->lower.g + ((var_a1[1].lower.g - var_a1->lower.g) * var_fs0);
    arg0->lowerHealthIndicatorColor.b = var_a1->lower.b + ((var_a1[1].lower.b - var_a1->lower.b) * var_fs0);
    arg0->lowerHealthIndicatorColor.a = 0x5C;
    if (temp_fv0 < 0.25f) {
        temp_fa0 = (cosf(2.0f * (arg0->unk238 * 3.1415927f)) + 1.0f) * 0.5f;
        arg0->upperHealthIndicatorColor.a *= temp_fa0;
        var_fs0 = (2.0f * var_fs0) * arg1;
        arg0->unk238 += (var_fs0) + arg1;
    }
    if (arg0->unk23C > 0.0f) {
        var_fs0 = (sinf((2.0f * (2.0f * arg0->unk23C * 3.1415927f)) - 1.5707964f) + 1.0f) * 0.5f;
        arg0->upperHealthIndicatorColor.r += (0xFF - arg0->upperHealthIndicatorColor.r) * var_fs0;
        arg0->upperHealthIndicatorColor.g += (0xFF - arg0->upperHealthIndicatorColor.g) * var_fs0;
        arg0->upperHealthIndicatorColor.b += (0xFF - arg0->upperHealthIndicatorColor.b) * var_fs0;
        permuter = (2.0f * arg0->unk23C);
        magic = (cosf(2.0f * (permuter * 3.1415927f)) + 1.0f);
        arg0->upperHealthIndicatorColor.a *= (magic * 0.5f);
        arg0->unk23C -= arg1;
        if (arg0->unk23C < 0.0f) {
            arg0->unk23C = 0.0f;
        }
    }
}

void setHudSecondaryWeaponInfo(struct func_800C0084_type *arg0) {
    u8 secondaryWeaponLevel;
    u8 secondaryWeaponType;

    switch (gMissionState.secondaryWeapon) {
    case SECONDARY_WEAPON_MISSLES:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_MISSLE;
        secondaryWeaponLevel = (gGameSettings.unlockAndSettingsFlags[0] >> GAME_SETTINGS_ADVANCED_MISSILES) & 1;
        break;
    case SECONDARY_WEAPON_SEEKER_MISSILES:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_MISSLE;
        secondaryWeaponLevel = SECONDARY_WEAPON_LEVEL_SEEKER;
        break;
    case SECONDARY_WEAPON_CLUSTER_MISSILES:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_CLUSTER_MISSLE;
        secondaryWeaponLevel = (gGameSettings.unlockAndSettingsFlags[0] >> GAME_SETTINGS_SEEKER_CLUSTER_MISSILES) & 1;
        break;
    case SECONDARY_WEAPON_SEEKER_CLUSTER_MISSILES:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_CLUSTER_MISSLE;
        secondaryWeaponLevel = SECONDARY_WEAPON_LEVEL_SEEKER;
        break;
    case SECONDARY_WEAPON_PROTON_TORPEDOS:
        secondaryWeaponType = SECONDARY_WEAPON_TYPE_TORPEDO;
        if (!ADVANCED_TORPEDOS_UNLOCKED) {
            secondaryWeaponLevel = ((gGameSettings.unlockAndSettingsFlags[0] & GAME_SETTING_MASK(GAME_SETTINGS_SEEKER_TORPEDOS)) != 0) * 2;
        } else {
            secondaryWeaponLevel = SECONDARY_WEAPON_LEVEL_ADVANCED;
        }
        break;
    case SECONDARY_WEAPON_SEEKER_TORPEDOS:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_TORPEDO;
        secondaryWeaponLevel = SECONDARY_WEAPON_LEVEL_SEEKER;
        break;
    case SECONDARY_WEAPON_BOMBS:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_BOMB;
        secondaryWeaponLevel = (gGameSettings.unlockAndSettingsFlags[0] >> GAME_SETTINGS_ADVANCED_BOMBS) & 1;
        break;
    default:
        secondaryWeaponType  = SECONDARY_WEAPON_TYPE_MISSLE;
        secondaryWeaponLevel = SECONDARY_WEAPON_LEVEL_NORMAL;
        break;
    }
    arg0->secondaryWeaponType  = secondaryWeaponType;
    arg0->secondaryWeaponLevel = secondaryWeaponLevel;
}

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} HudPt;

void findHudElementExtremes(u8 *out, u8 **objp, s32 flag) {
    HudPt *base;
    u32 idx;
    u32 i;
    s32 f;

    *(s32 *)(*objp + 0xC) &= ~8;
    *(s32 *)(*objp + 0xC) |= 0x20000;
    *(s32 *)(out + 0x20) = 0xC;
    *(s32 *)(out + 0x24) = 0x0A0C9005;
    *(s32 *)(out + 0x28) = 0;
    base = *(HudPt **)(*objp + 0x24);

    idx = 0;
    for (i = 1; i < 4; i++) {
        if (base[i].x <= base[idx].x && base[i].y <= base[idx].y) {
            idx = i;
        }
    }
    *(u16 *)(out + 0x2C) = idx;

    idx = 0;
    for (i = 1; i < 4; i++) {
        if (base[i].x >= base[idx].x && base[i].y <= base[idx].y) {
            idx = i;
        }
    }
    *(u16 *)(out + 0x2E) = idx;

    idx = 0;
    for (i = 1; i < 4; i++) {
        if (base[i].x >= base[idx].x && base[i].y >= base[idx].y) {
            idx = i;
        }
    }
    *(u16 *)(out + 0x30) = idx;

    idx = 0;
    for (i = 1; i < 4; i++) {
        if (base[i].x <= base[idx].x && base[i].y >= base[idx].y) {
            idx = i;
        }
    }
    f = *(s32 *)(out + 0x20);
    *(u16 *)(out + 0x32) = idx;
    *(u16 *)(out + 0x34) = 0;
    *(u16 *)(out + 0x36) = 0;
    *(u16 *)(out + 0x38) = 0x1000;
    *(u16 *)(out + 0x3A) = 0;
    *(u16 *)(out + 0x3C) = 0x1000;
    *(u16 *)(out + 0x3E) = 0x1000;
    *(u16 *)(out + 0x40) = 0;
    *(u16 *)(out + 0x42) = 0x1000;
    *(s32 *)(out + 0x20) = f | 0x180;
    if (flag & 0xFF) {
        *(s32 *)(out + 0x20) = f | 0x182;
    }
    *(u8 **)(*(u8 **)(*objp + 0x20) + 8) = out + 0x20;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C0390", handleHUD);

typedef struct {
    u16 btn;
    u8 pad2[4];
} PauseBtn;
typedef struct {
    f32 x;
    f32 y;
} PauseStick;
extern PauseBtn D_main_bss_80130B88[];
extern PauseStick D_mission_overlay_8010BDD8[];

s32 evalPauseMenuInputMode(s32 arg0, u32 arg1) {
    s32 r = 0;

    switch (arg1) {
    case 0:
        r = (D_mission_overlay_8010BDD8[arg0].y > 0.4f) | (u16)(D_main_bss_80130B88[arg0].btn & 0x800);
        break;
    case 1:
        r = (D_mission_overlay_8010BDD8[arg0].y < -0.4f) | (u16)(D_main_bss_80130B88[arg0].btn & 0x400);
        break;
    case 2:
        r = (D_mission_overlay_8010BDD8[arg0].x < -0.4f) | (u16)(D_main_bss_80130B88[arg0].btn & 0x200);
        break;
    case 3:
        r = (D_mission_overlay_8010BDD8[arg0].x > 0.4f) | (u16)(D_main_bss_80130B88[arg0].btn & 0x100);
        break;
    case 4:
        r = (u16)(D_main_bss_80130B88[arg0].btn & 0x4000);
        break;
    case 5:
        r = (u16)(D_main_bss_80130B88[arg0].btn & 0x1000);
        break;
    case 6:
        r = (u16)(D_main_bss_80130B88[arg0].btn & 0x8000);
        break;
    }
    return r != 0;
}

typedef struct {
    s16 x, y, z, pad;
} PsVtx;

typedef struct {
    u16 flags;
    s16 h2;
    s16 h4;
} PsEntry;

typedef struct {
    u8 pad0[0x234];
    s32 player;
    u8 pad238[0x20];
    u8 state;
    u8 pad259[3];
    f32 f25C;
    f32 f260;
    u8 pad264[0x7BC - 0x264];
    u16 h7BC[4];
    u8 b7C4;
    u8 b7C5;
    u8 pad7C6[0xC78 - 0x7C6];
    s32 wC78;
    s32 wC7C;
    s32 wC80;
    s32 wC84;
    void *pC88;
    s32 wC8C;
    s32 wC90;
    f32 vC94[12];
    s32 wCC4;
    s32 wCC8;
    s32 wCCC;
    s32 wCD0;
    s32 wCD4;
    s32 wCD8;
    s32 wCDC;
    f32 fCE0;
    void *pCE4;
    void *pCE8;
    s32 wCEC;
    u8 padCF0[0x30];
    s32 wD20;
    s32 wD24;
    void *pD28;
    s32 wD2C;
    s32 wD30;
    s32 wD34;
    s32 wD38;
    s16 hD3C;
    s16 hD3E;
    s16 hD40;
    s16 hD42;
    u8 bD44;
    u8 bD45;
    u8 bD46;
    u8 bD47;
    PsVtx v[4];
    s16 hD68;
    u8 bD6A;
    u8 bD6B;
    u8 bD6C;
    u8 padD6D[3];
    f32 fD70;
    f32 fD74;
    f32 fD78;
    f32 fD7C;
    f32 fD80;
} PsHud;

extern s32 D_mission_overlay_8010CA20_ps __asm__("D_mission_overlay_8010CA20");
extern s32 D_mission_overlay_8010C9E0_ps __asm__("D_mission_overlay_8010C9E0");
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_8010C9F1;
extern u16 D_mission_overlay_8010BFA8[];
extern u8 D_mission_overlay_80109D80[];
extern s32 D_main_bss_80130B50;
extern s32 D_main_bss_80138898;
extern s32 D_main_bss_80138928;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138926;
extern s8 D_main_bss_80130B14;
extern u8 D_main_bss_80130B60;
extern u8 D_main_bss_80130B61;
extern u8 D_main_bss_80130B62;
extern PsEntry pauseMenuMissionObjectives[];
extern PsEntry pauseMenuGameSettings[];
extern PsEntry pauseMenuAudioSettings[];
extern PsEntry pauseMenuAbortLevel[];
void setVec3At0x24_ps(void *, f32, f32, f32) __asm__("setVec3At0x24");
void clearStructPair2C30(void *);
void musyxSetSequenceParamLocked(s32, s32);
void playSimpleAudioCmd(s32, s32, s32);
void serializeSettingsToSaveAndPersist_ps(void) __asm__("serializeSettingsToSaveAndPersist");
void applyVolumeSettingsToMixer_ps(void) __asm__("applyVolumeSettingsToMixer");
s32 getSpeechPlaybackElapsedTime(s32);
void queueSpeechClipWithPriority(s32, s32, f32, s32);
void bsearchFactor5TableByU16Key(s32, s32, s32);

#define PS_GET_MENU(r, id)     if ((id) != 0) {         if ((id) != 1) {             if ((id) == 2) {                 r = pauseMenuAudioSettings;             } else {                 r = pauseMenuAbortLevel;             }         } else {             r = pauseMenuGameSettings;         }     } else {         r = pauseMenuMissionObjectives;     }

void initOrUpdatePauseScreenDim(PsHud *s, f32 dt) {
    PsEntry *cur;
    PsEntry *p;
    s32 cnt;
    s32 i;
    u16 *src;
    u16 *dst;

    if (s->state == 0) {
        void *cc4;
        f32 zero;
        if (D_mission_overlay_8010CA20_ps != 5) {
            return;
        }
        cc4 = &s->wCC4;
        s->state = 1;
        s->hD68 = 0;
        s->bD6A = 0;
        s->bD6B = 1;
        s->bD6C = 0;
        s->wC84 = 0;
        s->wC80 = 0;
        s->wC7C = 0;
        s->wC78 = 0;
        s->pC88 = cc4;
        s->wC8C = 0;
        zero = 0.0f;
        s->f25C = zero;
        s->f260 = zero;
        s->fD70 = zero;
        s->fD74 = zero;
        s->fD78 = zero;
        s->fD7C = zero;
        setVec3At0x24_ps(s->vC94, zero, zero, 1.0f);
        s->wCD0 = 0x02560000;
        s->wCD8 = 4;
        s->pCE4 = &s->wD20;
        s->wCC8 = 0;
        s->wCC4 = 0;
        s->wCCC = 0;
        s->fCE0 = zero;
        s->wCD4 = 0;
        s->wCDC = 0;
        s->pCE8 = s->v;
        s->wCEC = 0;
        clearStructPair2C30(cc4);
        s->pD28 = &s->wD30;
        s->wD2C = 1;
        s->wD30 = 8;
        s->hD40 = 1;
        s->hD3C = 3;
        s->hD3E = 2;
        s->v[3].x = -0x100;
        s->v[1].y = -0x100;
        s->v[0].y = -0x100;
        s->v[0].x = -0x100;
        s->wD24 = 0;
        s->wD20 = 0;
        s->wD34 = 0x060C5140;
        s->wD38 = 0;
        s->hD42 = 0;
        s->bD44 = 0;
        s->bD45 = 0;
        s->bD46 = 0;
        s->bD47 = 0;
        s->v[3].y = 0x100;
        s->v[2].y = 0x100;
        s->v[2].x = 0x100;
        s->v[1].x = 0x100;
        s->v[3].z = 0;
        s->v[2].z = 0;
        s->v[1].z = 0;
        s->v[0].z = 0;
        s->wD30 |= 2;
        musyxSetSequenceParamLocked(0x18, 0xA);
        musyxSetSequenceParamLocked(0x17, 0xA);
        playSimpleAudioCmd(0x7F, 0, 0xA);
        s->b7C4 = 0;
        s->fD80 = 8.0f;
        for (i = 0; i < 4; i++) {
            s->h7BC[i] = D_mission_overlay_8010BFA8[i];
            D_mission_overlay_8010BFA8[i] = 0;
        }
        if (!(D_main_bss_80130B50 & 1)) {
            D_main_bss_80138898 = (D_main_bss_80138898 & ~0x11) | 4;
            D_main_bss_80138928 = (D_main_bss_80138928 | 0x11) & ~4;
        } else {
            D_main_bss_80138898 |= 0xC;
            D_main_bss_80138928 |= ~0xC;
        }
    }
    s->f260 = s->f260 + dt * 0.25f * 3.1415927f;
    if (s->state == 1) {
        f32 f = s->f25C + dt;
        s->f25C = f;
        if (f >= 1.0f) {
            s->state = 3;
            s->f25C = 1.0f;
        }
        return;
    }
    if (s->state == 2) {
        f32 f = s->f25C - dt;
        s->f25C = f;
        if (f <= 0.0f) {
            s->state = 0;
            D_mission_overlay_8010C9E0_ps |= 0x20;
            musyxSetSequenceParamLocked(0x18, 0xFE);
            musyxSetSequenceParamLocked(0x17, 0xFE);
            for (i = 0; i < 4; i++) {
                D_mission_overlay_8010BFA8[i] = s->h7BC[i];
            }
            if (!(D_main_bss_80130B50 & 1)) {
                D_main_bss_80138898 &= ~0x15;
                D_main_bss_80138928 |= 0x15;
            } else {
                D_main_bss_80138898 &= ~0xC;
                D_main_bss_80138928 |= 0xC;
            }
        }
        if (D_mission_overlay_8010C9F1 != 0 && (D_mission_overlay_8010CA1C & 0x100) && s->f25C < 0.5f) {
            D_mission_overlay_8010CA1C &= ~0x100;
        }
        return;
    }
    if (s->state != 3) {
        return;
    }
    PS_GET_MENU(cur, s->bD6A);
    p = cur;
    if (s->bD6A == 0) {
        if (s->bD6C != 0) {
            if (--s->bD6C == 0) {
                serializeSettingsToSaveAndPersist_ps();
            }
        }
    }
    cnt = 0;
    {
        s32 k;
        for (k = 0; p[k].flags != 0xFFFF; k++) {
            if (p[k].flags & 1) {
                if (cnt++ == s->hD68) {
                    cur = &p[k];
                }
            }
        }
    }
    if (!(D_main_bss_80130B50 & 8) && s->bD6A == 0 && getSpeechPlaybackElapsedTime(0) < 0) {
        f32 f = s->fD80 - dt;
        s->fD80 = f;
        if (f <= 0.0f) {
            s32 idx = s->b7C4;
            u8 *tb = D_mission_overlay_80109D80;
            u8 *e = &tb[idx + gCurrentLevel * 4];
            if (*e != 0xFF && !((gMissionState.hiddenObjectiveFlags >> idx) & 1) && !((gMissionState.completedObjectiveFlags >> idx) & 1)) {
                queueSpeechClipWithPriority(*e + 0x2C0, 0x73, 0.0f, 0x80);
                s->b7C5 = s->b7C4;
                s->b7C4 = (s->b7C4 + 1) % 4;
                s->fD80 = s->b7C4 == 0 ? 1000.0f : 0.5f;
            } else {
                s->b7C4 = (idx + 1) % 4;
                s->fD80 = s->b7C4 == 0 ? 1000.0f : 0.1f;
                s->b7C5 = 0xFF;
            }
        } else {
            s->b7C5 = 0xFF;
        }
    }
    s->fD70 = s->fD70 + dt;
    s->fD78 = s->fD78 - dt;
    s->fD7C = s->fD7C - dt;
    s->fD74 = s->fD74 + dt * 0.75f;
    if (D_main_bss_80138838 != 0) {
        D_main_bss_80138898 &= ~0x1D;
        D_main_bss_80138928 |= 0x1D;
        if (D_main_bss_80138926 != 0) {
            D_mission_overlay_8010CA1C &= ~1;
        } else {
            D_mission_overlay_8010CA1C |= 1;
        }
        return;
    }
    if ((u8)evalPauseMenuInputMode(s->player, 4) && s->bD6A != 0 && s->bD6B == 0) {
        cnt = s->bD6B = 1;
        s->bD6A = 0;
        s->hD68 = 0;
        s->b7C4 = 0;
        s->fD80 = 8.0f;
    } else if ((u8)evalPauseMenuInputMode(s->player, 6) || (u8)evalPauseMenuInputMode(s->player, 5)) {
        if (s->bD6B == 0) {
            u16 fl;
            s->bD6B = 1;
            fl = cur->flags;
            if (fl & 0x20) {
                PsEntry *q;
                PS_GET_MENU(p, cur->h4);
                cnt = 0;
                {
                    s32 k;
                    for (k = 0; p[k].flags != 0xFFFF; k++) {
                        if (p[k].flags & 1) {
                            cnt++;
                            if ((p[k].flags & 0x20) && p[k].h4 == s->bD6A) {
                                break;
                            }
                        }
                    }
                }
            found:
                s->bD6A = cur->h4;
                s->hD68 = cnt - 1;
                s->b7C4 = 0;
                s->fD80 = 8.0f;
            } else if (fl & 0x80) {
                D_main_bss_80130B14 = 0;
                D_mission_overlay_8010C9E0_ps |= 1;
            } else if (fl & 4) {
                gGameSettings.unlockAndSettingsFlags[s->player] ^= 1 << cur->h4;
                s->bD6C = 3;
            } else if (fl & 8) {
                gGameSettings.unlockAndSettingsFlags[1] ^= 1 << cur->h4;
                s->bD6C = 3;
                if (cur->h4 == 7) {
                    applyVolumeSettingsToMixer_ps();
                }
            } else if (fl & 2) {
                D_mission_overlay_8010CA1C ^= 1 << cur->h4;
                s->bD6C = 3;
            } else if (fl & 0x40) {
                s->state = 2;
            }
            bsearchFactor5TableByU16Key(0x18, 0x5F, 0x40);
        }
    } else {
        s->bD6B = 0;
    }
    if (cur->flags & 0x200) {
        s32 changed = 0;
        f32 vol;
        u8 v;
        if (cur->h4 == 0) {
            v = D_main_bss_80130B60;
        } else if (cur->h4 == 1) {
            v = D_main_bss_80130B61;
        } else {
            v = D_main_bss_80130B62;
        }
        vol = v;
        if ((u8)evalPauseMenuInputMode(s->player, 2)) {
            vol -= dt * 32.0f;
            if (vol < 0.0f) {
                vol = 0.0f;
            }
            changed = 1;
        } else if ((u8)evalPauseMenuInputMode(s->player, 3)) {
            vol += dt * 32.0f;
            if (vol > 127.0f) {
                vol = 127.0f;
            }
            changed = 1;
        }
        if (changed) {
            if (cur->h4 == 0) {
                gGameSettings.musicVolume = (u32)vol;
            } else if (cur->h4 == 1) {
                gGameSettings.soundFxVolume = (u32)vol;
            } else {
                gGameSettings.speechVolume = (u32)vol;
            }
            s->bD6C = 3;
            applyVolumeSettingsToMixer_ps();
        }
    }
    if ((u8)evalPauseMenuInputMode(s->player, 0) || (cur->h2 == 0x32 && (u8)evalPauseMenuInputMode(s->player, 2))) {
        if (s->fD78 <= 0.0f) {
            s16 t;
            s->fD78 = 0.5f;
            s->fD70 = 0.25f;
            t = s->hD68 - 1;
            s->hD68 = t;
            if (t < 0) {
                s->hD68 = cnt - 1;
            }
            bsearchFactor5TableByU16Key(0x17, 0x5F, 0x40);
        }
    } else if ((u8)evalPauseMenuInputMode(s->player, 1) || (cur->h2 == 0x31 && (u8)evalPauseMenuInputMode(s->player, 3))) {
        if (s->fD78 <= 0.0f) {
            s16 t;
            s->fD78 = 0.5f;
            s->fD70 = 0.25f;
            t = s->hD68 + 1;
            s->hD68 = t;
            if (t >= cnt) {
                s->hD68 = 0;
            }
            bsearchFactor5TableByU16Key(0x17, 0x5F, 0x40);
        }
    } else {
        s->fD78 = 0.0f;
    }
    if (gGameSettings.unlockAndSettingsFlags[s->player] & 8) {
        D_mission_overlay_8010CA1C &= ~0x80;
    } else {
        D_mission_overlay_8010CA1C |= 0x80;
    }
    if (D_mission_overlay_8010CA20_ps != 5) {
        s->state = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C0390", runPauseMenuStateMachine);

void spawnHudNpc(void) {
    s32 var_a0;
    s32 var_v0;
    u32 var_a1;

    var_a1 = 0;
    for (var_a0 = 0; var_a0 < 4; var_a0++) {
        if (missionObjectiveTextIds[gCurrentLevel][var_a0] != 0) var_a1++;
    }
    gMissionState.numMissionObjectives = var_a1;
    D_mission_overlay_8010BFD0 = spawnNpcOfType(handleHUD, NULL, 4U, 0x64U);
}

s32 getAvailableShipsForLevel();

void broadcastSceneShutdownAndCleanup(void) {
    slotDispatcherIter(D_mission_overlay_8010BFD0, 0xC, NULL);
    getAvailableShipsForLevel();
}

s32 slotDispatcherIter(u16, s32, void *);

void broadcastSceneEventWithPayload(struct rgba *payload, f32 arg1) {
    D_mission_overlay_8010BFD8 = *payload;
    slotDispatcherIter(D_mission_overlay_8010BFD0, 5, &arg1);
}

void setRenderObjectTargetOrClear(u8 *obj, u16 id, struct rgba *payload) {
    if (id != 0xFFFF) {
        *(s32 *)(obj + 0x28) = id << 16;
        *(s32 *)(obj + 0x20) &= ~0x100;
        *(struct rgba *)(obj + 0x44) = *payload;
    } else {
        *(s32 *)(obj + 0x20) |= 0x100;
    }
}

f32 getPlayerHealthPercentage(s32 arg0) {
    if ((gPlayers[arg0].inner.currentHealth <= 0.0f)) {
        return 0.0f;
    } else {
        return gPlayers[arg0].inner.currentHealth / gPlayers[arg0].inner.maxHealth;
    } 
}

u8 *rs_strcpy(u8 *, u8 *);
s32 get_manifest_entry_type(u32, u8 *);
extern s32 D_main_bss_80137CFC;

s32 probeNumberedAssetFilename(u8 *buf, u8 *src, s32 n) {
    u8 *s;
    u8 saved;
    s32 i;

    if (src != NULL) {
        rs_strcpy(buf, src);
    }
    s = buf;
    for (i = 0; buf[i] != 0; i++) {
        if (buf[i] == '/') {
            s = &buf[i + 1];
        }
    }
    saved = *s;
    *s = n + '0';
    if (get_manifest_entry_type(D_main_bss_80137CFC, buf) != 1) {
        *s = saved;
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C0390", fake_func_800C41AC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C0390", D_mission_overlay_800A6724);
