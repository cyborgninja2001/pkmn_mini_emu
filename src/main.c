#include "cartridge.h"
#include "bus.h"
#include "bios.h"
#include "cpu.h"
#include "common.h"
#include <stdio.h>

BIOS bios;
Bus bus;
Cartridge cart;
Ram ram;
Cpu cpu;
Emulator emu;
Cartridge cart;

int main(int argc, char* argv[]) {
    init_bios(&bios, "");
    bus_init(&bus, &cart, &ram, &bios);
    cpu_reset(&cpu);

    cartridge_load(&cart, argv[1]);
    cartridge_print_data(cart);

    while(true) {
        cpu_step(&cpu, bus, emu);
        cpu_debug(cpu);
    }
    return 0;
}
