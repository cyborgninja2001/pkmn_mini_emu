#ifndef RAM_H
#define RAM_H

#include "common.h"

#define RAM_SIZE 0x001000 // 4KB

typedef struct {
    uint8_t data[RAM_SIZE];
} Ram;

void ram_init(Ram *ram);
uint8_t ram_read(Ram ram, uint32_t address);
void ram_write(Ram *ram, uint32_t address, uint8_t value);

#endif