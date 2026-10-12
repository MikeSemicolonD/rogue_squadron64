#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A76E0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A7730);

typedef struct {
    u8 pad0[0xE];
    u16 hE;
    u8 pad10[0x20];
    u8 *buf;
    u8 *cur;
    u8 *sos;
} LjSt;
extern s32 D_main_bss_80137CFC;
void *rs_malloc(u32, u16);
void rs_memset(u8 *, u8, u32);
s32 resetJfifDecodeState(u8 *, void *);
s32 get_asset_size_extra(s32, s32);
s32 findAssetAcrossSegments(s32, s32, s32, s32, s32);
u8 setupAssetDma(s32, s32, s32, s32, s32, void *);
void teardownAssetDma(s32, s32);
s32 ljCell(LjSt *) __asm__("allocZeroedCellRecord");
s32 ljSoi(LjSt *) __asm__("parseJfifSOIMarker");
s32 ljSof(LjSt *) __asm__("parseJfifSOF0Marker");
s32 ljDqt(LjSt *) __asm__("parseJfifDQTMarker");
s32 ljDht(LjSt *) __asm__("parseJfifDHTMarker");
s32 ljSos(LjSt *) __asm__("paserJfifSOSMarker");

LjSt *loadJfifAsset(s32 assetId, void *arg1, u8 *err, s32 seg) {
    LjSt *s;
    s32 size;
    s32 handle;
    u8 r;
    u8 done;
    u32 len;
    u32 i;
    u8 m;

    s = rs_malloc(0x7F0, 0);
    if (s == NULL) goto e6;
    rs_memset((u8 *)s, 0, 0x7F0);
    r = resetJfifDecodeState((u8 *)s, arg1);
    if (r != 0) goto er;
    size = get_asset_size_extra(D_main_bss_80137CFC, assetId);
    if (size == 0) goto e1;
    if (size == -1) goto e1;
    s->buf = rs_malloc(size, s->hE);
    if (s->buf == NULL) goto e6;
    handle = findAssetAcrossSegments(seg, 0, D_main_bss_80137CFC, assetId, 0);
    if (setupAssetDma(seg, 0, handle, 0, size, s->buf) != 0) goto e2;
    teardownAssetDma(seg, handle);
    ljCell(s);
    done = 0;
    s->cur = s->buf;
    do {
        if ((m = *s->cur++) != 0xFF) goto e3;
        while (*s->cur == 0xFF) {
            s->cur++;
        }
        m = *s->cur++;
        switch (m) {
        case 0xD8:
            r = ljSoi(s);
            if (r != 0) goto er;
            break;
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCD:
        case 0xCE:
        case 0xCF:
            *err = 5;
            return NULL;
        case 0xC0:
            r = ljSof(s);
            if (r != 0) goto er;
            break;
        case 0xDB:
            r = ljDqt(s);
            if (r != 0) goto er;
            break;
        case 0xC4:
            r = ljDht(s);
            if (r != 0) goto er;
            break;
        case 0xDA:
            r = ljSos(s);
            if (r != 0) goto er;
            done = 1;
            s->sos = s->cur;
            break;
        case 0xFE:
            {
                s32 hi = s->cur[0] << 8;
                len = (s->cur[1] | hi) - 2;
            }
            s->cur += 2;
            for (i = 0; i < len; i++) {
                s->cur++;
            }
            break;
        case 0xD9:
            *err = 0xB;
            goto fail;
        case 0xDD:
            *err = 0xB;
            goto fail;
        case 0xDC:
            *err = 0xB;
            goto fail;
        default:
            *err = 0xB;
            goto fail;
        }
    } while (done == 0);
    *err = 0;
    return s;
e6:
    *err = 6;
    return NULL;
e1:
    *err = 1;
    return NULL;
e2:
    *err = 2;
    return NULL;
e3:
    *err = 3;
    return NULL;
er:
    *err = r;
fail:
    return NULL;
}

void zmemcpy(void *, void *, u32);
void rs_free(void *);
void cloneCellBufferWithAlloc(u8 *);
void allocCellGeometryBuffer(u8 *);

