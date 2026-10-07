#include "common.h"
#include "common_types.h"

typedef struct {
    u8 active;
    u8 pad1[3];
    u8 (*fn)(u32, u32, u32, u32, u32);
    void *unk8;
    void *unkC;
    u32 cursor;
    u32 arg;
} StreamedVoice;

extern u8 D_main_bss_80141AD0;
extern StreamedVoice D_main_bss_80152A20[];

void clearStreamedVoiceFlags(void) {
    s32 i;

    for (i = 0; i < D_main_bss_80141AD0; i++) {
        D_main_bss_80152A20[i].active = 0;
    }
}

extern void writebackDCacheHalfwords(u32, u32);
extern u32 getVoiceUserField(s32);

void serviceStreamedVoices(void) {
    s32 i;
    u32 cur;
    u32 old;

    for (i = 0; i < D_main_bss_80141AD0; i++) {
        if (D_main_bss_80152A20[i].active == 1) {
            cur = getVoiceUserField(i);
            old = D_main_bss_80152A20[i].cursor;
            if (old != cur) {
                if (old < cur) {
                    if (D_main_bss_80152A20[i].fn((u32)D_main_bss_80152A20[i].unk8 + old * 2, cur - old, 0, 0, D_main_bss_80152A20[i].arg)) {
                        writebackDCacheHalfwords((u32)D_main_bss_80152A20[i].unk8 + D_main_bss_80152A20[i].cursor * 2, cur - D_main_bss_80152A20[i].cursor);
                    }
                } else {
                    if (D_main_bss_80152A20[i].fn((u32)D_main_bss_80152A20[i].unk8 + old * 2, (u32)D_main_bss_80152A20[i].unkC - old, (u32)D_main_bss_80152A20[i].unk8, cur, D_main_bss_80152A20[i].arg)) {
                        writebackDCacheHalfwords((u32)D_main_bss_80152A20[i].unk8 + D_main_bss_80152A20[i].cursor * 2, (u32)D_main_bss_80152A20[i].unkC - D_main_bss_80152A20[i].cursor);
                        writebackDCacheHalfwords((u32)D_main_bss_80152A20[i].unk8, cur);
                    }
                }
            }
            D_main_bss_80152A20[i].cursor = cur;
        }
    }
}

void copyFourHalfwordsWriteback(void *, void *);

void flushStreamedVoiceBuffers(void) {
    s32 i;

    for (i = 0; i < D_main_bss_80141AD0; i++) {
        if (D_main_bss_80152A20[i].active == 1) {
            copyFourHalfwordsWriteback(D_main_bss_80152A20[i].unk8, D_main_bss_80152A20[i].unkC);
        }
    }
}

typedef struct {
    u32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    u8 b18;
} SsvSample;
extern u8 gMusyXActiveFlag;
extern f64 D_main_8003DE70;
extern f32 D_main_8003DE78;
extern f32 D_main_8003DE7C;
extern s32 D_main_bss_801440C0;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();
s32 stopVoiceByKey(u8);
void musyxInitVoiceFromSample(s32, SsvSample *, s32);
void musyxSetVoicePitchBend(s32, u16);
void setVoiceModulationParams(s32, s32, s32, s32, s32);
void musyxTriggerVoiceAttack(s32);

s32 startStreamedSampleVoice(u8 key, s32 buf, s32 len, u32 rate, u8 p4, u8 p5, u8 p6, u8 p7, void *fn, s32 arg) {
    SsvSample s;
    s32 v;
    f64 d;
    f32 f;
    u32 t;

    if (gMusyXActiveFlag != 0) {
    factor5MutexAcquire();
    v = stopVoiceByKey(key);
    if (v != -1) {
        D_main_bss_80152A20[v].unk8 = (void *)buf;
        D_main_bss_80152A20[v].unkC = (void *)len;
        D_main_bss_80152A20[v].fn = fn;
        D_main_bss_80152A20[v].active = 1;
        D_main_bss_80152A20[v].cursor = 0;
        D_main_bss_80152A20[v].arg = arg;
        s.w0 = rate | 0x400000;
        s.w4 = buf;
        s.w8 = 0;
        s.wC = len;
        s.w10 = 0;
        s.w14 = len;
        s.b18 = 0;
        musyxInitVoiceFromSample(v, &s, 1);
        d = (s32)rate;
        if ((s32)rate < 0) {
            d += D_main_8003DE70;
        }
        f = (f32)d / (f32)D_main_bss_801440C0 * D_main_8003DE78;
        if (!(f >= D_main_8003DE7C)) {
            t = (s32)f;
        } else {
            t = (s32)(f - D_main_8003DE7C);
            t |= 0x80000000;
        }
        musyxSetVoicePitchBend(v, t);
        setVoiceModulationParams(v, p4 << 16, p5 << 16, p6 << 16, p7 << 16);
        musyxTriggerVoiceAttack(v);
    }
    factor5MutexRelease();
    return v;
    }
    return -1;
}

