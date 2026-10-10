#include "common.h"
#include "common_types.h"

#include "compiler/gcc/string.h"

#include "main/08120.h"
#include "menu_overlay/1197D0.h"

/*
BSS, for when matching it is possible
char D_menu_overlay_800CE6B0[0x40];
nonmatching D_menu_overlay_800CE6F0, 0x2
nonmatching D_menu_overlay_800CE6F2, 0x2
nonmatching D_menu_overlay_800CE6F4, 0xC
*/

// Interim BSS externs
extern char D_menu_overlay_800CE6B0[0x40];

/* Data Variables, uncomment when Data matching is possible
u8  D_menu_overlay_800CC850 = 0;
s32 D_menu_overlay_800CC85C = 0;
*/

// Interim `extern` definitions for Data variables. Remove these when Data matching is possible.
extern u8  D_menu_overlay_800CC850;
extern s32 D_menu_overlay_800CC85C;

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C20);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C2C);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C34);

typedef struct {
    u16 w;
    u16 h;
    s16 f44;
    u8 pad6[2];
    s32 f48;
    s32 f4C;
    u8 pad50[0x18];
    u16 w68;
    u16 h68;
} BgReq;

typedef struct {
    u16 type;
    u16 pad2;
    u16 w;
    u16 h;
} BgInfo;

typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u16 *wC;
    u8 pad10[0x14];
    f32 f24;
    f32 f28;
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
} BgElem;

typedef struct {
    u16 w;
    u16 h;
    u16 depth;
    u8 pad6[2];
    u32 count;
    BgElem *elem;
    BgInfo *info;
    u16 *ids;
    u8 b18;
    u8 pad19[3];
    s32 flags;
    u8 pad20[0x14];
    u16 h34;
    u16 h36;
} BgObj;

typedef struct {
    u8 pad0[0x3C];
    u16 w;
    u16 h;
} BgImg;

typedef struct {
    s32 a;
    s16 b;
} BgRoA;

typedef struct {
    s32 a;
    s16 b;
    s8 c;
} BgRoB;

typedef struct {
    s32 a;
    s16 b;
    s8 c;
    u8 pad7;
    s32 a8;
    s16 bC;
    s8 cE;
} BgHdr;

typedef struct {
    u8 b0;
    u8 b1;
    u8 pad2[0x36];
    void *p38;
    void *p3C;
    u8 pad40[0x1C];
    void *p5C;
    u16 h60;
    u16 h62;
    u8 b64;
    u8 b65;
    u16 h66;
    u8 pad68[4];
    BgImg *img6C;
    void *p70;
} BgBuf;

extern char D_menu_overlay_800A5C20[];
extern char D_menu_overlay_800A5C2C[] __attribute__((aligned(4)));
extern char D_menu_overlay_800A5C34[] __attribute__((aligned(4)));
extern void sprintf(char *, const char *, ...);
extern void *loadJfifAsset(char *, u16 *, void *, s32);
u8 *rs_malloc(s32, s32);
extern char *buildPrefixedAssetName(char *);

s32 buildFormatMessageGlyphBuffer(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    BgObj *obj = arg0;
#define buf ((BgBuf *)arg1)
    char name[0x30];
    BgReq req;
    u8 sp70[8];
    s32 var_s0;
    u32 i;
    s32 ret;
    s32 area;
    s32 bytes;
    BgElem *e;
    u8 *p8;
    s32 d2;
    s32 half;
    BgBuf *bb;

    req.w = obj->w;
    req.h = obj->h;
    req.w68 = obj->h34;
    req.h68 = obj->h36;
    req.f48 = obj->info->type;
    req.f4C = 0;
    req.f44 = 0x50;
    if (obj->h34 != 0 && obj->h36 != 0) {
        req.f44 = 0xD0;
    }
    sprintf(name, D_menu_overlay_800A5C20);
    buf->img6C = loadJfifAsset(name, (u16 *)&req, sp70, arg3);
    if (obj->info->w == 0) {
        obj->info->w = buf->img6C->w;
        obj->info->h = buf->img6C->h;
        switch (obj->info->type) {
        case 2:
            obj->depth = 4;
            break;
        case 3:
            obj->depth = 8;
            break;
        case 4:
            obj->depth = 1;
            break;
        case 5:
            obj->depth = 2;
            break;
        }
        obj->count = ((obj->info->w + obj->w - 1) / obj->w) * ((obj->info->h + obj->h - 1) / obj->h);
        obj->ids = rs_malloc(obj->count * 2, 0);
        for (i = 0; i < obj->count; i++) {
            obj->ids[i] = 0xFFFF;
        }
        if (obj->elem == 0) {
            obj->elem = rs_malloc(0x30, 0);
            rs_memset(obj->elem, 0, 0x30);
        }
        e = obj->elem;
        e->wC = rs_malloc(obj->count * 2, 0);
        e->h8 = buf->img6C->w / obj->w;
        d2 = buf->img6C->h / obj->h;
        e->f24 = 1.0f;
        e->f28 = 1.0f;
        e->b2C = 0xFF;
        e->b2D = 0xFF;
        e->b2E = 0xFF;
        e->b2F = 0xFF;
        e->hA = d2;
    }
    bb = arg1;
    __builtin_memcpy(bb, D_menu_overlay_800A5C2C, 6);
    __builtin_memcpy((char *)bb + 8, D_menu_overlay_800A5C34, 7);
    buf->b1 = obj->b18 + 0x41;
    ((u8 *)buf)[9] = obj->b18 + 0x41;
    rs_memset((u8 *)buf + 0x14, 0, 0x24);
    rs_memset((u8 *)buf + 0x38, 0, 0x34);
    rs_strcpy((u8 *)buf + 0x28, (u8 *)buf);
    buf->p5C = (char *)buf + 8;
    buf->h60 = obj->w;
    buf->h62 = obj->h;
    buf->b64 = 1;
    buf->h66 = obj->info->type;
    if (obj->flags & 6) {
        if (obj->flags & 2) {
            buf->h66 |= 0x800;
            req.f48 = 4;
        }
        if (obj->flags & 4) {
            buf->h66 |= 0x400;
            req.f48 = 5;
        }
        req.w = obj->w >> 1;
        req.h = obj->h >> 1;
        buf->b65 = 1;
        buf->p70 = loadJfifAsset(buildPrefixedAssetName(name), (u16 *)&req, sp70, arg3);
    }
    area = obj->w * obj->h;
    bytes = area * obj->depth;
    half = bytes / 2;
    if (obj->flags & 6) {
        var_s0 = area / 4;
    } else {
        var_s0 = 0;
    }
    buf->p38 = rs_malloc(half, 0);
    ret = obj->flags & 6;
    if (ret != 0) {
        ret = (s32)rs_malloc(var_s0, 0);
        buf->p3C = (void *)ret;
    }
    *(s32 *)((u8 *)buf + 0x10) = 0;
    return ret;
}
#undef buf

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C40);

