#include "common.h"
#include "common_types.h"

extern s32 D_main_bss_801126E0;
extern u8 *D_main_bss_801126E4;
typedef struct { u8 b[0x68]; } ImpPfs;
typedef struct { u16 type; u8 status; u8 errno; } ImpCont;
extern ImpPfs impPfs[] __asm__("D_main_bss_80112730");
extern ImpCont *impCont __asm__("D_main_bss_801126E8");
extern s32 (*impCb)(s32) __asm__("D_main_bss_801126F0");
s32 osPfsInitPak(s32, void *, s32);
s32 osPfsRepairId(void *);
s32 osContStartQuery(s32);
s32 osRecvMesg(s32, void *, s32);
void osContGetQuery(void *);

s32 initMemoryPack(u32 chan) {
    s32 err;
    s32 cont;

retry:
    err = 0;
    if ((*D_main_bss_801126E4 >> chan) & 1) {
        if ((impCont[chan].type & 5) == 5) {
            switch (osPfsInitPak(D_main_bss_801126E0, &impPfs[chan], chan)) {
            case 1:
                osContStartQuery(D_main_bss_801126E0);
                osRecvMesg(D_main_bss_801126E0, NULL, 1);
                osContGetQuery(impCont);
                if (impCont[chan].errno == 8) {
                    goto nopak;
                }
                err = 1;
                break;
            case 2:
                err = 7;
                break;
            case 4:
                err = 9;
                break;
            case 10:
                cont = 0;
                if (impCb != NULL) {
                    cont = impCb(8);
                }
                if (cont == 1) {
                    goto retry;
                }
                if (cont < 2) {
                    if (cont == 0) {
                        goto ret0;
                    }
                } else if (cont == 2) {
                    osPfsRepairId(&impPfs[chan]);
                    goto retry;
                }
                break;
            case 0:
            ret0:
                return 0;
            case 11:
                if (impCb != NULL) {
                    impCb(0xD);
                }
                return 0xD;
            }
            cont = 0;
            if (impCb != NULL) {
                cont = impCb(err);
            }
            if (cont == 0) {
                return err;
            }
            if (cont < 0) {
                goto reterr;
            }
            if (cont >= 3) {
                goto reterr;
            }
            goto retry;
        }
        if (impCb != NULL) {
            impCb(0xC);
        }
        return 0xC;
    }
nopak:
    if (impCb != NULL) {
        impCb(0xB);
    }
    return 0xB;
reterr:
    return err;
}

extern s32 gSaveDataBuffer;
extern s32 D_main_bss_801126E0;
extern u32 D_main_bss_801126C8;
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);
typedef struct { u32 unk0; u32 unk4; } SaveHdrW;
extern struct {
    u32 gameCode;
    u8 pad4[8];
    u16 companyCode;
    u8 padE[2];
    u8 name[0x10];
} gGamesaveAssetW __asm__("gGamesaveAsset");
typedef struct { u8 b[0x68]; } PfsW;
extern PfsW D_main_bss_80112730[];
typedef struct { u16 type; u8 status; u8 errno; } ContStatW;
extern ContStatW *D_main_bss_801126E8;
extern s32 (*gSaveCbW)(s32) __asm__("D_main_bss_801126F0");
s32 initMemoryPack(u32);
s32 osPfsAllocateFile(void *, u16, u32, u8 *, u8 *, s32, s32 *);
s32 osPfsDeleteFile(void *, u16, u32, u8 *, u8 *);
s32 osPfsReadWriteFile(void *, s32, u8, s32, s32, u8 *);
s32 osContStartQuery(s32);
s32 osRecvMesg(s32, void *, s32);
void osContGetQuery(void *);

