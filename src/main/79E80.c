#include "common.h"
#include "common_types.h"

typedef struct HmNode {
    struct HmNode *next;
    struct HmNode *prev;
    struct HmNode *parent;
    struct HmNode *child;
    u8 pad10[0xC];
    f32 m[12];
} HmNode;

typedef struct { f32 x, y, z; } HmV3;

typedef struct {
    u16 id;
    u16 pad;
    f32 pos[3];
} HmMsg;

#define HF(o) (*(f32 *)(d + (o)))

extern u16 D_main_bss_80139574;
extern u8 D_main_bss_80138058[];
extern void *getNpcContextByIndex(u16);
extern HmNode *lookupHmtMaterialByName(void *, s32, void *);
extern u16 findFreeNpcSlotByKey(u16, u16);
extern void zmemcpy(void *, void *, u32);
extern void mat3x4Multiply(void *, void *, void *);
extern void normalize_vector(void *);
extern void popNpcSlotFromTail(u16, void *);
extern s32 slotDispatcherIter(u16, s32, void *);
extern void destroyNpcSlotChain(u16);
extern u16 getNextSlotNpcTypeId(u16);
extern void destroyNpcSlotByIndex(u16);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, void *);
extern f32 vec3NormalizeInto(void *, void *);
extern void quatFromAxisAngle(void *, void *, f32);
extern void rotateVec3ByQuat(void *, void *, void *);
extern void orthonormalizeFrame(void *);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern void addVec3At0x24(void *, f32, f32, f32);
extern s32 transformVec3ToNpcLocalWithScale(void *, s32, void *, f32, s32);

