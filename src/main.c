#include "cartridge.h"
#include "bus.h"
#include <stdio.h>

Cartridge cart;
Bus bus;

int main(int argc, char* argv[]) {
    cartridge_load(&cart, argv[1]);
    cartridge_print_data(cart);
    bus_init(&bus, cart);
    uint8_t a = bus_read(bus, 0x002100 + 8);
    printf("a:%02X\n", a);
    uint8_t b = bus_read(bus, 0x200000);
    return 0;
}
