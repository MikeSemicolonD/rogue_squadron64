#include "common.h"

#include "PR/gu.h"
#include "rs_math.h"
#include "main/192E0.h"
#include "main/1D000.h"

f32 sinfApprox(f32 y) {
    f32 t;
    f32 s2;
    f32 t3;
    f32 t5;
    f32 t7;
    f32 r;
    f32 p;
    f32 x;
    f32 z;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    u8 mid;

    if (y > 0.999999f) {
        return 1.5707964f;
    }
    if (y < -0.999999f) {
        return -1.5707964f;
    }
    a = y < 0.70710677f;
    b = y > -0.70710677f;
    mid = a & b;
    if (!mid) {
        x = y;
        if (x < 0.0f) {
            SQRTF_PURE(r, 1.0f - x * x);
            z = -r;
        } else {
            t = 1.0f - x * x;
            SQRTF_PURE(z, t);
        }
    } else {
        z = y;
    }
    c = z < 0.001f;
    d = z > -0.001f;
    if (!(c & d)) {
        s2 = z * z;
        t3 = z * s2;
        t5 = t3 * s2;
        t7 = t5 * s2;
        p = t7 * s2;
        z = z + t3 * 0.16666667f + t5 * 0.075f + t7 * 0.04464286f + p * 0.047446f;
    }
    if (!mid) {
        if (x < 0.0f) {
            return -1.5707964f - z;
        }
        return 1.5707964f - z;
    }
    return z;
}

f32 constMinusSinfApprox(f32 arg0) {
    return M_HALF_PI_F - sinfApprox(arg0);
}

f32 atan2Approx(f32 arg0, f32 arg1) {
    register f32 a asm("$f4");

    a = arg0;
    arg0 = (a * a) + (arg1 * arg1);
    if (arg0 > 0.0f) {
        SQRTF_PURE(arg0, arg0);
        arg1 = arg1 / arg0;
        arg0 = a / arg0;
        if (fabs((f64)arg0) < fabs((f64)arg1)) {
            if (arg0 >= 0.0f) {
                if (arg1 >= 0.0f) {
                    return sinfApprox(arg0);
                }
                return 3.1415927f - sinfApprox(arg0);
            }
            if (arg1 >= 0.0f) {
                return 6.2831855f - sinfApprox(-arg0);
            }
            return 3.1415927f + sinfApprox(-arg0);
        }
        if (arg0 >= 0.0f) {
            if (arg1 >= 0.0f) {
                return 1.5707964f - sinfApprox(arg1);
            }
            return 1.5707964f + sinfApprox(-arg1);
        }
        if (arg1 >= 0.0f) {
            return 4.712389f + sinfApprox(arg1);
        }
        return 4.712389f - sinfApprox(-arg1);
    }
    return 0.0f;
}

