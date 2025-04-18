#ifndef CPU_H
#define CPU_H

#include "common.h"
#include "bus.h"
#include "emulator.h"

// 4 MHz -> that means 4,000,000 cycles per second.

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

typedef struct {
    Registers registers;
    uint8_t current_opcode;
} Cpu;

// functions to get the 16 bit register pairs
uint16_t reg_BA(Cpu cpu);
uint16_t reg_HL(Cpu cpu);
uint32_t reg_XiX(Cpu cpu);
uint32_t reg_YiY(Cpu cpu);
uint32_t reg_VPC(Cpu cpu);

void set_BA(Cpu *cpu, uint16_t value);
void set_HL(Cpu *cpu, uint16_t value);

// access the flags
bool get_flag_Z(Cpu cpu);      // 0 Zero
bool get_flag_C(Cpu cpu);      // 1 Carry
bool get_flag_O(Cpu cpu);      // 2 Overflow
bool get_flag_S(Cpu cpu);      // 3 Sign
bool get_flag_BCD(Cpu cpu);    // 4 Binary Coded Decimal Mode (8-bit add\sub)
bool get_flag_NIBBLE(Cpu cpu); // 5 Low-Mask Mode (8-bit add\sub)
bool get_flag_ID(Cpu cpu);     // 6 Interrupt Disable
bool get_flag_IB(Cpu cpu);     // 7 Interrupt Branch

// set the flags
void set_flag_Z(Cpu *cpu, bool v);
void set_flag_C(Cpu *cpu, bool v);
void set_flag_O(Cpu *cpu, bool v);
void set_flag_S(Cpu *cpu, bool v);
void set_flag_BCD(Cpu *cpu, bool v);
void set_flag_NIBBLE(Cpu *cpu, bool v);
void set_flag_ID(Cpu *cpu, bool v);
void set_flag_IB(Cpu *cpu, bool v);

void cpu_reset(Cpu *cpu);
void cpu_step(Cpu *cpu, Bus bus, Emulator *emu);
void cpu_debug(Cpu cpu);

#endif