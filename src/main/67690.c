#include "common.h"
#include "common_types.h"

#include "main/67690.h"

u16 voiceIdtoTextIdMap[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 
    0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F, 
    0x0000, 0x0010, 0x0011, 0x0012, 0x0013, 0x0000, 0x0014, 0x0015, 
    0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x0000, 0x001B, 0x001C, 
    0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 
    0x0025, 0x0026, 0x0000, 0x0000, 0x0000, 0x0027, 0x0000, 0x0028, 
    0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x0000, 0x0000, 0x002E, 
    0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0000, 0x0034, 0x0000, 
    0x0000, 0x0035, 0x0036, 0x0000, 0x0000, 0x0000, 0x0000, 0x0037, 
    0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x0000, 0x003E, 
    0x003F, 0x0040, 0x0000, 0x0041, 0x0000, 0x0042, 0x0043, 0x0044, 
    0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 
    0x0000, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0000, 0x0052, 
    0x0000, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 
    0x0000, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 0x0060, 
    0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 
    0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 
    0x0071, 0x0072, 0x0073, 0x0074, 0x0000, 0x0075, 0x0076, 0x0077, 
    0x0078, 0x0000, 0x0079, 0x007A, 0x007B, 0x0000, 0x007C, 0x0000, 
    0x0000, 0x007D, 0x0000, 0x007E, 0x0000, 0x0000, 0x0000, 0x007F, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0080, 0x0081, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0082, 0x0083, 0x0000, 0x0084, 0x0000, 0x0085, 
    0x0000, 0x0086, 0x0000, 0x0000, 0x0000, 0x0087, 0x0088, 0x0089, 
    0x0000, 0x0000, 0x008A, 0x008B, 0x008C, 0x0000, 0x0000, 0x008D, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x008E, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x008F, 0x0090, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0091, 0x0092, 0x0093, 0x0094, 0x0000, 0x0095, 0x0096, 
    0x0097, 0x0098, 0x0000, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 
    0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 
    0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 
    0x00AE, 0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x0000, 0x0000, 
    0x0000, 0x00B4, 0x00B5, 0x0000, 0x0000, 0x00B6, 0x00B7, 0x0000, 
    0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x0000, 0x0000, 0x00BD, 
    0x00BE, 0x00BF, 0x00C0, 0x00C1, 0x0000, 0x00C2, 0x00C3, 0x00C4, 
    0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 
    0x00CD, 0x0000, 0x00CE, 0x00CF, 0x0000, 0x00D0, 0x00D1, 0x00D2, 
    0x0000, 0x0000, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 
    0x00D9, 0x0000, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF, 
    0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 
    0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 
    0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 
    0x00F8, 0x00F9, 0x0000, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x0000, 
    0x00FE, 0x0000, 0x00FF, 0x0100, 0x0000, 0x0101, 0x0102, 0x0000, 
    0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 
    0x010B, 0x010C, 0x0000, 0x010D, 0x010E, 0x010F, 0x0000, 0x0110, 
    0x0000, 0x0111, 0x0112, 0x0113, 0x0114, 0x0115, 0x0116, 0x0117, 
    0x0118, 0x0119, 0x011A, 0x011B, 0x011C, 0x011D, 0x011E, 0x011F, 
    0x0120, 0x0121, 0x0122, 0x0000, 0x0123, 0x0124, 0x0125, 0x0126, 
    0x0127, 0x0128, 0x0129, 0x0000, 0x0000, 0x0000, 0x012A, 0x012B, 
    0x012C, 0x0000, 0x0000, 0x0000, 0x012D, 0x012E, 0x012F, 0x0130, 
    0x0131, 0x0132, 0x0133, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0134, 0x0135, 0x0136, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0137, 0x0138, 0x0139, 
    0x013A, 0x013B, 0x013C, 0x013D, 0x013E, 0x013F, 0x0000, 0x0140, 
    0x0000, 0x0000, 0x0141, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0142, 0x0143, 0x0144, 0x0145, 0x0146, 0x0147, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
    0x0148, 0x0149, 0x014A, 0x014B, 0x014C, 0x014D, 0x014E, 0x014F, 
    0x0150, 0x0151, 0x0152, 0x0000, 0x0153, 0x0154, 0x0155, 0x0000, 
    0x0000, 0x0156, 0x0000, 0x0157, 0x0158, 0x0000, 0x0159, 0x015A, 
    0x015B, 0x0000, 0x015C, 0x015D, 0x0000, 0x0000, 0x015E, 0x015F, 
    0x0160, 0x0000, 0x0000, 0x0161, 0x0000, 0x0162, 0x0163, 0x0164, 
    0x0165, 0x0000, 0x0000, 0x0000, 0x0166, 0x0167, 0x0168, 0x0169, 
    0x016A, 0x016B, 0x016C, 0x0000, 0x0000, 0x0000, 0x016D, 0x016E, 
    0x016F, 0x0170, 0x0000, 0x0000, 0x0171, 0x0000, 0x0172, 0x0173, 
    0x0174, 0x0175, 0x0176, 0x0177, 0x0178, 0x0000, 0x0000, 0x0179, 
    0x0000, 0x017A, 0x0000, 0x0000, 0x017B, 0x017C, 0x017D, 0x0000, 
    0x0000, 0x017E, 0x017F, 0x0000, 0x0180, 0x0181, 0x0182, 0x0000, 
    0x0183, 0x0184, 0x0185, 0x0000, 0x0186, 0x0000, 0x0187, 0x0000, 
    0x0188, 0x0000, 0x0000, 0x0189, 0x018A, 0x018B, 0x018C, 0x018D, 
    0x018E, 0x018F, 0x0190, 0x0191, 0x0192, 0x0193, 0x0194, 0x0195, 
    0x0196, 0x0000, 0x0197, 0x0198, 0x0199, 0x0000, 0x019A, 0x019B, 
    0x019C, 0x0000, 0x019D, 0x019E, 0x0000, 0x0000, 0x0000, 0x019F, 
    0x01A0, 0x01A1, 0x01A2, 0x01A3, 0x01A4, 0x01A5, 0x01A6, 0x01A7, 
    0x0000, 0x01A8, 0x01A9, 0x0000, 0x0000, 0x01AA, 0x0000, 0x0000, 
    0x01AB, 0x01AC, 0x01AD, 0x01AE, 0x01AF, 0x01B0, 0x01B1, 0x01B2, 
    0x01B3, 0x01B4, 0x01B5, 0x01B6, 0x01B7, 0x01B8, 0x01B9, 0x01BA, 
    0x01BB, 0x0000, 0x01BC, 0x0000, 0x01BD, 0x01BE, 0x01BF, 0x01C0, 
    0x01C1, 0x01C2, 0x01C3, 0x01C4, 0x01C5, 0x01C6, 0x01C7, 0x01C8, 
    0x01C9, 0x01CA, 0x01CB, 0x01CC, 0x01CD, 0x01CE, 0x01CF, 0x01D0, 
    0x01D1, 0x01D2, 0x01D3, 0x01D4, 0x0000, 0x01D5, 0x0000, 0x0000, 
    0x0000, 0x0000, 0x0000, 0x01D6, 0x0000, 0x0000, 0x01D7, 0x0000, 
    0x0000, 0x01D8, 0x0000, 0x01D9, 0x01DA, 0x0000, 0x01DB, 0x01DC, 
    0x0000, 0x01DD, 0x01DE, 0x01DF, 0x01E0, 0x01E1, 0x01E2, 0x0000, 
    0x01E3, 0x01E4, 0x01E5, 0x0000, 0x0000, 0x01E6, 0x01E7, 0x01E8, 
    0x01E9, 0x0000, 0x0000, 0x0000, 0x01EA, 0x01EB, 0x01EC, 0x0000, 
    0x01ED, 0x0000, 0x0000, 0x0000, 0x01EE, 0x01EF, 0x01F0, 0x01F1, 
    0x01F2, 0x01F3, 0x01F4, 0x01F5, 0x01F6, 0x01F7, 0x01F8, 0x01F9, 
    0x01FA, 0x01FB, 0x01FC, 0x01FD, 0x01FE, 0x01FF, 0x0200, 0x0201, 
    0x0202, 0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 
    0x020A, 0x020B, 0x020C, 0x020D, 0x020E, 0x020F, 0x0210, 0x0211, 
    0x0212, 0x0213, 0x0214, 0x0215, 0x0216, 0x0217, 0x0218, 0x0219, 
    0x021A, 0x021B, 0x021C, 0x021D, 0x0000, 0x021E, 0x021F, 0x0000, 
    0x0000, 0x0000, 0x0220, 0x0221,
};