static __inline__ BgObj *afSpawn(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    BgObj *obj;
    BgInfo *info;

    obj = (BgObj *)rs_malloc(0x38, 0);
    rs_memset((u8 *)obj, 0, 0x38);
    info = (BgInfo *)rs_malloc(0x10, 0);
    obj->info = info;
    rs_memset((u8 *)info, 0, 0x10);
    *(u16 *)obj->info = arg0;
    obj->flags = arg3;
    obj->w = arg1;
    obj->h = arg2;
    obj->b18 = D_menu_overlay_800CC850++;
    return obj;
}

BgObj *allocFormatTextElement(BgObj *src, u16 w, u16 h, s32 flags, u16 h34, u16 h36) {
    BgObj *obj;
    BgElem *e;
    s16 d2;

    obj = afSpawn(src->info->type, src->w, src->h, flags);
    D_menu_overlay_800CC850--;
    obj->b18 = src->b18;
    obj->info->w = w;
    obj->info->h = h;
    obj->h34 = h34;
    obj->h36 = h36;
    switch (obj->info->type) {
    case 2:
        obj->depth = 4;
        break;
    case 3:
        obj->depth = 8;
        break;
    case 4:
        obj->depth = 1;
        break;
    case 5:
        obj->depth = 2;
        break;
    }
    obj->count = ((obj->info->w + obj->w - 1) / obj->w) * ((obj->info->h + obj->h - 1) / obj->h);
    obj->ids = rs_malloc(obj->count * 2, 0);
    obj->elem = rs_malloc(0x30, 0);
    rs_memset(obj->elem, 0, 0x30);
    e = obj->elem;
    e->wC = rs_malloc(obj->count * 2, 0);
    e->h8 = w / obj->w;
    d2 = h / obj->h;
    e->f24 = 1.0f;
    e->f28 = 1.0f;
    e->b2C = 0xFF;
    e->b2D = 0xFF;
    e->b2E = 0xFF;
    e->b2F = 0xFF;
    e->hA = d2;
    return obj;
}

typedef struct {
    u8 *p0;
    u8 pad4[0x1C];
    u8 *p20;
    char *p24;
    u16 h28;
    u16 h2A;
    u8 b2C;
    u8 pad2D;
    u16 h2E;
    u8 pad30[4];
} HmtA;

typedef struct {
    u8 pad0[0x14];
    char name[0x10];
} HmtB;

typedef union {
    struct {
        char a[8];
        char b[8];
    } s;
    s32 align;
} HmtHdr;

extern char D_menu_overlay_800A5C40[];
void *load_asset(char *);
s32 rs_free(s32);
void zmemcpy(u8 *, u8 *, u32);
s32 registerHmtTextureInTable(void *, void *, u8);