s32 writeSaveBodyToEeprom(u32 chan, s32 arg1, u8 *hdr, u8 *body, s32 size) {
    u8 ext[8];
    s32 fileNo;
    s32 err;
    s32 r;
    s32 blk;
    s32 cont;
    u8 *buf;
    u8 *b8;
    u8 *b18;

retry:
    r = initMemoryPack(chan);
    if (r != 0) {
        goto out;
    }
    rs_memset(ext, 0, 4);
    if (arg1 != 0) {
        ext[0] = arg1 + 0x11;
    } else {
        ext[0] = 0;
    }
    blk = (size + 0x117) & ~0xFF;
alloc:
    switch (osPfsAllocateFile(&D_main_bss_80112730[chan], gGamesaveAssetW.companyCode, gGamesaveAssetW.gameCode, gGamesaveAssetW.name, ext, blk, &fileNo)) {
    case 0:
        err = 0;
        break;
    case 1:
        osContStartQuery(D_main_bss_801126E0);
        osRecvMesg(D_main_bss_801126E0, NULL, 1);
        osContGetQuery(D_main_bss_801126E8);
        if (D_main_bss_801126E8[chan].errno != 8) {
            err = 1;
            break;
        }
        if (gSaveCbW != NULL) {
            gSaveCbW(0xB);
        }
        return 0xB;
    case 2:
        err = 7;
        break;
    case 3:
    case 4:
    case 5:
        err = 9;
        break;
    case 7:
    case 8:
        err = 2;
        break;
    case 9:
        err = 6;
        break;
    }
    if (err != 0) {
        cont = 0;
        if (gSaveCbW != NULL) {
            cont = gSaveCbW(err);
        }
        switch (err) {
        case 1:
        case 9:
            if (cont != 0) {
                goto alloc;
            }
            goto ret_err;
        case 6:
            if (cont == 0) {
                break;
            }
            if (osPfsDeleteFile(&D_main_bss_80112730[chan], gGamesaveAssetW.companyCode, gGamesaveAssetW.gameCode, gGamesaveAssetW.name, ext) == 0) {
                goto alloc;
            }
            err = 5;
            if (gSaveCbW == NULL) {
                break;
            }
            gSaveCbW(err);
            goto ret_err;
        case 7:
            goto check;
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
            goto ret_err;
        }
        goto ret_err;
    }
    buf = (u8 *)gSaveDataBuffer;
    rs_memset(buf, 0, blk);
    b18 = buf + 0x18;
    memcpy(b18, body, size);
    b8 = buf + 8;
    memcpy(b8, hdr, 0x10);
    ((SaveHdrW *)buf)->unk4 = adler32(adler32(0, 0, 0), b8, 0x10);
    ((SaveHdrW *)buf)->unk0 = adler32(adler32(0, 0, 0), b18, D_main_bss_801126C8);
    if (osPfsReadWriteFile(&D_main_bss_80112730[chan], fileNo, 1, 0, blk, (u8 *)gSaveDataBuffer) != 0) {
        err = 5;
        if (gSaveCbW != NULL) {
            cont = gSaveCbW(err);
        } else {
            cont = 0;
        }
    check:
        if (cont != 0) {
            goto retry;
        }
    ret_err:
        return err;
    }
out:
    return r;
}

s32 wsFind(void *, u16, u32, u8 *, u8 *, s32 *) __asm__("osPfsFindFile");

s32 writeSaveDataBodyToEeprom(u32 chan, s32 arg1, u8 *dst, s32 size) {
    u8 ext[8];
    s32 fileNo;
    s32 err;
    s32 r;
    s32 blk;
    s32 cont;
    u8 *buf;
    u8 *b18;

retry:
    r = initMemoryPack(chan);
    if (r != 0) {
        goto out;
    }
    rs_memset(ext, 0, 4);
    if (arg1 != 0) {
        ext[0] = arg1 + 0x11;
    } else {
        ext[0] = 0;
    }
    blk = (size + 0x117) & ~0xFF;
    switch (wsFind(&D_main_bss_80112730[chan], gGamesaveAssetW.companyCode, gGamesaveAssetW.gameCode, gGamesaveAssetW.name, ext, &fileNo)) {
    case 0:
        err = 0;
        break;
    case 1:
        err = 1;
        osContStartQuery(D_main_bss_801126E0);
        osRecvMesg(D_main_bss_801126E0, NULL, 1);
        osContGetQuery(D_main_bss_801126E8);
        if (D_main_bss_801126E8[chan].errno == 8) {
            err = 0xB;
        }
        break;
    case 2:
        err = 7;
        break;
    case 3:
    case 4:
        err = 9;
        break;
    case 5:
        err = 3;
        break;
    }
    if (err != 0) {
        return err;
    }
    if (osPfsReadWriteFile(&D_main_bss_80112730[chan], fileNo, 0, 0, blk, (u8 *)gSaveDataBuffer) != 0) {
        err = 4;
        if (gSaveCbW != NULL) {
            cont = gSaveCbW(err);
        } else {
            cont = 0;
        }
        if (cont != 0) {
            goto retry;
        }
        return err;
    }
    buf = (u8 *)gSaveDataBuffer;
    if (((SaveHdrW *)buf)->unk4 != adler32(adler32(0, 0, 0), buf + 8, 0x10)) {
        return 4;
    }
    b18 = buf + 0x18;
    if (((SaveHdrW *)buf)->unk0 != adler32(adler32(0, 0, 0), b18, D_main_bss_801126C8)) {
        return 4;
    }
    memcpy(dst, b18, size);
out:
    return r;
}

