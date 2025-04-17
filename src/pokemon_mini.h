#ifndef POKEMON_MINI_H
#define POKEMON_MINI_H

#include "common.h"
#include "cartridge.h"
#include "ram.h"

typedef struct {
    //Cartridge cartridge;
    Ram ram;
} PokemonMini;

void pokemon_mini_init();

#endif