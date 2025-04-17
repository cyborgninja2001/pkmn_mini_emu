#include "cartridge.h"
#include "bus.h"
#include <stdio.h>

Cartridge cart;
Bus bus;
Ram ram;

int main(int argc, char* argv[]) {
    cartridge_load(&cart, argv[1]);
    cartridge_print_data(cart);
    bus_init(&bus, &cart, &ram);
    uint8_t a = bus_read(bus, 0x002100 + 0x000008);
    printf("address:%06X\n", 0x002100 + 0x000008);
    return 0;
}