s32 resetJfifDecodeState(u8 *arg0, void *arg1) {
    s32 temp;
    void *q;

    zmemcpy(arg0, arg1, 0x30);
    if ((*(u16 *)(arg0 + 4) & 1) && (u16)(*(u16 *)(arg0 + 0x10) + 0x100) > 0x200) {
        return 0x12;
    }
    if ((*(u16 *)(arg0 + 4) & 2) && (u16)(*(u16 *)(arg0 + 0x12) + 0x100) > 0x200) {
        return 0x12;
    }
    if ((*(u16 *)(arg0 + 4) & 4) && (u16)(*(u16 *)(arg0 + 0x14) + 0x100) > 0x200) {
        return 0x12;
    }
    temp = *(s32 *)(arg0 + 0xC);
    if (temp != 0 && temp != 4) {
        return 0x12;
    }
    q = *(void **)(arg0 + 0x50);
    if (q != NULL) {
        *(u8 **)(arg0 + 0x50) = (u8 *)q - 0x100;
        rs_free((u8 *)q - 0x100);
    }
    q = *(void **)(arg0 + 0x54);
    if (q != NULL) {
        *(u8 **)(arg0 + 0x54) = (u8 *)q - 0x100;
        rs_free((u8 *)q - 0x100);
    }
    cloneCellBufferWithAlloc(arg0);
    q = *(void **)(arg0 + 0x7D8);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7DC);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7E0);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7E4);
    if (q != NULL) {
        rs_free(q);
    }
    allocCellGeometryBuffer(arg0);
    if (!((u32)(*(s32 *)(arg0 + 8) - 2) < 4)) {
        return 0x16;
    }
    *(u16 *)(arg0 + 0x46) = 0;
    *(u16 *)(arg0 + 0x7EC) = 0;
    *(u16 *)(arg0 + 0x7EE) = 0;
    *(u16 *)(arg0 + 0x7D2) = 0;
    *(u16 *)(arg0 + 0x7E8) = 0;
    *(u16 *)(arg0 + 0x7EA) = 0;
    *(arg0 + 0x4D) = 0;
    *(s32 *)(arg0 + 0x34) = *(s32 *)(arg0 + 0x38);
    return 0;
}

void rs_free(void *);

void freeJfifDecodeState(u8 *arg0) {
    u8 i;
    u8 *p;
    u8 *p2;
    void *q;

    if (arg0 != NULL) {
        i = 0;
        do {
            if ((arg0[0x48] >> i) & 1) {
                p = arg0 + i * 0xA8;
                rs_free(*(void **)(p + 0x5C));
                rs_free(*(void **)(p + 0x60));
            }
            i++;
        } while (i < 4);
        i = 0;
        do {
            p2 = arg0 + i * 0x2C;
            q = *(void **)(p2 + 0x708);
            i++;
            if (q != NULL) {
                rs_free(q);
            }
        } while (i < 3);
        q = *(void **)(arg0 + 0x77C);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x50);
        if (q != NULL) {
            *(void **)(arg0 + 0x50) = (u8 *)q - 0x100;
            rs_free((u8 *)q - 0x100);
        }
        q = *(void **)(arg0 + 0x7D8);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7DC);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7E0);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7E4);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x30);
        if (q != NULL) {
            rs_free(q);
        }
    }
    rs_free(arg0);
}

typedef struct {
    u8 pad0[0x30];
    u8 *base;
    u8 *cur;
} SoiSt;

s32 parseJfifSOIMarker(SoiSt *s) {
    u8 soi[2];
    char id[5];
    u32 i;
    s32 len;
    s32 len2;
    u8 xt;
    u8 yt;

    soi[0] = 0xFF;
    soi[1] = 0xE0;
    { char *ip = id; __builtin_memcpy(ip, "JFIF", 5); }
    for (i = 0; i < 2; i++) {
        if (*s->cur++ != soi[i]) {
            return 3;
        }
    }
    { s32 hi = s->cur[0] << 8; len = s->cur[1] | hi; }
    s->cur += 2;
    for (i = 0; i < 5; i++) {
        if (*s->cur++ != id[i]) {
            return 3;
        }
    }
    { s32 hi = s->cur[0] << 8; len2 = s->cur[1] | hi; }
    s->cur += 2;
    if (len2 != 0x101) {
        return 4;
    }
    for (i = 0; i < 5; i++) {
        s->cur++;
    }
    xt = *s->cur++;
    yt = *s->cur++;
    if (xt != 0 || yt != 0) {
        return 7;
    }
    return (s->cur - s->base != len + 4) ? 8 : 0;
}

typedef struct {
    u8 id;
    u8 h;
    u8 v;
    u8 tq;
    u8 pad4[4];
    s32 f8;
    s32 fC;
    u8 pad10[0x1C];
} SofComp;
typedef struct {
    u16 d0;
    u16 d2;
    u16 flags;
    u8 pad6[0x2A];
    u8 *base;
    u8 *cur;
    u8 pad38[4];
    u16 w;
    u16 hgt;
    u8 pad40[0xA];
    u8 maxH;
    u8 maxV;
    u8 ncomp;
    u8 pad4D[0x6F8 - 0x4D];
    SofComp comp[4];
    u8 pad7A8[0x7D4 - 0x7A8];
    u16 h7D4;
} SofSt;
static __inline__ s32 sofCdiv(s32 a, s32 b) { s32 t = a - 1; return (t + b) / b; }