char *D_main_800A05C8[] = {
    "speech",
};

// DO NOT DELETE ME I AM REQUIRED FOR MATCHING
u32 data_pad_67690 = 0x10400019;

INCLUDE_ASM("asm/nonmatchings/main/67690", initSpeechSubsystem);

extern s32 D_main_80139B80[];
extern u8 D_main_80139BA0[];
extern s16 D_main_bss_80139BA8;
extern f32 D_main_bss_80139C84;
s32 isVoiceHandleActive(s32);
void stopVoiceByHandle(s32);
s32 allocAndConfigureNewVoice(s16, s32, s32, s32, s32, s32, s32);

s32 enqueueSpeechClip(u32 arg0, u8 arg1)
{
  s32 *p;
  u8 idx;
  s32 v;
  if (arg0 < 0x2F4U)
  {
    D_main_bss_80139BA8 = (D_main_bss_80139BA8 + 1) % 8;
    idx = ((u8 *) (&D_main_bss_80139BA8))[1];
    ;
    if ((*(&D_main_80139B80[idx])) != (-1))
    {
 do { if ((u8) isVoiceHandleActive(*(&D_main_80139B80[idx]))) { stopVoiceByHandle(*(&D_main_80139B80[idx])); } } while (0);
      *(&D_main_80139B80[idx]) = -1;
    }
    v = allocAndConfigureNewVoice(voiceIdtoTextIdMap[arg0], 0, 0xFF, (u8) ((u32) (D_main_bss_80139C84 * arg1)), 0x40, 0, 0);
    if ((double) (v != (-1)))
    {
      D_main_80139B80[D_main_bss_80139BA8] = v;
      D_main_80139BA0[D_main_bss_80139BA8] = arg1;
      return (((u8 *) (&D_main_bss_80139BA8))[1] + 1) & 0xFF;
    }
  }
  return 0;
}

