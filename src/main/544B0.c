#include "common.h"
#include "common_types.h"
#include "main/3F160.h"

INCLUDE_ASM("asm/nonmatchings/main/544B0", trackResourceListWithMappingTables);

typedef struct {
    u8 pad0[0xC];
    u32 flags;
    u8 pad10[0x14];
    s32 src;
} OvlMdlNode;

typedef struct {
    u8 pad0[2];
    s16 type;
    s32 root;
    OvlMdlNode **wnd;
    OvlMdlNode **crmA;
    OvlMdlNode **crmB;
    OvlMdlNode **eng[2];
    s32 engBuf[2];
    s16 engFlag[2];
    u8 pad28[4];
    f32 f2C;
    f32 f30;
} OvlSetupDst;

extern OvlMdlNode **findModelChildNodeByName(s32, char *);
extern s32 rs_strcmp(s32, char *);
extern void setMaterialFlagByIdInMeshTree(OvlMdlNode *, s32, u16);
extern int sprintf(char *, const char *, ...);
extern void zmemcpy(s32, s32, s32);
extern s32 rs_malloc(s32, s32);
extern u16 D_main_bss_80137C70;

void dispatchOverlaySetupV(s32, s32, s32) __asm__("dispatchOverlaySetupByParentAssetName");

void dispatchOverlaySetupV(s32 a0, s32 a1, s32 arg2) {
    s32 *arg0 = (s32 *)a0;
    char buf[16];
    s16 t;
    s16 t2;
    s32 i;
    OvlSetupDst *arg1 = (OvlSetupDst *)a1;
    s32 name;
    OvlSetupDst *p1;
    OvlSetupDst *p0;
    OvlMdlNode **n;

    name = *arg0;
    if (rs_strcmp(name, "awing") != 0) {
        if (rs_strcmp(name, "vwing") != 0) {
            if (rs_strcmp(name, "xwing") != 0) {
                if (rs_strcmp(name, "ywing") != 0) {
                    if (rs_strcmp(name, "snowspeeder") != 0) {
                        if (rs_strcmp(name, "falcon") != 0) {
                            if (rs_strcmp(name, "tie_inter") != 0) {
                                if (rs_strcmp(name, "koelsch") != 0) {
                                    if (rs_strcmp(name, "t16") == 0) {
                                        t = 7;
                                    } else {
                                        t = -1;
                                    }
                                } else {
                                    t = 8;
                                }
                            } else {
                                t = 6;
                            }
                        } else {
                            t = 5;
                        }
                    } else {
                        t = 4;
                    }
                } else {
                    t = 3;
                }
            } else {
                t = 2;
            }
        } else {
            t = 1;
        }
    } else {
        t = 0;
    }
    arg1->type = t;
    if (t < 0) {
        return;
    }
    arg1->root = (s32)arg0;
    n = findModelChildNodeByName((s32)arg0, "wnd_a");
    arg1->wnd = n;
    if (n != 0) {
        (*n)->flags &= ~8;
        setMaterialFlagByIdInMeshTree(*arg1->wnd, 0xFFFF, D_main_bss_80137C70);
    }
    arg1->crmA = 0;
    arg1->crmB = 0;
    for (i = 0; i < 2; i++) {
        arg1->engBuf[i] = rs_malloc(0x80, 0);
        sprintf(buf, "eng_%c", i + 0x61);
        n = findModelChildNodeByName((s32)arg0, buf);
        arg1->eng[i] = n;
        if (n != 0) {
            (*n)->flags &= ~8;
            zmemcpy(arg1->engBuf[i], (*arg1->eng[i])->src, 0x80);
            arg1->engFlag[i] = 0;
        } else {
            arg1->engFlag[i] = 0;
        }
    }
    {
        switch (arg1->type) {
        case 0:
            arg1->f2C = 3.0f;
            arg1->f30 = 5.625f;
            break;
        case 1:
            arg1->f2C = 3.0f;
            arg1->f30 = 4.5f;
            break;
        case 2:
            arg1->f2C = 1.875f;
            arg1->f30 = 3.75f;
            break;
        case 3:
            arg1->f2C = 2.25f;
            arg1->f30 = 3.375f;
            break;
        case 4:
            arg1->f2C = 2.625f;
            arg1->f30 = 3.5625f;
            break;
        case 5:
            arg1->f2C = 2.25f;
            arg1->f30 = 5.625f;
            break;
        case 6:
            arg1->f2C = 2.625f;
            arg1->f30 = 4.5f;
            break;
        case 8:
            n = findModelChildNodeByName((s32)arg0, "crm_a");
            arg1->crmA = n;
            if (n != 0) {
                (*n)->flags &= ~8;
            }
            n = findModelChildNodeByName((s32)arg0, "crm_b");
            arg1->crmB = n;
            if (n != 0) {
                (*n)->flags &= ~8;
            }
        case 7:
            arg1->f2C = 2.25f;
            arg1->f30 = 6.0f;
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/544B0", updateAnimatedTextureStreaming);

s32 rs_free(s32);
void *getNpcContextField8(u16);
void updateAnimatedTextureStreaming(u16 *, f32 *, f32);
extern char D_main_8009EBD0[];
extern u8 *D_main_bss_80138D1C;
extern u16 D_main_bss_80139594;
typedef struct {
    u8 pad0[4];
    char *unk4;
} MeshOvl;
typedef struct {
    u8 pad0[0x24];
    f32 x;
    f32 y;
    f32 z;
} NpcVec;
s32 attachedMeshOverlayNpcHandler(struct D_80130BB8_type *arg0, s32 a1, u16 *arg2) {
    s32 arg1 = a1 & 0xFFFF;
    f32 sp10[3];
    f32 len;
    f32 sq;
    NpcVec *v;
    MeshOvl *ovl;
    u16 *data;
    s32 i;
    s32 *p;

    data = (u16 *)arg0->unk04;
    switch (arg1) {
    case 1:
        *data = *arg2;
        ovl = (MeshOvl *)getNpcContextByIndex(*data)->unk0C;
        if (ovl == NULL) {
            destroyNpcSlotByIndex(arg0->unk16);
            return 1;
        }
        dispatchOverlaySetupByParentAssetName((s32)ovl, (s32)data, *data);
        *(char **)((char *)ovl + 4) = D_main_8009EBD0;
        popNpcSlotFromTail(D_main_bss_80139594, arg0);
        return 1;
    case 2:
        i = 0;
        p = (s32 *)data;
        do {
            rs_free(p[7]);
            p++;
            i++;
        } while (i < 2);
        return 1;
    case 4:
        ovl = (MeshOvl *)getNpcContextByIndex(*data)->unk0C;
        if (ovl != NULL) {
            v = getNpcContextField8(*data);
            sq = v->x * v->x + v->y * v->y + v->z * v->z;
            __asm__ volatile("sqrt.s %0, %1" : "=f"(len) : "f"(sq));
            sp10[0] = *(f32 *)(D_main_bss_80138D1C + 0x4C);
            sp10[1] = *(f32 *)(D_main_bss_80138D1C + 0x50);
            sp10[2] = *(f32 *)(D_main_bss_80138D1C + 0x54);
            updateAnimatedTextureStreaming(data, sp10, len);
        }
        return 1;
    }
    return 1;
}

typedef struct {
    s16 material_type;
    f32 misc_float;
    f32 one;
    s32 zero;
    u8 alwaysa;
    u8 pad[0x17];
} HdrMat;
extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;
extern u16 D_main_bss_80137C70;
u32 get_asset_size_extra(s32, char *);
s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
void setupAssetDma(s32, s32, s32, s32, u32, void *);
void teardownAssetDma(s32, s32);
s32 rs_free(s32);
s32 rs_malloc(s32, s32);
void full_header_image_offset_convert(void *, void *);
s32 registerHmtTextureInTable(void *, void *, s32);

u16 load_full_header_image(char *name) {
    HdrMat mat;
    u32 size;
    s32 buf;
    s32 handle;
    s32 hdr;

    size = get_asset_size_extra(D_main_bss_80137CFC, name);
    buf = rs_malloc(size, 0);
    handle = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, name, 0);
    setupAssetDma(D_main_bss_80138920, 0, handle, 0, size, (void *)buf);
    teardownAssetDma(D_main_bss_80138920, handle);
    hdr = buf + 4;
    full_header_image_offset_convert((void *)hdr, (void *)hdr);
    mat.material_type = 1;
    mat.zero = 0;
    mat.alwaysa = 1;
    mat.misc_float = 0.2f;
    mat.one = 1.0f;
    *(u16 *)((u8 *)buf + 0x32) |= 0x300;
    D_main_bss_80137C70 = registerHmtTextureInTable(&mat, (void *)hdr, 1);
    rs_free(buf);
    return D_main_bss_80137C70;
}

s32 dispatchOverlaySetupByParentAssetName(s32, s32, s32);
s32 rs_malloc(s32, s32);

s32 allocAndSetupModelInstance(s32 arg0) {
    s32 temp_v0;

    temp_v0 = rs_malloc(0x34, 0);
    if (temp_v0 != 0) {
        dispatchOverlaySetupByParentAssetName(arg0, temp_v0, 0xFFFF);
    }
    return temp_v0;
}

s16 rand();
typedef struct {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[2];
} ListSpacingEntry;
void randomizeListEntrySpacing(ListSpacingEntry *arg0, ListSpacingEntry *src, u16 range)
{
  u16 v = src->unk4;
  int r = range;
  ListSpacingEntry *p = src;
  ListSpacingEntry *dst = arg0;
  do
  {
    p++;
    dst->unk4 = v - (rand() % r);
    v = p->unk4;
    dst++;
  }
  while ((p->unk4 - src->unk4) < 16);
}

s32 rs_free(s32);

void freeListEntryPointers(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_a0 = (*(s32 *)((u8 *)(var_s0) + 0x1C));
        var_s0 += 4;
        var_s1 += 1;
        rs_free(temp_a0);
    } while (var_s1 < 2);
}

INCLUDE_ASM("asm/nonmatchings/main/544B0", fake_func_80054648);
