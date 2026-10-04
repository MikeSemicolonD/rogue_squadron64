#include "common.h"
#include "common_types.h"

void *rs_malloc(s32, s32);

void allocateNpcMeshVertexBuffer(u8 *arg0, u8 *arg1)
{
  u8 *mesh;
  u8 *list;
  u8 *e;
  void **out;
  u32 vi;
  s32 j;
  u16 *ids;
  s32 k;
  u8 *p;
  mesh = *((u8 **) ((*((u8 **) (arg1 + 0x1C))) + 8));
  *((u8 **) (arg0 + 4)) = mesh;
  list = *((u8 **) ((*((u8 **) ((*((u8 **) (arg1 + 0x1C))) + 8))) + 0x20));
  out = rs_malloc(((*((s32 *) (mesh + 0x14))) + ((*((s32 *) (list + 0xC))) * 4)) * 4, 0);
  *((void ***) arg0) = out;
  vi = 0;
  if ((*((s32 *) (mesh + 0x14))) != 0)
  {
    do
    {
      k = *((s32 *) (list + 0xC));
      e = *((u8 **) (list + 8));
      if (k > 0)
      {
        do
        {
          if (((*((u32 *) e)) & 0x18) == 0x18)
          {
            j = 0;
            ids = (u16 *) (e + (((*((u32 *) (e + 4))) & 0xFC0000) >> 16));
            do
            {
              if ((*ids) == vi)
              {
                *out = (e + (((*((u32 *) (e + 4))) & 0x3F000) >> 10)) + (j * 4);
                out++;
              }
              j++;
              ids++;
            }
            while (j < 4);
          }
          k--;
          e += ((*((u32 *) (e + 4))) & 0x3F000000) >> 22;
        }
        while (k > 0);
      }
      *out = 0;
      out++;
      vi++;
    }
    while (vi < (*((u32 *) (mesh + 0x14))));
  }
  k = 3;
  p = arg0 + 0xB4;
  do
  {
    *((u16 *) (p + 0x28)) = 0;
    k--;
    p -= 0x3C;
  }
  while (k >= 0);
  *((u32 *) (mesh + 0xC)) |= 0x09010008;
}

INCLUDE_ASM("asm/nonmatchings/main/7B470", transformMeshVerticesForNpc);

INCLUDE_ASM("asm/nonmatchings/main/7B470", npcDeformingMeshUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7B470", npcShieldUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7B470", heavyAttachedAudioEmitterNpcHandler);

extern void *D_main_bss_8013A970;
static const char D_main_8003D624[12] = "shield_PAL\0000";
void loadShieldPalette(void) {
    D_main_bss_8013A970 = load_asset((char *)D_main_8003D624);
}

INCLUDE_ASM("asm/nonmatchings/main/7B470", fake_func_8007C298);