typedef struct {
    u32 gameCode;
    u8 pad4[8];
    u16 companyCode;
    u16 count;
    u8 name[0x10];
} CsAsset;
extern CsAsset gCsAsset __asm__("gGamesaveAsset");
s32 csFind(void *, u16, u32, u8 *, u8 *, s32 *) __asm__("osPfsFindFile");

void copySaveUnk08(s32 arg0, u8 *arg1) {
    u8 ext[8];
    s32 fileNo;
    s32 i;
    PfsW *pfs;
    SaveHdrW *hdr;
    u8 *p8;
    u8 *dst;

    i = 0;
    if (gCsAsset.count != 0) {
    pfs = &D_main_bss_80112730[arg0];
    do {
        dst = arg1 + i * 0x10;
        if (initMemoryPack(arg0) == 0) {
            rs_memset(ext, 0, 4);
            if (i != 0) {
                ext[0] = i + 0x11;
            } else {
                ext[0] = 0;
            }
            if (csFind(pfs, gCsAsset.companyCode, gCsAsset.gameCode, gCsAsset.name, ext, &fileNo) == 0 && osPfsReadWriteFile(pfs, fileNo, 0, 0, 0x20, (u8 *)gSaveDataBuffer) == 0) {
                hdr = (SaveHdrW *)gSaveDataBuffer;
                p8 = (u8 *)hdr + 8;
                if (hdr->unk4 == adler32(adler32(0, 0, 0), p8, 0x10)) {
                    memcpy(dst, p8, 0x10);
                } else {
                    rs_memset(dst, 0, 0x10);
                }
            } else {
                rs_memset(dst, 0, 0x10);
            }
        }
        i++;
    } while (i < gCsAsset.count);
    }
}

typedef struct {
    u8 pad0[4];
    u32 size;
    s32 bodySize;
    u16 padC;
    u16 count;
} SaveAssetView;
extern SaveAssetView gSaveAssetView __asm__("gGamesaveAsset");
extern s32 gSaveDataBodySize;
extern s32 gSaveDataBuffer;
extern s32 D_main_bss_801126E0;
extern s32 D_main_bss_801126E4_l __asm__("D_main_bss_801126E4");
extern s32 D_main_bss_801126E8_l __asm__("D_main_bss_801126E8");
extern s32 D_main_bss_801126F0;
extern s32 gSaveCbAlias __asm__("D_main_bss_801126F0");
extern s32 D_main_bss_80112720;
extern s32 D_main_bss_801126C4;
extern u8 D_main_bss_801126EC;
extern u8 D_main_bss_801126ED;
extern u8 D_main_bss_8011272C;
extern u8 D_main_bss_80112700[];
extern u8 gSIEventMesgQueue[];
extern u8 gControllerBits[];
extern u8 gControllerStatuses[];
void waitForSerialIdle(void);
void releaseSerialLock(void);
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);
s32 rs_malloc(u32, s32);
s32 rs_free(s32);
s32 osEepromProbe(s32);
s32 osEepromLongRead(s32, s32, u8 *, s32);
s32 osEepromLongWrite(s32, s32, u8 *, s32);
s32 bcmp(u32 *, u8 *, s32);

