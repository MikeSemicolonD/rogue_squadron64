#include "common.h"
#include "common_types.h"

#include "main/832A0.h"
#include "main/94F50.h"

// Interim BSS externs

extern struct D_main_bss_801511C0_type D_main_bss_801511C0[0x100];
extern u32 D_main_bss_801499F0;
extern u32 D_main_bss_801499FC;
extern struct D_main_bss_80149A00_type  D_main_bss_80149A00[8];
extern struct D_main_bss_80149A00_type *D_main_bss_801529C0;
extern struct D_main_bss_801511C0_type *D_main_bss_801529C4;

typedef struct {
    u16 h0;
    u8 b2;
    u8 b3;
    u8 b4;
    u8 b5;
    u8 pad6[2];
} SsEnt;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} SsTrk;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    u8 pad14[0x10];
} SsChan;

typedef struct {
    u32 handle;
    SsEnt *tblA;
    u8 mapA[0x80];
    SsEnt *tblB;
    u8 mapB[0x80];
    u32 *sng;
    s32 unk110[6];
    SsTrk trk[0x40];
    u8 vol[0x40];
    SsChan ch[0x40];
    s32 E68;
    s32 E6C;
    s32 E70;
    s32 E74;
    s32 E78;
    s32 E7C;
    s32 prog[0x10];
    u8 EC0;
    u8 EC1;
    u16 EC2;
    u8 EC4;
    u8 EC5;
    u16 EC6;
    u8 padEC8[0x2C];
    u8 EF4;
    u8 padEF5[3];
} SsSlot;

typedef struct {
    s32 flags;
    s32 x4;
    s32 x8;
    u16 hC;
    u16 hE;
    u8 b10;
    u8 pad11;
    u8 b12;
    u8 pad13;
    u8 *p14;
    u8 b18;
    u8 pad19[3];
    u8 *p1C;
} SsCfg;

extern SsSlot D_ss_slots[8] __asm__("D_main_bss_80149A00");
extern u8 D_ss_fader[] __asm__("D_main_bss_80141AD8");
extern u32 D_ss_nextHandle __asm__("D_main_bss_801499F0");
void ssSetTrackVoiceTickBudget(u32, u8) __asm__("setTrackVoiceTickBudget");
void ssResetChannelStateRecord(u8, u8) __asm__("resetChannelStateRecord");
void ssDispatchAudioCommand(u8, u16, u8, u8, s32) __asm__("dispatchAudioCommand");
void ssSetAudioFaderState(u8, s32) __asm__("setAudioFaderState");
void ssSetChannelNoteCell(u8, u8, u8, u8) __asm__("setChannelNoteCell");

static __inline__ void ssInitMap(u8 *map, SsEnt *e) {
    u8 j;

    for (j = 0; j < 0x80; j++) {
        map[j] = 0xFF;
    }
    j = 0;
    while (e->b5 != 0xFF) {
        map[e->b5] = j;
        e++;
        j++;
    }
}

static __inline__ void ssSetProg(SsSlot *s, u8 pr, u8 ch) {
    SsEnt *e;

    if (ch != 9) {
        pr = s->mapA[pr];
        if (pr != 0xFF) {
            s->prog[ch] = (((SsEnt *)(pr * 8 + (s32)s->tblA))->h0 << 16) | (((SsEnt *)(pr * 8 + (s32)s->tblA))->b2 << 8) | ((SsEnt *)(pr * 8 + (s32)s->tblA))->b3;
        }
    } else {
        pr = s->mapB[pr];
        if (pr != 0xFF) {
            s->prog[9] = (((SsEnt *)(pr * 8 + (s32)s->tblB))->h0 << 16) | (((SsEnt *)(pr * 8 + (s32)s->tblB))->b2 << 8) | ((SsEnt *)(pr * 8 + (s32)s->tblB))->b3;
        }
    }
}

static __inline__ u32 ssCheck(u32 h) {
    u32 k;

    for (k = 0; k < 8; k++) {
        if (D_ss_slots[k].EC1 == 0 && D_ss_slots[k].handle == h) {
            h = -1;
            break;
        }
    }
    return h;
}

static __inline__ u32 ssAssignHandle(u32 idx) {
    u32 h;

    do {
        u32 t = D_ss_nextHandle;
        D_ss_nextHandle = (t + 1) & 0x7FFFFFFF;
        h = ssCheck(t);
    } while (h == -1);
    D_ss_slots[idx].handle = h;
    idx = h;
    return idx;
}

