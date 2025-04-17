#ifndef POKEMON_MINI_H
#define POKEMON_MINI_H

#include "common.h"
#include "cartridge.h"
#include "ram.h"
#include "bios.h"

typedef struct {
    //Cartridge cartridge;
    Ram ram;
    BIOS bios;
} PokemonMini;

void pokemon_mini_init(PokemonMini pkmini, const char *bios_path);

#endif