s32 initSaveData(u8 *arg0, s32 arg1) {
    u32 sum[8];
    u8 *buf;
    s32 r;
    s32 e;
    s32 i;
    u8 *rec;
    s32 off;

    D_main_bss_801126F0 = arg1;
    memcpy((u8 *)&gSaveAssetView, arg0, 0x20);
    D_main_bss_8011272C = 1;
    D_main_bss_801126E0 = (s32)gSIEventMesgQueue;
    D_main_bss_801126E4_l = (s32)gControllerBits;
    D_main_bss_801126E8_l = (s32)gControllerStatuses;
    gSaveDataBodySize = gSaveAssetView.bodySize + 0x18;
    gSaveDataBuffer = rs_malloc(gSaveAssetView.bodySize + 0x118, 0x81);
    D_main_bss_80112720 = gSaveAssetView.size ? 1 : 2;
    waitForSerialIdle();
    D_main_bss_801126EC = osEepromProbe(D_main_bss_801126E0) != 0;
    releaseSerialLock();
    if (gSaveAssetView.size != 0) {
        if (D_main_bss_801126EC == 0) {
            if (D_main_bss_801126F0 != 0) {
                ((void (*)(s32))D_main_bss_801126F0)(8);
            }
            return 0;
        }
        if (D_main_bss_801126EC == 1) {
            sum[1] = 0xF5F5F5F5;
            sum[5] = 0x47414D45;
            sum[2] = 0x47535953;
            sum[3] = 0xAAAAAAAA;
            sum[7] = 0x55555555;
            sum[6] = (*(u16 *)((u8 *)&gSaveAssetView + 0xA) << 16) | gSaveAssetView.count;
            sum[0] = adler32(adler32(0, 0, 0), (u8 *)&sum[1], 0xC);
            sum[4] = adler32(adler32(0, 0, 0), (u8 *)&sum[5], 0xC);
loop_10:
            waitForSerialIdle();
            e = osEepromLongRead(D_main_bss_801126E0, 0, D_main_bss_80112700, 0x20);
            releaseSerialLock();
            if (e != 0) {
                r = 0;
                if (D_main_bss_801126F0 != 0) {
                    r = ((s32 (*)(s32))D_main_bss_801126F0)(9);
                }
                if (r == 1) {
                    goto loop_10;
                }
                D_main_bss_801126EC = 0;
                D_main_bss_80112720 = 2;
                return 0;
            }
            if (bcmp(sum, D_main_bss_80112700, 0x20) != 0) {
                r = 0;
                if (D_main_bss_801126F0 != 0) {
                    r = ((s32 (*)(s32))D_main_bss_801126F0)(8);
                }
                if (r == 1) {
                    goto loop_10;
                }
                if (r == 2) {
                if (gSaveAssetView.size < gSaveAssetView.count * gSaveDataBodySize + 0x20) {
                    if (gSaveCbAlias != 0) {
                        ((void (*)(s32))gSaveCbAlias)(2);
                    }
                    return 0;
                }
                buf = (u8 *)rs_malloc(gSaveAssetView.size, 8);
                rs_memset(buf, 0, gSaveAssetView.size);
                i = 0;
                if (gSaveAssetView.count != 0) {
                    do {
                        off = i * (gSaveAssetView.bodySize + 0x18) + 0x20;
                        rec = buf + off;
                        *(u32 *)(rec + 4) = adler32(adler32(0, 0, 0), rec + 8, 0x10);
                        *(u32 *)rec = adler32(adler32(0, 0, 0), rec + 0x18, gSaveAssetView.bodySize);
                        i++;
                    } while (i < gSaveAssetView.count);
                }
loop_28:
                waitForSerialIdle();
                if (osEepromLongWrite(D_main_bss_801126E0, 0, buf, D_main_bss_801126C4) != 0) {
                    releaseSerialLock();
                    if (D_main_bss_801126F0 != 0) {
                        r = ((s32 (*)(s32))D_main_bss_801126F0)(9);
                    } else {
                        r = 0;
                    }
                    if (r != 1) {
                        D_main_bss_801126EC = 0;
                        D_main_bss_80112720 = 2;
                        rs_free((s32)buf);
                        return 0;
                    }
                    goto loop_28;
                }
                e = osEepromLongWrite(D_main_bss_801126E0, 0, (u8 *)sum, 0x20);
                releaseSerialLock();
                if (e != 0) {
                    r = 0;
                    if (D_main_bss_801126F0 != 0) {
                        r = ((s32 (*)(s32))D_main_bss_801126F0)(9);
                    }
                    if (r != 1) {
                        D_main_bss_801126EC = 0;
                        D_main_bss_80112720 = 2;
                        rs_free((s32)buf);
                        return 0;
                    }
                    goto loop_28;
                }
                rs_free((s32)buf);
                goto loop_10;
                }
                return 0;
            }
        }
    }
    D_main_bss_801126ED = 0;
    return 1;
}

s32 rs_free(s32);
extern s32 gSaveDataBuffer;

s32 freeSaveDataBuffer(void) {
    rs_free(gSaveDataBuffer);
    return 1;
}

extern s32 D_main_bss_801126F0;

void setSaveDataCallback(s32 arg0) {
    D_main_bss_801126F0 = arg0;
}