s32 heavyMechSubEffectNpcHandler(u8 *npc, u16 msg, u8 *arg) {
    HmV3 v18;
    union {
        f32 tmp[2][12];
        struct {
            f32 buf[10];
            f32 q[4];
            HmMsg m;
        } c3;
        struct {
            u8 pad[0x38];
            f32 p[3];
        } ce;
    } u;
    f32 mm[12];
    u8 *d = *(u8 **)(npc + 4);

    switch (msg) {
    case 1: {
        u8 *mat = d + 0x44;
        s32 k;
        HmNode *node;
        HmNode *nx;
        HmNode *n;
        f32 one;
        f32 z;
        register f32 (*tp)[12] asm("$22");
        void *src;
        void *dst;

        k = 0;
        *(HmNode **)(d + 4) = lookupHmtMaterialByName(*(void **)((u8 *)getNpcContextByIndex(*(u16 *)arg) + 0xC), *(s32 *)(arg + 4), 0);
        *(u16 *)d = findFreeNpcSlotByKey(*(u16 *)(npc + 0x16), *(u16 *)arg);
        node = *(HmNode **)(d + 4);
        nx = node->parent;
        if (nx == NULL) {
            zmemcpy(mat, node->m, 0x30);
        } else {
            tp = u.tmp;
            src = node->m;
            node = nx;
            do {
                dst = mat;
                if (node->parent != NULL) {
                    dst = tp[++k & 1];
                }
                mat3x4Multiply(node->m, src, dst);
                src = dst;
            } while ((node = node->parent) != NULL);
        }
        *(HmV3 *)(d + 0x74) = *(HmV3 *)(arg + 0x20);
        one = 1.0f;
        z = 0.0f;
        HF(0x8) = HF(0x68);
        HF(0xC) = HF(0x6C);
        HF(0x10) = HF(0x70);
        HF(0x68) = -HF(0x74);
        HF(0x6C) = -HF(0x78);
        HF(0x70) = -HF(0x7C);
        *(HmV3 *)(d + 0x2C) = *(HmV3 *)(arg + 8);
        HF(0x1C) = one;
        HF(0x24) = one;
        HF(0x80) = -HF(0x34);
        HF(0x18) = z;
        HF(0x14) = z;
        HF(0x28) = z;
        HF(0x20) = z;
        HF(0x84) = z;
        HF(0x88) = HF(0x2C);
        if (HF(0x80) == z && HF(0x88) == z) {
            HF(0x80) = one;
        }
        normalize_vector(d + 0x80);
        HF(0x8C) = *(f32 *)(arg + 0x2C);
        HF(0x38) = *(f32 *)(arg + 0x14);
        HF(0x40) = *(f32 *)(arg + 0x18);
        HF(0x3C) = *(f32 *)(arg + 0x1C);
        HF(0x90) = 0.0f;
        n = *(HmNode **)(d + 4);
        if (n->prev == NULL) {
            if (n->next != NULL) {
                n->next->prev = NULL;
                (*(HmNode **)(d + 4))->parent->child = (*(HmNode **)(d + 4))->next;
            } else {
                n->parent->child = NULL;
            }
        } else {
            if ((n->prev->next = n->next) != NULL) {
                (*(HmNode **)(d + 4))->next->prev = (*(HmNode **)(d + 4))->prev;
            }
        }
        (*(HmNode **)(d + 4))->parent = NULL;
        n = *(HmNode **)(d + 4);
        n->next = n->prev = NULL;
        *(u8 **)(npc + 8) = d + 8;
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        slotDispatcherIter(*(u16 *)(npc + 0x16), 0xE, 0);
        break;
    }
    case 2:
        destroyNpcSlotChain(*(u16 *)d);
        break;
    case 3: {
        f32 dt = *(f32 *)arg;
        f32 zero;
        f32 r;
        f32 dot;
        f32 kk;
        f32 dd;
        f32 a40;
        f32 a41;
        f32 z2;
        f32 c2c;
        f32 n80;
        f32 a90;
        f32 tz;
        u16 t;

        if (getNextSlotNpcTypeId(*(u16 *)d) == 0xFFFF) {
            goto destroy;
        }
        if (*(void **)(npc + 8) == NULL) {
            break;
        }
        if (HF(0x40) >= 0.0f && (HF(0x40) = HF(0x40) - dt) < 0.0f) {
            t = getNextSlotNpcTypeId(*(u16 *)d);
            if (t != 0xFFFF) {
                u.c3.m.id = *(u16 *)(npc + 0x16);
                u.c3.m.pos[0] = HF(0x8) + HF(0x74);
                u.c3.m.pos[1] = HF(0xC) + HF(0x78);
                u.c3.m.pos[2] = HF(0x10) + HF(0x7C);
                slotDispatcherIter(t, 0xF, &u.c3.m);
                if (u.c3.m.id == 0xFFFF) {
                    *(void **)(npc + 8) = NULL;
                }
            }
            if (*(void **)(npc + 8) == NULL) {
                break;
            }
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(npc + 0x16));
            break;
        }
        HF(0x90) = HF(0x90) + dt;
        r = wrapAngleToCyclicRange(HF(0x8) + HF(0x74), HF(0x10) + HF(0x7C), D_main_bss_80138058, u.c3.buf);
        zero = 0.0f;
        if (r < HF(0xC) + HF(0x78) + zero) {
            kk = vec3NormalizeInto(&v18, d + 0x2C);
            dot = v18.x * u.c3.buf[3] + v18.y * u.c3.buf[4] + v18.z * u.c3.buf[5];
            dd = dot + dot;
            if (zero < dd) {
                if (HF(0x90) < 0.25f) {
                    if (HF(0x2C) * HF(0x2C) + HF(0x34) * HF(0x34) < 0.040000003f) {
                        kk = zero;
                    }
                }
                kk *= HF(0x3C);
                HF(0x90) = 0.0f;
                if (kk < 0.01f) {
                    HF(0x8C) = HF(0x2C) = HF(0x30) = HF(0x34) = HF(0x90);
                } else {
                    a40 = HF(0x40);
                    a90 = HF(0x90);
                    if (a40 < a90) {
                        a41 = a40 + 1.0f;
                        HF(0x40) = a41;
                        if (a90 <= a41) {
                            HF(0x40) = a90;
                            break;
                        }
                    }
                    HF(0x2C) = (v18.x - dd * u.c3.buf[3]) * kk;
                    HF(0x30) = (v18.y - dd * u.c3.buf[4]) * kk;
                    tz = (v18.z - dd * u.c3.buf[5]) * kk;
                    z2 = 0.0f;
                    c2c = HF(0x2C);
                    HF(0x84) = z2;
                    HF(0x88) = c2c;
                    n80 = -tz;
                    HF(0x80) = n80;
                    HF(0x34) = tz;
                    if (n80 == z2 && c2c == z2) {
                        HF(0x80) = 1.0f;
                    }
                    normalize_vector(d + 0x80);
                    HF(0x8C) = HF(0x8C) * HF(0x3C);
                }
            }
        }
        HF(0x8) += HF(0x2C) * dt;
        HF(0xC) += HF(0x30) * dt;
        HF(0x10) += HF(0x34) * dt;
        HF(0x30) += HF(0x38) * dt;
        quatFromAxisAngle(u.c3.q, d + 0x80, HF(0x8C) * dt);
        v18 = *(HmV3 *)(d + 0x14);
        rotateVec3ByQuat(u.c3.q, &v18, d + 0x14);
        v18 = *(HmV3 *)(d + 0x20);
        rotateVec3ByQuat(u.c3.q, &v18, d + 0x20);
        orthonormalizeFrame(d + 8);
        break;
    }
    case 0xE: {
        HmNode *mesh = *(HmNode **)(d + 4);

        mat34CrossRowsAndCopyPos(mm, d + 8, 1.0f);
        addVec3At0x24(mm, HF(0x74), HF(0x78), HF(0x7C));
        mat3x4Multiply(mm, d + 0x44, mesh->m);
        if (arg != NULL) {
            u.ce.p[0] = HF(0x8) + HF(0x74);
            u.ce.p[1] = HF(0xC) + HF(0x78);
            u.ce.p[2] = HF(0x10) + HF(0x7C);
            if ((u8)transformVec3ToNpcLocalWithScale(*(void **)arg, 0, u.ce.p, 5.0f, 0)) {
                if ((mesh->next = **(HmNode ***)arg) != NULL) {
                    mesh->next->prev = mesh;
                }
                **(HmNode ***)arg = mesh;
            }
        }
        break;
    }
    }
    return 1;
}

