#ifndef EMULATOR_H
#define EMULATOR_H

#include "common.h"
#include "pokemon_mini.h"
#include "cartridge.h"
#include "bios.h"

typedef struct {
    PokemonMini pkmini;
    Cartridge cartridge;
    int emu_ticks;
} Emulator;

void emu_init(Emulator *emu);
void emu_cycles(Emulator *emulator, int n);
void emu_run(Emulator *emu, int argc, char* argv[]);

#endif