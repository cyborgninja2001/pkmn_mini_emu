#ifndef BIOS_H
#define BIOS_H

#include "common.h"

typedef struct {
    uint8_t data[0x001000]; // 4KB
} BIOS;

void init_bios(BIOS *bios, const char *path);
uint8_t bios_read(BIOS *bios, uint16_t addr);

#endif