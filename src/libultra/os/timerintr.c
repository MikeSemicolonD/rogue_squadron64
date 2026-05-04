#include "common.h"

INCLUDE_ASM("asm/nonmatchings/libultra/os/timerintr", __osTimerServicesInit);

INCLUDE_ASM("asm/nonmatchings/libultra/os/timerintr", __osTimerInterrupt);

INCLUDE_ASM("asm/nonmatchings/libultra/os/timerintr", __osSetTimerIntr);

INCLUDE_ASM("asm/nonmatchings/libultra/os/timerintr", __osInsertTimer);