#if 0
void mat3x3InverseInto(Mat4x3 arg0, Mat4x3 arg1) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft1_3;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = arg1[1][1];
    temp_ft1 = arg1[2][2];
    temp_fv1 = arg1[2][1];
    temp_fv0 = arg1[1][2];
    temp_ft2 = arg1[1][0];
    temp_ft3 = arg1[2][0];
    temp_fa0   =   (temp_fa1 * temp_ft1) - (temp_fv1 * temp_fv0);
    // If you change the `-` here to a `+` you get REALLY close to match, but its obviously wrong.
    temp_ft1_2 = -((temp_ft2 * temp_ft1) - (temp_ft3 * temp_fv0));
    temp_ft2_2 =   (temp_ft2 * temp_fv1) - (temp_ft3 * temp_fa1);
    temp_ft3_2 = 1.0f / ((arg1[0][0] * temp_fa0) + (arg1[0][1] * temp_ft1_2) + (arg1[0][2] * temp_ft2_2));
    arg0[0][0] =  temp_ft3_2 * temp_fa0;
    arg0[1][0] =  temp_ft3_2 * temp_ft1_2;
    arg0[2][0] =  temp_ft3_2 * temp_ft2_2;
    arg0[0][1] = -temp_ft3_2 * ((arg1[0][1] * arg1[2][2]) - (arg1[2][1] * arg1[0][2]));
    arg0[1][1] =  temp_ft3_2 * ((arg1[0][0] * arg1[2][2]) - (arg1[2][0] * arg1[0][2]));
    arg0[2][1] = -temp_ft3_2 * ((arg1[0][0] * arg1[2][1]) - (arg1[2][0] * arg1[0][1]));
    arg0[0][2] =  temp_ft3_2 * ((arg1[0][1] * arg1[1][2]) - (arg1[1][1] * arg1[0][2]));
    arg0[1][2] = -temp_ft3_2 * ((arg1[0][0] * arg1[1][2]) - (arg1[1][0] * arg1[0][2]));
    arg0[2][2] =  temp_ft3_2 * ((arg1[0][0] * arg1[1][1]) - (arg1[1][0] * arg1[0][1]));
    arg0[3][0] = ((-arg1[3][0] * arg0[0][0]) - (arg1[3][1] * arg0[0][1])) - (arg1[3][2] * arg0[0][2]);
    arg0[3][1] = ((-arg1[3][0] * arg0[1][0]) - (arg1[3][1] * arg0[1][1])) - (arg1[3][2] * arg0[1][2]);
    arg0[3][2] = ((-arg1[3][0] * arg0[2][0]) - (arg1[3][1] * arg0[2][1])) - (arg1[3][2] * arg0[2][2]);
}
#else
void mat3x3InverseInto(Mat4x3 arg0, Mat4x3 arg1) {
    f32 temp_fa0;
    register f32 temp_fa1 asm("$f14");
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 xa;
    f32 xb;
    f32 xc;
    register f32 q asm("$f0");

    temp_fa1 = arg1[1][1];
    temp_ft1 = arg1[2][2];
    xa = temp_fa1 * temp_ft1;
    temp_fv1 = arg1[2][1];
    temp_fv0 = arg1[1][2];
    xb = temp_fv1 * temp_fv0;
    temp_ft2 = arg1[1][0];
    xc = temp_ft2 * temp_ft1;
    temp_ft3 = arg1[2][0];
    __asm__ volatile("");
    q = temp_ft3 * temp_fv0;
    temp_fa0 = xa - xb;
    temp_ft1_2 = xc - q;
    q = arg1[0][2];
    temp_ft1_2 = -temp_ft1_2;
    temp_ft2_2 = (temp_ft2 * temp_fv1) - (temp_ft3 * temp_fa1);
    temp_ft3_2 = 1.0f / ((arg1[0][0] * temp_fa0) + (arg1[0][1] * temp_ft1_2) + (q * temp_ft2_2));
    arg0[0][0] =  temp_ft3_2 * temp_fa0;
    arg0[1][0] =  temp_ft3_2 * temp_ft1_2;
    arg0[2][0] =  temp_ft3_2 * temp_ft2_2;
    arg0[0][1] = -temp_ft3_2 * ((arg1[0][1] * arg1[2][2]) - (arg1[2][1] * arg1[0][2]));
    arg0[1][1] =  temp_ft3_2 * ((arg1[0][0] * arg1[2][2]) - (arg1[2][0] * arg1[0][2]));
    arg0[2][1] = -temp_ft3_2 * ((arg1[0][0] * arg1[2][1]) - (arg1[2][0] * arg1[0][1]));
    arg0[0][2] =  temp_ft3_2 * ((arg1[0][1] * arg1[1][2]) - (arg1[1][1] * arg1[0][2]));
    arg0[1][2] = -temp_ft3_2 * ((arg1[0][0] * arg1[1][2]) - (arg1[1][0] * arg1[0][2]));
    arg0[2][2] =  temp_ft3_2 * ((arg1[0][0] * arg1[1][1]) - (arg1[1][0] * arg1[0][1]));
    arg0[3][0] = ((-arg1[3][0] * arg0[0][0]) - (arg1[3][1] * arg0[0][1])) - (arg1[3][2] * arg0[0][2]);
    arg0[3][1] = ((-arg1[3][0] * arg0[1][0]) - (arg1[3][1] * arg0[1][1])) - (arg1[3][2] * arg0[1][2]);
    arg0[3][2] = ((-arg1[3][0] * arg0[2][0]) - (arg1[3][1] * arg0[2][1])) - (arg1[3][2] * arg0[2][2]);
}
#endif

typedef struct {
    s16 i[4][4];
    u16 f[4][4];
} FmMtx;

void floatMatrixToFixed(FmMtx *m, f32 *mf) {
    s32 i, j, e;
    f32 *src;
    FmMtx *p;
    f32 *row;
    src = mf;
    for (i = 0; i < 3; i++) {
        p = m;
        row = src + (i << 1) + i;
        for (j = 0; j < 3; j++) {
            p->i[j][i] = (e = row[j] * 65536.0f) >> 16;
            p->f[j][i] = e;
        }
        e = mf[9] * 16777216.0f;
        p->i[3][i] = e >> 16;
        p->f[3][i] = e;
        mf++;
    }
    p->i[2][3] = p->f[2][3] = 0;
    p->i[1][3] = p->f[1][3] = 0;
    p->i[0][3] = p->f[0][3] = 0;
    p->i[3][3] = 1;
    p->f[3][3] = 0;
}

