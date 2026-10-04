/* Overlay load symbols used by src/main/01720.c; kept outside roguesquadron.ld so splat regeneration doesn't drop them. */
mission_overlay_BASEROM_START = mission_overlay_ROM_START + 0xB0000000;
mission_overlay_ROM_SIZE = SIZEOF(.mission_overlay);
menu_overlay_BASEROM_START = menu_overlay_ROM_START + 0xB0000000;
menu_overlay_ROM_SIZE = SIZEOF(.menu_overlay);
cinematic_overlay_BASEROM_START = cinematic_overlay_ROM_START + 0xB0000000;
cinematic_overlay_ROM_SIZE = SIZEOF(.cinematic_overlay);
