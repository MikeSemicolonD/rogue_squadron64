#include "common.h"

#include "main/01720.h"
#include "main/07800.h"

struct D_801128D0_type *D_main_801128D0;
u32 gServiceWorkerNextId;
u16 D_main_801128D8;

s32 initServiceRegistry(void) {
    D_main_801128D0 = NULL;
    gServiceWorkerNextId = 0;
    D_main_801128D8 = 0;
    return 1;
}

s32 returnTrueServiceStub(void) {
    return 1;
}

void *rs_malloc(s32, s32);
u32 registerServiceWorker(u16 arg0, s32 arg1, u8 arg2, void (*arg3)(void *)) {
    s32 size;
    struct D_801128D0_type *w;
    struct D_801128D0_type *p;
    u32 stackSize;
    u32 sp;
    u32 *e;

    { s32 t = ((u32)(arg1 + 0x20) >> 3) * 8; size = arg0 * 4; t += 0x1F0; size += t; }
    w = rs_malloc(size, 0x81);
    w->unk005 = 1;
    w->threadStackSize = ((u32)(arg1 + 7) >> 3) * 8;
    w->threadStackPointer = (u32 *)(((u32)((u8 *)w + size - 8) >> 3) * 8);
    w->mesg = (OSMesg *)((u8 *)w + 0x1F0);
    w->next = NULL;
    w->entry = arg3;
    w->mesgCount = arg0;
    w->theadId = ++gServiceWorkerNextId;
    w->threadStackEnd = e = (u32 *)((u8 *)w->threadStackPointer - w->threadStackSize);
    w->threadPrio = arg2;
    *e = 0xCDCDCDCD;
    w->threadStackEnd[1] = 0xCDCDCDCD;
    if (w->mesgCount != 0) {
        osCreateMesgQueue(&w->mq, w->mesg, w->mesgCount);
    }
    osCreateThread(&w->thread, w->theadId, w->entry, w, w->threadStackPointer, w->threadPrio);
    if (D_main_801128D0 == NULL) {
        D_main_801128D0 = w;
    } else {
        p = D_main_801128D0;
        if (p->next != NULL) {
            do {
                p = p->next;
            } while (p->next != NULL);
        }
        p->next = w;
    }
    return w->theadId;
}

s32 startServiceWorker(OSId arg0) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    var_a0->unk005 = 2;
    osStartThread(&var_a0->thread);
    return 1;
}

s32 checkServiceWorkerStackGuard(OSId arg0) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    if ((var_a0->threadStackEnd[0] != 0xCDCDCDCD) || (var_a0->threadStackEnd[1] != 0xCDCDCDCD)) {
        return 0;
    } else {
        return 1;
    }
}

s32 peekServiceMessage(OSId arg0) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    if (osRecvMesg(&var_a0->mq, var_a0->mesg2, 0) == 0) {
        osJamMesg(&var_a0->mq, var_a0->mesg2, 0);
        return 1;
    } else {
        return 0;
    }
}

OSMesg tryRecvServiceMessage(OSId arg0) {
    struct D_801128D0_type *var_s0;

    var_s0 = D_main_801128D0;
    while (var_s0 != NULL) {
        if (var_s0->theadId == arg0) break;
        var_s0 = var_s0->next;
    }
    if (osRecvMesg(&var_s0->mq, var_s0->mesg2, 0) != -1) {
        return var_s0->mesg2[0];
    } else {
        return NULL;
    }
}

OSMesg recvServiceMessage(OSId arg0) {
    struct D_801128D0_type *var_s0;

    var_s0 = D_main_801128D0;
    while (var_s0 != NULL) {
        if (var_s0->theadId == arg0) break;
        var_s0 = var_s0->next;
    }
    osRecvMesg(&var_s0->mq, var_s0->mesg2, 1);
    return var_s0->mesg2[0];
}

struct ServiceMessage {
    u16 unk0;
    u16 id;
    u8 flags;
    OSMesgQueue *replyQueue;
};

