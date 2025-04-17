#include "hardware_registers.h"

void hw_registers_init(HWRegisters *hw_regs) {
    for (int i = 0; i < 0x000100; i++) {
        hw_regs->data[i] = 0;
    }
}

uint8_t hw_registers_read(HWRegisters *hw_regs, uint32_t address) {
    return hw_regs->data[address - 0x002000];
}

void hw_registers_write(HWRegisters *hw_regs, uint32_t address, uint8_t value) {
    hw_regs->data[address - 0x002000] = value;
}