s32 startSongSequence(SsEnt *tblA, SsEnt *tblB, u8 *ci, u32 *sng, SsCfg *cfg) {
    u32 i;
    SsSlot *s;
    s32 j;
    s32 pass;
    SsEnt *tbl;
    u8 *map;
    s32 *p;
    u32 h;
    u32 k;
    u32 *offs;

    for (i = 0; i < 8; i++) {
        if (D_ss_slots[i].EC1 != 0) {
            break;
        }
    }
    if (i != 8) {
    s = &D_ss_slots[i];
    s->tblA = tblA;
    s->EF4 = 0;
    s->tblB = tblB;
    s->sng = sng;
    ssInitMap(s->mapA, s->tblA);
    ssInitMap(s->mapB, s->tblB);
    s->EC4 = i + 0x17;
    for (j = 0; j < 0x40; j++) {
        s->vol[j] = s->EC4;
    }
    if (cfg == NULL) {
        s->unk110[0] = -1;
        s->unk110[1] = -1;
        s->EC2 = 0x100;
    } else {
        if (cfg->flags & 1) {
            s->unk110[0] = cfg->x4;
            s->unk110[1] = cfg->x8;
        } else {
            s->unk110[0] = -1;
            s->unk110[1] = -1;
        }
        if (cfg->flags & 2) {
            s->EC2 = cfg->hC;
        } else {
            s->EC2 = 0x100;
        }
        if (cfg->flags & 8) {
            for (j = 0; j < cfg->b12; j++) {
                s->vol[cfg->p14[j * 2]] = cfg->p14[j * 2 + 1];
                ssSetAudioFaderState(cfg->p14[j * 2 + 1], 0);
            }
        }
        if (cfg->flags & 4) {
            ssDispatchAudioCommand(cfg->b10, cfg->hE, s->EC4, 0, 0);
            for (j = 0; j < cfg->b18; j++) {
                ssDispatchAudioCommand(cfg->b10, cfg->hE, cfg->p1C[j], 0, 0);
            }
        }
    }
    {
        u32 b = sng[4];
        s->unk110[5] = b;
        ssSetTrackVoiceTickBudget(b, i);
    }
    s->E6C = s->E68 = sng[3] + (s32)sng;
    s->E70 = 0;
    s->E74 = 0;
    s->EC5 = 0;
    offs = (u32 *)(sng[0] + (s32)sng);
    for (j = 0; j < 0x40; j++) {
        u32 off;

        D_ss_fader[j] = 0x7F;
        s->trk[j].c = 0;
        s->trk[j].d = 0;
        s->ch[j].c = 0;
        s->ch[j].d = 0;
        s->ch[j].e = 0;
        off = offs[j];
        if (off != 0) {
            s->trk[j].b = s->trk[j].a = off + (s32)sng;
        } else {
            s->trk[j].b = s->trk[j].a = 0;
        }
    }
    s->E78 = 0;
    s->E7C = 0;
    for (j = 0; j < 0x10; j++) {
        ssResetChannelStateRecord(j, i);
    }
    {
        s32 m = -1;
        j = 0xF;
        do {
            s->prog[j] = m;
        } while (--j >= 0);
    }
    tbl = s->tblA;
    map = s->mapA;
    for (pass = 0; pass < 2; pass++) {
        for (j = 0; j < 0x80; j++) {
            u8 v = map[j];
            if (v != 0xFF) {
                SsEnt *e = (SsEnt *)(v * 8 + (s32)tbl);
                if (e->b4 != 0xFF) {
                    s->prog[e->b4] = (e->h0 << 16) | (e->b2 << 8) | e->b3;
                }
            }
        }
        tbl = s->tblB;
        map = s->mapB;
    }
    if (ci != NULL) {
        for (j = 0; j < 0x10; j++) {
            ssSetProg(s, ci[j * 8 + 4], j);
            ssSetChannelNoteCell(7, j, i, ci[j * 8 + 5]);
            ssSetChannelNoteCell(10, j, i, ci[j * 8 + 6]);
            ssSetChannelNoteCell(0x5B, j, i, ci[j * 8 + 7]);
            ssSetChannelNoteCell(0x5D, j, i, ci[j * 8 + 8]);
        }
    }
    s->EC6 = 0;
    if (cfg == NULL || !(cfg->flags & 0x10)) {
        s->EC0 = 1;
    }
    h = ssAssignHandle(i);
    s->EC1 = 0;
    return h;
    }
    return -1;
}

typedef struct {
    u32 unk0;
    u16 unk4;
    u8 unk6;
    u8 unk7;
} SatEv;
typedef struct {
    u32 unk00;
    u32 unk04;
    SatEv *ev;
    u8 pad0C[0x14];
    u8 ch;
    s8 vel;
    s8 note;
    u8 ch2;
} SatLane;
typedef struct {
    u32 a;
    u32 b;
} SatPair;
typedef struct {
    u16 a;
    u8 b;
    u8 c;
    u32 pad;
} SatProg;
typedef struct { SatProg *tbl; u8 map[0x80]; } SatBank;
#define SLANE(o) ((SatLane *)((u8 *)D_main_bss_801529C0 + (o) + 0x568))

extern s32 D_main_bss_801499F4;
extern u8 D_sat801499F8 __asm__("D_main_bss_801499F8");
extern u8 D_main_bss_801529CB;
void setChannelNoteCell(u8, u8, u8, u8);
s32 processSongByHandle(s32, s32, s32);
extern s32 dispatchSequencerNoteEvent(s32, u8, u8, s32, s32, s32, s32, s32, s32, s32);

static __inline__ struct D_main_bss_801511C0_type *satAllocNode(void) {
    struct D_main_bss_801511C0_type *n = D_main_bss_801529C4;
    if (n != NULL) {
        D_main_bss_801529C4 = n->unk00;
        if (D_main_bss_801529C4 != NULL) {
            D_main_bss_801529C4->unk04 = NULL;
        }
        n->unk04 = NULL;
        n->unk00 = D_main_bss_801529C0->unkE78[0];
        if (n->unk00 != NULL) {
            D_main_bss_801529C0->unkE78[0]->unk04 = n;
        }
        D_main_bss_801529C0->unkE78[0] = n;
    }
    return n;
}

static __inline__ void satSetProg(SsSlot *s, u8 pr, s32 ch) {
    if (ch != 9) {
        pr = s->mapA[pr];
        if (pr != 0xFF) {
            s->prog[ch] = (((SsEnt *)(pr * 8 + (s32)s->tblA))->h0 << 16) | (((SsEnt *)(pr * 8 + (s32)s->tblA))->b2 << 8) | ((SsEnt *)(pr * 8 + (s32)s->tblA))->b3;
        }
    } else {
        pr = s->mapB[pr];
        if (pr != 0xFF) {
            s->prog[9] = (((SsEnt *)(pr * 8 + (s32)s->tblB))->h0 << 16) | (((SsEnt *)(pr * 8 + (s32)s->tblB))->b2 << 8) | ((SsEnt *)(pr * 8 + (s32)s->tblB))->b3;
        }
    }
}