BgObj *loadNamedTextureDescriptor(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    HmtHdr hdr;
    char name[0x40];
    HmtA a;
    HmtB b;
    BgObj *obj;
    u8 fl = arg3;
    BgElem *e;
    s32 scale;
    u32 i;
    u32 j;
    u32 cols;
    u32 off;
    u8 *src;
    s32 ty;
    u16 t;
    s16 v;

    obj = (BgObj *)rs_malloc(0x38, 0);
    rs_memset((u8 *)obj, 0, 0x38);
    sprintf(name, D_menu_overlay_800A5C20, arg0);
    obj->info = load_asset(name);
    obj->flags = 0;
    obj->w = arg1;
    obj->h = arg2;
    obj->depth = 2;
    obj->b18 = D_menu_overlay_800CC850++;
    scale = 0x100;
    if ((obj->info->type & 0xF) == 0) {
        obj->depth = 1;
        scale = 0x10;
    }
    if ((obj->info->type & 0xF) == 2) {
        obj->depth = 4;
    }
    if ((obj->info->type & 0xF) == 3) {
        obj->depth = 8;
    }
    obj->count = (obj->info->w + obj->w - 1) / obj->w;
    obj->count = obj->count * ((obj->info->h + obj->h - 1) / obj->h);
    obj->ids = (u16 *)rs_malloc(obj->count * 2, 0);
    for (i = 0; i < obj->count; i++) {
        obj->ids[i] = 0xFFFF;
    }
    e = (BgElem *)rs_malloc(0x30, 0);
    obj->elem = e;
    rs_memset((u8 *)e, 0, 0x30);
    obj->elem->wC = (u16 *)rs_malloc(obj->count * 2, 0);
    __builtin_memcpy(hdr.s.a, D_menu_overlay_800A5C2C, 6);
    __builtin_memcpy(hdr.s.b, D_menu_overlay_800A5C34, 7);
    hdr.s.a[1] = obj->b18 + 0x41;
    hdr.s.b[1] = obj->b18 + 0x41;
    rs_memset((u8 *)&b, 0, 0x24);
    rs_memset((u8 *)&a, 0, 0x34);
    rs_strcpy((u8 *)b.name, (u8 *)hdr.s.a);
    a.p24 = hdr.s.b;
    a.h28 = obj->w;
    a.h2A = obj->h;
    a.b2C = 1;
    t = obj->info->type;
    if (fl) {
        t |= 0x2000;
    }
    a.h2E = t;
    a.p20 = (u8 *)obj->info + 0xC;
    a.p0 = rs_malloc(obj->w * obj->h * obj->depth / 2, 0);
    src = (u8 *)obj->info + 0xC + ((obj->info->type & 0x8000) ? scale * 4 : scale * 3);
    ty = obj->info->type & 0xF;
    if ((u32)(ty - 4) < 2 || (u16)ty == 2 || (u16)ty == 3) {
        src = (u8 *)obj->info + 0xC;
    }
    for (i = 0; i < obj->count; i++) {
        sprintf(b.name + 2, D_menu_overlay_800A5C40, i);
        sprintf(a.p24 + 2, D_menu_overlay_800A5C40, i);
        {
            u32 iw = obj->info->w;
            register u32 ow asm("$2");
            __asm__("" :: "r"(iw));
            ow = obj->w;
            cols = iw / ow;
            {
                u32 r = i % cols;
                register u32 q asm("$4") = i / cols;
                off = r * ow;
                off += q * obj->h * iw;
                off *= obj->depth;
                off >>= 1;
            }
        }
        for (j = 0; j < obj->h; j++) {
            zmemcpy(a.p0 + ((j * obj->w * obj->depth) >> 1), src + (off + ((j * obj->info->w * obj->depth) >> 1)), (obj->w * obj->depth) / 2);
        }
        v = registerHmtTextureInTable(&b, &a, 1);
        {
            u16 *p = e->wC;
            u16 *q = obj->ids;
            p[i] = v;
            q[i] = v;
        }
    }
    rs_free((s32)a.p0);
    e->h8 = obj->info->w / obj->w;
    v = obj->info->h / obj->h;
    e->f24 = 1.0f;
    e->f28 = 1.0f;
    e->b2C = 0xFF;
    e->b2D = 0xFF;
    e->b2E = 0xFF;
    e->b2F = 0xFF;
    e->hA = v;
    rs_free((s32)obj->info);
    obj->info = NULL;
    return obj;
}

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuAlpha);




typedef struct { u8 b[4]; f32 f4; f32 f8; s32 wC; s32 w10; char name[16]; } AtMat;
typedef struct { u8 *pix[8]; u8 *plte; char *name; u16 w; u16 h; u8 one; u8 depth; u16 flags; u32 trans; } AtTex;
typedef struct { u8 pad0[8]; s16 tilesX; s16 tilesY; u16 *ids; u8 pad10[0x14]; f32 f24; f32 f28; u8 b2C; u8 b2D; u8 b2E; u8 b2F; } AtSet;
typedef struct { u16 w; u16 h; u16 bpp; u16 pad6; s32 count; AtSet *ts; void *asset; u16 *ids; u8 idx; u8 pad19[3]; s32 x1C; u8 pad20[0x18]; } AtObj;
s32 atRegister(AtMat *, AtTex *, u8) __asm__("registerHmtTextureInTable");
void *atMalloc(s32, s32) __asm__("rs_malloc");
void atFree(void *) __asm__("rs_free");

