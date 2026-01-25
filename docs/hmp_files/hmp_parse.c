#include <stdio.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>

float fread_float(FILE *hmp) {
    uint32_t f;
    fread(&f, sizeof(uint32_t), 1, hmp);
    f = be32toh(f);
    return *(float*)&f;
}

uint16_t fread_u16(FILE *hmp) {
    uint16_t u16;
    fread(&u16, sizeof(uint16_t), 1, hmp);
    return be16toh(u16);
}

uint8_t fread_u8(FILE *hmp) {
    uint8_t u8;
    fread(&u8, sizeof(uint8_t), 1, hmp);
    return u8;
}

int8_t fread_s8(FILE *hmp) {
    int8_t s8;
    fread(&s8, sizeof(int8_t), 1, hmp);
    return s8;
}

uint32_t fread_u32(FILE *hmp) {
    uint32_t u32;
    fread(&u32, sizeof(uint32_t), 1, hmp);
    return be32toh(u32);
}

void print_rgba(uint32_t rgba) {
    printf("R: %#04x, G: %#04x, B: %#04x, A: %#04x\n",
        (rgba & 0xFF000000) >> 0x18,
        (rgba & 0x00FF0000) >> 0x10,
        (rgba & 0x0000FF00) >> 0x08,
        (rgba & 0x000000FF) >> 0x00
    );
}

void parse_global_light_object(FILE *hmp) {
    printf("\tGlobal Light Object\n");
    printf("\t\tRGB Intensities:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    printf("\t\tActive?: %d\n", fread_u8(hmp));
    printf("\t\tMode: %d\n", fread_u8(hmp));
    printf("\t\tIntensity Boost?: %d\n", fread_u8(hmp));
    printf("\t\tUnknown byte: %d\n", fread_u8(hmp));

    printf("\t\tLight Direction:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    printf("\t\tUnknown float: %f\n", fread_float(hmp));
}

void parse_light_object(FILE *hmp, int index) {
    printf("\tLight Object #%d\n", index);
    printf("\t\tRGB Intensities:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    printf("\t\tActive?: %d\n", fread_u8(hmp));
    printf("\t\tMode: %d\n", fread_u8(hmp));
    printf("\t\tIntensity Boost?: %d\n", fread_u8(hmp));
    printf("\t\tUnknown byte: %d\n", fread_u8(hmp));

    printf("\t\tLocation:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    printf("\t\tSize Scale: %f\n", fread_float(hmp));
}

void parse_tile(FILE *hmp, int index) {
    printf("\tTile #%d\n", index);
    printf("\t\tTexture Map ID: %d\n", fread_u16(hmp));
    printf("\t\tFlags: %#02x\n", fread_u8(hmp));
    printf("\t\tMinimum Height: %d\n", fread_s8(hmp));
    printf("\t\tMaximum Height: %d\n", fread_s8(hmp));

    for (int y = 0; y < 5; y++) {
        printf("\t\t");
        for (int x = 0; x < 5; x++) {
            printf("%3d ", fread_s8(hmp));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *hmp = fopen(argv[1], "rb");
    printf("%s\n", argv[1]);

    printf("Header:\n");

    printf("\tUnknown floats:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    printf("\tSize scales:");
    for (int i = 0; i < 3; i++) {
        printf(" %f", fread_float(hmp));
    }
    printf("\n");

    uint16_t tile_count = fread_u16(hmp);
    printf("\tTile Count: %d\n", tile_count);
    printf("\tTexture Count: %d\n", fread_u16(hmp));
    printf("\tTile Offset: %#010x\n", fread_u32(hmp));
    printf("\tLighting Offset: %#010x\n", fread_u32(hmp));
    uint16_t width = fread_u16(hmp);
    printf("\tWidth: %d\n", width);
    uint16_t height = fread_u16(hmp);
    printf("\tHeight: %d\n", height);
    printf("\n");

    printf("Tile Indices:\n");
    for (int y = 0; y < height; y++) {
        printf("\t");
        for (int x = 0; x < width; x++) {
            printf("%04d ", fread_u16(hmp));
        }
        printf("\n");
    }
    printf("\n");

    printf("Lighting Data:\n");
    uint32_t light_object_count = fread_u32(hmp);
    printf("\tLight Object Count: %d\n", light_object_count);
    printf("\tTerrain Shadow Color: "); print_rgba(fread_u32(hmp));
    printf("\tWorld Light Color: "); print_rgba(fread_u32(hmp));

    parse_global_light_object(hmp);

    for (int i = 1; i < light_object_count; i++) {
        parse_light_object(hmp, i);
    }
    printf("\n");

    printf("Tiles\n");
    for (int i = 0; i < tile_count; i++) {
        parse_tile(hmp, i);
    }

    printf("\n");
    fclose(hmp);

    return 0;
}