s32 stepActiveSongTracks(void) {
    s32 ret;
    s32 i;
    s32 off;
    s32 o;
    struct D_main_bss_80149A00_type *d;
    SatLane *l;
    SatEv *ev;
    SatProg *pg;
    s32 b6;
    s32 b7;
    u8 ch;
    s32 k;
    s32 p;
    s32 idx;
    s32 ch2;
    s32 h;
    s32 note;
    s32 vel;
    struct D_main_bss_801511C0_type *n;
    struct D_main_bss_801511C0_type *nx;

    ret = 0;
    for (i = 0; i < 0x40; i++) {
        off = i * 0x24;
        if (SLANE(off)->ev != NULL) {
            D_main_bss_801499F4++;
            ret = 1;
            while (SLANE(off)->ev != NULL) {
                o = off;
                d = D_main_bss_801529C0;
                l = (SatLane *)((u8 *)d + o + 0x568);
                ev = l->ev;
                if (l->unk04 + d->unk110[4] < ev->unk0) {
                    break;
                }
                b6 = ev->unk6;
                b7 = ev->unk7;
                ch = l->ch;
                if ((b6 == 0xFF) & (b7 == 0xFF)) {
                    l->ev = NULL;
                    continue;
                }
                if (((b6 & 0x80) != 0) & (b7 == 0)) {
                    k = b6 & 0x7F;
                    satSetProg((SsSlot *)d, k, ch);
                } else if (((b6 & 0x80) != 0) & (b7 == 1)) {
                    k = 0x82;
                    setChannelNoteCell(k, ch, D_main_bss_801529CB, b6 & 0x7F);
                } else if ((b6 & 0x80) && (b7 & 0x80)) {
                    k = b7 & 0x7F;
                    if (k == 0x68) {
                        if (*((u8 *)d + 0xEF4) != 0) {
                            processSongByHandle((s32)d->unkEC8, d->unkEF0[0], 1);
                            *((u8 *)D_main_bss_801529C0 + 0xEF4) = 0;
                        }
                    } else {
                        setChannelNoteCell(k, ch, D_main_bss_801529CB, b6 & 0x7F);
                    }
                } else {
                    ch2 = SLANE(o)->ch2;
                    if (D_main_bss_801529C0->unk110[ch2 / 32] & (1 << (ch2 & 0x1F))) {
                        h = *(s32 *)((u8 *)D_main_bss_801529C0 + ch * 4 + 0xE80);
                        if (h != -1) {
                            b6 += SLANE(o)->note;
                            b6 = (b6 < 0x80) ? ((b6 < 0) ? 0 : b6) : 0x7F;
                            b7 += SLANE(o)->vel;
                            b7 = (b7 < 0x80) ? ((b7 < 0) ? 0 : b7) : 0x7F;
                            n = satAllocNode();
                            if (n != NULL) {
                                h = dispatchSequencerNoteEvent(h, b6, b7, 0x40, ch, D_main_bss_801529CB, 0, ch2,
                                    D_main_bss_801529C0->unk528[ch2], D_sat801499F8 ? -1 : 0);
                                if (h != -1) {
                                    n->unk08 = h;
                                    l = SLANE(o);
                                    n->unk0C = l->ev->unk0 + l->ev->unk4;
                                    *(SatPair *)&n->unk10 = *(SatPair *)&l->unk00;
                                } else {
                                    if (n->unk00 != NULL) {
                                        n->unk00->unk04 = n->unk04;
                                    }
                                    if (n->unk04 != NULL) {
                                        n->unk04->unk00 = n->unk00;
                                    } else {
                                        D_main_bss_801529C0->unkE78[0] = n->unk00;
                                    }
                                    n->unk00 = D_main_bss_801529C4;
                                    if (D_main_bss_801529C4 != NULL) {
                                        D_main_bss_801529C4->unk04 = n;
                                    }
                                    n->unk04 = NULL;
                                    D_main_bss_801529C4 = n;
                                }
                            }
                        }
                    }
                }
                SLANE(o)->ev++;
            }
        }
    }
    return ret;
}

// https://decomp.me/scratch/9HNev
s32 tickScheduledSongEvents(void) {
    s32 temp_v0_3;
    struct D_main_bss_801511C0_type *temp_s1;
    struct D_main_bss_801511C0_type *temp_v0;
    struct D_main_bss_801511C0_type *var_s0;

    var_s0 = D_main_bss_801529C0->unkE78[0];
    if (var_s0 == NULL) {
        return 0;
    }
    temp_v0 = var_s0;
    while (temp_v0 != NULL) {
        D_main_bss_801499FC += 1;
        temp_s1 = temp_v0->unk00;
        if ((temp_v0->unk14 + D_main_bss_801529C0->unk110[4]) >= temp_v0->unk0C) {
            flagVoiceChainForStop(temp_v0->unk08);
            if (temp_v0->unk00 != NULL) {
                temp_v0->unk00->unk04 = temp_v0->unk04;
            }
            if (temp_v0->unk04 != NULL) {
                temp_v0->unk04->unk00 = temp_v0->unk00;
            } else {
                D_main_bss_801529C0->unkE78[0] = temp_v0->unk00;
            }
            temp_v0->unk00 = D_main_bss_801529C0->unkE78[1];
            if (temp_v0->unk00 != NULL) {
                D_main_bss_801529C0->unkE78[1]->unk04 = temp_v0;
            }
            temp_v0->unk04 = NULL;
            D_main_bss_801529C0->unkE78[1] = temp_v0;
        } else {
            temp_v0_3 = temp_v0->unk10 + D_main_bss_801529C0->unk110[2];
            temp_v0->unk10 = temp_v0_3 & 0xFFFF;
            temp_v0->unk14 += (temp_v0_3 >> 0x10) + D_main_bss_801529C0->unk110[3];
        }
        temp_v0 = temp_s1;
    }
    return 1;
}

typedef struct {
    s32 baseTime;
    s32 pad4;
    u8 *stream;
    s32 padC;
    u16 value;
    u16 pad12;
    u32 time;
    s32 pad18;
    u8 channel;
    u8 pad1D[7];
} SongLane;

#define LANE(o) ((SongLane *)((u8 *)D_main_bss_801529C0 + (o) + 0x56C))

extern u8 D_main_bss_801529CB;
void setChannelNoteCell(u8, u8, u8, u8);

void stepSongPitchBendLanes(void) {
    s32 off;
    s32 o;
    u8 done;
    s32 b0;
    s32 b1;
    s32 delta;
    s32 len;
    u32 t;
    s32 v;
    u8 *p;
    u8 *q;

    off = 0;
    do {
        if (LANE(off)->stream != NULL) {
            done = 0;
            o = off;
            do {
                b0 = LANE(o)->stream[0];
                b1 = LANE(o)->stream[1];
                if ((b0 == 0x80) & (b1 == 0)) {
                    LANE(o)->stream = NULL;
                    done = 1;
                } else {
                    if (b0 & 0x80) {
                        delta = b1 | ((b0 & 0x7F) << 8);
                        len = 2;
                    } else {
                        delta = b0 & 0xFF;
                        len = 1;
                    }
                    t = delta + LANE(o)->time;
                    if (LANE(o)->baseTime + D_main_bss_801529C0->unk110[4] >= t) {
                        LANE(o)->stream = LANE(o)->stream + len;
                        LANE(o)->time = t;
                        p = LANE(o)->stream;
                        b0 = p[0];
                        b1 = p[1];
                        if (b0 & 0x80) {
                            v = ((s32)((b1 | ((b0 & 0x7F) << 8)) << 17)) >> 17;
                            LANE(o)->stream = p + 2;
                        } else {
                            v = ((s32)(b0 << 25)) >> 25;
                            LANE(o)->stream = p + 1;
                        }
                        LANE(o)->value += v;
                        setChannelNoteCell(0x80, LANE(o)->channel, D_main_bss_801529CB, (LANE(o)->value >> 7) & 0xFF);
                        setChannelNoteCell(0x81, LANE(o)->channel, D_main_bss_801529CB, LANE(o)->value & 0x7F);
                    } else {
                        done = 1;
                    }
                }
            } while (!done);
        }
        off += 0x24;
    } while (off < 0x900);
}