AtObj *atImpl(s16 w, s16 h) __asm__("allocTextRenderTarget");
AtObj *atImpl(s16 w, s16 h) {
    AtMat mat = { { 0, 1, 0, 0 }, 1.0f, 1.0f, 0, 0, "P____" };
    AtTex tex = { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, D_menu_overlay_800A5C2C, 0, 0, 1, 0, 4, 0 };
    AtObj *b;
    AtSet *ts;
    s32 n;
    s32 q;
    u32 i;
    s16 id;

    b = atMalloc(0x38, 0);
    rs_memset(b, 0, 0x38);
    b->w = 0x40;
    b->h = 0x10;
    q = w / b->w;
    b->bpp = 1;
    b->count = q;
    b->count = q * (h / b->h);
    b->ids = atMalloc(b->count * 2, 0);
    ts = atMalloc(0x30, 0);
    b->ts = ts;
    rs_memset(ts, 0, 0x30);
    ts->ids = atMalloc(b->count * 2, 0);
    n = b->w * b->h * b->bpp / 2;
    tex.w = b->w;
    tex.h = b->h;
    tex.one = 1;
    tex.depth = 0;
    tex.pix[0] = atMalloc(n, 0);
    rs_memset(tex.pix[0], 0xFF, n);
    tex.name[1] = D_menu_overlay_800CC850 + 'A';
    mat.name[1] = D_menu_overlay_800CC850 + 'A';
    id = atRegister(&mat, &tex, 1);
    ts->ids[0] = b->ids[0] = id;
    atFree(tex.pix[0]);
    ts->tilesX = w / b->w;
    { s16 ty = h / b->h;
    ts->f24 = ts->f28 = 1.0f;
    ts->tilesY = ty; }
    for (i = 1; i < b->count; i++) {
        ts->ids[i] = ts->ids[0];
        b->ids[i] = 0xFFFF;
    }
    b->idx = D_menu_overlay_800CC850++;
    return b;
}

typedef struct {
    u8 pad0[0x10];
    s32 idx;
    u8 mat[0x16];
    char name[0xE];
    s32 tex0;
    s32 tex1;
    u8 pad40[0x1C];
    char *label;
    u8 pad60[0xC];
    s32 jfif0;
    s32 jfif1;
    u8 pad74[4];
} GlyphBuf;

typedef struct {
    u8 pad0[0x14];
    s32 f14;
} WorkerReply;

typedef struct {
    u8 pad0[8];
    u32 count;
    struct {
        u8 pad0[0xC];
        u16 *ids;
    } *elem;
    u8 pad10[4];
    u16 *ids;
    u8 pad18[4];
    s32 flags;
} FmtObj;

typedef struct {
    u8 pad0[0x14];
    FmtObj *obj;
    u8 text[0x40];
    s32 replyTo;
    s32 serial;
} FmtRequest;

extern char D_menu_overlay_800A5C40[];
void sprintf(char *, const char *, ...);
void buildDebrisMeshFromCells(s32, s32);
s32 registerHmtTextureInTable(void *, void *, u8);
s32 findMatchingTextureRecursive(u16, void *, void *, s32);
s32 rs_free(s32);
s32 freeJfifDecodeState(s32);
s32 buildFormatMessageGlyphBuffer(void *, void *, s32, s32);
s32 sendServiceMessage(s32, s32, void *, s32);

void tickFormatMessageWorker(s32 *arg0) {
    WorkerReply reply;
    GlyphBuf buf;
    FmtRequest *req;
    FmtObj *obj;
    u32 i;
    u32 j;
    u16 *p;

    for (;;) {
        i = 0;
        req = (FmtRequest *)recvServiceMessage(*arg0);
        buildFormatMessageGlyphBuffer(req->obj, &buf, (s32)req->text, *arg0);
        for (; i < req->obj->count; i++) {
            obj = req->obj;
            for (j = 0; j < 1; j++) {
                sprintf(buf.name, D_menu_overlay_800A5C40, buf.idx);
                sprintf(buf.label + 2, D_menu_overlay_800A5C40, buf.idx);
                buildDebrisMeshFromCells(buf.jfif0, buf.tex0);
                if (obj->flags & 6) {
                    buildDebrisMeshFromCells(buf.jfif1, buf.tex1);
                }
                p = (u16 *)(buf.idx * 2 + (s32)obj->ids);
                *p = (*p == 0xFFFF) ? registerHmtTextureInTable(buf.mat, &buf.tex0, 0) : findMatchingTextureRecursive(*p, buf.mat, &buf.tex0, 0);
                obj->elem->ids[buf.idx] = obj->ids[buf.idx];
                buf.idx++;
            }
            yieldThreadRet1(*arg0);
        }
        if (req->obj->flags & 6) {
            rs_free(buf.tex1);
            freeJfifDecodeState(buf.jfif1);
        }
        rs_free(buf.tex0);
        freeJfifDecodeState(buf.jfif0);
        reply.f14 = req->serial;
        sendServiceMessage(*arg0, req->replyTo, &reply, 0);
        rs_free((s32)req);
    }
}