void clearVec4QuadStruct(Mat4x3 arg0) {
    arg0[2][0] = arg0[2][1] = arg0[3][2] = arg0[1][0] = arg0[1][2] = arg0[3][1] = arg0[0][1] = arg0[0][2] = arg0[3][0] = 0.0f;
    arg0[0][0] = arg0[1][1] = arg0[2][2] = 1.0f;
}

void addVec3At0x24(Mat4x3 arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0[3][0] += arg1;
    arg0[3][1] += arg2;
    arg0[3][2] += arg3;
}

void setVec3At0x24(Mat4x3 arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0[3][0] = arg1;
    arg0[3][1] = arg2;
    arg0[3][2] = arg3;
    arg0[2][0] = arg0[2][1] = arg0[1][0] = arg0[1][2] = arg0[0][1] = arg0[0][2] = 0.0f;
    arg0[0][0] = arg0[1][1] = arg0[2][2] = 1.0f;
}

void applyScaleToMat3x4(Mat4x3 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Mat4x3 sp10;

    sp10[0][0] = arg1;
    sp10[1][1] = arg2;
    sp10[2][2] = arg3;
    sp10[2][0] = sp10[2][1] = sp10[3][2] = sp10[1][0] = sp10[1][2] = sp10[3][1] = sp10[0][1] = sp10[0][2] = sp10[3][0] = 0.0f;
    mat3x4Multiply(sp10, arg0, arg0);
}

void initVec4TripletFromArgs(Mat4x3 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 zero = 0.0f;
    arg0[0][0] = arg1;
    arg0[1][1] = arg2;
    arg0[2][2] = arg3;
    arg0[2][0] = arg0[2][1] = arg0[3][2] = arg0[1][0] = arg0[1][2] = arg0[3][1] = arg0[0][1] = arg0[0][2] = arg0[3][0] = 0.0f;
}

void composeRotationMatrixSlot0(Mat4x3 arg0, f32 arg1) {
    Mat4x3 sp10;
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    sp10[2][1] = temp_fs0;
    sp10[1][1] = temp_fv0;
    sp10[2][2] = temp_fv0;
    sp10[1][2] = -temp_fs0;
    sp10[1][0] = sp10[2][0] = sp10[3][1] = sp10[3][2] = sp10[0][1] = sp10[0][2] = sp10[3][0] = 0.0f;
    sp10[0][0] = 1.0f;
    mat3x4Multiply(sp10, arg0, arg0);
}

void buildRotationMatrixSlot0(Mat4x3 arg0, f32 arg1) {
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    arg0[2][1] = temp_fs0;
    arg0[1][1] = temp_fv0;
    arg0[2][2] = temp_fv0;
    arg0[1][2] = -temp_fs0;
    arg0[1][0] = arg0[2][0] = arg0[3][1] = arg0[3][2] = arg0[0][1] = arg0[0][2] = arg0[3][0] = 0.0f;
    arg0[0][0] = 1.0f;
}

void composeRotationMatrixSlot1(Mat4x3 arg0, f32 arg1) {
    Mat4x3 sp10;
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    sp10[0][2] = temp_fs0;
    sp10[0][0] = temp_fv0;
    sp10[2][2] = temp_fv0;
    sp10[2][0] = -temp_fs0;
    sp10[1][2] = sp10[2][1] = sp10[3][1] = sp10[3][2] = sp10[0][1] = sp10[1][0] = sp10[3][0] = 0.0f;
    sp10[1][1] = 1.0f;
    mat3x4Multiply(sp10, arg0, arg0);
}

void buildRotationMatrixSlot1(Mat4x3 arg0, f32 arg1) {
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    arg0[0][2] = temp_fs0;
    arg0[0][0] = temp_fv0;
    arg0[2][2] = temp_fv0;
    arg0[2][0] = -temp_fs0;
    arg0[1][2] = arg0[2][1] = arg0[3][1] = arg0[3][2] = arg0[0][1] = arg0[1][0] = arg0[3][0] = 0.0f;
    arg0[1][1] = 1.0f;
}

void composeRotationMatrixSlot2(Mat4x3 arg0, f32 arg1) {
    Mat4x3 sp10;
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    sp10[1][0] = temp_fs0;
    sp10[0][0] = temp_fv0;
    sp10[1][1] = temp_fv0;
    sp10[0][1] = -temp_fs0;
    sp10[2][0] = sp10[2][1] = sp10[3][1] = sp10[3][2] = sp10[0][2] = sp10[1][2] = sp10[3][0] = 0.0f;
    sp10[2][2] = 1.0f;
    mat3x4Multiply(sp10, arg0, arg0);
}