void zmemcpy(void *, void *, u32);
void mat3x4Multiply(void *, void *, void *);
typedef struct TransformChainNode {
    u8 pad0[8];
    struct TransformChainNode *child;
    u8 padC[0x10];
    f32 mtx[12];
} TransformChainNode;
void concatChildTransformAlongChain(TransformChainNode *node, f32 *arg1) {
    f32 *out = arg1;
    f32 tmp[2][12];
    s32 n = 0;
    f32 *src;
    f32 *dst;

    if (node->child == NULL) {
        zmemcpy(out, node->mtx, 0x30);
        return;
    }
    src = node->mtx;
    node = node->child;
    do {
        dst = out;
        if (node->child != NULL) {
            n++;
            dst = tmp[n & 1];
        }
        mat3x4Multiply(node->mtx, src, dst);
        node = node->child;
        src = dst;
    } while (node != NULL);
}

s32 initWaterSprayParticles();
s32 loadSfxAsset();

void initWaterSprayEffectAndSfx(void) {
    loadSfxAsset();
    initWaterSprayParticles();
}

INCLUDE_ASM("asm/nonmatchings/main/79E80", spawnNpcWithRandomRotation);

s32 heavyMechSubEffectNpcHandler(u8 *, u16, u8 *);
u16 spawnNpcOfType(void *, void *, u32, u8);
typedef struct {
    u16 unk0;
    s32 unk4;
} HeavyMechSubEffectArgs;
u16 spawnHeavyMechSubEffect(HeavyMechSubEffectArgs *args, u8 *parent, s32 arg2) {
    args->unk0 = *(u16 *)(parent + 0x16);
    args->unk4 = arg2;
    return spawnNpcOfType(heavyMechSubEffectNpcHandler, args, 2, parent[0x19] + 1);
}

void buildRotationMatrixSlot0(f32 *, f32);
void composeRotationMatrixSlot1(f32 *, f32);
s16 rand();

void setRandomFacingDirection(f32 *arg0, s16 arg1) {
    f32 m[12];

    buildRotationMatrixSlot0(m, (f32)(rand() % arg1));
    composeRotationMatrixSlot1(m, (f32)rand());
    arg0[0] = -m[1];
    arg0[1] = -m[4];
    arg0[2] = -m[7];
}

INCLUDE_ASM("asm/nonmatchings/main/79E80", fake_func_80079CD8);