extern u16 blTex1 __asm__("D_menu_overlay_800CE6F0");
extern u16 blTex2 __asm__("D_menu_overlay_800CE6F2");
f32 quadraticEaseInOut(f32);

void buildLevelSelectTextTextures(f32 lim) {
    u8 b0[0x200];
    u8 b1[0x200];
    u8 b2[0x200];
    AtMat mat1 = { { 0, 1, 0, 0 }, 1.0f, 1.0f, 0, 0, "GRAD1" };
    AtMat mat2 = { { 0, 1, 0, 0 }, 1.0f, 1.0f, 0, 0, "GRAD2" };
    AtTex tex1 = { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, "GRAD1A", 0x40, 8, 1, 0, 0x405, 0 };
    AtTex tex2 = { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, "GRAD2A", 8, 0x40, 1, 0, 0x405, 0 };
    u32 i;
    u32 j;
    f32 v;

    for (i = 0; i < 0x40; i++) {
        for (j = 0; j < 8; j++) {
            b0[i * 8 + j] = 0xFF;
            v = quadraticEaseInOut((f32)i * 0.015625f) * 1746.0f;
            if (lim < v) {
                v = lim;
            }
            b1[i * 8 + j] = (u32)v;
            b2[j * 0x40 + i] = (u32)v;
        }
    }
    tex2.pix[0] = b0;
    tex2.pix[1] = b1;
    tex1.pix[0] = b0;
    tex1.pix[1] = b2;
    blTex1 = atRegister(&mat1, &tex1, 1);
    blTex2 = atRegister(&mat2, &tex2, 1);
}

typedef struct { u8 pad[0x6C]; u8 *p6C; u8 pad2[8]; } FmtBuf;
typedef struct {
    u8 pad0[8];
    s16 h8;
    s16 hA;
    u16 *wC;
    u8 pad10[0x14];
    f32 f24;
    f32 f28;
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
} FmtElem;

s32 buildFormatMessageGlyphBuffer(void *, void *, s32, s32);
s32 rasterizeFormatMessageGlyphs(void *, void *, u16);
void disposeFormatMsgQueueMember(void *, void *);
u8 *spawnProjectileObject(s32, s16, s16, s32);

void *buildScaledFormatTextElement(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5) {
    FmtBuf buf;
    u8 *obj;
    FmtElem *e;
    u32 i;
    s32 d2;

    obj = spawnProjectileObject(arg1, arg2, arg3, arg4);
    buildFormatMessageGlyphBuffer(obj, &buf, arg0, arg5);
    rasterizeFormatMessageGlyphs(obj, &buf, *(u16 *)(obj + 0xA));
    e = *(FmtElem **)(obj + 0xC);
    e->h8 = *(u16 *)(buf.p6C + 0x3C) / arg2;
    d2 = *(u16 *)(buf.p6C + 0x3E) / arg3;
    e->f24 = 1.0f;
    e->f28 = 1.0f;
    e->b2C = 0xFF;
    e->b2D = 0xFF;
    e->b2E = 0xFF;
    e->b2F = 0xFF;
    e->hA = d2;
    i = 0;
    if (*(s32 *)(obj + 8) != 0) {
        do {
            e->wC[i] = (*(u16 **)(obj + 0x14))[i];
            i += 1;
        } while (i < *(u32 *)(obj + 8));
    }
    disposeFormatMsgQueueMember(obj, &buf);
    return obj;
}

s32 buildFormatMessageGlyphBuffer(void *, void *, s32, s32);
s32 rasterizeFormatMessageGlyphs(void *, void *, u16);
void disposeFormatMsgQueueMember(void *arg0, void *arg1);

void processAndDisposeFormatMessage(u8 *arg0, s32 arg1, s32 arg2) {
    u8 buf[0x78];

    buildFormatMessageGlyphBuffer(arg0, buf, arg1, arg2);
    rasterizeFormatMessageGlyphs(arg0, buf, *(u16 *)(arg0 + 0xA));
    disposeFormatMsgQueueMember(arg0, buf);
}

void decrementTextTextureRefcount(void) {
    D_menu_overlay_800CC850--;
}

void setChildPosFromI16Pair(void *arg0, s16 arg1, s16 arg2) {
    (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0xC))) + 0x18)) = (f32) arg1;
    (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0xC))) + 0x1C)) = (f32) arg2;
}

s32 getStructField0xC(void *arg0) {
    return (*(s32 *)((u8 *)(arg0) + 0xC));
}

extern char D_menu_overlay_800A5C40[];

