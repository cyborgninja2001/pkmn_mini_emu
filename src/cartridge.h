#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include "common.h"

#define CARTRIDGE_ROM_SIZE 0x1FDF00 // 2MB
#define CARTRIDGE_ROM_START 0x000000
#define CARTRIDGE_ROM_END 0x1FFFFF

typedef struct {
    uint8_t rom[CARTRIDGE_ROM_SIZE]; // 0x002100 - 0x1FFFFF
    uint32_t rom_size;
    bool loaded;
} Cartridge;

bool cartridge_load(Cartridge *cartridge, const char *path);
uint8_t cartridge_read(Cartridge cartridge, uint32_t address);
void cartridge_write(Cartridge *cartridge, uint32_t address, uint8_t value);
void cartridge_print_data(Cartridge cartridge);

#endif