typedef struct {
    s32 baseTime;
    s32 pad4;
    u8 *stream;
    u8 *stream2;
    u16 value;
    u16 value2;
    u32 time;
    u32 time2;
    u8 channel;
    u8 pad1D[7];
} SongLane2;

#define LANE2(o) ((SongLane2 *)((u8 *)D_main_bss_801529C0 + (o) + 0x56C))


void stepSongModulationLanes(void) {
    s32 off;
    s32 o;
    u8 done;
    s32 b0;
    s32 b1;
    s32 delta;
    s32 len;
    u32 t;
    s32 v;
    u8 *p;
    u8 *q;

    off = 0;
    do {
        if (LANE2(off)->stream2 != NULL) {
            done = 0;
            o = off;
            do {
                b0 = LANE2(o)->stream2[0];
                b1 = LANE2(o)->stream2[1];
                if ((b0 == 0x80) & (b1 == 0)) {
                    LANE2(o)->stream2 = NULL;
                    done = 1;
                } else {
                    if (b0 & 0x80) {
                        v = b1 | ((b0 & 0x7F) << 8);
                        len = 2;
                    } else {
                        v = b0 & 0xFF;
                        len = 1;
                    }
                    t = LANE2(o)->time2 + (s16)v;
                    if (LANE2(o)->baseTime + D_main_bss_801529C0->unk110[4] >= t) {
                        LANE2(o)->stream2 = LANE2(o)->stream2 + len;
                        LANE2(o)->time2 = t;
                        p = LANE2(o)->stream2;
                        b0 = p[0];
                        b1 = p[1];
                        if (b0 & 0x80) {
                            v = ((s32)((b1 | ((b0 & 0x7F) << 8)) << 17)) >> 17;
                            LANE2(o)->stream2 = p + 2;
                        } else {
                            v = ((s32)(b0 << 24)) >> 24;
                            LANE2(o)->stream2 = p + 1;
                        }
                        LANE2(o)->value2 += v;
                        setChannelNoteCell(0x1, LANE2(o)->channel, D_main_bss_801529CB, (LANE2(o)->value2 >> 7) & 0xFF);
                        setChannelNoteCell(0x21, LANE2(o)->channel, D_main_bss_801529CB, LANE2(o)->value2 & 0x7F);
                    } else {
                        done = 1;
                    }
                }
            } while (!done);
        }
        off += 0x24;
    } while (off < 0x900);
}

typedef struct {
    u32 time;
    u8 prog;
    u8 vol;
    u8 pad6[2];
    u16 kind;
    u16 hA;
} SrEv;
typedef struct {
    u8 pad[0x128];
    SrEv *base;
    SrEv *cur;
    u32 frac;
    u32 time;
} SrReg;
typedef struct {
    u32 w0;
    u32 w4;
    u8 *p8;
    u8 *pC;
    u8 *p10;
    u16 h14;
    u16 h16;
    u32 w18;
    u32 w1C;
    u8 ch;
    u8 b21;
    u8 b22;
    u8 idx;
} SrLane;
#define SREG(d, o) ((SrReg *)((u8 *)(d) + (o)))
#define SRLANE(d, o) ((SrLane *)((u8 *)(d) + (o) + 0x568))
void updateSongTempoTickRate(u32);

s32 asrImpl(void) __asm__("advanceSongRegion");
s32 asrImpl(void) {
    u8 first;
    s32 ret;
    s32 i;
    s32 o;
    s32 off;
    s32 lo;
    struct D_main_bss_80149A00_type *d;
    SrReg *r;
    SrEv *ev;
    u8 *p;
    u32 t;
    s32 kk;
    s32 q;

    first = 1;
    ret = 0;
    i = 0;
    do {
        o = i * 16;
        off = i * 0x24;
        d = D_main_bss_801529C0;
        if (SREG(d, o)->cur != NULL) {
            ret = 1;
            if (SREG(d, o)->time + d->unk110[4] >= SREG(d, o)->cur->time) {
                lo = off;
                do {
                    r = SREG(d, i * 16);
                    ev = r->cur;
                    kk = ev->kind;
                    switch (kk) {
                    case 0xFFFF:
                        r->cur = NULL;
                        goto next;
                    case 0xFFFE:
                        if ((q = d->unkEC5) != 0) {
                            r->cur = NULL;
                            goto next;
                        }
                        t = ev->hA;
                        r->cur = r->base + t;
                        r->time = d->SNG_file->unk14;
                        r->frac = 0;
                        if (first) {
                            first = 0;
                            updateSongTempoTickRate(d->SNG_file->unk14);
                            D_main_bss_801529C0->unkEC6++;
                        }
                        break;
                    default:
                        #undef p
{ s32 *tbl = (s32 *)((u8 *)d->SNG_file->unk04 + (s32)d->SNG_file); t = tbl[kk] + (s32)d->SNG_file; }
#define p ((u8 *)t)
#define p ((u8 *)t)
                        SRLANE(d, lo)->w4 = 0;
                        SRLANE(d, lo)->w0 = 0;
                        SRLANE(d, lo)->p8 = p + 0xC;
                        if (*(s32 *)(p + 4) != 0) {
                            SRLANE(d, lo)->pC = (u8 *)(*(s32 *)(p + 4) + (s32)d->SNG_file);
                        } else {
                            SRLANE(d, lo)->pC = NULL;
                        }
                        SRLANE(D_main_bss_801529C0, lo)->w18 = 0;
                        SRLANE(D_main_bss_801529C0, lo)->h14 = 0x2000;
                        if (*(s32 *)(p + 8) != 0) {
                            SRLANE(D_main_bss_801529C0, lo)->p10 = (u8 *)(*(s32 *)(p + 8) + (s32)D_main_bss_801529C0->SNG_file);
                        } else {
                            SRLANE(D_main_bss_801529C0, lo)->p10 = NULL;
                        }
                        SRLANE(D_main_bss_801529C0, lo)->w1C = 0;
                        SRLANE(D_main_bss_801529C0, lo)->h16 = 0;
                        SRLANE(D_main_bss_801529C0, lo)->ch = ((u8 *)D_main_bss_801529C0->SNG_file->unk08 + (s32)D_main_bss_801529C0->SNG_file)[i];
                        SRLANE(D_main_bss_801529C0, lo)->b21 = ((u8 *)ev)[0xB];
                        SRLANE(D_main_bss_801529C0, lo)->b22 = ((u8 *)ev)[0xA];
                        SRLANE(D_main_bss_801529C0, lo)->idx = i;
                        if (ev->prog != 0xFF) {
                            satSetProg((SsSlot *)D_main_bss_801529C0, ev->prog, SRLANE(D_main_bss_801529C0, lo)->ch);
                        }
                        if (ev->vol != 0xFF) {
                            setChannelNoteCell(7, SRLANE(D_main_bss_801529C0, lo)->ch, D_main_bss_801529CB, ev->vol);
                        }
                        SREG(D_main_bss_801529C0, o)->cur++;
#undef p
                        break;
                    }
                    d = D_main_bss_801529C0;
                } while (SREG(d, q = i * 16)->time + d->unk110[4] >= SREG(d, q)->cur->time);
            }
            t = SREG(D_main_bss_801529C0, o)->frac + D_main_bss_801529C0->unk110[2];
            SREG(D_main_bss_801529C0, o)->frac = t & 0xFFFF;
            t >>= 16;
            SREG(D_main_bss_801529C0, o)->time += t + D_main_bss_801529C0->unk110[3];
        }
    next:
        i++;
    } while (i < 0x40);
    return ret;
}

