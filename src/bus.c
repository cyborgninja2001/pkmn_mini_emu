#include "bus.h"

void bus_init(Bus* bus, Cartridge cartridge) {
    bus->cartridge = &cartridge;
}

uint8_t bus_read(Bus bus, uint32_t address) {
    if ((0x000000 <= address) && (address <= 0x000FFF)) {
        // bios read
        printf("*BIOS read not yet implemented!*\n");
        exit(-1);
    } else if ((0x001000 <= address) && (address <= 0x001FFF)) {
        return ram_read(*bus.ram, address);
    } else if ((0x002000 <= address) && (address <= 0x0020FF)) {
        // hardware registers read
        printf("*HW Registers read not yet implemented!*\n");
        exit(-1);
    } else if ((0x002100 <= address) && (address <= 0xFFFFFF)) {
        uint32_t real_address = address & 0x1FFFFF; // mask the mirror
        return cartridge_read(*bus.cartridge, real_address);
    } else {
        printf("*Unvalid address: bus_read(0x%06X)*\n", address);
        exit(-1);
    }
}

void bus_write(Bus *bus, uint32_t address, uint8_t value) {}
