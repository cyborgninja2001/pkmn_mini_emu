#ifndef POKEMON_MINI_H
#define POKEMON_MINI_H

#include "common.h"
#include "cartridge.h"

typedef struct {
    Cartridge cartridge;
} PokemonMini;

void pokemon_mini_init();

#endif