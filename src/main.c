#include "cartridge.h"
#include "bus.h"
#include "bios.h"
#include <stdio.h>

BIOS bios;
int main(int argc, char* argv[]) {
    init_bios(&bios, argv[1]);
    return 0;
}
