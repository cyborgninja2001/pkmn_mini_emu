#ifndef CPU_H
#define CPU_H

#include "common.h"

typedef struct {
    uint8_t A;
    uint8_t B;
    uint8_t L;
    uint8_t H;
    uint8_t N;

    uint16_t X;  // extends to 24 bits with Xi
    uint8_t Xi;  // high part of the 24-bit address for X

    uint16_t Y;  // extends to 24 bits with Yi
    uint8_t Yi;  // high part of the 24-bit address for X

    uint8_t I;   // It is used as part of 24-bit addresses

    uint16_t PC; // It is extended to 23 bits with the V register
    uint8_t V;   // PC Bank Register (extended upper part of the PC)
    uint8_t U;   // V Delay Register (temporarily stores the value for V)
    uint16_t SP;
    uint8_t F;
    uint8_t E;
} Registers;

#endif

// uint32_t direccion_x = ((uint32_t)Xi << 16) | X;

/*
uint32_t direccion_pc;

if (PC & 0x8000) { // Verificar si el bit mas significativo de PC esta establecido (bit 15)
    direccion_pc = ((uint32_t)V << 16) | PC;
} else {
    direccion_pc = PC; // Si el bit mas significativo no esta establecido, la direccion es simplemente el valor de PC
}
*/