s32 parseJfifSOF0Marker(SofSt *s) {
    u8 i;
    u8 p;
    SofComp *c;

    s->cur += 2;
    p = *s->cur++;
    if (p != 8) {
        return 10;
    }
    s->hgt = (s->cur[0] << 8) | s->cur[1];
    s->cur += 2;
    s->w = (s->cur[0] << 8) | s->cur[1];
    s->cur += 2;
    if (!(s->flags & 0x40)) {
        if (s->w % s->d0 != 0 || s->hgt % s->d2 != 0) {
            return 0x15;
        }
    }
    s->ncomp = *s->cur++;
    if (s->ncomp != 3 && s->ncomp != 1) {
        return 0xC;
    }
    for (i = 0; i < s->ncomp; i++) {
        s->comp[i].id = *s->cur++;
        if (s->comp[i].id != i + 1) {
            return 0x13;
        }
        p = *s->cur++;
        s->comp[i].h = p >> 4;
        s->comp[i].v = p & 0xF;
        s->comp[i].tq = *s->cur++;
    }
    s->maxH = 1;
    s->maxV = 1;
    for (i = 0; i < s->ncomp; i++) {
        c = &s->comp[i];
        s->maxH = (c->h < s->maxH) ? s->maxH : c->h;
        s->maxV = (c->v < s->maxV) ? s->maxV : c->v;
    }
    { s32 hm = s->hgt - 1; s32 q = (hm + s->maxV * 8) / (s->maxV * 8); s->h7D4 = (hm + q) / q; }
    for (i = 0; i < s->ncomp; i++) {
        c = &s->comp[i];
        c->f8 = sofCdiv(s->w * c->h, s->maxH);
        c->fC = sofCdiv(s->hgt * c->v, s->maxV);
    }
    return 0;
}

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad1[0x11];
    u8 mask;
    u8 pad2[0x2AE];
    f32 qt[256];
} JfifDQT;

extern u8 D_menu_overlay_800A76E0[];
extern f64 D_menu_overlay_800A7730[];

s32 parseJfifDQTMarker(JfifDQT *arg0) {
    f32 q[64];
    s32 len;
    u32 id;
    u16 i;
    u16 j;
    u16 k;
    f64 cj;

    {
        u8 *p = arg0->cur;
        s32 hi = p[0] << 8;
        len = (p[1] | hi) - 2;
    }
    arg0->cur += 2;
    do {
        id = *arg0->cur;
        arg0->cur++;
        if (id >= 4) {
            return 9;
        }
        i = 0;
        do {
            q[D_menu_overlay_800A76E0[i]] = *arg0->cur++;
            i++;
        } while (i < 0x40);
        i = 0;
        j = 0;
        arg0->mask |= 1 << (u16)id;
        do {
            k = 0;
            cj = D_menu_overlay_800A7730[j];
            do {
                *(f32 *)((u8 *)arg0 + (i * 4 + ((u16)id << 8)) + 0x2F8) = q[i] * cj * D_menu_overlay_800A7730[k];
                i++;
                k++;
            } while (k < 8);
            j++;
        } while (j < 8);
        len -= 0x41;
    } while ((u16)len != 0);
    return 0;
}

extern u8 decodeDeltaCellCounts_l(void *s, u8 idx, u8 *counts) __asm__("decodeDeltaCellCounts");
extern u8 allocDebrisCellTable_l(void *s, u8 idx) __asm__("allocDebrisCellTable");
extern s32 buildCellSlotCall(void *s, u8 idx) __asm__("buildCellSlotTableAndFindFree");

typedef struct {
    u8 *bits;
    u8 pad4[8];
    s16 count;
    u8 pad[2];
    u8 *vals;
    u8 padE[0xA8 - 0x14];
} DhtTbl;

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad1[0x10];
    u8 mask;
    u8 pad2[0xF];
    DhtTbl tbl[4];
} JfifDHT;

s32 parseJfifDHTMarker(JfifDHT *s) {
    u16 len;
    u32 tc;
    u32 th;
    u8 idx;
    u16 sum;
    u16 i;
    u8 *start;
    u8 b;
    u8 r;
    u16 t2;

    {
        u8 *p = s->cur;
        s32 hi = p[0] << 8;
        len = (p[1] | hi) - 2;
    }
    s->cur += 2;
    do {
        b = *s->cur;
        s->cur++;
        th = b & 0xF;
        t2 = th;
        tc = b >> 4;
        start = s->cur;
        if (tc >= 2 || t2 >= 2) {
            return 0xD;
        }
        idx = tc + (b & 0xF) * 2;
        __asm__("" :: "r"(b));
        sum = 0;
        i = 0;
        do {
            sum += *s->cur++;
            i++;
        } while ((u8)i < 0x10);
        s->tbl[idx].bits = start;
        s->tbl[idx].vals = s->cur;
        s->tbl[idx].count = sum;
        i = 0;
        while ((u8)i < sum) {
            s->cur++;
            i++;
        }
        r = decodeDeltaCellCounts_l(s, idx, start);
        if (r != 0) {
            return r;
        }
        r = allocDebrisCellTable_l(s, idx);
        if (r != 0) {
            return r;
        }
        buildCellSlotCall(s, idx);
        len -= 0x11;
        len -= sum;
        s->mask |= 1 << idx;
    } while (len != 0);
    return 0;
}