extern s32 D_main_bss_80142038;
extern s32 D_main_bss_801440C0;
extern u8 D_main_bss_801529CB;
void setTrackVoiceTickBudget(u32, u8, struct D_main_bss_80149A00_type *);

void updateSongTempoTickRate(u32 arg0) {
    struct SNG_unk0C_type *cur;
    struct SNG_unk0C_type *prev;
    u32 budget;
    u32 tickDelta;
    s32 deltaTime;
    s32 neg;

    D_main_bss_801529C0->unkE6C = D_main_bss_801529C0->unkE68;
    D_main_bss_801529C0->unkE74 = arg0;
    D_main_bss_801529C0->unkE70 = 0;
    if (D_main_bss_801529C0->unkE6C->unk0 != -1U) {
        neg = -1;
loop:
        cur = D_main_bss_801529C0->unkE6C;
        if (D_main_bss_801529C0->unkE74 + D_main_bss_801529C0->unk110[4] >= cur->unk0) {
            budget = cur->unk4;
            D_main_bss_801529C0->unk110[5] = budget;
            setTrackVoiceTickBudget(budget, D_main_bss_801529CB, D_main_bss_801529C0);
            prev = D_main_bss_801529C0->unkE6C;
            D_main_bss_801529C0->unkE6C = prev + 1;
            if (((s32 *)prev)[2] != neg) {
                goto loop;
            }
        }
    }
    deltaTime = (s32)(D_main_bss_80142038 << 16) / D_main_bss_801440C0;
    tickDelta = ((u32)(D_main_bss_801529C0->unk110[5] * 0x600) / 240) * deltaTime;
    tickDelta = (tickDelta * D_main_bss_801529C0->unkEC2) >> 8;
    D_main_bss_801529C0->unk110[2] = tickDelta & 0xFFFF;
    D_main_bss_801529C0->unk110[3] = tickDelta >> 16;
    D_main_bss_801529C0->unk110[4] = D_main_bss_801529C0->unk110[3] >> 1;
}

static inline s32 findSongSlotByHandle(u32 handle) {
    u32 i;

    for (i = 0; i < 8; i++) {
        if (D_main_bss_80149A00[i].unkEC1 == 0 && D_main_bss_80149A00[i].unk000 == (handle & 0x7FFFFFFF)) {
            return i | (handle & 0x80000000);
        }
    }
    return -1;
}
u16 getSongParamByHandle(u32 handle) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            if (slot >= 0) {
                return D_main_bss_80149A00[slot].unkEC6;
            }
        }
    }
    return 0;
}

s32 isSongHandleActive(u32 handle) {
    if (gMusyXActiveFlag != 0) {
        return findSongSlotByHandle(handle) != -1;
    }
    return 0;
}

extern void stopVoicesByHandle(s32);

s32 stopSongByHandle(s32 handle) {
    struct D_main_bss_80149A00_type *e;
    struct D_main_bss_80149A00_type *e2;
    struct D_main_bss_801511C0_type *n;
    struct D_main_bss_801511C0_type *t;
    struct D_main_bss_801511C0_type *m;

    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                e = &D_main_bss_80149A00[handle];
                D_main_bss_80149A00[handle].unkEC0 = 0;
                n = e->unkE78[0];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                n = e->unkE78[1];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                e2 = &D_main_bss_80149A00[handle];
                m = e2->unkE78[0];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[0];
                    e2->unkE78[0] = 0;
                    D_main_bss_801529C4 = t;
                }
                m = e2->unkE78[1];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[1];
                    e2->unkE78[1] = 0;
                    D_main_bss_801529C4 = t;
                }
            }
        } else {
            handle &= 0x7FFFFFFF;
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                D_main_bss_80149A00[handle].unkEEE |= 8;
            }
        }
    }
}

s32 stopSongByHandle(s32);

void stopSongByHandleLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        stopSongByHandle(arg0);
        factor5MutexRelease();
    }
}

extern void stopVoicesByHandle(s32);

