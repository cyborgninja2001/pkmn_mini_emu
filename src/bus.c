#include "bus.h"

void bus_init(Bus* bus, Cartridge cartridge) {
    bus->cartridge = &cartridge;
}

uint8_t bus_read(Bus bus, uint32_t address) {
    // for now it only reads form cartridge
    if (address >= 0x002100 && address <= 0x1FFFFF) {
        return cartridge_read(*bus.cartridge, address);
    } else {
        printf("*ERROR bus_read(0x%06X)*\n", address);
        exit(-1);
    }
}