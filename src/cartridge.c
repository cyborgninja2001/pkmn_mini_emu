#include "cartridge.h"

bool cartridge_load(Cartridge *cartridge, const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Could not open the file: %s\n", path);
        return false;
    }

    // get the rom size
    fseek(f, 0, SEEK_END);
    cartridge->rom_size = ftell(f);
    rewind(f);

    memset(cartridge->rom, 0xFF, CARTRIDGE_ROM_SIZE);
    size_t read = fread(cartridge->rom, 1, CARTRIDGE_ROM_SIZE, f);
    fclose(f);

    cartridge->loaded = read > 0;
    return cartridge->loaded;
}

uint8_t cartridge_read(Cartridge cartridge, uint32_t address) {
    if ((address < CARTRIDGE_ROM_START) || (address > CARTRIDGE_ROM_END)) {
        return 0xFF;
        printf("*ERROR: cartridge_read(%06X)*\n", address);
        exit(-1);
    } else {
        return cartridge.rom[address];
    }
}

void cartridge_write(Cartridge *cartridge, uint32_t address, uint8_t value) {
    cartridge->rom[address] = value;
}

void cartridge_print_data(Cartridge cartridge) {
    if (!cartridge.loaded) {
        printf("cartridge not loaded!\n");
        return;
    }

    // 0x2102 (6 bytes)
    printf("Reset location: ");
    for (int i = 0; i < 6; i++) {
        printf("%X", cartridge_read(cartridge, 0x2102 + i));
    }
    printf("\n");

    // 0x21A4 (8 bytes)
    printf("NINTENDO in plain text: ");
    for (int i = 0; i < 8; i++) {
        printf("%c", cartridge_read(cartridge, 0x21A4 + i));
    }
    printf("\n");

    // 0x21AC (4 bytes)
    printf("Game code: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", cartridge_read(cartridge, 0x21AC + i));
    }
    printf("\n");

    // 0x21B0 (12 bytes)
    char title[13];                     // 12 + 1 for the null terminator
    for (int i = 0; i < 12; i++) {
        title[i] = cartridge_read(cartridge, 0x21B0 + i);
    }
    title[12] = '\0';                  // null terminator
    printf("Game title: %s\n", title);

    printf("ROM size: %dKB\n", cartridge.rom_size / 1024);
}
