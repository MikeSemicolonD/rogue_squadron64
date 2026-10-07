#include "common.h"

#include "PR/os.h"

#include "main/03290.h"
#include "main/033C0.h"
#include "main/080E0.h"
#include "main/08510.h"

OSContPad    gControllerPads[4];
OSMesg       gSIEventMesgBuf;
OSMesgQueue  D_main_8010FF50;
OSMesg       D_main_8010FF68;
u32          bss_padding;
OSThread     D_main_8010FF70;
u32          D_main_8010FF70_stack[0x100];
struct D_main_80110520 D_main_80110520[4];
volatile u8  D_main_bss_80110740;
volatile u8  D_main_bss_80110741;
volatile u8  D_main_bss_80110742;
u8           D_main_bss_80110743;
u32          D_main_bss_80110744;
OSContPad   *D_main_bss_80110748;
OSMesgQueue  D_main_bss_80110750;
OSMesg       D_main_bss_80110768;
OSMesgQueue  gSIEventMesgQueue;
OSContStatus gControllerStatuses[4];
u8           gControllerBits[8];

typedef struct {
    u16 len;
    u16 n;
    u16 *on;
    u16 *off;
} RumblePattern;

s32 floatToInt(f32);
f32 getViModePeriod(void);

void processPolledControllerData(void) {
    struct D_main_80110520 *r;
    OSContStatus *st;
    s32 i;
    RumblePattern *p;
    f32 t;
    f32 len;
    f32 inv;
    s32 k;
    s32 last;
    u8 f;

    i = 0;
    r = D_main_80110520;
    st = gControllerStatuses;
loop:
        if (r->unk6B != 0) {
            t = r->unk80;
            len = ((RumblePattern *)r->unk70)->len;
            if (t < len && !(r->unk6C & 2)) {
                t = t / len;
                t = t * ((RumblePattern *)r->unk70)->n;
                k = floatToInt(t);
                p = (RumblePattern *)r->unk70;
                last = p->n - 1;
                t = t - k;
                if (k >= last) {
                    r->unk78 = p->on[last];
                    r->unk7C = ((RumblePattern *)r->unk70)->off[last];
                } else {
                    inv = 1.0f; inv = inv - t;
                    r->unk78 = p->on[k] * inv + p->on[k + 1] * t;
                    r->unk7C = ((RumblePattern *)r->unk70)->off[k] * inv + ((RumblePattern *)r->unk70)->off[k + 1] * t;
                }
                r->unk80 += getViModePeriod();
            } else {
                r->unk6B = 0;
                r->unk84 = -1;
                if (st->errno != 8 && st->errno != 4 && r->unk68 != 0) {
                    if (osMotorInit(&gSIEventMesgQueue, &r->pfs, i) == 0) {
                        osMotorStop(&r->pfs);
                        r->unk6A = 0;
                    } else {
                        r->unk68 = 0;
                        r->unk6A = 0;
                    }
                }
            }
        }
        if (st->errno != 8 && st->errno != 4) {
            if (r->unk68 == 0) {
                if (r->unk69 == 0) {
                if ((r->unk68 = (osMotorInit(&gSIEventMesgQueue, &r->pfs, i) == 0))) {
                    r->unk6A = 0;
                    r->unk74 = 0.0f;
                }
                r->unk69 = 1;
            }
            }
            if (r->unk6B != 0 && r->unk68 != 0) {
                if (r->unk74 <= 0.0f) {
                    f = r->unk6C;
                    if ((f & 1) && (r->unk6C = f & 0xFE, r->unk6A != 0)) {
                        goto on;
                    }
                    if (r->unk6A == 0) {
                        if (osMotorStart(&r->pfs) == 0) {
                        on:
                            r->unk6A = 1;
                            r->unk74 = r->unk78;
                        } else {
                            goto fail;
                        }
                    } else if (osMotorStop(&r->pfs) == 0) {
                        r->unk6A = 0;
                        r->unk74 = r->unk7C;
                    } else {
                    fail:
                        r->unk6C |= 2;
                    }
                }
                r->unk74 -= getViModePeriod();
            }
        } else {
            r->unk69 = 0;
        }
        r++;
        i++;
        st++;
    if (i < 4) {
        goto loop;
    }
}