s32 rasterizeFormatMessageGlyphs(void *arg0, void *arg1, u16 arg2) {
    u32 i;
    u16 *slot;
    s32 off;

    for (i = 0; i < arg2; i++) {
        {
            sprintf((u8 *)arg1 + 0x2A, D_menu_overlay_800A5C40, *(s32 *)((u8 *)arg1 + 0x10));
            sprintf(*(char **)((u8 *)arg1 + 0x5C) + 2, D_menu_overlay_800A5C40, *(s32 *)((u8 *)arg1 + 0x10));
            buildDebrisMeshFromCells(*(s32 *)((u8 *)arg1 + 0x6C), *(s32 *)((u8 *)arg1 + 0x38));
            if (*(s32 *)((u8 *)arg0 + 0x1C) & 6) {
                buildDebrisMeshFromCells(*(s32 *)((u8 *)arg1 + 0x70), *(s32 *)((u8 *)arg1 + 0x3C));
            }
            slot = (u16 *)(*(s32 *)((u8 *)arg1 + 0x10) * 2 + *(s32 *)((u8 *)arg0 + 0x14));
            *slot = (*slot == 0xFFFF) ? registerHmtTextureInTable((u8 *)arg1 + 0x14, (u8 *)arg1 + 0x38, 0) : findMatchingTextureRecursive(*slot, (u8 *)arg1 + 0x14, (u8 *)arg1 + 0x38, 0);
            off = *(s32 *)((u8 *)arg1 + 0x10) * 2;
            *(u16 *)(off + *(s32 *)(*(s32 *)((u8 *)arg0 + 0xC) + 0xC)) = *(u16 *)(off + *(s32 *)((u8 *)arg0 + 0x14));
            *(s32 *)((u8 *)arg1 + 0x10) = *(s32 *)((u8 *)arg1 + 0x10) + 1;
        }
    }
}

s32 freeJfifDecodeState(s32);
s32 rs_free(s32);

void disposeFormatMsgQueueMember(void *arg0, void *arg1) {
    if ((*(s32 *)((u8 *)(arg0) + 0x1C)) & 6) {
        rs_free((*(s32 *)((u8 *)(arg1) + 0x3C)));
        freeJfifDecodeState((*(s32 *)((u8 *)(arg1) + 0x70)));
    }
    rs_free((*(s32 *)((u8 *)(arg1) + 0x38)));
    freeJfifDecodeState((*(s32 *)((u8 *)(arg1) + 0x6C)));
}

extern s32 D_menu_overlay_800CC858;
s32 registerServiceWorker(s32, s32, s32, s32 *);
s32 startServiceWorker(s32);
extern s32 D_menu_overlay_800CC854;
void tickFormatMessageWorker(s32 *);

void initFormatMessageWorker(s32 arg0) {
    s32 temp_v0;

    D_menu_overlay_800CC854 = 1;
    temp_v0 = registerServiceWorker(8, 0x800, arg0 & 0xFF, &tickFormatMessageWorker);
    D_menu_overlay_800CC858 = temp_v0;
    startServiceWorker(temp_v0);
}

s32 unregisterServiceWorker(s32);
extern s32 D_menu_overlay_800CC858;

void shutdownFormatMessageWorker(void) {
    unregisterServiceWorker(D_menu_overlay_800CC858);
}

extern s32 D_main_bss_80138920;
extern s32 D_menu_overlay_800CC854;
extern s32 D_menu_overlay_800CC858;
s32 sendServiceMessage(s32, s32, void *, s32);

typedef struct {
    u8 pad0[0x14];
    s32 f14;
    u8 text[0x40];
    s32 f58;
    s32 f5C;
} FormatMsg;

u8 enqueueFormatMessage(s32 arg0, u8 *arg1) {
    FormatMsg *msg;

    msg = rs_malloc(0x60, 0);
    rs_memset((u8 *)msg, 0, 0x60);
    msg->f14 = arg0;
    msg->f58 = D_main_bss_80138920;
    msg->f5C = D_menu_overlay_800CC854;
    rs_strcpy(msg->text, arg1);
    sendServiceMessage(D_main_bss_80138920, D_menu_overlay_800CC858, msg, 0);
    D_menu_overlay_800CC854 += 1;
    return msg->text[0x47];
}

void *tryRecvServiceMessage(s32);
extern s32 D_main_bss_80138920;

s32 pollServiceMessageByte(u8 *arg0) {
    void *temp_v0;

    temp_v0 = tryRecvServiceMessage(D_main_bss_80138920);
    if (temp_v0 != NULL) {
        *arg0 = (*(u8 *)((u8 *)(temp_v0) + 0x17));
    }
    return temp_v0 != NULL;
}

s32 allocTextRenderTarget(s32, s32);
extern s32 D_menu_overlay_800CC864;

void initTextTextureTarget(void) {
    D_menu_overlay_800CC864 = allocTextRenderTarget(0x40, 0x10);
}

extern f32 D_menu_overlay_800CE6F4;
extern u8 D_menu_overlay_800CC860;
extern u8 gBootConfig[];
s32 utInsert(void *, void *, s32) __asm__("insertLookupEntry");
void utSet5(void *, void *, s32) __asm__("setLookupEntryField5ByKey");
void beginSceneRenderFrame(s32);

typedef struct {
    u8 pad0[0x14];
    s32 w14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
} UtEnt;