extern s32 D_main_80139B80[];
s32 isVoiceHandleActive(s32);
static inline u8 speechSlotActiveInline(u8 slot) {
    if (slot != 0) {
        s32 h = D_main_80139B80[slot - 1];
        if (h != -1) {
            return isVoiceHandleActive(h);
        }
    }
    return 0;
}
extern u8 D_main_80139BA0[];
extern f32 D_main_bss_80139C80;
extern f32 D_main_bss_80139C84;
extern f32 D_main_bss_80139C88;
void setVoiceMixByKey(s32, s32, s32, s32, s32);

void applySpeechVolumeScalar(f32 arg0) {
    u8 i;

    D_main_bss_80139C88 = arg0;
    D_main_bss_80139C84 = D_main_bss_80139C80 * arg0;
    for (i = 1; i < 9; i++) {
        if (speechSlotActiveInline(i) == 1) {
            u8 vol = (u32)(D_main_80139BA0[i - 1] * D_main_bss_80139C84);
            if (D_main_80139B80[i - 1] != -1) {
                setVoiceMixByKey(D_main_80139B80[i - 1], vol, 0x40, 0, 0);
            }
        }
    }
}

extern u8 subtitleSlotHead;
extern u8 subtitleSlotTail;
extern u8 subtitleSlotsAvailable;
extern u8 D_main_80139C73;
extern s32 D_main_bss_80139C78;
extern f32 D_main_bss_80139C7C;
void stopVoiceByHandle(s32);

