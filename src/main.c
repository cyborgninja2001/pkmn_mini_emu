#include "cartridge.h"
#include <stdio.h>

Cartridge cart;

int main(int argc, char* argv[]) {
    cartridge_load(&cart, argv[1]);
    cartridge_print_data(cart);
    return 0;
}