typedef struct { u8 pad0[0xC]; UtEnt *ent; } UtHolder;
void updateTextOverlayLookupEntry(void *list, s32 *ctx, f32 dur) {
    UtEnt *n;
    UtHolder *h;

    if (D_menu_overlay_800CC85C == 0) {
        h = (UtHolder *)D_menu_overlay_800CC864;
        n = h->ent;
        n->f24 = (f32)ctx[4] * 0.015625f;
        n->f28 = (f32)ctx[5] * 0.0625f;
        D_menu_overlay_800CC860 = 0;
        D_menu_overlay_800CC85C = (s32)h;
        n->f18 = -((f32)ctx[4] * 0.5f);
        n->f1C = -((f32)ctx[5] * 0.5f);
        D_menu_overlay_800CE6F4 = dur * 30.0f;
        n->f20 = -100.0f;
        n->w14 |= 0x2400003;
        utInsert(list, n, 0);
        utSet5(list, n, 1);
    }
    if (!(*(s32 *)(gBootConfig + 0x44) & 0x80)) {
        beginSceneRenderFrame(8);
    }
}

extern f32 D_menu_overlay_800CE6F4;
extern u8 D_menu_overlay_800CC860;

s32 accumulateShipThrottleCharge(s32 arg0, s32 arg1, f32 dt) {
    f32 charge;

    if (D_menu_overlay_800CC85C != 0) {
        charge = D_menu_overlay_800CE6F4 * dt + (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F];
        if (charge > 255.0f) {
            (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F] = 0xFF;
            if (++D_menu_overlay_800CC860 >= 7) {
                return 1;
            }
        } else {
            (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F] = charge;
        }
    }
    return 0;
}

f32 computeThrottleChargeFraction(void) {
    f32 var_ft0;

    var_ft0 = 1.0f;
    if (D_menu_overlay_800CC85C != 0) {
        var_ft0 = 1.0f - ((f32) (*(u8 *)((u8 *)((*(void **)((u8 *)(D_menu_overlay_800CC85C) + 0xC))) + 0x2F)) / 255.0f);
    }
    return var_ft0;
}

s32 isPlayerShipActive(void) {
    return D_menu_overlay_800CC85C != 0;
}

void removeLookupTableEntry(s32, s32);
void requestViFeatureChange(s32);
extern u8 gBootConfig[];

void destroyPlayerShipRecord(s32 arg0) {
    if (D_menu_overlay_800CC85C != 0) {
        removeLookupTableEntry(arg0, *(s32 *)((u8 *)D_menu_overlay_800CC85C + 0xC));
        D_menu_overlay_800CC85C = 0;
        D_menu_overlay_800CC850--;
        if (!(*(s32 *)(gBootConfig + 0x44) & 0x80)) {
            requestViFeatureChange(8);
        }
    }
}

u8 *spawnProjectileObject(s32 arg0, s16 arg1, s16 arg2, s32 arg3) {
    BgObj *obj;
    BgInfo *info;

    obj = (BgObj *)rs_malloc(0x38, 0);
    rs_memset((u8 *)obj, 0, 0x38);
    info = (BgInfo *)rs_malloc(0x10, 0);
    obj->info = info;
    rs_memset((u8 *)info, 0, 0x10);
    *(u16 *)obj->info = arg0;
    obj->flags = arg3;
    obj->w = arg1;
    obj->h = arg2;
    obj->b18 = D_menu_overlay_800CC850++;
    return (u8 *)obj;
}

typedef struct {
    u8 pad0[8];
    u32 count;
    u8 *morph;
    u8 pad10[4];
    u16 *verts;
} MorphMesh;

void copyMorphTargetVertices(MorphMesh *arg0, MorphMesh *arg1, u16 base) {
    u32 i;



    for (i = 0; i < arg0->count; i++) {
        (*(u16 **)(arg0->morph + 0xC))[i] = arg0->verts[i] = arg1->verts[i + base];
    }
}

#if 0
// Text matching, have not check if rodata works yet
// Appends "alplha" to the end of arg0, placing the combined result in D_menu_overlay_800CE6B0
char *buildPrefixedAssetName(char *arg0) {
    s32 temp_s3;
    char *temp_v0;
    u32 var_s1;

    temp_v0 = "alpha";
    rs_strcpy(D_menu_overlay_800CE6B0, arg0);
    temp_s3 = strlen(D_menu_overlay_800CE6B0);
    for (var_s1 = 0; var_s1 < strlen(temp_v0) + 1; var_s1++) {
        D_menu_overlay_800CE6B0[temp_s3 + var_s1] = temp_v0[var_s1];
    }
    return D_menu_overlay_800CE6B0;
}
#else
extern char strMenuAlpha[];

char *buildPrefixedAssetName(char *arg0) {
    char *alpha;
    s32 len;
    u32 i;

    alpha = strMenuAlpha;
    rs_strcpy(D_menu_overlay_800CE6B0, arg0);
    len = strlen(D_menu_overlay_800CE6B0);
    for (i = 0; i < strlen(alpha) + 1; i++) {
        D_menu_overlay_800CE6B0[len + i] = alpha[i];
    }
    return D_menu_overlay_800CE6B0;
}
#endif