void tickSongSequence(s32 handle) {
    struct D_main_bss_80149A00_type *e;
    struct D_main_bss_80149A00_type *e2;
    struct D_main_bss_801511C0_type *n;
    struct D_main_bss_801511C0_type *t;
    struct D_main_bss_801511C0_type *m;

    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                e = &D_main_bss_80149A00[handle];
                D_main_bss_80149A00[handle].unkEC0 = 0;
                n = e->unkE78[0];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                n = e->unkE78[1];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                e2 = &D_main_bss_80149A00[handle];
                m = e2->unkE78[0];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[0];
                    e2->unkE78[0] = 0;
                    D_main_bss_801529C4 = t;
                }
                m = e2->unkE78[1];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[1];
                    e2->unkE78[1] = 0;
                    D_main_bss_801529C4 = t;
                }
            }
            D_main_bss_80149A00[handle].unkEC1 = 1;
        } else {
            handle &= 0x7FFFFFFF;
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                D_main_bss_80149A00[handle].unkEF0[0] = 0;
            }
        }
    }
}

void tickSongSequenceLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        tickSongSequence(arg0);
        factor5MutexRelease();
    }
}

void tickActiveSongs(void) {
    u32 i;

    for (i = 0; i < 8; i++) {
        tickSongSequence(D_main_bss_80149A00[i].unk000);
    }
}

s32 setSongPauseStateByHandle(u32 handle, u8 paused) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            if (slot >= 0) {
                D_main_bss_80149A00[slot].unkEC5 = paused == 0;
                return 1;
            }
        }
    }
    return 0;
}

s32 applySongU16ParamCmd(s32 handle, s32 value) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unkEC2 = value;
        } else {
            handle &= 0x7FFFFFFF;
            D_main_bss_80149A00[handle].unkEEC = value;
            D_main_bss_80149A00[handle].unkEEE |= 0x20;
        }
    }
}

s32 applySongU16ParamCmd(s32, s32);

void applySongU16ParamCmdLocked(s32 arg0, s32 arg1) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        applySongU16ParamCmd(arg0, arg1 & 0xFFFF);
        factor5MutexRelease();
    }
}

s32 quiesceSongSlotCmd(s32 handle) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unkEC0 = 1;
        } else {
            D_main_bss_80149A00[handle & 0x7FFFFFFF].unkEEE &= ~8;
        }
    }
}

s32 quiesceSongSlotCmd(s32);

void quiesceSongSlotCmdLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        quiesceSongSlotCmd(arg0);
        factor5MutexRelease();
    }
}

s32 setSongParamPairCmd(s32 handle, s32 a, s32 b) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unk110[0] = a;
            D_main_bss_80149A00[handle].unk110[1] = b;
        } else {
            handle &= 0x7FFFFFFF;
            D_main_bss_80149A00[handle].unkEC8[7] = a;
            D_main_bss_80149A00[handle].unkEC8[8] = b;
            D_main_bss_80149A00[handle].unkEEE |= 0x10;
        }
    }
}

s32 setSongParamPairCmd(s32, s32, s32);

void setSongParamPairCmdLocked(s32 arg0, s32 arg1, s32 arg2) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        setSongParamPairCmd(arg0, arg1, arg2);
        factor5MutexRelease();
    }
}

extern void dispatchAudioCommand(u8, u16, u8, u8, s32);

void queueAudioVoiceCmdLocked(u8 arg0, u16 arg1, s32 arg2, u8 arg3) {
    s32 h;
    s32 idx;
    u32 i;
    u32 end;

    h = arg2;
    for (i = 0; i < 8; i++) {
        if (D_main_bss_80149A00[i].unkEC1 == 0 && D_main_bss_80149A00[i].unk000 == (arg2 & 0x7FFFFFFF)) {
            arg2 = i | (arg2 & 0x80000000);
            goto found;
        }
    }
    arg2 = -1;
found:
    if (arg2 != -1) {
        if (arg2 >= 0) {
            idx = arg2;
            dispatchAudioCommand(arg0, arg1, D_main_bss_80149A00[idx].unkEC4, arg3, h);
            {
                s32 o = idx * sizeof(D_main_bss_80149A00[0]);
                i = (u32)D_main_bss_80149A00 + o + 0x528;
                end = i + 0x40;
                do {
                    if (*(u8 *)i != *(u8 *)((u8 *)D_main_bss_80149A00 + o + 0xEC4)) {
                        dispatchAudioCommand(arg0, arg1, *(u8 *)i, 0, 0);
                    }
                    i++;
                } while (i < end);
            }
        } else {
            idx = arg2 & 0x7FFFFFFF;
            switch (arg3 & 0xF) {
            case 0:
                *(u8 *)&D_main_bss_80149A00[idx].unkEC8[6] = arg0;
                break;
            case 1:
                D_main_bss_80149A00[idx].unkEF0[0] = 0;
                break;
            case 2:
                *(u8 *)&D_main_bss_80149A00[idx].unkEC8[6] = arg0;
                D_main_bss_80149A00[idx].unkEEE |= 8;
                break;
            case 3:
                *(u8 *)&D_main_bss_80149A00[idx].unkEC8[6] = arg0;
                D_main_bss_80149A00[idx].unkEEE |= 0x80;
                break;
            }
        }
    }
}

void queueAudioVoiceCmdLocked(u8, u16, s32, u8);
void queueAudioVoiceCmd(u8 arg0, u16 arg1, s32 arg2, u8 arg3) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        queueAudioVoiceCmdLocked(arg0, arg1, arg2, arg3);
        factor5MutexRelease();
    }
}

u8 getSongStateByteByHandle(u32 handle) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            return D_main_bss_80149A00[slot].unkEC4;
        }
    }
    return 0;
}

void setAudioFaderState(u8, s32);
void setSongChannelParamByHandle(u32 handle, u8 ch, u8 val) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            D_main_bss_80149A00[slot].unk528[ch] = val;
            setAudioFaderState(val, 2);
        }
    }
}

typedef struct {
    u32 handle;
    u16 h4;
    u16 pad6;
    s32 h8;
    u16 hC;
    u16 padE;
    s32 x10;
    u16 h14;
    u16 h16;
    u8 b18;
    u8 pad19[3];
    s32 x1C;
    s32 x20;
    u16 h24;
    u8 flags;
    u8 pad27;
} PsReq;
typedef struct {
    s32 flags;
    s32 x1C;
    s32 x20;
    u16 h24;
    u16 h26;
    u8 b28;
    u8 pad29[7];
    u8 b30;
    u8 pad31[3];
} PsCfg;
s32 playSongByIdLockCtl(u16, u16, s32, PsCfg *, s32);
s32 playSongById(u16, u16, s32, PsCfg *);
void queueAudioVoiceCmdLocked(u8, u16, s32, u8);
s32 quiesceSongSlotCmd(s32);
s32 setSongParamPairCmd(s32, s32, s32);
s32 applySongU16ParamCmd(s32, s32);

