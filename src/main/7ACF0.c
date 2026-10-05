#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/7ACF0", sampleRgbBoxFilter2x2AtSubpixel);

extern void *rs_malloc(s32, s32);
extern void rs_free(void *);
extern void zmemcpy(void *, void *, s32);
extern void sampleRgbBoxFilter2x2AtSubpixel(u16 *, void *, s32, f32, f32);

typedef struct {
    s8 *data;
    u8 pad4[0x24];
    u16 w;
    u16 h;
    u8 pad2C[2];
    u16 fmt;
} HalfImg;

s32 downscaleImageHalfResBoxFilter(HalfImg *img) {
    s32 uw = img->w << 16;
    s32 w = uw >> 16;
    s32 uh = img->h << 16;
    s32 h = uh >> 16;
    s32 w2;
    s32 h2;
    s32 ystep;
    s32 x;
    s32 y;
    s32 xi;
    s32 yi;
    s32 idx;
    f32 fx;
    f32 fy;
    f32 xstep;
    u8 *buf;
    s8 *out;
    u16 px[3];

    if (w >= 3 || h >= 3) {
    if ((img->fmt & 0xF) == 3) {
    if (!(img->fmt & 0x8000)) {
        w2 = uw >> 17;
        h2 = uh >> 17;
        out = img->data;
        buf = rs_malloc(w * h * 3, 0);
        zmemcpy(buf, out, w * h * 3);
        xstep = (f32)(w - 2) / (f32)(w2 - 2);
        ystep = (f32)(h - 2) / (f32)(h2 - 2);
        idx = 3;
        sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, 0.0f, 0.0f);
        out[0] = ((u8 *)px)[1];
        out[1] = ((u8 *)px)[3];
        out[2] = ((u8 *)px)[5];
        for (x = xi = 1; xi < w2 - 1; xi++) {
            sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)x, 0.0f);
            out[idx++] = (px[0] < 0xFF) ? (s32)((u8 *)px)[1] : -1;
            out[idx++] = (px[1] < 0xFF) ? (s32)((u8 *)px)[3] : -1;
            out[idx++] = (px[2] < 0xFF) ? (s32)((u8 *)px)[5] : -1;
            x = (s32)((f32)x + xstep);
        }
        sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)(w - 1), 0.0f);
        out[idx++] = ((u8 *)px)[1];
        out[idx++] = ((u8 *)px)[3];
        out[idx++] = ((u8 *)px)[5];
        for (yi = y = 1; yi < h2 - 1; yi++) {
            sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, 0.0f, (f32)y);
            out[idx++] = (px[0] < 0xFF) ? (s32)((u8 *)px)[1] : -1;
            out[idx++] = (px[1] < 0xFF) ? (s32)((u8 *)px)[3] : -1;
            out[idx++] = (px[2] < 0xFF) ? (s32)((u8 *)px)[5] : -1;
            for (xi = x = 1; xi < w2 - 1; xi++) {
                    sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)x, (f32)y);
                out[idx++] = (px[0] < 0xFF) ? (s32)((u8 *)px)[1] : -1;
                out[idx++] = (px[1] < 0xFF) ? (s32)((u8 *)px)[3] : -1;
                out[idx++] = (px[2] < 0xFF) ? (s32)((u8 *)px)[5] : -1;
                x = (s32)((f32)x + xstep);
            }
            sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)w - 1.0f, (f32)y);
            out[idx++] = (px[0] < 0xFF) ? (s32)((u8 *)px)[1] : -1;
            out[idx++] = (px[1] < 0xFF) ? (s32)((u8 *)px)[3] : -1;
            out[idx++] = (px[2] < 0xFF) ? (s32)((u8 *)px)[5] : -1;
            y += ystep;
        }
        sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, 0.0f, (f32)(h - 1));
        out[idx++] = ((u8 *)px)[1];
        out[idx++] = ((u8 *)px)[3];
        out[idx++] = ((u8 *)px)[5];
        for (xi = x = 1; xi < w2 - 1; xi++) {
            sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)x, (f32)(h - 1));
            out[idx++] = (px[0] < 0xFF) ? (s32)((u8 *)px)[1] : -1;
            out[idx++] = (px[1] < 0xFF) ? (s32)((u8 *)px)[3] : -1;
            out[idx++] = (px[2] < 0xFF) ? (s32)((u8 *)px)[5] : -1;
            x = (s32)((f32)x + xstep);
        }
        sampleRgbBoxFilter2x2AtSubpixel(px, buf, w, (f32)(w - 1), (f32)(h - 1));
        out[idx++] = ((u8 *)px)[1];
        out[idx++] = ((u8 *)px)[3];
        out[idx] = ((u8 *)px)[5];
        rs_free(buf);
    }
    img->w = w2;
    img->h = h2;
        return 1;
    }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/7ACF0", fake_func_8007A86C);

static u32 D_main_8003D4F8[] __attribute__((section(".rodata"))) = { 0xDF4F0090, 0xDF500098 };
