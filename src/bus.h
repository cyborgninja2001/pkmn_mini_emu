#ifndef BUS_H
#define BUS_H

#include "common.h"
#include "cartridge.h"
#include "pokemon_mini.h"

typedef struct {
    Cartridge *cartridge;
} Bus;

void bus_init(Bus* bus, Cartridge cartridge);
uint8_t bus_read(Bus bus, uint32_t address);

#endif