static inline void psQueue(u8 a0, u16 a1, s32 a2, u8 a3) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        queueAudioVoiceCmdLocked(a0, a1, a2, a3);
        factor5MutexRelease();
    }
}
static inline void psQuiesce(s32 a0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        quiesceSongSlotCmd(a0);
        factor5MutexRelease();
    }
}
static inline void psPair(s32 a0, s32 a1, s32 a2) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        setSongParamPairCmd(a0, a1, a2);
        factor5MutexRelease();
    }
}
static inline void psU16(s32 a0, u16 a1) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        applySongU16ParamCmd(a0, a1);
        factor5MutexRelease();
    }
}

s32 psImpl(PsReq *req, s32 *out, u8 locked) __asm__("processSongByHandle");
s32 psImpl(PsReq *req, s32 *out, u8 locked) {
    s32 slot;
    s32 h;
    PsCfg cfg;

    slot = findSongSlotByHandle(req->handle);
    if (slot == -1) {
        return;
    }
    if (req->flags & 4) {
        { struct D_main_bss_80149A00_type *e = &D_main_bss_80149A00[slot]; *(PsReq *)e->unkEC8 = *req; }
        *(u8 *)&D_main_bss_80149A00[slot].unkEF0[1] = 1;
        D_main_bss_80149A00[slot].unkEF0[0] = (u32)out;
        D_main_bss_80149A00[slot].unkEEE &= ~4;
        *out = req->handle | 0x80000000;
        return;
    }
    if (locked) {
        if (req->flags & 1) {
            queueAudioVoiceCmdLocked(0, req->h4, req->handle, 2);
        } else if (req->flags & 0x40) {
            queueAudioVoiceCmdLocked(0, req->h4, req->handle, 3);
        } else {
            queueAudioVoiceCmdLocked(0, req->h4, req->handle, 1);
        }
    } else {
        if (req->flags & 1) {
            psQueue(0, req->h4, req->handle, 2);
        } else if (req->flags & 0x40) {
            psQueue(0, req->h4, req->handle, 3);
        } else {
            psQueue(0, req->h4, req->handle, 1);
        }
    }
    if (out == NULL) {
        return;
    }
    if (req->flags & 2) {
        s32 h2 = findSongSlotByHandle(req->h8);
        if (h2 != -1) {
        if (locked) {
            quiesceSongSlotCmd(req->h8);
            queueAudioVoiceCmdLocked(req->b18, req->hC, req->h8, 0);
            if (req->flags & 0x10) {
                setSongParamPairCmd(req->h8, req->x1C, req->x20);
            }
            if (req->flags & 0x20) {
                applySongU16ParamCmd(req->h8, req->h24);
            }
        } else {
            psQuiesce(req->h8);
            psQueue(req->b18, req->hC, req->h8, 0);
            if (req->flags & 0x10) {
                psPair(req->h8, req->x1C, req->x20);
            }
            if (req->flags & 0x20) {
                psU16(req->h8, req->h24);
            }
        }
        *out = req->h8;
        } else {
            *out = h2;
        }
        return;
    }
    cfg.flags = 4;
    if (req->flags & 8) {
        cfg.flags = 0x14;
    }
    if (req->flags & 0x20) {
        cfg.flags |= 2;
        cfg.h24 = req->h24;
    }
    if (req->flags & 0x10) {
        cfg.flags |= 1;
        cfg.x1C = req->x1C;
        cfg.x20 = req->x20;
    }
    cfg.h26 = req->hC;
    cfg.b28 = req->b18;
    cfg.b30 = 0;
    if (locked) {
        s32 h3 = playSongByIdLockCtl(req->h14, req->h16, req->x10, &cfg, 1);
        *out = h3;
        if (h3 != -1 && (req->flags & 0x80)) {
            setSongParamPairCmd(h3, 0, 0);
        }
    } else {
        h = playSongById(req->h14, req->h16, req->x10, &cfg);
        *out = h;
        if (h != -1 && (req->flags & 0x80)) {
            psPair(h, 0, 0);
        }
    }
}

s32 processSongByHandle(s32, s32, s32);

void playSongIfMusyXActive(s32 arg0, s32 arg1) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        processSongByHandle(arg0, arg1, 0);
        factor5MutexRelease();
    }
}

s32 isSongHandleFree(s32 *h) {
    s32 v = *h;
    if (v != -1) {
        return ((u32)v >> 31) ^ 1;
    }
    return 1;
}

extern s32 D_main_bss_80142038;
extern s32 D_main_bss_801440C0;
extern s32 D_main_bss_801499F4;
extern s8 D_main_bss_801499F8;
extern u8 D_main_bss_8014A8C0[];
extern u8 D_main_bss_8014A8C1[];
extern u8 D_main_bss_8014A8C4[];
extern u32 D_main_bss_801529C8;
extern u8 D_main_bss_801529CB;
extern s32 D_main_bss_801529CC;
extern s32 advanceSongRegion(u32, struct D_main_bss_80149A00_type *, s32);
extern s8 isAudioFaderRampActive(u8);
extern void setTrackVoiceTickBudget(u32, u8, struct D_main_bss_80149A00_type *);
extern s32 stepActiveSongTracks();
extern void stepSongModulationLanes();
extern void stepSongPitchBendLanes();
extern s32 validateVoiceHandle(s32);