void buildRotationMatrixSlot2(Mat4x3 arg0, f32 arg1) {
    f32 temp_fs0;
    f32 temp_fv0;

    temp_fs0 = sinf(DEGREE_TO_RADIAN_F(arg1));
    temp_fv0 = cosf(DEGREE_TO_RADIAN_F(arg1));
    arg0[1][0] = temp_fs0;
    arg0[0][0] = temp_fv0;
    arg0[1][1] = temp_fv0;
    arg0[0][1] = -temp_fs0;
    arg0[2][0] = arg0[2][1] = arg0[3][1] = arg0[3][2] = arg0[0][2] = arg0[1][2] = arg0[3][0] = 0.0f;
    arg0[2][2] = 1.0f;
}

f32 vec3Length(Vec3f v) {
    f32 len;

    SQRTF_PURE(len, v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    return len;
}

f32 normalize_vector(Vec3f v) {
    f32 len;

    SQRTF_PURE(len, v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
    return len;
}

f32 vec3NormalizeInto(Vec3f dst, Vec3f src) {
    f32 len;

    SQRTF_PURE(len, src[0] * src[0] + src[1] * src[1] + src[2] * src[2]);
    dst[0] = src[0] / len;
    dst[1] = src[1] / len;
    dst[2] = src[2] / len;
    return len;
}

f32 vec3Dot(Vec3f arg0, Vec3f arg1) {
    return (arg0[0] * arg1[0]) + (arg0[1] * arg1[1]) + (arg0[2] * arg1[2]);
}

f32 vec2Cross2D(Vec3f arg0, Vec3f arg1) {
    return (arg0[0] * arg1[1]) - (arg0[1] * arg1[0]);
}

void quatFromCardinalAxis(Vec4f arg0, u8 arg1, f32 arg2) {
    f32 temp_fs0;

    arg0[1] = arg0[2] = arg0[3] = 0.0f;
    temp_fs0 = DEGREE_TO_RADIAN_F(arg2) / 2.0f;
    switch (arg1) {
    case 0:
        arg0[1] = 1.0f;
        break;
    case 1:
        arg0[2] = 1.0f;
        break;
    case 2:
        arg0[3] = 1.0f;
        break;
    case 3:
        arg0[1] = -1.0f;
        break;
    case 4:
        arg0[2] = -1.0f;
        break;
    case 5:
        arg0[3] = -1.0f;
        break;
    }
    arg0[0]  = cosf(temp_fs0);
    temp_fs0 = sinf(temp_fs0);
    arg0[1] *= temp_fs0;
    arg0[2] *= temp_fs0;
    arg0[3] *= temp_fs0;
}

#if 0
void quatFromAxisAngleSafe(Vec4f arg0, Vec3f arg1, f32 arg2) {
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 temp_fv0;
    f32 temp_fv1;
    s32 var_v0;
    s32 var_v1;

    temp_fv0 = arg1[0];
    temp_fv1 = arg1[1];
    temp_ft0 = arg1[2];
    temp_fs1 = sqrtf((temp_fv0 * temp_fv0) + (temp_fv1 * temp_fv1) + (temp_ft0 * temp_ft0));
    temp_fs0 = DEGREE_TO_RADIAN_F(arg2) / 2.0f;
    if (((temp_fs0 != 0.0f) && (temp_fs1 != 0.0f))) {
        arg0[0] = cosf(temp_fs0);
        temp_fs0 = sinf(temp_fs0) / temp_fs1;
        arg0[1] = arg1[0] * temp_fs0;
        arg0[2] = arg1[1] * temp_fs0;
        arg0[3] = arg1[2] * temp_fs0;
    } else {
        arg0[0] = 1.0f;
        arg0[1] = arg0[2] = arg0[3] = 0.0f;
    }
}
#else
f32 sinf(f32);
f32 cosf(f32);

void quatFromAxisAngleSafe(f32 *q, Vec3f axis, f32 angle) {
    f32 half;
    f32 len;

    half = angle * 0.008726646f;
    SQRTF_PURE(len, axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    if ((half != 0.0f) & (len != 0.0f)) {
        q[0] = cosf(half);
        half = sinf(half) / len;
        q[1] = axis[0] * half;
        q[2] = axis[1] * half;
        q[3] = axis[2] * half;
    } else {
        q[3] = 0.0f;
        q[2] = 0.0f;
        q[1] = 0.0f;
        q[0] = 1.0f;
    }
}
#endif

void quatFromAxisAngle(Vec4f arg0, Vec3f arg1, f32 arg2) {
    f32 temp_fs0;
    f32 temp_fv0;

    arg0[0]  = cosf(DEGREE_TO_RADIAN_F(arg2) / 2.0f);
    temp_fv0 = sinf(DEGREE_TO_RADIAN_F(arg2) / 2.0f);
    arg0[1] = arg1[0] * temp_fv0;
    arg0[2] = arg1[1] * temp_fv0;
    arg0[3] = arg1[2] * temp_fv0;
}

void quatMultiply(Vec4f arg0, Vec4f arg1, Vec4f arg2) {
    Vec3f sp10;

    arg2[0] = (arg0[0] * arg1[0]) - ((arg0[1] * arg1[1]) + (arg0[2] * arg1[2]) + (arg0[3] * arg1[3]));
    vec3Cross(sp10, &arg0[1], &arg1[1]);
    arg2[1] = (arg0[0] * arg1[1]) + (arg1[0] * arg0[1]) + sp10[0];
    arg2[2] = (arg0[0] * arg1[2]) + (arg1[0] * arg0[2]) + sp10[1];
    arg2[3] = (arg0[0] * arg1[3]) + (arg1[0] * arg0[3]) + sp10[2];
}

void rotateVec3ByQuat(Vec4f arg0, Vec3f arg1, Vec3f arg2) {
    Vec4f temp;

    temp[0] = -((arg0[1] * arg1[0]) + (arg0[2] * arg1[1]) + (arg0[3] * arg1[2]));
    temp[1] =   (arg0[0] * arg1[0]) + (arg0[2] * arg1[2]) - (arg0[3] * arg1[1]);
    temp[2] =   (arg0[0] * arg1[1]) + (arg0[3] * arg1[0]) - (arg0[1] * arg1[2]);
    temp[3] =   (arg0[0] * arg1[2]) + (arg0[1] * arg1[1]) - (arg0[2] * arg1[0]);
    arg2[0] =   (arg0[0] * temp[1]) - (temp[0] * arg0[1]) + (temp[3] * arg0[2]) - (temp[2] * arg0[3]);
    arg2[1] =   (arg0[0] * temp[2]) - (temp[0] * arg0[2]) + (temp[1] * arg0[3]) - (temp[3] * arg0[1]);
    arg2[2] =   (arg0[0] * temp[3]) - (temp[0] * arg0[3]) + (temp[2] * arg0[1]) - (temp[1] * arg0[2]);
}

void quatToRotationMatrix(Vec4f arg0, Mat4x3 arg1) {
    f32 temp_fa0;
    f32 temp_fa0_2;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs4;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_ft3 = arg0[1];
    temp_fa0 = arg0[2];
    temp_ft2 = arg0[3];
    temp_ft1 = arg0[0];
    temp_fv1 = 2.0f / ((temp_ft3 * temp_ft3) + (temp_fa0 * temp_fa0) + (temp_ft2 * temp_ft2) + (temp_ft1 * temp_ft1));
    temp_fs0 = temp_ft3 * temp_fv1;
    temp_ft0 = temp_fa0 * temp_fv1;
    temp_fv1_2 = temp_ft2 * temp_fv1;
    temp_fs1 = temp_ft1 * temp_ft0;
    temp_fv0 = temp_ft1 * temp_fv1_2;
    temp_fs4 = temp_fa0 * temp_ft0;
    temp_ft2_2 = temp_ft2 * temp_fv1_2;
    temp_ft0_2 = temp_ft3 * temp_ft0;
    temp_ft4 = temp_ft3 * temp_fv1_2;
    temp_ft3_2 = temp_ft3 * temp_fs0;
    temp_ft1_2 = temp_ft1 * temp_fs0;
    temp_fa0_2 = temp_fa0 * temp_fv1_2;
    arg1[0][0] = 1.0f - (temp_fs4 + temp_ft2_2);
    arg1[1][0] = temp_ft0_2 + temp_fv0;
    arg1[2][0] = temp_ft4 - temp_fs1;
    arg1[0][1] = temp_ft0_2 - temp_fv0;
    arg1[1][1] = 1.0f - (temp_ft3_2 + temp_ft2_2);
    arg1[2][1] = temp_fa0_2 + temp_ft1_2;
    arg1[0][2] = temp_ft4 + temp_fs1;
    arg1[1][2] = temp_fa0_2 - temp_ft1_2;
    arg1[2][2] = 1.0f - (temp_ft3_2 + temp_fs4);
    arg1[3][0] = (arg1[3][1] = (arg1[3][2] = 0.0f));
}

#if 0
void convertMat3x4ToQuat(Mat4x3 arg0, Vec4f arg1) {
    f32 temp_ft0;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft1_3;
    f32 temp_ft1_4;
    f32 temp_ft1_5;
    f32 temp_ft2;
    f32 temp_fv1;
    s32 temp_a2_2;
    s32 temp_t0_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_v0;
    s32 var_t1;
    u8 temp_a2;
    u8 temp_t0;
    void *temp_a0;
    void *temp_a1;
    void *temp_a3;
    void *temp_t4;

    temp_ft1 = arg0[0][0];
    temp_fv1 = arg0[1][1];
    temp_ft2 = arg0[2][2];
    temp_ft0 = temp_ft1 + temp_fv1 + temp_ft2;
    if (temp_ft0 > 0.0f) {
        temp_ft1_2 = sqrtf(temp_ft0 + 1.0f);
        temp_ft1_3 = 0.5f / temp_ft1_2;
        arg1[0] = (f32) (temp_ft1_2 * 0.5f);
        arg1[1] = (f32) ((arg0[2][1] - arg0[1][2]) * temp_ft1_3);
        arg1[2] = (f32) ((arg0[0][2] - arg0[2][0]) * temp_ft1_3);
        arg1[3] = (f32) ((arg0[1][0] - arg0[0][1]) * temp_ft1_3);
        return;
    }
    var_t1 = 0;
    temp_t4 = arg1 + 4;
    if (temp_ft1 < temp_fv1) {
        var_t1 = 1;
    }
    if (arg0[var_t1][var_t1] < temp_ft2) {
        var_t1 = 2;
    }
    temp_a2 = D_main_80037840[var_t1];
    temp_t0 = D_main_80037840[temp_a2];
    temp_ft1_4 = sqrtf((arg0[var_t1][var_t1] - (arg0[temp_a2][temp_a2] + arg0[temp_t0][temp_t0])) + 1.0f);
    temp_ft1_5 = 0.5f / temp_ft1_4;
    arg1[0] = (arg0[temp_t0][temp_a2] - arg0[temp_a2][temp_t0]) * temp_ft1_5;
    arg1[var_t1 + 1] = temp_ft1_4 * 0.5f;
    arg1[temp_a2 + 1] = (arg0[temp_a2][var_t1] + arg0[var_t1][temp_a2]) * temp_ft1_5;
    arg1[temp_t0 + 1] = (arg0[temp_t0][var_t1] + arg0[var_t1][temp_t0]) * temp_ft1_5;
}
#else
extern u8 D_main_80037840[];

void convertMat3x4ToQuat(Mat4x3 arg0, Vec4f arg1) {
    f32 tr;
    f32 a;
    f32 b;
    f32 c;
    f32 s;
    f32 inv;
    u8 i;
    s32 nv;
    u8 j;
    u8 k;
    f32 *q;
    f32 *ri;
    f32 *rj;
    f32 *rk;

    a = arg0[0][0];
    b = arg0[1][1];
    c = arg0[2][2];
    tr = a + b + c;
    if (tr > 0.0f) {
        SQRTF_PURE(s, tr + 1.0f);
        arg1[0] = s * 0.5f;
        s = 0.5f / s;
        arg1[1] = (arg0[2][1] - arg0[1][2]) * s;
        arg1[2] = (arg0[0][2] - arg0[2][0]) * s;
        arg1[3] = (arg0[1][0] - arg0[0][1]) * s;
        return;
    }
    i = 0;
    q = arg1 + 1;
    if (a < b) {
        i = 1;
    }
    {
        s32 rr = i * 12 + (s32)arg0;
        if (*(f32 *)(i * 4 + rr) < c) {
            i = 2;
        }
    }
    j = D_main_80037840[i];
    nv = j * 12;
    k = D_main_80037840[j];
    ri = (f32 *)(i * 12 + (s32)arg0);
    rj = (f32 *)(nv + (s32)arg0);
    SQRTF_PURE(s, (ri[i] - (rj[j] + (rk = (f32 *)(k * 12 + (s32)arg0))[k])) + 1.0f);
    q[i] = s * 0.5f;
    s = 0.5f / s;
    arg1[0] = (arg0[k][j] - rj[k]) * s;
    q[j] = (rj[i] + ri[j]) * s;
    q[k] = (arg0[k][i] + ri[k]) * s;
}
#endif

void slerpQuaternions(Vec4f arg0, Vec4f arg1, f32 arg2, Vec4f arg3) {
    f32 temp_ft3;
    f64 temp_fs0;
    f64 temp_fs0_2;
    f64 temp_fs1;
    f64 var_fa0;
    f64 var_fs2;

    temp_ft3 = arg0[2];
    temp_fs0 = (arg0[1] * arg1[1]) + (temp_ft3 * arg1[2]) + (arg0[3] * arg1[3]) + (arg0[0] * arg1[0]);
    if ((temp_fs0 + 1.0) > 1e-5f) {
        if ((1.0 - temp_fs0) > 1e-5f) {
            temp_fs1 = M_HALF_PI_F - sinfApprox(temp_fs0);
            {
                f32 sq;
                SQRTF_PURE(sq, 1.0f - (f32) (temp_fs0 * temp_fs0));
                temp_fs0_2 = sq;
            }
            var_fs2 = sinf((1.0f - arg2) * temp_fs1) / temp_fs0_2;
            var_fa0 = sinf(arg2 * temp_fs1) / temp_fs0_2;
        } else {
            var_fa0 = arg2;
            var_fs2 = 1.0f - arg2;
        }
        arg3[1] = (f32) ((var_fs2 * (f64) arg0[1]) + (var_fa0 * (f64) arg1[1]));
        arg3[2] = (f32) ((var_fs2 * (f64) arg0[2]) + (var_fa0 * (f64) arg1[2]));
        arg3[3] = (f32) ((var_fs2 * (f64) arg0[3]) + (var_fa0 * (f64) arg1[3]));
        arg3[0] = (f32) ((var_fs2 * (f64) arg0[0]) + (var_fa0 * (f64) arg1[0]));
    } else {
        arg3[1] = (f32) -temp_ft3;
        arg3[2] = (f32) arg0[1];
        arg3[3] = (f32) -arg0[0];
        arg3[0] = (f32) arg0[3];
        var_fs2 = (f64) sinf((1.0f - arg2) * M_HALF_PI_F);
        var_fa0 = (f64) sinf(arg2 * M_HALF_PI_F);
        arg3[1] = (f32) ((var_fs2 * (f64) arg0[1]) + (var_fa0 * (f64) arg3[1]));
        arg3[2] = (f32) ((var_fs2 * (f64) arg0[2]) + (var_fa0 * (f64) arg3[2]));
        arg3[3] = (f32) ((var_fs2 * (f64) arg0[3]) + (var_fa0 * (f64) arg3[3]));
    }
}

void composeQuatToMat3x4(Mat4x3 arg0, Vec4f arg1) {
    Mat4x3 sp10;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs4;
    f32 temp_ft0;
    f32 temp_ft0_2;
    f32 temp_ft1;
    f32 temp_ft1_2;
    f32 temp_ft2;
    f32 temp_ft2_2;
    f32 temp_ft3;
    f32 temp_ft3_2;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    f32 temp_fv1_2;

    temp_ft2 = arg1[1];
    temp_ft3 = arg1[2];
    temp_ft1 = arg1[3];
    temp_ft0 = arg1[0];
    temp_fv1 = 2.0f / ((temp_ft2 * temp_ft2) + (temp_ft3 * temp_ft3) + (temp_ft1 * temp_ft1) + (temp_ft0 * temp_ft0));
    temp_fs0 = temp_ft2 * temp_fv1;
    temp_fv0 = temp_ft3 * temp_fv1;
    temp_fv1_2 = temp_ft1 * temp_fv1;
    temp_fs1 = temp_ft0 * temp_fv0;
    temp_ft5 = temp_ft0 * temp_fv1_2;
    temp_fs4 = temp_ft3 * temp_fv0;
    temp_ft1_2 = temp_ft1 * temp_fv1_2;
    temp_fv0_2 = temp_ft2 * temp_fv0;
    temp_fa1 = temp_ft2 * temp_fv1_2;
    temp_ft2_2 = temp_ft2 * temp_fs0;
    temp_ft0_2 = temp_ft0 * temp_fs0;
    temp_ft3_2 = temp_ft3 * temp_fv1_2;
    sp10[3][2] = 0.0f;
    sp10[3][1] = 0.0f;
    sp10[3][0] = 0.0f;
    sp10[0][0] = 1.0f - (temp_fs4 + temp_ft1_2);
    sp10[1][0] = temp_fv0_2 + temp_ft5;
    sp10[2][0] = temp_fa1 - temp_fs1;
    sp10[0][1] = temp_fv0_2 - temp_ft5;
    sp10[1][1] = 1.0f - (temp_ft2_2 + temp_ft1_2);
    sp10[2][1] = temp_ft3_2 + temp_ft0_2;
    sp10[0][2] = temp_fa1 + temp_fs1;
    sp10[1][2] = temp_ft3_2 - temp_ft0_2;
    sp10[2][2] = 1.0f - (temp_ft2_2 + temp_fs4);
    mat3x4Multiply((f32 (*)[3]) &sp10, arg0, arg0);
}

extern f32 D_main_80037844;
extern f32 D_main_80037848;
extern f32 D_main_8003784C[3];
extern u32 D_tv_8011A838 __asm__("D_main_bss_8011A838");
extern f32 D_tv_8011A840 __asm__("D_main_bss_8011A840");
extern u32 D_tv_8011A844 __asm__("D_main_bss_8011A844");

typedef struct {
    u8 pad0[0x10];
    s32 w;
    s32 h;
    u8 pad18[8];
    f32 fov;
    f32 near;
    f32 far;
    f32 mtx[4][3];
} TvCam;

u8 transformVec3ToNpcLocalWithScale(TvCam *cam, f32 (*mat)[3], f32 *in, f32 scale, f32 *outZ) {
    f32 v[3];
    f32 r[3];
    f32 len;
    f32 k;
    f32 x, y;
    f32 ax;
    f32 dxp, dxn, dyp, dyn;
    f32 *c;

    mat = (mat != NULL) ? mat : cam->mtx;
    transformVec3ByMat34(mat, in, v);
    if (outZ != NULL) {
        *outZ = v[2];
    }
    if (scale != 0.0f) {
        rotateVec3ByMat3x3(mat, D_main_8003784C, r);
        SQRTF_PURE(len, r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
        scale = scale * len;
        if (v[0] - scale < -125.0f) return 0;
        if (v[1] - scale < -125.0f) return 0;
        if (v[2] - scale < -125.0f) return 0;
        if (125.0f < v[0] + scale) return 0;
        if (125.0f < v[1] + scale) return 0;
        if (125.0f < v[2] + scale) return 0;
        if (!(0.0f < v[2] + scale)) return 0;
        if (v[2] < cam->near) {
            v[2] = cam->near;
        }
        if (!(v[2] - scale < cam->far)) return 0;
        c = &D_main_80037844;
        if (cam->fov == *c) {
            k = D_main_80037848 / v[2];
        } else {
            *c = cam->fov;
            k = cam->fov * 0.008726646f;
            k = cosf(k) / sinf(k);
            D_main_80037848 = k;
            k = k / v[2];
        }
        scale = scale * k;
        x = v[0] * k;
        y = v[1] * k;
        ax = (f32)cam->w / (f32)cam->h * ((f32)D_tv_8011A844 / (f32)D_tv_8011A838) * D_tv_8011A840;
        dyp = 1.0f;
        dyn = -1.0f;
        dyn -= y;
        dyp -= y;
        dxn = -ax;
        ax -= x;
        dxn -= x;
        if (ax < 0.0f) {
            if (dyp < 0.0f) {
                return ax * ax + dyp * dyp < scale * scale;
            } else if (0.0f < dyn) {
                return ax * ax + dyn * dyn < scale * scale;
            } else {
                return __builtin_fabs(ax) < scale;
            }
        } else if (0.0f < dxn) {
            if (dyp < 0.0f) {
                return dxn * dxn + dyp * dyp < scale * scale;
            } else if (0.0f < dyn) {
                return dxn * dxn + dyn * dyn < scale * scale;
            } else {
                return dxn < scale;
            }
        } else {
            if (dyp < 0.0f) {
                return __builtin_fabs(dyp) < scale;
            } else if (0.0f < dyn) {
                return dyn < scale;
            } else {
                return 1;
            }
        }
    } else {
        if (v[0] < -125.0f) return 0;
        if (v[1] < -125.0f) return 0;
        if (v[2] < -125.0f) return 0;
        if (125.0f < v[0]) return 0;
        if (125.0f < v[1]) return 0;
        if (125.0f < v[2]) return 0;
        if (!(0.0f < v[2])) return 0;
        if (!(v[2] < cam->far)) return 0;
        c = &D_main_80037844;
        if (cam->fov == *c) {
            k = D_main_80037848 / v[2];
        } else {
            *c = cam->fov;
            k = cam->fov * 0.008726646f;
            k = cosf(k) / sinf(k);
            D_main_80037848 = k;
            k = k / v[2];
        }
        x = v[0] * k / ((f32)cam->w / (f32)cam->h * ((f32)D_tv_8011A844 / (f32)D_tv_8011A838) * D_tv_8011A840);
        y = v[1] * k;
        if (((-1.0f < x) & (x < 1.0f)) == 0) return 0;
        return (-1.0f < y) & (y < 1.0f);
    }
}

f32 floatModulo(f32 arg0, f32 arg1) {
    f32 temp_fv0;

    temp_fv0 = arg0 / arg1;
    return (temp_fv0 - (s32) temp_fv0) * arg1;
}

__asm__(".section .rodata\n.word 0x3A20496C\n.word 0x6C656761\n.section .text");