s32 streamSampleCountToByteSize(s32 arg0) {
    return (arg0 + 4) * 2;
}

extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();
void setVoiceModulationParams(s32, s32, s32, s32, s32);

void setVoiceVolumePanLocked(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    if ((gMusyXActiveFlag != 0) & (~arg0 != 0)) {
        factor5MutexAcquire();
        setVoiceModulationParams(arg0, arg1 << 0x10, arg2 << 0x10, arg3 << 0x10, arg4 << 0x10);
        factor5MutexRelease();
    }
}

extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();
void silenceVoiceSlot(s32);

void stopStreamedVoice(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        if (D_main_bss_80152A20[arg0].active == 1) {
            D_main_bss_80152A20[arg0].active = 0;
            silenceVoiceSlot(arg0);
        }
        factor5MutexRelease();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/98960", compute3DSourceSpatialMix);

INCLUDE_ASM("asm/nonmatchings/main/98960", applyVoice3DMixParams);

extern f32 D_main_8003DEC0;
extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();

typedef struct {
    s32 x, y, z;
} Vec3i;

typedef struct {
    u8 pad0[0xC];
    Vec3i pos;
    Vec3i vel;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} Active3DSource;

s32 updateActive3DAudioSource(Active3DSource *arg0, Vec3i *arg1, Vec3i *arg2, u8 arg3) {
    f32 v;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        v = (f32)arg3 / D_main_8003DEC0;
        arg0->pos = *arg1;
        arg0->vel = *arg2;
        arg0->unk28 = v;
        if (v < arg0->unk2C) {
            arg0->unk2C = v;
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

extern u8 gMusyXActiveFlag;

s32 isAudioVoiceActive(u8 *voice) {
    s32 r;

    if (gMusyXActiveFlag == 0) {
        r = 0;
    } else {
        r = *(u16 *)(voice + 8) & 1;
    }
    return r;
}

extern f32 D_main_8003DEC4;
extern u8 D_main_bss_80152D20[];
extern s32 D_main_bss_80153414;
extern void compute3DSourceSpatialMix(u8 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern s32 bsearchFactor5TableByU16Key(u16, s32, s32);
extern void applyVoice3DMixParams(void *, f32, f32, f32, f32, f32);

s32 play3DSoundEvent(u8 *arg0, Vec3i *arg1, Vec3i *arg2, f32 arg3, f32 arg4, s32 arg5, u16 arg6, u8 arg7, u8 arg8)
{
  f32 sp18;
  f32 sp1C;
  f32 sp20;
  f32 sp24;
  f32 sp28;
  u8 *s0;
  u8 *head;
  s32 r;
  f32 va;
  f32 vb;
  u32 t7;
  u32 fl;
  if (gMusyXActiveFlag != 0)
  {
    t7 = arg6 | 0x80000000;
    factor5MutexAcquire();
    s0 = arg0;
    if (s0 == 0)
    {
      s0 = D_main_bss_80152D20;
    }
    va = ((f32) arg7) / D_main_8003DEC4;
    vb = ((f32) arg8) / D_main_8003DEC4;
    *((s32 *) (s0 + 8)) = arg5;
    *((Vec3i *) (s0 + 0xC)) = *arg1;
    *((Vec3i *) (s0 + 0x18)) = *arg2;
    *((f32 *) (s0 + 0x24)) = arg3;
    *((u16 *) (s0 + 0x3C)) = arg6;
    *((f32 *) (s0 + 0x30)) = arg4;
    *((u32 *) (s0 + 0x38)) = t7;
    *((f32 *) (s0 + 0x28)) = va;
    *((f32 *) (s0 + 0x2C)) = vb;
    if (arg0 == 0)
    {
      compute3DSourceSpatialMix(s0, &sp18, &sp1C, &sp20, &sp24, &sp28);
      if (sp18 != 0.0f)
      {
        r = bsearchFactor5TableByU16Key(*((u16 *) (s0 + 0x3C)), 0x7F, 0x40);
        *((s32 *) (s0 + 0x34)) = r;
        if (r != (-1))
        {
          applyVoice3DMixParams(s0, sp18, sp20, sp24, sp28, sp1C);
          factor5MutexRelease();
          return *((s32 *) (s0 + 0x34));
        }
      }
    }
    else
    {
      head = (u8 *) D_main_bss_80153414;
      *((u8 **) (s0 + 0)) = head;
      if (head != 0)
      {
        *((u8 **) (head + 4)) = s0;
      }
      fl = *((u32 *) (s0 + 8));
      *((s32 *) (s0 + 0x34)) = -1;
      *((s32 *) (s0 + 4)) = 0;
      D_main_bss_80153414 = (s32) s0;
      *((u16 *) (s0 + 0x3E)) = 0;
      *((u32 *) (s0 + 8)) = fl | 0x30000;
    }
    factor5MutexRelease();
  }
  return -1;
}

extern u8 D_main_bss_80152D20[];
extern s32 D_main_bss_80153414;
extern f32 D_main_8003DEC8;
extern void compute3DSourceSpatialMix(u8 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern s32 bsearchFactor5TableByU16Key(u16, s32, s32);
extern void applyVoice3DMixParams(void *, f32, f32, f32, f32, f32);

s32 play3DSoundEventVariant(u8 *arg0, Vec3i *arg1, Vec3i *arg2, f32 arg3, f32 arg4, s32 arg5, u16 arg6, u16 arg7, u8 arg8, u8 arg9)
{
  f32 sp18;
  f32 sp1C;
  f32 sp20;
  f32 sp24;
  f32 sp28;
  int new_var;
  u8 *s0;
  u8 *head;
  s32 r;
  f32 va;
  f32 vb;
  s32 t7;
  u32 fl;
  if (gMusyXActiveFlag != 0)
  {
    new_var = arg7;
    t7 = new_var;
    factor5MutexAcquire();
    s0 = arg0;
    if (s0 == 0)
    {
      s0 = D_main_bss_80152D20;
    }
    va = ((f32) arg8) / D_main_8003DEC8;
    vb = ((f32) arg9) / D_main_8003DEC8;
    *((s32 *) (s0 + 8)) = arg5;
    *((Vec3i *) (s0 + 0xC)) = *arg1;
    *((Vec3i *) (s0 + 0x18)) = *arg2;
    *((f32 *) (s0 + 0x24)) = arg3;
    *((u16 *) (s0 + 0x3C)) = arg6;
    *((f32 *) (s0 + 0x30)) = arg4;
    *((s32 *) (s0 + 0x38)) = t7;
    *((f32 *) (s0 + 0x28)) = va;
    *((f32 *) (s0 + 0x2C)) = vb;
    if (arg0 == 0)
    {
      compute3DSourceSpatialMix(s0, &sp18, &sp1C, &sp20, &sp24, &sp28);
      if (sp18 != 0.0f)
      {
        r = bsearchFactor5TableByU16Key(*((u16 *) (s0 + 0x3C)), 0x7F, 0x40);
        *((s32 *) (s0 + 0x34)) = r;
        if (r != (-1))
        {
          applyVoice3DMixParams(s0, sp18, sp20, sp24, sp28, sp1C);
          factor5MutexRelease();
          return *((s32 *) (s0 + 0x34));
        }
      }
    }
    else
    {
      head = (u8 *) D_main_bss_80153414;
      *((u8 **) (s0 + 0)) = head;
      if (head != 0)
      {
        *((u8 **) (head + 4)) = s0;
      }
      fl = *((u32 *) (s0 + 8));
      *((s32 *) (s0 + 0x34)) = -1;
      *((s32 *) (s0 + 4)) = 0;
      D_main_bss_80153414 = (s32) s0;
      *((u16 *) (s0 + 0x3E)) = 0;
      *((u32 *) (s0 + 8)) = fl | 0x30000;
    }
    factor5MutexRelease();
  }
  return -1;
}

extern s32 D_main_bss_80153414;
extern u8 gMusyXActiveFlag;
s32 flagVoiceChainForStop(s32);
s32 factor5MutexAcquire();
s32 factor5MutexRelease();

inline s32 factor5RemoveListNode(void *arg0) {
    s32 temp_a0;
    void **temp_v1_2;
    void *temp_v1;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        temp_v1 = (*(void **)((u8 *)(arg0) + 0));
        if (temp_v1 != NULL) {
            (*(void ***)((u8 *)(temp_v1) + 4)) = (void **) (*(void ***)((u8 *)(arg0) + 4));
        }
        temp_v1_2 = (*(void ***)((u8 *)(arg0) + 4));
        if (temp_v1_2 != NULL) {
            *temp_v1_2 = (*(void **)((u8 *)(arg0) + 0));
        } else {
            D_main_bss_80153414 = (s32) (*(void **)((u8 *)(arg0) + 0));
        }
        temp_a0 = (*(s32 *)((u8 *)(arg0) + 0x34));
        (*(s32 *)((u8 *)(arg0) + 8)) = (s32) (*(u16 *)((u8 *)(arg0) + 0xA));
        if (temp_a0 != -1) {
            flagVoiceChainForStop(temp_a0);
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

s32 factor5MutexAcquire();
s32 factor5MutexRelease();
extern u8 gMusyXActiveFlag;

s32 mostlyMusyxFlagGatedHelper(void *arg0) {
    s32 var_s1;

    var_s1 = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        if ((*(s32 *)((u8 *)(arg0) + 8)) & 0x10000) {
            var_s1 = (*(s32 *)((u8 *)(arg0) + 0x34));
        }
        factor5MutexRelease();
    }
    return var_s1;
}

void tickAndReap3DAudioVoices(void) {
    void *node = (void *)D_main_bss_80153414;
    void *next;

    while (node != NULL) {
        next = *(void **)node;
        factor5RemoveListNode(node);
        node = next;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} IVec3;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} FVec3;

typedef struct {
    u8 pad0[0xC];
    IVec3 pos;
    IVec3 vel;
    IVec3 up;
    FVec3 cross;
    FVec3 fwd;
    f32 inv[15];
    f32 volume;
} MusyX3D;

extern f32 D_main_8003DECC;
extern void crossProductVec3(void *, void *, void *);
extern void invertOrientationMatrix(void *, void *);

s32 setMusyX3DProperties(MusyX3D *arg0, IVec3 *arg1, IVec3 *arg2, IVec3 *arg3, FVec3 *arg4, u8 arg5) {
    f32 sp10[12];

    if (gMusyXActiveFlag != 0) {
    factor5MutexAcquire();
    arg0->pos = *arg1;
    arg0->vel = *arg2;
    arg0->up = *arg3;
    arg0->fwd.x = -arg4->x;
    arg0->fwd.y = -arg4->y;
    arg0->fwd.z = -arg4->z;
    crossProductVec3(&arg0->cross, &arg0->fwd, &arg0->up);
    sp10[0] = arg0->cross.x;
    sp10[3] = arg0->cross.y;
    sp10[6] = arg0->cross.z;
    sp10[1] = arg0->fwd.x;
    sp10[4] = arg0->fwd.y;
    sp10[7] = arg0->fwd.z;
    sp10[2] = *(f32 *)&arg0->up.x;
    sp10[5] = *(f32 *)&arg0->up.y;
    sp10[8] = *(f32 *)&arg0->up.z;
    sp10[9] = *(f32 *)&arg0->pos.x;
    sp10[10] = *(f32 *)&arg0->pos.y;
    sp10[11] = *(f32 *)&arg0->pos.z;
    invertOrientationMatrix(&arg0->inv, sp10);
    arg0->volume = (f32)arg5 / D_main_8003DECC;
    factor5MutexRelease();
    return 1;
    }
    return 0;
}

extern s32 D_main_bss_80153418;
extern f32 D_main_8003DED0;

s32 register3DAudioListenerNode(MusyX3D *arg0, IVec3 *arg1, IVec3 *arg2, IVec3 *arg3, FVec3 *arg4, f32 arg5, f32 arg6, f32 arg7, s32 arg8, u8 arg9) {
    f32 sp10[12];
    MusyX3D *head;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        head = (MusyX3D *)D_main_bss_80153418;
        *(MusyX3D **)((u8 *)arg0 + 0) = head;
        if (head != 0) {
            *(MusyX3D **)((u8 *)head + 4) = arg0;
        }
        *(s32 *)((u8 *)arg0 + 4) = 0;
        D_main_bss_80153418 = (s32)arg0;
        arg0->pos = *arg1;
        arg0->vel = *arg2;
        arg0->up = *arg3;
        arg0->fwd.x = -arg4->x;
        arg0->fwd.y = -arg4->y;
        arg0->fwd.z = -arg4->z;
        arg0->inv[12] = arg5;
        arg0->inv[13] = arg6;
        arg0->inv[14] = arg7;
        crossProductVec3(&arg0->cross, &arg0->fwd, &arg0->up);
        sp10[0] = arg0->cross.x;
        sp10[3] = arg0->cross.y;
        sp10[6] = arg0->cross.z;
        sp10[1] = arg0->fwd.x;
        sp10[4] = arg0->fwd.y;
        sp10[7] = arg0->fwd.z;
        sp10[2] = *(f32 *)&arg0->up.x;
        sp10[5] = *(f32 *)&arg0->up.y;
        sp10[8] = *(f32 *)&arg0->up.z;
        sp10[9] = *(f32 *)&arg0->pos.x;
        sp10[10] = *(f32 *)&arg0->pos.y;
        sp10[11] = *(f32 *)&arg0->pos.z;
        invertOrientationMatrix(&arg0->inv, sp10);
        arg0->volume = (f32)arg9 / D_main_8003DED0;
        *(s32 *)((u8 *)arg0 + 8) = arg8;
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

extern s32 D_main_bss_80153418;
s32 unlinkMusyXListNode(void *arg0) {
    void **temp_v1_2;
    void *temp_v1;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        temp_v1 = (*(void **)((u8 *)(arg0) + 0));
        if (temp_v1 != NULL) {
            (*(void ***)((u8 *)(temp_v1) + 4)) = (void **) (*(void ***)((u8 *)(arg0) + 4));
        }
        temp_v1_2 = (*(void ***)((u8 *)(arg0) + 4));
        if (temp_v1_2 != NULL) {
            *temp_v1_2 = (*(void **)((u8 *)(arg0) + 0));
        } else {
            D_main_bss_80153418 = (s32) (*(void **)((u8 *)(arg0) + 0));
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

typedef struct SndNode {
    struct SndNode *next;
    f32 pri;
    void *snd;
} SndNode;
typedef struct {
    s32 id;
    s32 unk4;
    SndNode *head;
} SndGroup;
extern SndGroup D_main_bss_80152D70[];
extern u8 D_main_bss_80152EF0;
extern SndNode D_main_bss_80153290[];
extern u8 D_main_bss_80153410;

void enqueueSoundInPriorityGroup(void *arg0, f32 arg1) {
    s32 i;
    SndNode *prev;
    SndNode *cur;
    s32 cnt;
    s32 k;

    for (i = 0; i < D_main_bss_80152EF0; i++) {
        if (*(s32 *)((u8 *)arg0 + 0x38) == D_main_bss_80152D70[i].id) {
            break;
        }
    }
    if (i == D_main_bss_80152EF0) {
        D_main_bss_80152D70[i].unk4 = 0;
        D_main_bss_80152D70[i].head = 0;
        cnt = *(s32 *)((u8 *)arg0 + 0x38);
        D_main_bss_80152EF0++;
        D_main_bss_80152D70[i].id = cnt;
    }
    cur = D_main_bss_80152D70[i].head;
    prev = 0;
    while (cur != 0) {
        if (arg1 < cur->pri) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    if (prev == 0) {
        D_main_bss_80152D70[i].head = &D_main_bss_80153290[D_main_bss_80153410];
    } else {
        prev->next = &D_main_bss_80153290[D_main_bss_80153410];
    }
    k = D_main_bss_80153410;
    D_main_bss_80153290[k].next = cur;
    D_main_bss_80153290[k].snd = arg0;
    D_main_bss_80153410 = k + 1;
    D_main_bss_80153290[k].pri = arg1;
}

typedef struct PNode {
    struct PNode *next;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u8 *voice;
} PNode;
extern PNode D_main_bss_80152F00[];
extern u8 D_main_bss_80153280;

s32 enqueueSpatialSoundInPriorityGroup(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;
    PNode *cur;
    s32 cnt;
    s32 k;

    for (i = 0; i < D_main_bss_80152EF0; i++) {
        if (*(s32 *)(arg0 + 0x38) == D_main_bss_80152D70[i].id) {
            break;
        }
    }
    if (i == D_main_bss_80152EF0) {
        if (i == 0x20) {
            return 0;
        }
        D_main_bss_80152D70[i].unk4 = 0;
        D_main_bss_80152D70[i].head = 0;
        cnt = *(s32 *)(arg0 + 0x38);
        D_main_bss_80152EF0++;
        D_main_bss_80152D70[i].id = cnt;
    }
    if (D_main_bss_80153280 == 0x20) {
        return 0;
    }
    cur = (PNode *)D_main_bss_80152D70[i].unk4;
    if (cur != 0) {
        while (cur->next != 0) {
            if (cur->f4 < arg1) break;
            cur = cur->next;
        }
        D_main_bss_80152F00[D_main_bss_80153280].next = cur->next;
        cur->next = &D_main_bss_80152F00[D_main_bss_80153280];
    } else {
        D_main_bss_80152F00[D_main_bss_80153280].next = 0;
        D_main_bss_80152D70[i].unk4 = (s32)&D_main_bss_80152F00[D_main_bss_80153280];
    }
    k = D_main_bss_80153280;
    D_main_bss_80152F00[k].voice = arg0;
    D_main_bss_80152F00[k].f14 = arg5;
    D_main_bss_80152F00[k].f8 = arg2;
    D_main_bss_80152F00[k].fC = arg3;
    D_main_bss_80152F00[k].f10 = arg4;
    D_main_bss_80153280 = k + 1;
    D_main_bss_80152F00[k].f4 = arg1;
    return 1;
}

typedef struct PendNode {
    struct PendNode *next;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u8 *voice;
} PendNode;
extern f32 D_main_8003DED4;
extern f32 D_main_8003DED8;
extern s32 musyxNoteEventLockedDispatch(u16, s32, s32);
extern void applyVoice3DMixParams(void *, f32, f32, f32, f32, f32);

void dispatchPrioritizedSoundQueue(void) {
    s32 i;
    PendNode *n;
    SndNode *h;
    u8 *v;
    u8 *tv;
    f32 diff;
    s32 r;

    for (i = 0; i < D_main_bss_80152EF0; i++) {
        n = (PendNode *)D_main_bss_80152D70[i].unk4;
        if (n != 0) {
            do {
                h = D_main_bss_80152D70[i].head;
                if (h != 0) {
                    diff = n->f4 - h->pri;
                    if (diff <= D_main_8003DED4) {
                        goto next;
                    }
                    if (diff <= D_main_8003DED8) {
                        tv = n->voice;
                        (*(u16 *)(tv + 0x3E))++;
                        if (*(u16 *)(tv + 0x3E) < 0x14) {
                            goto next;
                        }
                    } else {
                        *(u16 *)(n->voice + 0x3E) = 0;
                    }
                }
                v = n->voice;
                r = musyxNoteEventLockedDispatch(*(u16 *)(v + 0x3C), 0x7F, 0x40);
                *(s32 *)(v + 0x34) = r;
                if (r == -1) {
                    if (!(*(u32 *)(v + 8) & 2)) {
                        *(u32 *)(v + 8) = (*(u32 *)(v + 8) | 0x40000) & 0xFFFDFFFF;
                    }
                } else {
                    *(s32 *)(v + 0x40) = 0;
                    *(u32 *)(v + 8) |= 0x100000;
                    applyVoice3DMixParams(v, n->f4, n->f8, n->fC, n->f10, n->f14);
                    *(u32 *)(v + 8) &= 0xFFFDFFFF;
                    if (D_main_bss_80152D70[i].head != 0) {
                        D_main_bss_80152D70[i].head = D_main_bss_80152D70[i].head->next;
                    }
                }
            next:
                n = n->next;
            } while (n != 0);
        }
    }
}

extern s32 D_main_bss_8015341C;
extern const f32 D_main_8003DEDC;
extern const f32 D_main_8003DEE0;
s32 validateVoiceHandle(s32);

void update3DAudioFrame(void) {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    u8 *v;
    u8 *next;
    u32 fl;
    s32 h;
    s32 r;
    s32 n;
    u32 f0;
    f32 t;

    v = (u8 *)D_main_bss_80153414;
    D_main_bss_8015341C = 0;
    D_main_bss_80152EF0 = 0;
    D_main_bss_80153280 = 0;
    D_main_bss_80153410 = 0;
    if (v != NULL) {
        do {
            n = D_main_bss_8015341C + 1;
            f0 = *(u32 *)(v + 8);
            next = *(u8 **)v;
            D_main_bss_8015341C = n;
            if (f0 & 0x40000) {
                if (*(void **)v != NULL) {
                    ((void **)*(void **)v)[1] = ((void **)v)[1];
                }
                if (((void ***)v)[1] != NULL) {
                    *((void ***)v)[1] = *(void **)v;
                } else {
                    D_main_bss_80153414 = *(s32 *)v;
                }
                h = *(s32 *)(v + 0x34);
                *(u32 *)(v + 8) = *(u16 *)(v + 0xA);
                if (h != -1) {
                    flagVoiceChainForStop(h);
                }
            } else {
                if (f0 & 0x20001) {
                    compute3DSourceSpatialMix(v, &a, &b, &c, &d, &e);
                }
                fl = *(u32 *)(v + 8);
                if (!(fl & 0x80000)) {
                    if (fl & 0x20000) {
                        if (a == 0.0f && (fl & 4)) {
                            *(u32 *)(v + 8) = (fl | 0x80000) & 0xFFFDFFFF;
                        } else if (*(u32 *)(v + 8) & 1) {
                            if ((u8)enqueueSpatialSoundInPriorityGroup(v, a, c, d, e, b)) {
                                goto next;
                            }
                        } else {
                            r = musyxNoteEventLockedDispatch(*(u16 *)(v + 0x3C), 0x7F, 0x40);
                            *(s32 *)(v + 0x34) = r;
                            if (r == -1) {
                                fl = *(u32 *)(v + 8);
                                if (fl & 2) {
                                    goto next;
                                }
                                *(u32 *)(v + 8) = (fl | 0x40000) & 0xFFFDFFFF;
                            }
                        }
                    } else {
                        r = validateVoiceHandle(*(s32 *)(v + 0x34));
                        *(s32 *)(v + 0x34) = r;
                        if (r == -1) {
                            fl = *(u32 *)(v + 8);
                            if (fl & 2) {
                                *(u32 *)(v + 8) = fl | 0x20000;
                            } else {
                                *(u32 *)(v + 8) = fl | 0x40000;
                            }
                        }
                    }
                    if (*(s32 *)(v + 0x34) != -1) {
                        if (*(u32 *)(v + 8) & 1) {
                            enqueueSoundInPriorityGroup(v, a);
                        }
                        if (a == 0.0f && ((fl = *(u32 *)(v + 8)) & 4)) {
                            *(u32 *)(v + 8) = fl | 0x80000;
                            flagVoiceChainForStop(*(s32 *)(v + 0x34));
                            *(s32 *)(v + 0x34) = -1;
                        } else {
                            applyVoice3DMixParams(v, a, c, d, e, b);
                        }
                    }
                    if (*(u32 *)(v + 8) & 0x100000) {
                        t = *(f32 *)(v + 0x40) + D_main_8003DEDC;
                        *(f32 *)(v + 0x40) = t;
                        if (D_main_8003DEE0 <= t) {
                            *(u32 *)(v + 8) &= 0xFFEFFFFF;
                        }
                    }
                } else {
                    if (a == 0.0f) {
                        goto next;
                    }
                    *(u32 *)(v + 8) = (fl & 0xFFF7FFFF) | 0x20000;
                }
            }
        next:
            v = next;
        } while (v != NULL);
    }
    dispatchPrioritizedSoundQueue();
}

extern s32 D_main_bss_80153414;
extern s32 D_main_bss_80153418;

void reset3DAudioLists(void) {
    D_main_bss_80153414 = 0;
    D_main_bss_80153418 = 0;
}

void noopHandler_80099C44(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/98960", fake_func_80099C4C);
