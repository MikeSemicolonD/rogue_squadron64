#include "common.h"
#include "common_types.h"

#include "main/02420.h"
#include "main/08510.h"
#include "main/1D000.h"
#include "main/56F50.h"

// Interim BSS externs
extern struct hobObjectListItem hobObjectListItems[0x60];

// You could alternatively consider this the next open hobObjectList index
// In practice this always ends up tracking the number of loaded objects
extern u16 numHobObjectsLoaded;

/*
A hashmap, of sorts
object names have their characters sum'd and then %25'd.
The entires in this array are indices of entries in hobObjectListItems, representing the 
*/
extern u16 hobObjectHashMap[25];

f32 D_main_8009ECB0[] = {
    19.5f,
    32.0f,
    100.0f,
    200.0f,
};

extern u16 D_main_bss_80139494;
extern u8 D_main_8013A498[];
extern u16 D_main_bss_8013A490;
extern u16 D_main_bss_801394E4;
extern u16 D_main_bss_801394E2;
extern void *D_main_bss_801394E8;
extern u8 D_main_801394F0[];
extern u8 D_main_bss_80139550;
extern s32 D_main_bss_80139554;
void *rs_malloc(u32, u16);

void initNpcBookkeepingTables(void)
{
  s32 i;
  u16 *hp;
  u8 *q;
  u16 ff;
  u16 ff2;
  i = 0;
  do
  {
    hobObjectListItems[i].nextIndex = 1;
    hobObjectListItems[i].nextIndex = i + hobObjectListItems[i].nextIndex;
    i = i + 1;
  }
  while (i < 0x60);
  ff2 = (D_main_bss_80139494 = 0xFFFF);
 do { i = 0x18; hp = hobObjectHashMap; hp += 0x18; } while (0);
  do
  {
    *hp = ff2;
    i--;
    hp--;
  }
  while (i >= 0);
  i = 0;
  do
  {
    D_main_8013A498[i] = i + 1;
    i = i + 1;
  }
  while (i < 0x80);
  D_main_bss_8013A490 = 0x7F;
  numHobObjectsLoaded = 0;
  D_main_bss_801394E4 = 0;
  D_main_bss_801394E2 = 0;
  D_main_bss_801394E8 = rs_malloc(0x4380, 0);
  i = 0x5F;
  q = D_main_801394F0 + i;
  do
  {
    *q = i;
    i--;
    q--;
  }
  while (i >= 0);
  i = 0x60;
  D_main_bss_80139550 = i;
  D_main_bss_80139554 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/56F50", load_hmt_and_hob);

s32 isHobObjectLoaded(u8 *name) {
    s32 sum = 0;
    u8 *p = name;
    u16 idx;
    s32 i;
    u8 *e;

    while (*p != 0) {
        sum += *p++;
    }
    idx = hobObjectHashMap[sum % 25];
    while (idx != 0xFFFF) {
        e = (u8 *)hobObjectListItems[idx].object_entry;
        i = 0;
        if (name[0] != 0) {
            p = name;
            do {
                if (*p != e[i]) {
                    goto next;
                }
                i++;
                if (i >= 16) {
                    break;
                }
                p++;
            } while (*p != 0);
        }
        if (name[i] == e[i]) {
            break;
        }
next:
        idx = hobObjectListItems[idx].nextIndex;
    }
    return idx != 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main/56F50", walkMeshdef0List);

void clearStructPair2C30(void *);

u8 *instantiateNamedMeshInstance(u8 *name) {
    s32 sum = 0;
    u8 *p = name;
    s32 idx;
    s32 i;
    u8 *e;
    struct hobObjectListItem *item;
    u8 *src;
    u8 *inst;
    u8 *copy;
    u8 *q;

    while (*p != 0) {
        sum += *p++;
    }
    idx = hobObjectHashMap[sum % 25];
    while (idx != 0xFFFF) {
        e = (u8 *)hobObjectListItems[idx].object_entry;
        i = 0;
        if (name[0] != 0) {
            p = name;
            do {
                if (*p != e[i]) {
                    goto next;
                }
                i++;
                if (i >= 16) {
                    break;
                }
                p++;
            } while (*p != 0);
        }
        if (name[i] == e[i]) {
            break;
        }
next:
        idx = hobObjectListItems[idx].nextIndex;
    }
    if (idx != 0xFFFF) {
    src = *(u8 **)(*(u8 **)((u8 *)hobObjectListItems[idx].object_entry + 0x18) + 4);
    inst = rs_malloc(((s32 *)src)[-1] + 0x58, 0);
    copy = inst + 0x58;
    zmemcpy(copy, src, ((s32 *)src)[-1]);
    *(struct object_entry **)(inst + 0) = hobObjectListItems[idx].object_entry;
    *(u16 *)(inst + 8) = 0x1001;
    *(s32 *)(inst + 4) = 0;
    inst[0xA] = 0;
    inst[0xB] = 0;
    *(s32 *)(inst + 0x18) = 0;
    *(s32 *)(inst + 0x14) = 0;
    *(s32 *)(inst + 0xC) = 0;
    *(s32 *)(inst + 0x10) = 0;
    *(u8 **)(inst + 0x1C) = copy;
    *(s32 *)(inst + 0x20) = 0;
    *(s32 *)(inst + 0x5C) = 0;
    *(s32 *)(inst + 0x58) = 0;
    *(s32 *)(inst + 0x64) &= ~8;
    q = &inst[(*(u8 **)(inst + 0x78) - src) + 0x58];
    *(u8 **)(inst + 0x78) = q;
    *(u8 **)(q + 8) = &inst[(*(u8 **)(q + 8) - src) + 0x58];
    clearStructPair2C30(copy);
    return inst;
    }
    return NULL;
}

void applyRgbaTintToMeshVertices(u8 *arg0, u8 *arg1) {
    u8 *t0;
    u8 *t5;
    u8 *a0;
    u8 *v1;
    u8 *p;
    s32 t4;
    s32 t3;
    s32 t2;
    s32 a2;
    s32 a1;
    u32 off;

    p = *(u8 **)(*(u8 **)(arg0 + 0x1C) + 0x20);
    t0 = *(u8 **)(p + 8);
    t4 = *(s32 *)(p + 0xC);
    t5 = *(u8 **)(*(u8 **)(*(u8 **)(*(u8 **)(*(u8 **)arg0 + 0x10) + 0x10) + 0x20) + 8);
    t3 = (arg1[0] << 8) / 255;
    t2 = (arg1[1] << 8) / 255;
    a2 = (arg1[2] << 8) / 255;
    a1 = (arg1[3] << 8) / 255;
    if (t4 > 0) {
        do {
            off = (*(u32 *)(t0 + 4) & 0x3F000) >> 10;
            a0 = t5 + off;
            v1 = t0 + off;
            v1[0] = (a0[0] * t3) >> 8;
            v1[1] = (a0[1] * t2) >> 8;
            v1[2] = (a0[2] * a2) >> 8;
            v1[3] = (a0[3] * a1) >> 8;
            if (*(u32 *)t0 & 0x10) {
                v1[4] = (a0[4] * t3) >> 8;
                v1[5] = (a0[5] * t2) >> 8;
                v1[6] = (a0[6] * a2) >> 8;
                v1[7] = (a0[7] * a1) >> 8;
                v1[8] = (a0[8] * t3) >> 8;
                v1[9] = (a0[9] * t2) >> 8;
                v1[10] = (a0[10] * a2) >> 8;
                v1[11] = (a0[11] * a1) >> 8;
                if (*(u32 *)t0 & 8) {
                    v1[12] = (a0[0] * t3) >> 8;
                    v1[13] = (a0[1] * t2) >> 8;
                    v1[14] = (a0[2] * a2) >> 8;
                    v1[15] = (a0[3] * a1) >> 8;
                }
            }
            t4 -= 1;
            off = (*(u32 *)(t0 + 4) & 0x3F000000) >> 22;
            t0 += off;
            t5 += off;
        } while (t4 > 0);
    }
}

typedef struct MeshAssetSlot {
    u8 *obj;
    u8 pad4[4];
    u16 flags;
    u8 padA;
    u8 typeId;
    u8 padC[0xB4 - 0xC];
} MeshAssetSlot;

void releaseMeshAsset(MeshAssetSlot *arg0) {
    s32 k;
    s32 cnt;
    u8 *p;
    u16 *tbl;
    struct meshdef1 **mp;
    struct meshdef1 *m;
    u8 *obj;
    u16 t;

    obj = arg0->obj;
    if (!(arg0->flags & 0x1000)) {
        t = *(u16 *)(obj + 0x3A) - 1;
        *(u16 *)(obj + 0x3A) = t;
        if (!(t & 0xFFFF)) {
            k = 0;
            p = obj;
loop1:
            tbl = *(u16 **)(p + 0x18);
            if (tbl != NULL) {
                cnt = tbl[0];
                mp = (struct meshdef1 **)(tbl + 2);
                for (; cnt > 0; cnt--, mp++) {
                    while ((m = *mp) != NULL) {
                        if (*(u32 *)((u8 *)m + 0xC) & 0x10) {
                            enqueueMeshForDeferredRelease(m);
                            *(u32 *)((u8 *)m + 0xC) |= 8;
                        }
                        mp++;
                    }
                }
                k++;
                p += 4;
                if (k < 4) goto loop1;
            }
        }
    }
    if (arg0->typeId != 0) {
        t = D_main_bss_8013A490 + 1;
        D_main_bss_8013A490 = t;
        D_main_8013A498[t] = arg0->typeId;
    }
    if (arg0->flags & 0x80) {
        D_main_bss_801394E2 -= 1;
    }
    if (arg0->flags & 0x100) {
        D_main_bss_801394E4 -= 1;
    }
    if (arg0->flags & 4) {
        D_main_801394F0[D_main_bss_80139550++] = (u32)((u8 *)arg0 - (u8 *)D_main_bss_801394E8) / 180;
        D_main_bss_80139554 -= 1;
        return;
    }
    if ((*(u32 *)((u8 *)arg0 + 8) & 0x10010000) != 0x10000) {
        rs_free(arg0);
    }
}

void releaseFlaggedMeshInstanceMeshes(u8 **arg0) {
    s32 i;
    s32 k;
    s32 cnt;
    u8 *p;
    u16 *tbl;
    struct meshdef1 **mp;
    struct meshdef1 *m;
    u32 idx;
    s32 k2;
    u8 *q;

    if (arg0 == NULL) {
        for (i = 0; i < 25; i++) {
            idx = hobObjectHashMap[i];
            {
                while (idx != 0xFFFF) {
                    u8 *e = (u8 *)hobObjectListItems[idx].object_entry;
                    if (!(*(u16 *)(e + 0x38) & 2)) {
                        k = 0;
                        p = e;
loop1:
                        tbl = *(u16 **)(p + 0x18);
                        if (tbl != NULL) {
                            cnt = tbl[0];
                            mp = (struct meshdef1 **)(tbl + 2);
                            for (; cnt > 0; cnt--, mp++) {
                                while ((m = *mp) != NULL) {
                                    if (*(u32 *)((u8 *)m + 0xC) & 0x10) {
                                        enqueueMeshForDeferredRelease(m);
                                        *(u32 *)((u8 *)m + 0xC) |= 8;
                                    }
                                    mp++;
                                }
                            }
                            k++;
                            p += 4;
                            if (k < 4) goto loop1;
                        }
                    }
                    idx = hobObjectListItems[idx].nextIndex;
                }
            }
        }
    } else {
        k2 = 0;
        q = *arg0;
loop2:
        tbl = *(u16 **)(q + 0x18);
        if (tbl != NULL) {
            cnt = tbl[0];
            mp = (struct meshdef1 **)(tbl + 2);
            for (; cnt > 0; cnt--, mp++) {
                while ((m = *mp) != NULL) {
                    if (*(u32 *)((u8 *)m + 0xC) & 0x10) {
                        enqueueMeshForDeferredRelease(m);
                        *(u32 *)((u8 *)m + 0xC) |= 8;
                    }
                    mp++;
                }
            }
            k2++;
            q += 4;
            if (k2 < 4) goto loop2;
        }
    }
}

struct object_entry *getHobObjectByName(u8 *name) {
    s32 sum = 0;
    u8 *p = name;
    s32 idx;
    s32 i;
    u8 *e;

    while (*p != 0) {
        sum += *p++;
    }
    idx = hobObjectHashMap[sum % 25];
    while (idx != 0xFFFF) {
        e = (u8 *)hobObjectListItems[idx].object_entry;
        i = 0;
        if (name[0] != 0) {
            p = name;
            do {
                if (*p != e[i]) {
                    goto next;
                }
                i++;
                if (i >= 16) {
                    break;
                }
                p++;
            } while (*p != 0);
        }
        if (name[i] == e[i]) {
            break;
        }
next:
        idx = hobObjectListItems[idx].nextIndex;
    }
    if (idx != 0xFFFF && (*(u16 *)((u8 *)hobObjectListItems[idx].object_entry + 0x38) & 1)) {
        return hobObjectListItems[idx].object_entry;
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/main/56F50", addNpcToVisibilityBucket);

INCLUDE_ASM("asm/nonmatchings/main/56F50", selectMeshLodAndSubmitForRender);

typedef struct HmtNode {
    u8 pad0[8];
    struct HmtNode *parent;
    u8 padC[0x10];
    f32 mtx[12];
} HmtNode;

void mat3x4Multiply(void *, void *, void *);
void transformVec3ByMat34(void *, void *, void *);
void rotateVec3ByMat3x3(void *, void *, void *);
void zmemcpy(u8 *, u8 *, u32);

s32 lookupHmtTextureByName(u8 **arg0, u8 *name, s32 idx, f32 *out, f32 *mtxBuf, s32 useBuf) {
    f32 tmp[2][12];
    u8 *e;
    u8 *elem;
    HmtNode *node;
    f32 *m;
    f32 *prev;
    s32 i;

    e = *(u8 **)(arg0[0] + 0x30);
    while (e[0] != 0) {
        for (i = 0; i < 6; i++) {
            if (e[i] != name[i] || e[i] == 0) {
                break;
            }
        }
        if (e[i] == name[i] && e[i] == 0) {
            elem = ((idx < e[7]) ? e + idx * 0x24 : e + (e[7] - 1) * 0x24) + 8;
            if (mtxBuf != NULL && useBuf != 0) {
                m = mtxBuf;
            } else {
                node = (HmtNode *)&((u8 *)arg0)[e[6] * 0x4C + 0xC];
                if (node->parent == NULL) {
                    if (mtxBuf != NULL) {
                        m = mtxBuf;
                        zmemcpy((u8 *)m, (u8 *)node->mtx, 0x30);
                    } else {
                        m = node->mtx;
                    }
                } else {
                    prev = node->mtx;
                    for (node = node->parent; node != NULL; node = node->parent) {
                        if (node->parent == NULL && mtxBuf != NULL) {
                            m = mtxBuf;
                        } else {
                            i++;
                            m = tmp[i & 1];
                        }
                        mat3x4Multiply(node->mtx, prev, m);
                        prev = m;
                    }
                }
            }
            transformVec3ByMat34(m, elem, out);
            rotateVec3ByMat3x3(m, elem + 0xC, out + 3);
            normalize_vector(out + 3);
            rotateVec3ByMat3x3(m, elem + 0x18, out + 6);
            normalize_vector(out + 6);
            return 1;
        }
        e = e + e[7] * 0x24 + 8;
    }
    return 0;
}

s32 computeNamedAttachPointTransform(u8 **arg0, u8 *name, s32 idx, s32 *slot, f32 *out, f32 *mtxBuf, s32 useBuf) {
    f32 tmp[2][12];
    u8 *e;
    u8 *elem;
    HmtNode *node;
    f32 *m;
    f32 *prev;
    s32 i;
    s32 count;

    e = *(u8 **)(arg0[0] + 0x30);
    count = 0;
    if (name == NULL) {
        for (count = *slot; count > 0; count--) {
            e = e + e[7] * 0x24 + 8;
        }
        goto found;
    }
    while (e[0] != 0) {
        for (i = 0; i < 6; i++) {
            if (e[i] != name[i] || e[i] == 0) {
                break;
            }
        }
        if (e[i] == name[i] && e[i] == 0) {
        found:
            elem = ((idx < e[7]) ? e + idx * 0x24 : e + (e[7] - 1) * 0x24) + 8;
            if (mtxBuf != NULL && useBuf != 0) {
                m = mtxBuf;
            } else {
                node = (HmtNode *)&((u8 *)arg0)[e[6] * 0x4C + 0xC];
                if (node->parent == NULL) {
                    if (mtxBuf != NULL) {
                        m = mtxBuf;
                        zmemcpy((u8 *)m, (u8 *)node->mtx, 0x30);
                    } else {
                        m = node->mtx;
                    }
                } else {
                    prev = node->mtx;
                    for (node = node->parent; node != NULL; node = node->parent) {
                        if (node->parent == NULL && mtxBuf != NULL) {
                            m = mtxBuf;
                        } else {
                            i++;
                            m = tmp[i & 1];
                        }
                        mat3x4Multiply(node->mtx, prev, m);
                        prev = m;
                    }
                }
            }
            transformVec3ByMat34(m, elem, out);
            rotateVec3ByMat3x3(m, elem + 0xC, out + 3);
            normalize_vector(out + 3);
            rotateVec3ByMat3x3(m, elem + 0x18, out + 6);
            normalize_vector(out + 6);
            if (name != NULL) {
                *slot = count;
            }
            return 1;
        }
        count++;
        e = e + e[7] * 0x24 + 8;
    }
    return 0;
}

typedef struct MdE { u32 w0; u32 w4; u32 w8; } MdE;
typedef struct MdQ { struct MdQ *next; u32 w4; MdE *e; u32 n; } MdQ;
typedef struct MdM { struct MdM *next; u32 w4; u8 pad8[4]; u32 flags; u8 pad10[0x10]; MdQ *q; u32 w24; u32 w28; } MdM;

void mdImpl(MdM *m, u32 base, u32 alt, u16 *tbl, u32 *list) __asm__("meshdef1_offset_convert");
void mdImpl(MdM *m, u32 base, u32 alt, u16 *tbl, u32 *list) {
    u32 off;
    u32 *p;
    MdQ *q;
    MdE *e;
    u32 i;

    if (m != NULL) {
        do {
            off = alt;
            for (i = 0; list[i] != 0; i += 3) {
                if ((u32)m == list[i]) {
                    off = base;
                    break;
                }
            }
            ((u32 *)m)[-1] -= (u32)m - base;
            m->flags |= 0x100008;
            if (m->next != NULL) {
                m->next = (MdM *)((u32)m->next + base);
            }
            if (m->w4 != 0) {
                m->w4 += base;
            }
            if (m->q != NULL) {
                m->q = (MdQ *)((u32)m->q + off);
                for (q = m->q; q != NULL; q = q->next) {
                    if (q->next != NULL) {
                        q->next = (MdQ *)((u32)q->next + off);
                    }
                    if (q->w4 != 0) {
                        q->w4 += off;
                    }
                    if (q->e != NULL && tbl != NULL) {
                        q->e = (MdE *)((u32)q->e + off);
                        e = q->e;
                        for (i = 0; i < q->n; i++) {
                            e->w8 = tbl[*(u16 *)&e->w8] << 16;
                            e = (MdE *)((u8 *)e + ((e->w4 & 0x3F000000) >> 22));
                        }
                    }
                }
            }
            if (m->w24 != 0) {
                m->w24 += off;
            }
            if (m->w28 != 0) {
                m->w28 += off;
            }
            m = m->next;
        } while (m != NULL);
    }
}

void meshdef0_offset_convert(struct meshdef0 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    if (arg0 != NULL) {
        do {
            if (arg0->inner.next_meshdef0_pointer != 0) {
                arg0->inner.next_meshdef0_pointer = (u32)arg0->inner.next_meshdef0_pointer + arg1;
            }
            if (arg0->inner.prev_meshdef0_pointer != 0) {
                arg0->inner.prev_meshdef0_pointer = (u32)arg0->inner.prev_meshdef0_pointer + arg1;
            }
            if (arg0->inner.unknown_meshdef0_pointer0 != 0) {
                arg0->inner.unknown_meshdef0_pointer0 = (u32)arg0->inner.unknown_meshdef0_pointer0 + arg1;
            }
            if (arg0->inner.unknown_meshdef0_pointer1 != 0) {
                arg0->inner.unknown_meshdef0_pointer1 = (u32)arg0->inner.unknown_meshdef0_pointer1 + arg1;
            }
            if (arg0->inner.meshdef1_pointer != 0) {
                arg0->inner.meshdef1_pointer = (u32)arg0->inner.meshdef1_pointer + arg1;
                meshdef1_offset_convert(arg0->inner.meshdef1_pointer, arg1, arg2, arg3, arg4);
            }
            if (arg0->inner.unknown_meshdef0_pointer1 != 0) {
                meshdef0_offset_convert(arg0->inner.unknown_meshdef0_pointer1, arg1, arg2, arg3, arg4);
            }
            clearVec4QuadStruct(arg0->inner.mtx);
            if (arg0->flags & 1) {
                addVec3At0x24(arg0->inner.mtx, -arg0->somevector0[0], -arg0->somevector0[1], -arg0->somevector0[2]);
            }
            if (arg0->flags & 2) {
                applyScaleToMat3x4(arg0->inner.mtx, arg0->somevector1[0], arg0->somevector1[1], arg0->somevector1[2]);
            }
            if (arg0->flags & 4) {
                composeQuatToMat3x4(arg0->inner.mtx, arg0->somequat0);
            }
            if ((arg0->flags & 9) == 9) {
                addVec3At0x24(arg0->inner.mtx, arg0->somevector2[0] + arg0->somevector0[0], arg0->somevector2[1] + arg0->somevector0[1], arg0->somevector2[2] + arg0->somevector0[2]);
            } else if ((arg0->flags & 9) == 8) {
                addVec3At0x24(arg0->inner.mtx, arg0->somevector2[0], arg0->somevector2[1], arg0->somevector2[2]);
            } else if ((arg0->flags & 9) & 1) {
                addVec3At0x24(arg0->inner.mtx, arg0->somevector0[0], arg0->somevector0[1], arg0->somevector0[2]);
            }
            arg0 = arg0->inner.next_meshdef0_pointer;
        } while (arg0 != NULL);
    }
}

typedef struct AmFaceGroup {
    struct AmFaceGroup *next;
    u32 pad4;
    u32 *faces;
    u32 count;
} AmFaceGroup;

#define AM_SCALE(c, s)                    {                                         f32 v_ = (c) * (s);                   u8 x_;                                if (v_ < 0.0f) {                          x_ = 0;                           } else if (v_ >= 256.0f) {                x_ = 255;                         } else {                                  x_ = (u32)v_;                     }                                     c = x_;                           }

void applyMeshdef1AnimColors(struct meshdef1 *arg0, u32 arg1) {
    f32 *scale = (f32 *)arg1;
    AmFaceGroup *g;
    u32 *f;
    u8 *col;
    u32 i;
    AmFaceGroup *tg;
    u32 *tf;

    if (arg0 != NULL) {
        do {
            tg = (AmFaceGroup *)arg0->facegroup_pointer;
            if (tg != NULL) {
                g = tg;
                do {
                    tf = g->faces;
                    if (tf != NULL) {
                        f = tf;
                        i = 0;
                        if (g->count != 0) {
                            do {
                                col = (u8 *)f + ((f[1] >> 10) & 0xFC);
                                if (f[0] & 0x10) {
                                    AM_SCALE(col[0], scale[0]);
                                    AM_SCALE(col[1], scale[1]);
                                    AM_SCALE(col[2], scale[2]);
                                    AM_SCALE(col[4], scale[0]);
                                    AM_SCALE(col[5], scale[1]);
                                    AM_SCALE(col[6], scale[2]);
                                    AM_SCALE(col[8], scale[0]);
                                    AM_SCALE(col[9], scale[1]);
                                    AM_SCALE(col[10], scale[2]);
                                    if (f[0] & 8) {
                                        AM_SCALE(col[12], scale[0]);
                                        AM_SCALE(col[13], scale[1]);
                                        AM_SCALE(col[14], scale[2]);
                                    }
                                } else {
                                    AM_SCALE(col[0], scale[0]);
                                    AM_SCALE(col[1], scale[1]);
                                    AM_SCALE(col[2], scale[2]);
                                }
                                i++;
                                f = (u32 *)((u8 *)f + ((f[1] >> 22) & 0xFC));
                            } while (i < g->count);
                        }
                    }
                    g = g->next;
                } while (g != NULL);
            }
            arg0 = arg0->next_meshdef1_pointer;
        } while (arg0 != NULL);
    }
}

#if 0
// https://decomp.me/scratch/X81CI
void freeAllHobFiles(void) {
    s32 var_s2;
    u16 var_v1;

    for (var_s2 = 0; var_s2 < 25; var_s2++) {
        var_v1 = hobObjectHashMap[var_s2];
        while (var_v1 != 0xFFFF) {
            if (hobObjectListItems[var_v1].hob_file != NULL) {
                rs_free(hobObjectListItems[var_v1].hob_file);
            }
            var_v1 = hobObjectListItems[var_v1].nextIndex;
            hobObjectHashMap[var_s2] = var_v1;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main/56F50", freeAllHobFiles);
#endif

extern void clearStructPair2C30(void *);

u8 *createMeshInstanceFromSource(u8 *src, u8 *inst) {
    if (inst == NULL) {
        inst = rs_malloc(0xB4, 0);
    }
    *(u8 **)(inst + 0) = src;
    *(u16 *)(src + 0x3A) += 1;
    *(s32 *)(inst + 4) = 0;
    *(u16 *)(inst + 8) = 1;
    *(u8 *)(inst + 0xA) = 0;
    *(u8 *)(inst + 0xB) = 0;
    *(s32 *)(inst + 0x18) = 0;
    *(s32 *)(inst + 0x14) = 0;
    *(s32 *)(inst + 0xC) = 0;
    *(s32 *)(inst + 0x10) = 0;
    *(u8 **)(inst + 0x1C) = inst + 0x58;
    *(s32 *)(inst + 0x20) = 0;
    *(s32 *)(inst + 0x5C) = 0;
    *(s32 *)(inst + 0x58) = 0;
    *(s32 *)(inst + 0x60) = *(s32 *)(*(u8 **)(src + 0x18) + 4);
    *(s32 *)(inst + 0x64) = 4;
    clearStructPair2C30(inst + 0x58);
    return inst;
}

typedef struct MlNode {
    struct MlNode *next;
    struct MlNode *prev;
    void *data;
    u8 padC[0x50];
} MlNode;

typedef struct {
    u8 pad0[0x10];
    MlNode *head;
    u8 pad14[0x38];
} MlEnt;

void setMeshInstanceLodAndRebuildNodes(u8 *inst, s32 lod) {
    u8 *def = *(u8 **)inst;
    u16 *ld = ((u16 **)((s32)def + (lod << 2)))[6];
    u16 *hdr;
    void **src;
    MlNode *nd;
    MlNode *prev;
    MlEnt *e;
    s32 i;
    s32 n;

    if (ld == NULL) {
        return;
    }
    nd = *(MlNode **)(def + 0x14);
    src = (void **)(ld + 2);
    if (((u16 *)nd)[1] < ld[1]) {
        return;
    }
    n = ((u16 *)nd)[0];
    nd = (MlNode *)(inst + (n * 0x4C + 0xC));
    e = (MlEnt *)(inst + 0xC);
    for (i = 0; i < n; i++, e++, src++) {
        __asm__("" :: "r"(n)); __asm__("" :: "r"(n)); __asm__("" :: "r"(n)); __asm__("" :: "r"(n)); __asm__("" :: "r"(n)); __asm__("" :: "r"(n)); 
        if (*src != NULL) {
            prev = NULL;
            e->head = nd;
        loop:
            ld = (u16 *)((src[1] != NULL) ? nd + 1 : NULL);
            nd->next = (MlNode *)ld;
            nd->prev = prev;
            prev = nd;
            __asm__("" :: "r"(prev));
            nd->data = *src;
            nd++;
            src++;
            if (*src != NULL) goto loop;
        } else {
            e->head = NULL;
        }
    }
    inst[0xA] = lod;
}

extern s32 transformVec3ToNpcLocalWithScale(void *, s32, void *, void *, void *);

u8 checkAndReturnByteFlagAsU8(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 out;

    return transformVec3ToNpcLocalWithScale(arg0, 0, arg2, arg3, &out);
}

u8 *lookupHmtMaterialByName(void **arg0, u8 *name, s32 *out) {
    u8 *e = *(u8 **)((u8 *)*arg0 + 0x28);
    u8 *idx;
    s32 i;

    if (e == NULL) {
        return NULL;
    }
    idx = e + 9;
    while (*e != 0) {
        for (i = 0; i < 9; i++) {
            if (e[i] != name[i]) {
                break;
            }
            if (e[i] == 0) {
                if (out != NULL) {
                    u8 *p = *(u8 **)((u8 *)*arg0 + 0x14);

                    p += *idx * 8;
                    *out = *(s32 *)(p + 8);
                }
                return (u8 *)arg0 + (*idx * 0x4C + 0xC);
            }
        }
        e += 0xA;
        idx += 0xA;
    }
    return NULL;
}

f32 getNpcContextFloatAt34(void **arg0) {
    return (*(f32 *)((u8 *)(*arg0) + 0x34));
}

u8 *findModelChildNodeByName(void **arg0, u8 *name) {
    u8 *e = *(u8 **)((u8 *)*arg0 + 0x2C);
    u32 i;

    if (e == NULL) {
        return NULL;
    }
    while (*(s32 *)e != 0) {
        for (i = 0; i < 7; i++) {
            if ((e + i)[4] != name[i]) {
                break;
            }
            if ((e + i)[4] == 0) {
                return e;
            }
        }
        e += 0xC;
    }
    return NULL;
}

void applyFlagsToMeshTreeOrList(void **arg0, struct meshdef1 *arg1, u32 arg2, u32 arg3) {
    if (arg0 != NULL) {
        applyFlagsToMeshdef1List((*(struct meshdef0 **)((u8 *)(*arg0) + 0x10)), arg2, arg3);
        return;
    }
    walkListAndUpdateFlagsAt0xC(arg1, arg2, arg3);
}

void setMaterialFlagByIdInMeshTree(void *arg0, u16 arg1, s32 arg2) {
    u8 *node;
    u8 *item;
    s32 n;

    for (node = *(u8 **)((u8 *)arg0 + 0x20); node != NULL; node = *(u8 **)node) {
        n = *(s32 *)(node + 0xC);
        item = *(u8 **)(node + 8);
        while (n > 0) {
            if (arg1 == 0xFFFF || *(u16 *)(item + 8) == arg1) {
                *(u32 *)(item + 8) = *(u16 *)(item + 0xA) | (arg2 << 16);
            }
            n--;
            item += (*(u32 *)(item + 4) & 0x3F000000) >> 22;
        }
    }
}

void releaseSceneObjectMeshTree(void **arg0) {
    recursivelyReleaseMeshTree((*(struct meshdef0 **)((u8 *)(*arg0) + 0x10)));
}

void recursivelyReleaseMeshTree(struct meshdef0 *arg0) {
    struct meshdef1 *temp_a0;
    struct meshdef1 *var_s0;

    if (arg0 != NULL) {
        do {
            temp_a0 = arg0->inner.meshdef1_pointer;
            if (temp_a0 != NULL) {
                var_s0 = temp_a0;
                do {
                    if (var_s0->unk0C & 0x10) {
                        enqueueMeshForDeferredRelease(var_s0);
                        var_s0->unk0C |= 8;
                    }
                    var_s0 = var_s0->next_meshdef1_pointer;
                } while (var_s0 != NULL);
            }
            if (arg0->inner.unknown_meshdef0_pointer1 != NULL) {
                recursivelyReleaseMeshTree(arg0->inner.unknown_meshdef0_pointer1);
            }
            arg0 = arg0->inner.next_meshdef0_pointer;
        } while (arg0 != NULL);
    }
}

void walkMeshdef0TreeApplyAnimColors(struct meshdef0 *arg0, u32 arg1) {
    if (arg0 != NULL) {
        do {
            if (arg0->inner.meshdef1_pointer != NULL) {
                applyMeshdef1AnimColors(arg0->inner.meshdef1_pointer, arg1);
            }
            if (arg0->inner.unknown_meshdef0_pointer1 != NULL) {
                walkMeshdef0TreeApplyAnimColors(arg0->inner.unknown_meshdef0_pointer1, arg1);
            }
            arg0 = arg0->inner.next_meshdef0_pointer;
        } while (arg0 != NULL);
    }
}

u8 findNameTreeEntryIndexByName(void **arg0, u8 *name, s32 *outIndex) {
    u8 *e = *(u8 **)((u8 *)*arg0 + 0x30);
    s32 i;
    s32 n = 0;

    while (*e != 0) {
        for (i = 0; i < 6; i++) {
            if (e[i] != name[i] || e[i] == 0) {
                break;
            }
        }
        if (e[i] == name[i] && e[i] == 0) {
            if (outIndex != NULL) {
                *outIndex = n;
            }
            return e[7];
        }
        n++;
        e = e + e[7] * 0x24 + 8;
    }
    return 0;
}

u8 *findNameTreeEntryNodeByName(void **arg0, u8 *name, s32 idx) {
    u8 *e = *(u8 **)((u8 *)*arg0 + 0x30);
    s32 i;

    while (*e != 0) {
        for (i = 0; i < 6; i++) {
            if (e[i] != name[i] || e[i] == 0) {
                break;
            }
        }
        if (e[i] == name[i] && e[i] == 0) {
            return e + idx * 0x24 + 8;
        }
        e = e + e[7] * 0x24 + 8;
    }
    return NULL;
}

s32 rs_strcpy(void *, void *);

s32 readFirstNameTreeEntry(void **arg0, void *arg1) {
    void *temp_s0;

    (*(void **)((u8 *)(arg1) + 8)) = NULL;
    (*(s8 *)((u8 *)(arg1) + 0)) = 0;
    (*(s16 *)((u8 *)(arg1) + 6)) = 0;
    temp_s0 = (*(void **)((u8 *)(*arg0) + 0x30));
    if (temp_s0 != NULL) {
        if ((*(u8 *)((u8 *)(temp_s0) + 0)) != 0) {
            rs_strcpy(arg1, temp_s0);
            (*(s16 *)((u8 *)(arg1) + 6)) = (s16) (*(u8 *)((u8 *)(temp_s0) + 7));
            (*(void **)((u8 *)(arg1) + 8)) = (void *) (temp_s0 + ((*(u8 *)((u8 *)(temp_s0) + 7)) * 0x24) + 8);
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

s32 readFirstNameTreeEntryFromNode(void *arg0) {
    void *temp_s0;

    temp_s0 = (*(void **)((u8 *)(arg0) + 8));
    if ((temp_s0 != NULL) && ((*(u8 *)((u8 *)(temp_s0) + 0)) != 0)) {
        rs_strcpy(arg0, temp_s0);
        (*(s16 *)((u8 *)(arg0) + 6)) = (s16) (*(u8 *)((u8 *)(temp_s0) + 7));
        (*(void **)((u8 *)(arg0) + 8)) = (void *) (temp_s0 + ((*(u8 *)((u8 *)(temp_s0) + 7)) * 0x24) + 8);
        return 1;
    }
    (*(void **)((u8 *)(arg0) + 8)) = NULL;
    (*(s8 *)((u8 *)(arg0) + 0)) = 0;
    (*(s16 *)((u8 *)(arg0) + 6)) = 0;
    return 0;
}

extern u16 D_main_bss_8013A490;
extern u8 D_main_8013A498[];

void enqueueMeshTypeForCleanup(u8 *arg0) {
    if (arg0[0xB] != 0 && !(*(u16 *)(arg0 + 8) & 0x20)) {
        D_main_8013A498[++D_main_bss_8013A490] = arg0[0xB];
        arg0[0xB] = 0;
    }
}

void walkListAndUpdateFlagsAt0xC(struct meshdef1 *arg0, u32 arg1, u32 arg2) {
    if (arg0 != NULL) {
        do {
            arg0->unk0C = (arg0->unk0C & ~arg2) | arg1;
            arg0 = arg0->next_meshdef1_pointer;
        } while (arg0 != NULL);
    }
}

void applyFlagsToMeshdef1List(struct meshdef0 *arg0, u32 arg1, u32 arg2) {
    struct meshdef1 *why;
    struct meshdef0 *doublewhy;
    struct meshdef1 *var_v1;

    doublewhy = arg0;
    while (doublewhy != NULL) {
        // It feels like this is meant to be an inlined version of `walkListAndUpdateFlagsAt0xC`, but I can't get that to match
        why = doublewhy->inner.meshdef1_pointer;
        if (why != NULL) {
            var_v1 = why;
            while (var_v1 != NULL) {
                var_v1->unk0C = ((var_v1->unk0C & ~arg2) | arg1);
                var_v1 = var_v1->next_meshdef1_pointer;
            }
        }
        if (doublewhy->inner.unknown_meshdef0_pointer1 != NULL) {
            applyFlagsToMeshdef1List(doublewhy->inner.unknown_meshdef0_pointer1, arg1, arg2);
        }
        doublewhy = doublewhy->inner.next_meshdef0_pointer;
    }
}

typedef struct {
    void *ptr;
    s32 unk4;
    s32 unk8;
} MeshExcludeEntry;

extern void processMeshdef1ForLod(void *, s32, s32);

void processMeshTreeExcludingList(u8 *node, MeshExcludeEntry *list) {
    void **m;
    s32 i;

    for (; node != NULL; node = *(u8 **)node) {
        if (*(void ***)(node + 0x10) != NULL) {
            m = *(void ***)(node + 0x10);
            do {
                for (i = 0; list[i].ptr != NULL; i++) {
                    if (m == list[i].ptr) {
                        break;
                    }
                }
                if (list[i].ptr == NULL) {
                    processMeshdef1ForLod(m, 0, 0);
                }
                m = *m;
            } while (m != NULL);
        }
        if (*(void **)(node + 0xC) != NULL) {
            processMeshTreeExcludingList(*(void **)(node + 0xC), list);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/56F50", fake_func_80059B4C);
