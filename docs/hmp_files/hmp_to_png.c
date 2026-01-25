#include <stdio.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>
#include <spng.h>

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

void export_grayscale8(uint8_t *pixels, uint16_t pixel_width, uint16_t pixel_height, char *png_file_name) {
    int ret;
    spng_ctx *ctx  = NULL;
    ctx  = spng_ctx_new(SPNG_CTX_ENCODER);

    FILE *png_file;
    png_file = fopen(png_file_name, "wb");
    ret = spng_set_png_file(ctx, png_file);
    if (ret != SPNG_OK) {
        printf("\tset_png_file: %d: %s\n", ret, spng_strerror(ret));
    }

    struct spng_ihdr ihdr = {0};
    ihdr.bit_depth = 8;
    ihdr.width     = pixel_width;
    ihdr.height    = pixel_height;
    ihdr.color_type = SPNG_COLOR_TYPE_GRAYSCALE;

    ret = spng_set_ihdr(ctx, &ihdr);
    if (ret != SPNG_OK) {
        printf("\tset_ihdr: %d: %s\n", ret, spng_strerror(ret));
    }

    size_t len = sizeof(uint8_t) * pixel_width * pixel_height;

    ret = spng_encode_image(ctx, pixels, len, SPNG_FMT_RAW, SPNG_ENCODE_FINALIZE);
    if (ret != SPNG_OK) {
        printf("\tencode_image: %d: %s\n", ret, spng_strerror(ret));
    }

    fclose(png_file);
    spng_ctx_free(ctx);
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

    fseek(hmp, 0x18, SEEK_SET);

    uint16_t tile_count  = fread_u16(hmp);
    fseek(hmp, 0x2, SEEK_CUR);
    uint32_t tile_offset = fread_u32(hmp);
    fseek(hmp, 0x4, SEEK_CUR);
    uint16_t tile_width  = fread_u16(hmp);
    uint16_t tile_height = fread_u16(hmp);

    uint16_t *tile_indices = malloc(sizeof(uint16_t) * tile_width * tile_height);
    for (int y = 0; y < tile_height; y++) {
        for (int x = 0; x < tile_width; x++) {
            tile_indices[(y*tile_width) + x] = fread_u16(hmp);
        }
    }

    #define TILES(i, y, x) tiles[(i)*25 + (y)*5 + (x)]
    int8_t *tiles;
    tiles = malloc(sizeof(int8_t) * tile_count * 25);
    fseek(hmp, tile_offset, SEEK_SET);
    for (int i = 0; i < tile_count; i++) {
        fseek(hmp, 5, SEEK_CUR);
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                TILES(i, y, x) = fread_s8(hmp);
            }
        }
    }

    uint16_t pixel_width  = (4 * tile_width)  + 1;
    uint16_t pixel_height = (4 * tile_height) + 1;
    uint8_t  *pixels = malloc(sizeof(uint8_t) * pixel_width * pixel_height);

    for (int ty = 0; ty < tile_height; ty++) {
        for (int tx = 0; tx < tile_width; tx++) {
            for (int py = 0; py < 5; py++) {
                for (int px = 0; px < 5; px++) {
                    // Got to learn some fun stuff about C integer promotion stuff here.
                    // Refer to https://stackoverflow.com/questions/46073295/implicit-type-promotion-rules
                    // I thought that adding 128 to the int8_t would cause overflows, but due to promotion rules that isn't the case.
                    // Specifically, int8_t is a "small" integer, which always gets promoted to a regular int in binary operations
                    // This means no overflow will occur :)
                    pixels[(ty*4*pixel_width) + (py*pixel_width) + (tx*4) + px] = TILES(tile_indices[(ty * tile_width) + tx], py, px) + 128;
                }
            }
        }
    }

    export_grayscale8(pixels, pixel_width, pixel_height, argv[2]);

    fclose(hmp);

    return 0;
}