extern s32 gSaveDataBodySize;
extern s32 D_main_bss_801126E0;
extern s32 D_main_bss_80112720;
void waitForSerialIdle(void);
void releaseSerialLock(void);
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);
extern u32 D_main_bss_801126C8;
typedef struct {
    u32 unk0;
    u32 unk4;
} SaveHdr;
s32 osEepromLongWrite(s32, s32, u8 *, s32);
s32 writeSaveBodyToEeprom(u32, s32, u8 *, u8 *, s32);
s32 saveLoadDispatcher(s32 arg0, u32 arg1, s32 arg2, u8 *arg3, u8 *arg4, s32 arg5) {
    s32 ret;
    u8 *buf;
    u8 *b8;
    u8 *b18;

    if (arg0 == 0) {
        arg0 = D_main_bss_80112720;
    }
    waitForSerialIdle();
    switch (arg0) {
    case 1:
        buf = (u8 *)gSaveDataBuffer;
        rs_memset(buf, 0, gSaveDataBodySize);
        b18 = buf + 0x18;
        memcpy(b18, arg4, arg5);
        b8 = buf + 8;
        memcpy(b8, arg3, 0x10);
        ((SaveHdr *)buf)->unk4 = adler32(adler32(0, 0, 0), b8, 0x10);
        ret = 0;
        ((SaveHdr *)buf)->unk0 = adler32(adler32(0, 0, 0), b18, D_main_bss_801126C8);
        osEepromLongWrite(D_main_bss_801126E0, ((u32)(arg2 * gSaveDataBodySize + 0x20) >> 3) & 0xFF, (u8 *)gSaveDataBuffer, gSaveDataBodySize);
        break;
    case 2:
        if (arg1 >= 4) {
            return 0xA;
        }
        ret = writeSaveBodyToEeprom(arg1, arg2, arg3, arg4, arg5);
        break;
    }
    releaseSerialLock();
    return ret;
}

s32 osEepromLongRead(s32, s32, u8 *, s32);
s32 writeSaveDataBodyToEeprom(u32, s32, u8 *, s32);

s32 loadOrSaveEepromRecord(s32 arg0, u32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    s32 ret;
    u8 *buf;
    u8 *b18;

    if (arg0 == 0) {
        arg0 = D_main_bss_80112720;
    }
    waitForSerialIdle();
    switch (arg0) {
    case 1:
        osEepromLongRead(D_main_bss_801126E0, ((u32)(arg2 * gSaveDataBodySize + 0x20) >> 3) & 0xFF, (u8 *)gSaveDataBuffer, gSaveDataBodySize);
        buf = (u8 *)gSaveDataBuffer;
        if (((SaveHdr *)buf)->unk4 == adler32(adler32(0, 0, 0), buf + 8, 0x10)) {
            b18 = buf + 0x18;
            if (((SaveHdr *)buf)->unk0 != adler32(adler32(0, 0, 0), b18, D_main_bss_801126C8)) {
                ret = 4;
            } else {
                memcpy(arg3, b18, arg4);
                ret = 0;
            }
        } else {
            ret = 4;
        }
        break;
    case 2:
        if (arg1 >= 4) {
            return 0xA;
        }
        ret = writeSaveDataBodyToEeprom(arg1, arg2, arg3, arg4);
        break;
    }
    releaseSerialLock();
    return ret;
}

extern struct {
    u8 pad[0xE];
    u16 count;
} gGamesaveAsset;
extern s32 gSaveDataBodySize;
extern s32 D_main_bss_801126E0;
extern s32 D_main_bss_80112720;
void waitForSerialIdle(void);
void releaseSerialLock(void);
s32 osEepromLongRead(s32, s32, u8 *, s32);
void copySaveUnk08(s32, u8 *);
void rs_memset(u8 *, s32, s32);
void memcpy(u8 *, u8 *, s32);
u32 adler32(u32, u8 *, u32);

void loadOrSaveAllEepromRecords(s32 arg0, s32 arg1, u8 *arg2) {
    s32 i;
    s32 addr;
    u8 *buf;

    if (arg0 == 0) {
        arg0 = D_main_bss_80112720;
    }
    waitForSerialIdle();
    switch (arg0) {
    case 1:
        i = 0;
        if (gGamesaveAsset.count != 0) {
            do {
                addr = ((u32)(i * gSaveDataBodySize + 0x20) >> 3) & 0xFF;
                osEepromLongRead(D_main_bss_801126E0, addr, (u8 *)gSaveDataBuffer, 0x18);
                buf = (u8 *)gSaveDataBuffer;
                if (*(u32 *)(buf + 4) != adler32(adler32(0, 0, 0), buf + 8, 0x10)) {
                    rs_memset(arg2, 0, 0x10);
                    arg2 += 0x10;
                } else {
                    memcpy(arg2, buf + 8, 0x10);
                    arg2 += 0x10;
                }
                i++;
            } while (i < gGamesaveAsset.count);
        }
        break;
    case 2:
        copySaveUnk08(arg1, arg2);
        break;
    }
    releaseSerialLock();
}

INCLUDE_ASM("asm/nonmatchings/main/06560", fake_func_80006BFC);