typedef struct {
    f32 f0;
    u16 id;
    u16 flags;
    u8 prio;
    u8 pad9[3];
} SubtitleSlot;

extern SubtitleSlot subtitleSlots[];
extern s32 D_main_bss_80130B50;
extern s8 D_main_bss_80139C8C;
extern s8 D_main_bss_80139C8E;
extern u8 D_main_bss_80139C8F;

void playSpeechClip(s32 id, u8 prio, f32 vol, s32 flags)
{
  s32 *p;
  s32 slot;
  u8 i;
  s32 n;
  s32 t;
  unsigned short fl = flags;
  if ((((((id < 0x2F4) && ((*((u8 *) (&D_main_bss_80139C8E))) == 0)) && (((*((u8 *) (&D_main_bss_80139C8C))) == 0) || (flags & 0x40))) && ((subtitleSlotsAvailable == 0x10) || (!(flags & 8)))) && (!(D_main_bss_80130B50 & 8))) && (id != 0x28C))
  {
    if (flags & 0x10)
    {
      slot = D_main_80139C73;
      i = slot - 1;
      if (i < 8)
      {
        s32 *base = D_main_80139B80;
        p = base + ((u8) (slot - 1));
        if ((*p) != (-1))
        {
          if ((u8) isVoiceHandleActive(*p))
          {
            stopVoiceByHandle(*p);
          }
          *p = -1;
        }
      }
      subtitleSlotTail = 0;
      subtitleSlotHead = 0;
      subtitleSlotsAvailable = 0x10;
      D_main_80139C73 = 0;
      D_main_bss_80139C78 = 0;
      D_main_bss_80139C7C = 0.0f;
    }
    if (subtitleSlotsAvailable != 0)
    {
      if (subtitleSlotsAvailable == 0x10)
      {
        if (((vol < 0.5f) && (D_main_bss_80139C8F == 0)) && (fl & 6))
        {
          vol = 0.5f;
        }
        *((f32 *) (&D_main_bss_80139C78)) = vol;
      }
      subtitleSlots[subtitleSlotTail].id = id;
      (*(&subtitleSlots[subtitleSlotTail])).flags = fl;
      subtitleSlots[subtitleSlotTail].prio = prio;
      subtitleSlots[subtitleSlotTail].f0 = vol;
      n = subtitleSlotTail + 1;
      t = n;
      if (n < 0)
      {
        t = subtitleSlotTail + 0x10;
      }
      subtitleSlotTail = n - (t & 0x1F0);
      subtitleSlotsAvailable--;
    }
    if (fl & 0x20)
    {
      D_main_bss_80139C8C = 1;
    }
  }
}

