#ifndef HARDWARE_REGSITERS_H
#define HARDWARE_REGSITERS_H

#include "common.h"

typedef struct {
    uint8_t data[0x000100]; // 256B
} HWRegisters;

void hw_registers_init(HWRegisters *hw_regs);
uint8_t hw_registers_read(HWRegisters *hw_regs, uint32_t address);
void hw_registers_write(HWRegisters *hw_regs, uint32_t address, uint8_t value);

#endif