typedef struct {
    u8 id;
    u8 h;
    u8 v;
    u8 tq;
    u8 dc;
    u8 ac;
    u8 pad6[4];
    u16 hA;
    u8 padC[4];
    void *p10;
    u8 pad14[0x18];
} SosComp;
typedef struct {
    u16 h0;
    u16 h2;
    u16 flags;
    u8 pad6[8];
    u16 hE;
    u8 pad10[0x18];
    u16 h28;
    u16 h2A;
    u8 pad2C[4];
    u8 *base;
    u8 *cur;
    u8 pad38[4];
    u16 w;
    u16 hgt;
    u16 h40;
    u16 h42;
    u8 pad44[4];
    u8 b48;
    u8 pad49;
    u8 maxH;
    u8 maxV;
    u8 ncomp;
    u8 pad4D[0x6F8 - 0x4D];
    SosComp comp[4];
    u8 pad7A8[0x7D4 - 0x7A8];
    u16 h7D4;
} SosSt;
static __inline__ s32 sosCdiv(s32 a, s32 b) { s32 t = a - 1; return (t + b) / b; }
u8 sosGrid(SosSt *) __asm__("computeCellGridIndices");

s32 paserJfifSOSMarker(SosSt *s) {
    u8 n;
    u8 i;
    u8 id;
    u8 t;
    s32 xdc;
    s32 xac;
    u8 ss;
    u8 se;
    u8 a;
    u8 r;
    SosComp *c;

    s->cur += 2;
    n = *s->cur++;
    if (n != s->ncomp) {
        return 0xC;
    }
    for (i = 0; i < n; i++) {
        id = *s->cur++;
        if (id != i + 1) {
            return 0xE;
        }
        t = *s->cur++;
        s->comp[i].dc = xdc = t >> 4;
        s->comp[i].ac = xac = t & 0xF;
        if (!((s->b48 >> xdc) & 1)) {
            return 0xF;
        }
        if (!((s->b48 >> (xac + 1)) & 1)) {
            return 0xF;
        }
        s->h40 = s->h0;
        s->h42 = s->h2;
        if (s->flags & 0x80) {
            s->h40 = s->w * s->h40 / s->h28;
            s->h42 = s->hgt * s->h2 / s->h2A;
        }
        {
            u16 rows = sosCdiv(s->h42, s->h7D4);
            u16 sz;
            rows += ((u32)s->h42 % (u32)s->h7D4) != 0;
            sz = rows * s->h7D4;
            sz >>= s->maxV - s->comp[i].v;
            s->comp[i].p10 = rs_malloc(s->comp[i].hA * sz, s->hE);
        }
    }
    ss = *s->cur++;
    se = *s->cur++;
    a = *s->cur++;
    if (ss != 0 || se != 0x3F || a != 0) {
        return 0xE;
    }
    r = sosGrid(s);
    if (r != 0) {
        return r;
    }
    return 0;
}

typedef struct {
    u8 pad[0x77C];
    s32 blk[8];
} JpS;
extern void buildDebrisCellBitfield(u8 *, u8, s32);
extern void emitDebrisCellFaces(u8 *, u8, s32, s32, s32);

s32 rebuildDebrisCellGeometry(u8 *s) {
    u8 mcu;
    u8 k;
    u8 ci;
    u8 j;
    u8 fp;
    u8 *c;
    s32 s1;
    s32 s3;
    u8 r;

    mcu = 0;
    while (mcu < *(u16 *)(s + 0x7CC)) {
        k = 0;
        while (k < *(u16 *)(s + 0x7CE)) {
            buildDebrisCellBitfield(s, (s + k)[0x7BC], ((JpS *)s)->blk[k]);
            k++;
        }
        fp = 0;
        ci = 0;
        while (ci < s[0x4C]) {
            c = s + 0x6F8 + ci * 0x2C;
            s3 = *(u16 *)(s + 0x7EC) >> (s[0x4B] - c[2]);
            j = 0;
            while (j < *(s32 *)(c + 0x18)) {
                s1 = mcu * *(s32 *)(c + 0x20);
                k = 0;
                while (k < *(s32 *)(c + 0x14)) {
                    emitDebrisCellFaces(s, ci, ((JpS *)s)->blk[fp + k], s1, s3);
                    s1 += 8;
                    k++;
                }
                j++;
                fp += c[0x17];
                s3 += 8;
            }
            ci++;
        }
        mcu++;
    }
    *(u16 *)(s + 0x7D2) += 1;
    *(u16 *)(s + 0x7EC) += *(u16 *)(s + 0x7D4);
    return !(*(u16 *)(s + 0x7D2) < *(u16 *)(s + 0x7D0));
}

typedef struct {
    u8 pad0[3];
    u8 qtbl;
    u8 pad4[4];
    s32 stride;
    u8 padC[4];
    u8 *buf;
    u8 pad14[0x2C - 0x14];
} EdComp;

typedef struct {
    u8 pad0[0x50];
    u8 *rangeLimit;
    u8 pad54[0x2F8 - 0x54];
    f32 qt[4][64];
    EdComp comp[4];
} EdState;