void queueSpeechClipWithPriority(s32 id, u8 prio, f32 vol, s32 flags)
{
  s32 *p;
  s32 slot;
  u8 i;
  s32 n;
  s32 t;
  s32 k;
  unsigned short fl = flags;
  if ((((((*((u8 *) (&D_main_bss_80139C8E))) == 0) && (((*((u8 *) (&D_main_bss_80139C8C))) == 0) || (flags & 0x40))) && ((subtitleSlotsAvailable == 0x10) || (!(flags & 8)))) && (!(D_main_bss_80130B50 & 8))))
  {
    if (flags & 0x10)
    {
      slot = D_main_80139C73;
      i = slot - 1;
      if (i < 8)
      {
        s32 *base = D_main_80139B80;
        p = base + ((u8) (slot - 1));
        if ((*p) != (-1))
        {
          if ((u8) isVoiceHandleActive(*p))
          {
            stopVoiceByHandle(*p);
          }
          *p = -1;
        }
      }
      subtitleSlotTail = 0;
      subtitleSlotHead = 0;
      subtitleSlotsAvailable = 0x10;
      D_main_80139C73 = 0;
      D_main_bss_80139C78 = 0;
      D_main_bss_80139C7C = 0.0f;
    }
    if (subtitleSlotsAvailable != 0)
    {
      n = subtitleSlotHead + 0xF;
      t = n;
      if (n < 0)
      {
        t = subtitleSlotHead + 0x1E;
      }
      k = n - (t & 0x1F0);
      if (vol < 0.5f)
      {
        if (D_main_bss_80139C8F == 0)
        {
          if (fl & 6)
          {
            vol = 0.5f;
          }
        }
      }
      *((f32 *) (&D_main_bss_80139C78)) = vol;
      subtitleSlots[k].id = id;
      subtitleSlots[k].flags = fl;
      subtitleSlots[k].prio = prio;
      subtitleSlots[k].f0 = vol;
      subtitleSlotHead = k;
      subtitleSlotsAvailable--;
    }
    if (fl & 0x20)
    {
      D_main_bss_80139C8C = 1;
    }
  }
}

INCLUDE_ASM("asm/nonmatchings/main/67690", tickSpeechSubsystem);

extern s32 D_main_80139B80[];
s32 isVoiceHandleActive(s32);
extern u8 subtitleSlotHead;
extern u8 subtitleSlotTail;
extern u8 subtitleSlotsAvailable;
extern u8 D_main_80139C73;
extern s32 D_main_bss_80139C78;
extern f32 D_main_bss_80139C7C;
extern s8 D_main_bss_80139C8E;
void stopVoiceByHandle(s32);

void resetSpeechSubsystem(void) {
    s32 *p;
    s32 slot = D_main_80139C73;
    u8 i = slot - 1;

    if (i < 8) {
        s32 *base = D_main_80139B80;
        p = base + (u8)(slot - 1);
        if (*p != -1) {
            if ((u8)isVoiceHandleActive(*p)) {
                stopVoiceByHandle(*p);
            }
            *p = -1;
        }
    }
    subtitleSlotTail = 0;
    subtitleSlotHead = 0;
    subtitleSlotsAvailable = 0x10;
    D_main_80139C73 = 0;
    D_main_bss_80139C78 = 0;
    D_main_bss_80139C7C = 0.0f;
    D_main_bss_80139C8E = 1;
}

void shutdownMusyXVoices(void);
s32 rs_free(s32);
s32 teardownAssetDma(s32, s32);
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_80139B70;
extern s32 D_main_bss_80139B74;
s32 finalizeCurrentSpeechBuffer(void) {
    shutdownMusyXVoices();
    if (D_main_bss_80139B74 != 0) {
        rs_free(D_main_bss_80139B74);
    } else {
        teardownAssetDma(D_main_bss_80138920, D_main_bss_80139B70);
    }
    return 1;
}

extern u8 subtitleSlotHead;
extern u8 subtitleSlotTail;
extern u8 subtitleSlotsAvailable;
extern u8 D_main_80139C73;
extern s32 D_main_bss_80139C78;
extern f32 D_main_bss_80139C7C;
extern s8 D_main_bss_80139C8C;

void initSpeechPlaybackState(void)
{
  u8 t;
  u8 *p = &D_main_80139C73;
  t = *p;
  subtitleSlotTail = 0;
  subtitleSlotHead = 0;
  subtitleSlotsAvailable = 0x10;
  *p = 0;
  D_main_bss_80139C78 = 0;
  *((s32 *) (&D_main_bss_80139C7C)) = 0;
  D_main_bss_80139C8C = 1;
  *p = t;
  D_main_bss_80139C7C = 1.0f;
}

extern s8 D_main_bss_80139C8C;
extern s8 D_main_bss_80139C8E;

void clearSpeechActiveFlags(void) {
    D_main_bss_80139C8C = 0;
    D_main_bss_80139C8E = 0;
}