u32 startRumbleEffect(u8 arg0, UNIDENTIFIED_TYPE *arg1) {
    if (D_main_bss_80110740 == 0) {
        osRecvMesg(&D_main_bss_80110750, NULL, 1);
        D_main_80110520[arg0].unk6B = 1;
        D_main_80110520[arg0].unk6C = 1;
        D_main_80110520[arg0].unk70 = arg1;
        D_main_80110520[arg0].unk74 = 0.0f;
        D_main_80110520[arg0].unk80 = 0.0f;
        D_main_80110520[arg0].unk84 = D_main_bss_80110744++;
        if (D_main_bss_80110744 == -1U) {
            D_main_bss_80110744 = 0;
        }
        osSendMesg(&D_main_bss_80110750, NULL, 0);
        return D_main_80110520[arg0].unk84;
    }
    return -1U;
}

s32 stopRumbleEffect(s32 arg0) {
    s32 var_a1;

    if (D_main_bss_80110740 == 0) {
        osRecvMesg(&D_main_bss_80110750, NULL, 1);
        for (var_a1 = 0; var_a1 < 4; var_a1++) {
            if ((D_main_80110520[var_a1].unk6B != 0) && (arg0 == D_main_80110520[var_a1].unk84)) {
                D_main_80110520[var_a1].unk6C |= 2;
                osSendMesg(&D_main_bss_80110750, NULL, 0);
                return 1;
            }
        }
        osSendMesg(&D_main_bss_80110750, NULL, 0);
    }
    return 0;
}

void initRumblePakSlots(void) {
    s32 var_s1;

    D_main_bss_80110740 = 1;
    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        
        D_main_80110520[var_s1].unk6B = 0;
        D_main_80110520[var_s1].unk84 = -1U;
        if ((gControllerStatuses[var_s1].errno == CONT_NO_RESPONSE_ERROR) ||
            (gControllerStatuses[var_s1].errno == CONT_OVERRUN_ERROR) ||
            (D_main_80110520[var_s1].unk68 == 0)) continue;

        osMotorInit(&gSIEventMesgQueue, &D_main_80110520[var_s1].pfs, var_s1);
        osMotorStop(&D_main_80110520[var_s1].pfs);
    }
}

void serviceRumblePakMotors(void) {
    s32 var_s1;

    osRecvMesg(&D_main_bss_80110750, NULL, 1);
    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        D_main_80110520[var_s1].unk6B = 0;
        D_main_80110520[var_s1].unk84 = -1U;
        if ((gControllerStatuses[var_s1].errno == CONT_NO_RESPONSE_ERROR) ||
            (gControllerStatuses[var_s1].errno == CONT_OVERRUN_ERROR) ||
            (D_main_80110520[var_s1].unk68 == 0)) continue;

        if (osMotorInit(&gSIEventMesgQueue, &D_main_80110520[var_s1].pfs, var_s1) == 0) {
            osMotorStop(&D_main_80110520[var_s1].pfs);
            do { } while (0);
            D_main_80110520[var_s1].unk6A = 0;
        } else {
            D_main_80110520[var_s1].unk68 = 0;
            D_main_80110520[var_s1].unk6A = 0;
        }
    }
    osSendMesg(&D_main_bss_80110750, NULL, 0);
}

void siServiceThread(void) {
    osCreateMesgQueue(&gSIEventMesgQueue, &gSIEventMesgBuf, 1);
    osSetEventMesg(5U, &gSIEventMesgQueue, NULL);
    osContInit(&gSIEventMesgQueue, gControllerBits, gControllerStatuses);
    osCreateMesgQueue(&D_main_8010FF50, &D_main_8010FF68, 1);

    while (1) {
        osRecvMesg(&D_main_8010FF50, NULL, 1);
        osYieldThread();
        osRecvMesg(&D_main_bss_80110750, NULL, 1);
        D_main_bss_80110741 = 1;
        osContStartQuery(&gSIEventMesgQueue);
        osRecvMesg(&gSIEventMesgQueue, NULL, 1);
        osYieldThread();
        osContGetQuery(gControllerStatuses);
        osContStartReadData(&gSIEventMesgQueue);
        osRecvMesg(&gSIEventMesgQueue, NULL, 1);
        osYieldThread();
        osContGetReadData(gControllerPads);
        processPolledControllerData();
        D_main_bss_80110741 = 0;
        osSendMesg(&D_main_bss_80110750, NULL, 0);
    }
}