void tickAllActiveSongs(void)
{
  s32 temp_a2_2;
  s32 temp_s3;
  s32 temp_s6;
  s32 temp_s7;
  s32 temp_v1_3;
  s32 var_a2;
  s32 var_s2;
  struct D_main_bss_80149A00_type *temp_a3;
  struct D_main_bss_80149A00_type *var_a1;
  struct D_main_bss_801511C0_type *temp_s1;
  struct D_main_bss_801511C0_type *var_s0;
  struct SNG_unk0C_type *temp_a1;
  struct SNG_unk0C_type *temp_v1;
  u32 temp_a0;
  u32 temp_a0_2;
  u32 temp_lo;
  u32 temp_v0;
  register u32 temp_v1_2 asm("$3");
  u32 var_s5;
  u8 *var_s4;
  struct D_main_bss_80149A00_type *p;
  if (D_main_bss_80142038 != 0)
  {
    var_s5 = 0;
    D_main_bss_801499F4 = 0;
    D_main_bss_801499FC = 0;
    D_main_bss_801529CC = 0;
    do
    {
      var_s2 = var_s5 * 0xEF8;
      if (D_main_bss_8014A8C0[var_s2] != 0)
      {
        D_main_bss_801529C0 = (struct D_main_bss_80149A00_type *) (((u8 *) D_main_bss_80149A00) + var_s2);
        D_main_bss_801529C8 = var_s5;
        D_main_bss_801499F8 = isAudioFaderRampActive(*(D_main_bss_8014A8C4 + var_s2));
        p = D_main_bss_801529C0;
        if (p->unkE6C->unk0 != (-1U))
        {
          u32 end = -1;
          do
          {
            temp_a1 = p->unkE6C;
            if (((u32) (p->unkE74 + p->unk110[4])) >= ((u32) temp_a1->unk0))
            {
              temp_a0 = temp_a1->unk4;
              p->unk110[5] = (s32) temp_a0;
              setTrackVoiceTickBudget(temp_a0, D_main_bss_801529CB, p);
              temp_v1 = D_main_bss_801529C0->unkE6C;
              D_main_bss_801529C0->unkE6C = temp_v1 + 1;
              p = D_main_bss_801529C0;
            }
            else
            {
              break;
            }
          }
          while (temp_v1[1].unk0 != end);
        }
        {
            register s32 rt asm("$4") = ((s32) (D_main_bss_80142038 << 0x10)) / ((s32) D_main_bss_801440C0);
            temp_lo = ((u32) (D_main_bss_801529C0->unk110[5] * 0x600)) / 240;
            temp_v1_2 = temp_lo * rt;
        }
        temp_lo = temp_v1_2 * D_main_bss_801529C0->unkEC2;
        temp_v1_2 = (temp_lo >> 8) & 0xFFFF;
        *((volatile s32 *) (&D_main_bss_801529C0->unk110[2])) = temp_v1_2;
        temp_v1_2 = (*(volatile u32 *)&D_main_bss_801529C0->unkE70);
        temp_v1_2 += (*((volatile s32 *) (&D_main_bss_801529C0->unk110[2])));
        temp_lo = temp_lo >> 0x18;
        *((volatile s32 *) (&D_main_bss_801529C0->unk110[3])) = (s32) temp_lo;
        temp_a2_2 = *((volatile s32 *) (&D_main_bss_801529C0->unk110[3]));
        *((volatile s32 *) (&D_main_bss_801529C0->unk110[4])) = ((s32) temp_lo) >> 1;
        temp_a0_2 = temp_v1_2 & 0xFFFF;
        D_main_bss_801529C0->unkE70 = temp_a0_2;
        D_main_bss_801529C0->unkE74 += (temp_v1_2 >> 0x10) + temp_a2_2;
        temp_s7 = advanceSongRegion(temp_a0_2, D_main_bss_801529C0, temp_a2_2);
        temp_s6 = stepActiveSongTracks();
        stepSongPitchBendLanes();
        stepSongModulationLanes();
        for (var_a2 = 0; var_a2 < 0x40; var_a2++)
        {
          temp_v1_3 = D_main_bss_801529C0->unk568[var_a2].unk00 + D_main_bss_801529C0->unk110[2];
          D_main_bss_801529C0->unk568[var_a2].unk00 = temp_v1_3 & 0xFFFF;
          D_main_bss_801529C0->unk568[var_a2].unk04 += (temp_v1_3 >> 0x10) + D_main_bss_801529C0->unk110[3];
        }

        temp_s3 = tickScheduledSongEvents();
        var_s0 = D_main_bss_801529C0->unkE78[1];
        if (var_s0 != 0)
        {
          do
          {
            temp_s1 = var_s0->unk00;
            D_main_bss_801529CC += 1;
            if (validateVoiceHandle(var_s0->unk08) == (-1))
            {
              if (var_s0->unk00 != 0)
              {
                var_s0->unk00->unk04 = var_s0->unk04;
              }
              if (var_s0->unk04 != 0)
              {
                var_s0->unk04->unk00 = var_s0->unk00;
              }
              else
              {
                D_main_bss_801529C0->unkE78[1] = var_s0->unk00;
              }
              var_s0->unk00 = D_main_bss_801529C4;
              if (D_main_bss_801529C4 != 0)
              {
                D_main_bss_801529C4->unk04 = var_s0;
              }
              var_s0->unk04 = 0;
              D_main_bss_801529C4 = var_s0;
            }
            var_s0 = temp_s1;
          }
          while (var_s0 != 0);
        }
        if (((!(temp_s7 & 0xFF)) & (!(temp_s6 & 0xFF))) && (!(temp_s3 & 0xFF)))
        {
          D_main_bss_8014A8C0[var_s2] = 0;
          *(D_main_bss_8014A8C1 + var_s2) = 1;
        }
      }
      var_s5 += 1;
    }
    while (var_s5 < 8U);
  }
}

void initSongSequencerPools(void) {
    struct D_main_bss_801511C0_type *var_v1_2;
    u32 var_a0;
    s32 var_a1;

    for (var_a0 = 0; var_a0 < 8; var_a0++) {
        D_main_bss_80149A00[var_a0].unkEC0 = 0;
        D_main_bss_80149A00[var_a0].unkEC1 = 1; 
    }
    var_v1_2 = NULL;
    D_main_bss_801529C4 = &D_main_bss_801511C0;
    for (var_a1 = 0; var_a1 < 0x100; var_a1++) {
        D_main_bss_801511C0[var_a1].unk04 = var_v1_2;
        if (var_v1_2 != NULL) {
            var_v1_2->unk00 = &D_main_bss_801511C0[var_a1];
        }
        var_v1_2 = &D_main_bss_801511C0[var_a1];
    }
    var_v1_2->unk00 = NULL;
    D_main_bss_801499F0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", fake_func_8009711C);
