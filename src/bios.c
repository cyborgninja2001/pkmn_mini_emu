#include "bios.h"

void init_bios(BIOS *bios, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        printf("*COULD NOT OPEN BIOS FILE: %s*\n", path);
        exit(-1);
    }

    size_t read = fread(bios->data, 1, sizeof(bios->data), f);

    if (read != sizeof(bios->data)) {
        fprintf(stderr, "*Error: BIOS incomplete!, were only read %zu bytes*\n", read);
        fclose(f);
        exit(-1);
    }

    printf("BIOS opened successfully!\n");
    fclose(f);
}

uint8_t bios_read(BIOS bios, uint16_t address) {
    return bios.data[address];
}