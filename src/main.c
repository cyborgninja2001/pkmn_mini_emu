#include "cartridge.h"
#include "bus.h"
#include "bios.h"
#include "common.h"
#include <stdio.h>

BIOS bios;
Bus bus;
Cartridge cart;
Ram ram;
int main(int argc, char* argv[]) {
    init_bios(&bios, argv[1]);
    bus_init(&bus, &cart, &ram, &bios);
    uint8_t a = bus_read(bus, 0x0000FF);
    printf("a: %02X\n", a);
    return 0;
}