void edIdct(EdState *s, u8 ci, s16 *coef, s32 col, s32 row) __asm__("emitDebrisCellFaces");
void edIdct(EdState *s, u8 ci, s16 *coef, s32 col, s32 row) {
    f32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    f32 tmp10, tmp11, tmp12, tmp13;
    f32 z5, z10, z11, z12, z13;
    s16 *inptr;
    f32 *quantptr;
    f32 *wsptr;
    u8 *outptr;
    u8 *range_limit;
    u32 ctr;
    f32 workspace[64];

    inptr = coef;
    quantptr = s->qt[s->comp[ci].qtbl];
    range_limit = s->rangeLimit + 0x80;
    wsptr = workspace;
    for (ctr = 8; ctr > 0; ctr--) {
        if (inptr[8 * 1] == 0 && inptr[8 * 2] == 0 && inptr[8 * 3] == 0 && inptr[8 * 4] == 0 && inptr[8 * 5] == 0 && inptr[8 * 6] == 0 && inptr[8 * 7] == 0) {
            f32 dcval = inptr[8 * 0] * quantptr[8 * 0];

            wsptr[8 * 7] = dcval;
            wsptr[8 * 6] = dcval;
            wsptr[8 * 5] = dcval;
            wsptr[8 * 4] = dcval;
            wsptr[8 * 3] = dcval;
            wsptr[8 * 2] = dcval;
            wsptr[8 * 1] = dcval;
            wsptr[8 * 0] = dcval;
            inptr++;
            quantptr++;
            wsptr++;
            continue;
        }

        tmp0 = inptr[8 * 0] * quantptr[8 * 0];
        tmp1 = inptr[8 * 2] * quantptr[8 * 2];
        tmp2 = inptr[8 * 4] * quantptr[8 * 4];
        tmp3 = inptr[8 * 6] * quantptr[8 * 6];

        tmp10 = tmp0 + tmp2;
        tmp11 = tmp0 - tmp2;

        tmp13 = tmp1 + tmp3;
        tmp12 = (tmp1 - tmp3) * 1.414213562f - tmp13;

        tmp0 = tmp10 + tmp13;
        tmp3 = tmp10 - tmp13;
        tmp1 = tmp11 + tmp12;
        tmp2 = tmp11 - tmp12;

        tmp4 = inptr[8 * 1] * quantptr[8 * 1];
        tmp5 = inptr[8 * 3] * quantptr[8 * 3];
        tmp6 = inptr[8 * 5] * quantptr[8 * 5];
        tmp7 = inptr[8 * 7] * quantptr[8 * 7];

        z13 = tmp6 + tmp5;
        z10 = tmp6 - tmp5;
        z11 = tmp4 + tmp7;
        z12 = tmp4 - tmp7;

        tmp7 = z11 + z13;
        tmp11 = (z11 - z13) * 1.414213562f;

        z5 = (z10 + z12) * 1.847759065f;
        tmp10 = 1.082392200f * z12 - z5;
        tmp12 = -2.613125930f * z10 + z5;

        tmp6 = tmp12 - tmp7;
        tmp5 = tmp11 - tmp6;
        tmp4 = tmp10 + tmp5;

        wsptr[8 * 0] = tmp0 + tmp7;
        wsptr[8 * 7] = tmp0 - tmp7;
        wsptr[8 * 1] = tmp1 + tmp6;
        wsptr[8 * 6] = tmp1 - tmp6;
        wsptr[8 * 2] = tmp2 + tmp5;
        wsptr[8 * 5] = tmp2 - tmp5;
        wsptr[8 * 4] = tmp3 + tmp4;
        wsptr[8 * 3] = tmp3 - tmp4;

        inptr++;
        quantptr++;
        wsptr++;
    }

    wsptr = workspace;
    for (ctr = 0; ctr < 8; ctr++) {
        outptr = s->comp[ci].buf + (col + (row + ctr) * s->comp[ci].stride);

        tmp10 = wsptr[0] + wsptr[4];
        tmp11 = wsptr[0] - wsptr[4];

        tmp13 = wsptr[2] + wsptr[6];
        tmp12 = (wsptr[2] - wsptr[6]) * 1.414213562f - tmp13;

        tmp0 = tmp10 + tmp13;
        tmp3 = tmp10 - tmp13;
        tmp1 = tmp11 + tmp12;
        tmp2 = tmp11 - tmp12;

        z13 = wsptr[5] + wsptr[3];
        z10 = wsptr[5] - wsptr[3];
        z11 = wsptr[1] + wsptr[7];
        z12 = wsptr[1] - wsptr[7];

        tmp7 = z11 + z13;
        tmp11 = (z11 - z13) * 1.414213562f;

        z5 = (z10 + z12) * 1.847759065f;
        tmp10 = 1.082392200f * z12 - z5;
        tmp12 = -2.613125930f * z10 + z5;

        tmp6 = tmp12 - tmp7;
        tmp5 = tmp11 - tmp6;
        tmp4 = tmp10 + tmp5;

        outptr[0] = range_limit[(((s32)(tmp0 + tmp7) + 4) >> 3) & 0x3FF];
        outptr[7] = range_limit[(((s32)(tmp0 - tmp7) + 4) >> 3) & 0x3FF];
        outptr[1] = range_limit[(((s32)(tmp1 + tmp6) + 4) >> 3) & 0x3FF];
        outptr[6] = range_limit[(((s32)(tmp1 - tmp6) + 4) >> 3) & 0x3FF];
        outptr[2] = range_limit[(((s32)(tmp2 + tmp5) + 4) >> 3) & 0x3FF];
        outptr[5] = range_limit[(((s32)(tmp2 - tmp5) + 4) >> 3) & 0x3FF];
        outptr[4] = range_limit[(((s32)(tmp3 + tmp4) + 4) >> 3) & 0x3FF];
        outptr[3] = range_limit[(((s32)(tmp3 - tmp4) + 4) >> 3) & 0x3FF];

        wsptr += 8;
    }
}

