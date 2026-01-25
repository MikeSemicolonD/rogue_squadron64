#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <endian.h>

void parse_singlet_list(FILE *src, uint32_t offset, uint32_t count) {
    int16_t x;

    fseek(src, offset, SEEK_SET);

    for (int i = 0; i < count; i++) {
        fread(&x, sizeof(int16_t), 1, src);
        x = be16toh(x);

        printf("        %5d\n", x);
    }
}

void parse_triplet_list(FILE *src, uint32_t offset, uint32_t count) {
    int16_t x, y, z;

    fseek(src, offset, SEEK_SET);

    for (int i = 0; i < count; i++) {
        fread(&x, sizeof(int16_t), 1, src);
        fread(&y, sizeof(int16_t), 1, src);
        fread(&z, sizeof(int16_t), 1, src);
        x = be16toh(x);
        y = be16toh(y);
        z = be16toh(z);

        printf("        (%5d, %5d, %5d)\n", x, y, z);
    }
}


void parse_quadlet_list(FILE *src, uint32_t offset, uint32_t count) {
    int16_t w, x, y, z;

    fseek(src, offset, SEEK_SET);

    for (int i = 0; i < count; i++) {
        fread(&w, sizeof(int16_t), 1, src);
        fread(&x, sizeof(int16_t), 1, src);
        fread(&y, sizeof(int16_t), 1, src);
        fread(&z, sizeof(int16_t), 1, src);
        w = be16toh(w);
        x = be16toh(x);
        y = be16toh(y);
        z = be16toh(z);

        printf("        (%5d, %5d, %5d, %5d)\n", w, x, y, z);
    }
}

struct model_anim_type2 {
    /* 0x00 */ uint32_t entry_count;
    /* 0x04 */ uint32_t flags;
    /* 0x08 */ uint32_t singlet_offset;
    /* 0x0C */ uint32_t triplet_offset1; // flags 0x1
    /* 0x10 */ uint32_t triplet_offset2; // flags 0x2
    /* 0x14 */ uint32_t quadlet_offset;  // flags 0x4
    /* 0x18 */ uint32_t triplet_offset3; // flags 0x8
}; // size = 0x1C

void parse_type2(FILE *src, uint32_t type2_num, uint32_t offset) {
    struct model_anim_type2 type2;

    fseek(src, offset, SEEK_SET);
    fread(&type2, sizeof(struct model_anim_type2), 1, src);

    type2.entry_count     = be32toh(type2.entry_count);
    type2.flags           = be32toh(type2.flags);
    type2.singlet_offset  = be32toh(type2.singlet_offset);
    type2.triplet_offset1 = be32toh(type2.triplet_offset1);
    type2.triplet_offset2 = be32toh(type2.triplet_offset2);
    type2.quadlet_offset  = be32toh(type2.quadlet_offset);
    type2.triplet_offset3 = be32toh(type2.triplet_offset3);

    printf("    Type 2 #%d\n", type2_num);
    printf("      Count: %#010x\n", type2.entry_count);
    printf("      Flags: %#010x\n", type2.flags);

    printf("      Singlet List\n");
    parse_singlet_list(src, type2.singlet_offset,  type2.entry_count);
    printf("      Triplet List #1\n");
    parse_triplet_list(src, type2.triplet_offset1, type2.flags & 1 ? type2.entry_count : 1);
    printf("      Triplet List #2\n");
    parse_triplet_list(src, type2.triplet_offset2, type2.flags & 2 ? type2.entry_count : 1);
    printf("      Quadlet List #1\n");
    parse_quadlet_list(src, type2.quadlet_offset,  type2.flags & 4 ? type2.entry_count : 1);
    printf("      Triplet List #3\n");
    parse_triplet_list(src, type2.triplet_offset3, type2.flags & 8 ? type2.entry_count : 1);
}

struct model_anim_type1 {
    /* 0x00 */ uint32_t type2_offset;
    /* 0x04 */ uint32_t unk04;
    /* 0x08 */ uint32_t unk08;
    /* 0x0C */ uint16_t unk0C;
    /* 0x0E */ uint16_t type2_count;
}; // size = 0x10

void parse_type1(FILE *src, uint32_t type1_num, uint32_t offset) {
    struct model_anim_type1 type1;
    uint32_t type2_offset;
    uint32_t unk04;
    uint32_t unk08;
    uint16_t unk0C;
    uint16_t type2_count;

    fseek(src, offset, SEEK_SET);
    fread(&type1, sizeof(struct model_anim_type1), 1, src);
    type1.type2_offset = be32toh(type1.type2_offset);
    type1.unk04        = be32toh(type1.unk04);
    type1.unk08        = be32toh(type1.unk08);
    type1.unk0C        = be16toh(type1.unk0C);
    type1.type2_count  = be16toh(type1.type2_count);

    printf("Type 1 #%d\n", type1_num);
    printf("  Offset:      %#010x\n", type1.type2_offset);
    printf("  unk04:       %#010x\n", type1.unk04);
    printf("  unk08:       %#010x\n", type1.unk08);
    printf("  unk0C:       %#06x\n",  type1.unk0C);
    printf("  type2_count: %#06x\n",  type1.type2_count);

    for (int i = 0; i < type1.type2_count; i++) {
        parse_type2(src, i, type1.type2_offset + (sizeof(struct model_anim_type2) * i));
    }
}

int main(int argc, char *argv[]) {
    FILE *src;

    src = fopen(argv[1], "rb");

    if (src == NULL) {
        printf("Failed to open %s\n", argv[1]);
        return 1;
    }

    uint32_t type1_count;
    uint32_t type1_offset;

    fread(&type1_count, sizeof(uint32_t), 1, src);
    fread(&type1_offset, sizeof(uint32_t), 1, src);
    type1_count  = be32toh(type1_count);
    type1_offset = be32toh(type1_offset);
    
    printf("%s\n",  argv[1]);
    printf("Type 1 Count: %d\n", type1_count);
    printf("Type 1 Offset: %#010x\n", type1_offset);
    for (int i = 0; i < type1_count; i++) {
        parse_type1(src, i, type1_offset + (0x10 * i));
    }

    fclose(src);

    return 0;
}