typedef struct {
    u8 pad[4];
    u16 w;
    u16 h;
} HudMeshBounds;

typedef struct {
    u8 pad[0xC];
    s32 unkC;
    HudMeshBounds *bounds;
    u8 pad14[0xC];
    u8 unk20[1];
} HudMeshRef;

void spawnHudReticleAtMeshBounds(s32 arg0, HudMeshRef *arg1, s32 arg2, u8 arg3) {
    HudMeshBounds *b = arg1->bounds;
    s32 c = arg1->unkC;

    createHudSpritePair(arg0, arg1->unk20, c, b->w, b->h, arg2, arg3);
}

void layoutHudSpriteScreenRect(s32 a, s32 b, s32 c, f32 d);
void positionHudSpriteOffset(s32 a, s32 b, s32 c, f32 d) {
    layoutHudSpriteScreenRect(a, b, c + 0x20, d);
}

s32 insertLookupEntry(s32, u8 *, s32);
u8 *rs_malloc(s32, s32);
extern s32 D_menu_overlay_800CE6F0;
extern s32 D_menu_overlay_800CE6F2;

void createHudSpritePair(s32 arg0, void *arg1, s32 arg2, s16 arg3, s32 arg4, f32 arg5, u8 arg6) {
    s32 temp_s3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = rs_malloc(0x30, 0);
    (*(u8 **)((u8 *)(arg1) + 0)) = temp_v0;
    temp_v0_2 = rs_malloc(0x30, 0);
    (*(u8 **)((u8 *)(arg1) + 4)) = temp_v0_2;
    rs_memset(temp_v0, 0U, 0x30U);
    rs_memset(temp_v0_2, 0U, 0x30U);
    (*(s32 *)((u8 *)(arg1) + 8)) = arg2;
    (*(s16 *)((u8 *)(arg1) + 0x10)) = arg3;
    temp_s3 = arg6 & 0xFF;
    (*(f32 *)((u8 *)(arg1) + 0xC)) = arg5;
    (*(s16 *)((u8 *)(arg1) + 0x12)) = (s16) arg4;
    (*(s32 **)((u8 *)(temp_v0) + 0xC)) = &D_menu_overlay_800CE6F0;
    (*(s32 **)((u8 *)(temp_v0_2) + 0xC)) = &D_menu_overlay_800CE6F2;
    (*(s16 *)((u8 *)(temp_v0_2) + 0xA)) = 1;
    (*(s16 *)((u8 *)(temp_v0_2) + 8)) = 1;
    (*(s16 *)((u8 *)(temp_v0) + 0xA)) = 1;
    (*(s16 *)((u8 *)(temp_v0) + 8)) = 1;
    (*(s32 *)((u8 *)(temp_v0_2) + 0x14)) = 0x23;
    (*(s32 *)((u8 *)(temp_v0) + 0x14)) = 0x23;
    insertLookupEntry(arg0, temp_v0, temp_s3);
    insertLookupEntry(arg0, temp_v0_2, temp_s3);
}

typedef struct HudElemF {
    u8 pad0[0x18];
    f32 f18;
    f32 f1C;
    u8 pad20[4];
    f32 f24;
    f32 f28;
    u8 pad2C[3];
    u8 b2F;
} HudElemF;

typedef struct HudRectDesc {
    HudElemF *e0;
    HudElemF *e1;
    HudElemF *e2;
    f32 scale;
    u16 w;
    u16 h;
} HudRectDesc;

extern u32 getLookupEntryField5(s32, HudElemF *);
extern void setLookupEntryField5ByKey(s32, HudElemF *, s32);

void layoutHudSpriteScreenRect(s32 a, s32 b, s32 cc, f32 off) {
    HudRectDesc *c = (HudRectDesc *)cc;
    HudElemF *s0 = c->e0;
    HudElemF *s1 = c->e1;
    HudElemF *a1 = c->e2;
    s32 v;

    s0->f24 = ((f32)c->w + c->scale) * 0.015625f;
    s0->f28 = c->scale * 0.125f * 1.25f;
    s1->f24 = c->scale * 0.125f;
    s1->f28 = ((f32)c->h + c->scale * 0.0f * 0.5f) * 0.015625f;
    s0->f24 = s0->f24 * a1->f24;
    s1->f24 = s1->f24 * a1->f24;
    s0->f28 = s0->f28 * a1->f28;
    s1->f28 = s1->f28 * a1->f28;
    s0->f18 = a1->f18 + off;
    s0->f1C = a1->f1C + off + (f32)c->h * a1->f28;
    s1->f18 = a1->f18 + off + (f32)c->w * a1->f24;
    s1->f1C = a1->f1C + off;
    v = (s0->b2F = s1->b2F = a1->b2F) ? getLookupEntryField5(a, a1) : 0;
    setLookupEntryField5ByKey(b, s0, v & 0xFF);
    setLookupEntryField5ByKey(b, s1, v & 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", fake_func_800B47C4);

static u32 D_menu_overlay_800A5DC4[] __attribute__((section(".rodata"))) = { 0x4602003E, 0, 0x45000003 };