typedef struct {
    u8 pad0[1];
    u8 h;
    u8 v;
    u8 pad3[3];
    u16 h6;
    u8 pad8[0xC];
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
} CgComp;

typedef struct {
    u8 pad0[0x3C];
    u16 w;
    u16 hgt;
    u8 pad40[0xA];
    u8 maxH;
    u8 maxV;
    u8 ncomp;
    u8 pad4D[0x6F8 - 0x4D];
    CgComp comp[4];
    u8 pad7A8[0x7BC - 0x7A8];
    u8 order[0x10];
    s16 mcuW;
    u16 cnt;
    s16 mcuH;
} CgState;

static __inline__ s32 cdiv(s32 a, s32 b) { s32 t = a - 1; return (t + b) / b; }
#define CDIV cdiv
static __inline__ s32 cdiv2(s32 a, s32 m) { s32 t = a - 1; return (t + m * 8) / (m * 8); }

s32 computeCellGridIndices(CgState *s) {
    u32 i;
    CgComp *c;
    s32 n;
    s32 a;

    s->cnt = 0;
    s->mcuW = cdiv2(s->w, s->maxH);
    s->mcuH = cdiv2(s->hgt, s->maxV);
    for (i = 0; i < s->ncomp; i++) {
        c = &s->comp[i];
        c->f28 = CDIV(s->w * c->h, s->maxH * 8);
        c->f24 = CDIV(s->hgt * c->v, s->maxV * 8);
        c->f14 = c->h;
        c->f18 = c->v;
        c->f1C = c->f14 * c->f18;
        c->f20 = c->f14 * 8;
        n = c->f1C;
        if (s->cnt + n > 16) {
            return 17;
        }
        while (n-- > 0) {
            s->order[s->cnt++] = i;
        }
        c->h6 = 0;
    }
    return 0;
}

extern s32 allocCellBitGroup(void *, u8);
extern s32 findFreeBitsL(void *, u8) __asm__("findFreeCellBitSlot");
extern void rs_memset(u8 *, u8, u32);

static __inline__ s32 extendAcBits(u8 *s, s32 sz) {
    s32 b = findFreeBitsL(s, sz);
    return b < (1 << (sz - 1)) ? b + ((-1 << sz) + 1U) : b;
}

void buildDebrisCellBitfield(u8 *s, u8 idx, s32 blkArg) {
    register s16 *blk asm("$21") = (s16 *)blkArg;
    s32 diff;
    s32 sz;
    register s32 run asm("$3");
    s32 k;
    s32 bits;
    s16 sbits;
    u8 acTbl;
    u8 dc;
    u8 *t;

    rs_memset((u8 *)blk, 0, 0x80);
    diff = 0;
    t = s + idx * 0x2C;
    dc = (t[0x6FC] << 1) & 0xFE;
    acTbl = (t[0x6FD] << 1) | 1;
    sz = allocCellBitGroup(s, dc);
    if (sz != 0) {
        bits = findFreeBitsL(s, sz);
        {
            s32 v = (s16)bits < (1 << (sz - 1)) ? bits + ((-1 << sz) + 1) : bits;
            diff = v;
        }
    }
    k = 1;
    {
        u8 *t2 = s + idx * 0x2C;
        s32 pred = *(u16 *)(t2 + 0x6FE) + diff;
        *(u16 *)(t2 + 0x6FE) = pred;
        blk[0] = pred;
    }
    do {
        sz = allocCellBitGroup(s, acTbl);
        run = sz >> 4;
        sz &= 0xF;
        if (sz != 0) {
            k += run;
            bits = extendAcBits(s, sz);
            blk[D_menu_overlay_800A76E0[k]] = bits;
        } else {
            if (run != 15) {
                break;
            }
            k += 15;
        }
        k++;
    } while (k < 64);
}