void startSiPollingThread(void) {
    s32 var_a1;

    for (var_a1 = 0; var_a1 < 4; var_a1++) {
        gControllerPads[var_a1].errno = 8;
        D_main_80110520[var_a1].unk69 = 0;
        D_main_80110520[var_a1].unk68 = 0;
        D_main_80110520[var_a1].unk6B = 0;
    }
    D_main_bss_80110741 = 0;
    osCreateThread(&D_main_8010FF70, 0, siServiceThread, NULL, D_main_80110520, 0x76);
    osStartThread(&D_main_8010FF70);
    registerSiCallback(wakeSerialThreadOnSi);
}

s32 pollControllerInputs(void) {
    s32 var_t0;
    OSContPad *huh;
    OSContPad *why;

    if (D_main_bss_80110748 != NULL) {
        osRecvMesg(&D_main_bss_80110750, NULL, 1);
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if ((gControllerStatuses[var_t0].errno != CONT_NO_RESPONSE_ERROR) &&
                (gControllerStatuses[var_t0].errno != CONT_OVERRUN_ERROR) &&
                (gControllerStatuses[var_t0].type & 1) &&
                (gControllerPads[var_t0].errno != CONT_NO_RESPONSE_ERROR) &&
                (gControllerPads[var_t0].errno != CONT_OVERRUN_ERROR)) {
                    why = &D_main_bss_80110748[var_t0];
                    why->button  = gControllerPads[var_t0].button;
                    why->stick_x = gControllerPads[var_t0].stick_x;
                    huh = &D_main_bss_80110748[var_t0];
                    huh->stick_y = gControllerPads[var_t0].stick_y;
                    huh = &D_main_bss_80110748[var_t0];
                    huh->errno   = 1;
                } else {
                    huh = &D_main_bss_80110748[var_t0];
                    huh->errno = 0;
                }

        }
        osSendMesg(&D_main_bss_80110750, NULL, 0);
    }
    return 1;
}

s32 bindControllerStatusBuffer(u8 arg0, OSContPad *arg1) {
    s32 var_a0;
    OSContPad *blah;

    if (arg0 == 1) {
        D_main_bss_80110748 = arg1;
        for (var_a0 = 0; var_a0 < 4; var_a0++) {
            blah = &D_main_bss_80110748[var_a0];
            blah->errno = 0;
        }
        return 1;
    } else {
        return 0;
    }
}

u8 isRumbleSlotActive(u8 arg0) {
    if (arg0 >= 4) {
        return 0;
    } else {
        return D_main_80110520[arg0].unk6B;
    }
}

s32 clearControllerPakPresence(u8 arg0) {
    if (arg0 >= 4U) {
        return 0;
    }
    if (D_main_80110520[arg0].unk69 != 0) {
        D_main_80110520[arg0].unk69 = 0;
        D_main_80110520[arg0].unk68 = 0;
    }
    return 1;
}

s32 setRumbleSuspended(u8 arg0) {
    s32 var_s1;
    struct D_main_80110520 *var_s0;

    if ((D_main_bss_80110740 == 0) && (arg0)) {
        for (var_s1 = 0; var_s1 < 4; var_s1++) {
            if (D_main_80110520[var_s1].unk6B != 0) stopRumbleEffect(D_main_80110520[var_s1].unk84);
        }
    }
    D_main_bss_80110740 = arg0;
    return 1;
}

void wakeSerialThreadOnSi(void) {
    if (D_main_bss_80110742 == 0) {
        osSendMesg(&D_main_8010FF50, NULL, 0);
    }
}

void waitForSerialIdle(void) {
    while (D_main_bss_80110741 != 0) {
        osYieldThread();
    }
    D_main_bss_80110742 = 1;
    osStopThread(&D_main_8010FF70);
}

void releaseSerialLock(void) {
    D_main_bss_80110742 = 0;
    osStartThread(&D_main_8010FF70);
}

void initSiQueue(void) {
    D_main_bss_80110742 = 0;
    D_main_bss_80110748 = NULL;
    D_main_bss_80110744 = 0;
    D_main_bss_80110740 = 0;
    osCreateMesgQueue(&D_main_bss_80110750, &D_main_bss_80110768, 1);
    osSendMesg(&D_main_bss_80110750, NULL, 0);
    startSiPollingThread();
}

INCLUDE_ASM("asm/nonmatchings/main/033C0", fake_func_8000337C);
__asm__(".section .rodata\n.word 0x80003318\n.word 0x00000000\n.word 0x00000000\n.section .text");

