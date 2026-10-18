#ifndef RSMATH_H
#define RSMATH_H

#define M_PI_F    3.14159265358979323846f
// This OUGHT to just be (M_PI_F/180.f), but that leads to silly floating point rounding differenes. Literally 1 bit off >:(
#define M_DTOR_F 0.01745329238474369f
// This OUGHT to just be (180.f/M_PI_F), but that leads to silly floating point rounding differenes. Literally 1 bit off >:(
#define M_RTOD_F 57.29578f
#define DEGREE_TO_RADIAN_F(x) ((x) * M_DTOR_F)
#define RADIAN_TO_DEGREE_F(x) ((x) * M_RTOD_F)

#define M_HALF_PI_F (M_PI_F / 2.0f)

#define SQRTF(out, in) __asm__ volatile("sqrt.s %0, %1" : "=f"(out) : "f"(in))
#define SQRTF_PURE(out, in) __asm__("sqrt.s %0, %1" : "=f"(out) : "f"(in))
#define FABSF(out, in) __asm__ volatile("abs.s %0, %1" : "=f"(out) : "f"(in))
#define FABSF_VAL(x) ({ f32 _r; FABSF(_r, (x)); _r; })
#define FABSF_SELF(x) ({ f32 _r = (x); __asm__ volatile("abs.s %0, %0" : "+f"(_r)); _r; })

static __inline__ f32 sqrtfInline(f32 x) {
    f32 r;
    SQRTF(r, x);
    return r;
}

static __inline__ f32 fabsfInline(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}

#endif