typedef struct {
    s8 *sizes;
    s32 *codes;
    u8 pad8[0x98];
    s32 n;
    u8 padA4[4];
} DdTbl;
typedef struct {
    u8 pad0[0xE];
    u16 hE;
    u8 pad10[0x4C];
    DdTbl t[4];
} DdSt;

s32 decodeDeltaCellCounts(DdSt *s, u8 tbl, u8 *counts) {
    s32 p;
    s32 l;
    s32 i;

    p = 0;
    for (l = 1; l <= 16; l++) {
        i = counts[l - 1];
        if (i < 0 || p + i > 256) {
            return 16;
        }
        while (i--) {
            p++;
        }
    }
    s->t[tbl].sizes = rs_malloc(p + 1, s->hE);
    if (s->t[tbl].sizes == NULL) {
        return 6;
    }
    p = 0;
    for (l = 1; l <= 16; l++) {
        i = counts[l - 1];
        while (i--) {
            s->t[tbl].sizes[p++] = l;
        }
    }
    s->t[tbl].sizes[p] = 0;
    s->t[tbl].n = p;
    return 0;
}

typedef struct {
    s8 *sizes;
    s32 *codes;
    u8 pad8[0x98];
    s32 n;
    u8 padA4[4];
} AdTbl;
typedef struct {
    u8 pad0[0xE];
    u16 hE;
    u8 pad10[0x4C];
    AdTbl t[4];
} AdSt;

s32 allocDebrisCellTable(AdSt *s, u8 tbl) {
    s32 p;
    s32 code;
    s32 si;

    p = 0;
    code = 0;
    si = s->t[tbl].sizes[0];
    while (s->t[tbl].sizes[p] != 0) {
        while (s->t[tbl].sizes[p] == si) {
            p++;
            code++;
        }
        if (code >= (1 << si)) {
            return 16;
        }
        code <<= 1;
        si++;
    }
    s->t[tbl].codes = rs_malloc(p * 4, s->hE);
    if (s->t[tbl].codes == NULL) {
        return 6;
    }
    p = 0;
    code = 0;
    si = s->t[tbl].sizes[0];
    while (s->t[tbl].sizes[p] != 0) {
        while (s->t[tbl].sizes[p] == si) {
            s->t[tbl].codes[p++] = code;
            code++;
        }
        code <<= 1;
        si++;
    }
    return 0;
}

typedef struct {
    u8 *bits;
    u8 pad4[4];
    s32 *codes;
    u8 padC[4];
    u8 *vals;
    s32 maxcode[18];
    s32 valptr[18];
    u32 count;
} HuffTable;

typedef struct {
    u8 pad0[0x58];
    HuffTable tables[4];
} JfifHuffState;

s32 buildCellSlotTableAndFindFree(JfifHuffState *state, u8 index) {
    s32 code = 0;
    s32 k;
    HuffTable *tbl = &state->tables[index];
    u32 i;

    for (k = 1; k < 17; k++) {
        if (tbl->bits[k - 1] != 0) {
            tbl->valptr[k] = code - tbl->codes[code];
            code += tbl->bits[k - 1];
            tbl->maxcode[k] = tbl->codes[code - 1];
        } else {
            tbl->maxcode[k] = -1;
            tbl->valptr[k] = -1;
        }
    }
    tbl->maxcode[17] = 0xFFFFF;
    if (!(index & 1)) {
        for (i = 0; i <= tbl->count; i++) {
            if (tbl->vals[i] >= 16) {
                return 16;
            }
        }
    }
    return 0;
}

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad38[0xC];
    u16 bitbuf;
    u16 bitcnt;
    u8 pad48[5];
    u8 eof;
} JfifBitReader;

s32 findFreeCellBitSlot(JfifBitReader *arg0, u8 arg1) {
    u8 var_t0 = 0;
    u8 temp_a1 = arg1;
    s32 var_a3;
    s32 temp_a3;
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_v1;
    u8 *temp_v0_2;
    u8 var_v1;
    u8 t;

    var_a3 = 0;
    if (temp_a1 != 0) {
        do {
            temp_v0 = arg0->bitcnt;
            temp_a3 = var_a3 * 2;
            if (temp_v0 == 0) {
                arg0->bitcnt = 8;
                if (arg0->eof == 0) {
                    temp_v0_2 = arg0->cur;
                    var_v1 = *temp_v0_2;
                    arg0->cur = temp_v0_2 + 1;
                } else {
                    var_v1 = 0;
                }
                arg0->bitbuf = var_v1;
                if (var_v1 == 0xFF) {
                    t = *arg0->cur++;
                    if (t == 0xD9) {
                        arg0->eof = 1;
                    }
                }
                temp_v0_4 = arg0->bitbuf;
                var_a3 = temp_a3 + ((temp_v0_4 >> 7) & 1);
                arg0->bitcnt = arg0->bitcnt - 1;
                arg0->bitbuf = temp_v0_4 * 2;
            } else {
                arg0->bitcnt = temp_v0 - 1;
                temp_v1 = arg0->bitbuf * 2;
                var_a3 = temp_a3 + ((temp_v1 >> 8) & 1);
                arg0->bitbuf = temp_v1;
            }
            var_t0++;
        } while (var_t0 < temp_a1);
    }
    return var_a3;
}

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad38[0xC];
    u16 bitbuf;
    u16 bitcnt;
    u8 pad48[5];
    u8 eof;
    u8 pad4E[0x58 - 0x4E];
    HuffTable tables[4];
} CbSt;

