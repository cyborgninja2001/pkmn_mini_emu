#include "ram.h"

void ram_init(Ram *ram) {
    for (int i = 0; i < RAM_SIZE; i++) {
        ram->data[i] = 0;
    }
}

uint8_t ram_read(Ram ram, uint32_t address) {
    return ram.data[address - 0x001000];
}

void ram_write(Ram *ram, uint32_t address, uint8_t value) {
    ram->data[address - 0x001000] = value;
}