extern s8 D_main_bss_80139C8D;
extern f32 D_main_bss_80139C7C;

void beginSpeechTimingWindow(void) {
    D_main_bss_80139C8D = 1;
    D_main_bss_80139C7C = 1.0f;
}

extern s8 D_main_bss_80139C8D;

void endSpeechTimingWindow(void) {
    D_main_bss_80139C8D = 0;
}

extern s32 D_main_80139B80[];
s32 isVoiceHandleActive(s32);
extern u8 subtitleSlotHead;
extern u8 subtitleSlotTail;
extern u8 D_main_80139C73;
f32 getVoicePlaybackProgressByKey(s32, f32 *);
extern u16 D_main_bss_80139C74;
s32 getSpeechPlaybackElapsedTime(f32 *out) {
    f32 total;
    f32 progress;

    if (!speechSlotActiveInline(D_main_80139C73)) {
        return -1;
    }
    if (out != NULL) {
        progress = getVoicePlaybackProgressByKey(D_main_80139B80[D_main_80139C73 - 1], &total);
        *out = total - progress;
    }
    return D_main_bss_80139C74;
}

u8 isSpeechBusyOrQueued(void) {
    if (subtitleSlotTail == subtitleSlotHead && !speechSlotActiveInline(D_main_80139C73)) {
        return 1;
    }
    return 0;
}

extern f32 D_main_bss_80139C80;
extern f32 D_main_bss_80139C88;
void applySpeechVolumeScalar(f32);
void setSpeechVolume(u8 vol) {
    D_main_bss_80139C80 = vol / 127.0f;
    applySpeechVolumeScalar(D_main_bss_80139C88);
}

extern s32 D_main_80139B80[];
s32 isVoiceHandleActive(s32);
u8 isSpeechSlotActive(u8 slot) {
    if (slot != 0) {
        s32 h = D_main_80139B80[slot - 1];
        if (h != -1) {
            return isVoiceHandleActive(h);
        }
    }
    return 0;
}

void stopVoiceByHandle(s32);
void stopSpeechSlotIfActive(s32 slot) {
    s32 *p;
    u8 i = slot - 1;

    if (i < 8) {
        s32 *base = D_main_80139B80;
        p = base + (u8)(slot - 1);
        if (*p != -1) {
            if ((u8)isVoiceHandleActive(*p)) {
                stopVoiceByHandle(*p);
            }
            *p = -1;
        }
    }
}

extern s16 D_main_bss_80139BA8;
void stopAllSpeechSlots(void) {
    u8 i;
    s32 *p;

    for (i = 0; i < 8; i++) {
        p = &D_main_80139B80[i];
        if (*p != -1) {
            if ((u8)isVoiceHandleActive(*p)) {
                stopVoiceByHandle(*p);
            }
            *p = -1;
        }
    }
    D_main_bss_80139BA8 = 0;
}

extern u8 D_main_bss_80139BA9;
extern s16 D_main_bss_80139BA8;
void advanceSpeechRingAndStopHead(void) {
    u8 idx = D_main_bss_80139BA9;
    s32 *base = D_main_80139B80;
    s32 *p = &base[idx];

    if (*p != -1) {
        if ((u8)isVoiceHandleActive(*p)) {
            stopVoiceByHandle(*p);
        }
        *p = -1;
    }
    if (--D_main_bss_80139BA8 < 0) {
        D_main_bss_80139BA8 += 8;
    }
}

extern s32 D_8010CA20;
extern u8 subtitleSlotsAvailable;
void playSpeechClip(s32, u8, f32, s32);
void playSpeechClipGated(s32 arg0, u8 arg1, f32 arg2, u8 arg3) {
    if (D_8010CA20 == 0) {
        if (arg3 == 0 || subtitleSlotsAvailable == 0x10) {
            playSpeechClip(arg0, arg1, arg2, arg3 ? 8 : 0);
        }
    }
}

const u32 rodata_pad_67690[2] = { 0x25290080, 0x240A00FF };