#define CBBIT(OP) \
    if (s->bitcnt == 0) { \
        s->bitcnt = 8; \
        if (s->eof == 0) { \
            c = *s->cur++; \
        } else { \
            c = 0; \
        } \
        s->bitbuf = c; \
        if (c == 0xFF) { \
            u8 tt = *s->cur++; \
            if (tt == 0xD9) { \
                s->eof = 1; \
            } \
        } \
        v = s->bitbuf; \
        code OP ((v >> 7) & 1); \
        s->bitcnt = s->bitcnt - 1; \
        s->bitbuf = v * 2; \
    } else { \
        s->bitcnt = s->bitcnt - 1; \
        v = s->bitbuf * 2; \
        code OP ((v >> 8) & 1); \
        s->bitbuf = v; \
    }

s32 cbImpl(CbSt *s, u8 tbl) __asm__("allocCellBitGroup");
s32 cbImpl(CbSt *s, u8 tbl) {
    s32 l = 1;
    HuffTable *h = &s->tables[tbl];
    s32 code;
    u16 v;
    u8 c;
    u8 t;

    CBBIT(=)
    while (code > h->maxcode[l]) {
        code <<= 1;
        CBBIT(|=)
        l++;
    }
    if (l > 16) {
        code = 0;
        l = 1;
    }
    return h->vals[code + h->valptr[l]];
}

void allocCellGeometryBuffer(u8 *arg0) {
    f32 sp[4];
    f32 *dst;
    u8 *src;
    s32 i;
    s32 j;
    s32 off;

    i = 0;
    if (*(u16 *)(arg0 + 4) & 0x20) {
        dst = sp;
        src = arg0;
        do {
            f32 t = *(f32 *)(src + 0x18);
            src += 4;
            i += 1;
            *dst = t;
            dst += 1;
        } while (i < 4);
    } else {
        sp[0] = 1.402f;
        sp[1] = 1.772f;
        sp[2] = 0.71414f;
        sp[3] = 0.34414f;
    }
    *(void **)(arg0 + 0x7D8) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7DC) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7E0) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7E4) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    i = 0;
    j = -0x80;
    do {
        off = i * 4;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7D8)) = (((s32)(sp[0] * 65536.0f + 0.5f) * j) + 0x8000) >> 16;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7DC)) = (((s32)(sp[1] * 65536.0f + 0.5f) * j) + 0x8000) >> 16;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7E0)) = -(s32)(sp[2] * 65536.0f + 0.5f) * j;
        i += 1;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7E4)) = (-(s32)(sp[3] * 65536.0f + 0.5f) * j) + 0x8000;
        j += 1;
    } while (i < 0x100);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", buildDebrisMeshFromCells);

void *rs_malloc(u32, u16);
void rs_memset(u8 *, u8, u32);
void zmemcpy(void *, void *, u32);

void cloneCellBufferWithAlloc(u8 *state) {
    s32 size = 0x580;
    u8 *buf;
    u8 *tbl;
    s32 i;

    buf = rs_malloc(size, *(u16 *)(state + 0xE));
    rs_memset(buf, 0, size);
    tbl = buf + 0x100;
    *(u8 **)(state + 0x50) = tbl;
    for (i = 0; i < 0x100; i++) {
        (*(u8 **)(state + 0x50))[i] = i;
    }
    tbl += 0x80;
    for (i = 0x80; i < 0x200; i++) {
        tbl[i] = 0xFF;
    }
    zmemcpy(tbl + 0x380, *(u8 **)(state + 0x50), 0x80);
    *(u8 **)(state + 0x54) = rs_malloc(size, *(u16 *)(state + 0xE));
    zmemcpy(*(u8 **)(state + 0x54), buf, size);
    for (i = 0; i < size; i++) {
        (*(u8 **)(state + 0x54))[i] >>= 3;
    }
    *(u8 **)(state + 0x54) += 0x100;
}

typedef struct {
    u8 pad0[0xE];
    u16 heapTag;
    u8 pad10[0x77C - 0x10];
    u8 *cells[16];
} CellRecord;

void *rs_malloc(u32, u16);

void allocZeroedCellRecord(CellRecord *rec) {
    u8 *buf = rs_malloc(0x800, rec->heapTag);
    u8 i;

    for (i = 0; i < 16; i++) {
        rec->cells[i] = buf + i * 0x80;
    }
}

static u32 D_menu_overlay_800A78AC[] __attribute__((section(".rodata"))) = { 0x0C020B28 };
