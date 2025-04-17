#ifndef BUS_H
#define BUS_H

#include "common.h"
#include "cartridge.h"
#include "pokemon_mini.h"
#include "ram.h"
#include "bios.h"

typedef struct {
    Cartridge *cartridge;
    Ram *ram;
    BIOS *bios;
} Bus;

void bus_init(Bus* bus, Cartridge *cartridge, Ram *ram, BIOS *bios);
uint8_t bus_read(Bus bus, uint32_t address);
void bus_write(Bus bus, uint32_t address, uint8_t value);

#endif