s32 sendServiceMessage(OSId from, OSId to, struct ServiceMessage *msg, s32 block) {
    struct D_801128D0_type *dst;
    struct D_801128D0_type *src;

    dst = D_main_801128D0;
    while (dst != NULL) {
        if (dst->theadId == to) break;
        dst = dst->next;
    }
    src = D_main_801128D0;
    while (src != NULL) {
        if (src->theadId == from) break;
        src = src->next;
    }
    msg->flags = 0;
    msg->replyQueue = &src->mq;
    msg->id = D_main_801128D8++;
    while (osSendMesg(&dst->mq, msg, 0) == -1) {
        if (!(block & 1)) {
            return 0;
        }
    }
    return 1;
}

struct blah {
    u32 unk0;
    u8  unk4;
    OSMesgQueue * unk8;
};

// This function appears to be unused, so for matching purposes the argument type
// is mostly immaterial
// Howerver, I would assume its type is whatever `gServiceWorkerMesgBuf` is
s32 signalServiceWorkerStop(struct blah *arg0) {
    arg0->unk4 |= 0x40;
    osJamMesg(arg0->unk8, arg0, 1);
    return 1;
}

s32 postMessageToServiceWorker(OSId arg0, OSMesg arg1) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    osSendMesg(&var_a0->mq, arg1, 1);
    return 1;
}

s32 unregisterServiceWorker(OSId arg0) {
    struct D_801128D0_type *var_s0;
    struct D_801128D0_type *var_s1;

    var_s0 = D_main_801128D0;
    var_s1 = var_s0;
    while (var_s0 != NULL) {
        if (var_s0->theadId == arg0) break;
        var_s1 = var_s0;
        var_s0 = var_s0->next;
    }
    var_s0->unk005 = 0;
    osDestroyThread(&var_s0->thread);
    if (var_s0 == D_main_801128D0) {
        D_main_801128D0 = var_s0->next;
    } else {
        var_s1->next = var_s0->next;
    }
    rs_free(var_s0);
    return 1;
}

s32 sendServiceMessageAwaitReply(OSId from, OSId to, struct ServiceMessage *msg, s32 block) {
    struct D_801128D0_type *dst;
    struct D_801128D0_type *src;
    OSMesgQueue *q;
    OSMesg *buf;

    dst = D_main_801128D0;
    while (dst != NULL) {
        if (dst->theadId == to) break;
        dst = dst->next;
    }
    src = D_main_801128D0;
    while (src != NULL) {
        if (src->theadId == from) break;
        src = src->next;
    }
    msg->flags = 0x80;
    msg->replyQueue = &src->mq;
    msg->id = D_main_801128D8++;
loop_7:
    if (osSendMesg(&dst->mq, msg, 0) == -1) {
        if (block & 1) {
            goto loop_7;
        }
        return 0;
    }
    q = &src->mq;
    buf = src->mesg2;
loop_13:
    osRecvMesg(q, buf, 1);
    if (((struct ServiceMessage *)src->mesg2[0])->id != msg->id) {
        osSendMesg(q, buf, 1);
        goto loop_13;
    }
    return 1;
}

s32 setServiceWorkerPriority(OSId arg0, u8 arg1) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    var_a0->threadPrio = arg1;
    osSetThreadPri(&var_a0->thread, arg1);
    return 1;
}

s32 yieldThreadRet1(s32 unused) {
    osYieldThread();
    return 1;
}

s32 stopServiceWorker(OSId arg0) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    var_a0->unk005 = 4;
    osStopThread(&var_a0->thread);
    return 1;
}

s32 restartServiceWorker(OSId arg0) {
    struct D_801128D0_type *var_a0;

    var_a0 = D_main_801128D0;
    while (var_a0 != NULL) {
        if (var_a0->theadId == arg0) break;
        var_a0 = var_a0->next;
    }
    var_a0->unk005 = 2;
    osStartThread(&var_a0->thread);
    return 1;
}

s32 getServiceMessagePayload(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xC);
}
__asm__(".word 0");

INCLUDE_ASM("asm/nonmatchings/main/07800", fake_func_8000737C);
