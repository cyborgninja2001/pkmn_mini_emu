#include "cpu.h"

// *FUNCTIONS TO GET THE 16 BIT REGISTER PAIRS*
uint16_t reg_BA(Cpu cpu) {
    return ((uint16_t)cpu.registers.B << 8) | (cpu.registers.A);
}

uint16_t reg_HL(Cpu cpu) {
    return ((uint16_t)cpu.registers.H << 8) | (cpu.registers.L);
}

uint32_t reg_XiX(Cpu cpu) {
    return ((uint32_t)cpu.registers.Xi << 16) | (cpu.registers.X);
}

uint32_t reg_YiY(Cpu cpu) {
    return ((uint32_t)cpu.registers.Yi << 16) | (cpu.registers.Y);
}

uint32_t reg_VPC(Cpu cpu) {
    return ((uint32_t)cpu.registers.V << 16) | cpu.registers.PC;
}

void set_BA(Cpu *cpu, uint16_t value) {
    cpu->registers.B = (value >> 8) & 0xFF;
    cpu->registers.A =  value & 0xFF;
}

void set_HL(Cpu *cpu, uint16_t value) {
    cpu->registers.H = (value >> 8) & 0xFF;
    cpu->registers.L =  value & 0xFF;
}

// *ACCESSS THE FLAGS*
bool get_flag_Z(Cpu cpu) {
    return BIT(cpu.registers.F, 0);
}

bool get_flag_C(Cpu cpu) {
    return BIT(cpu.registers.F, 1);
}

bool get_flag_O(Cpu cpu) {
    return BIT(cpu.registers.F, 2);
}

bool get_flag_S(Cpu cpu) {
    return BIT(cpu.registers.F, 3);
}

bool get_flag_BCD(Cpu cpu) {
    return BIT(cpu.registers.F, 4);
}

bool get_flag_NIBBLE(Cpu cpu) {
    return BIT(cpu.registers.F, 5);
}

bool get_flag_ID(Cpu cpu) {
    return BIT(cpu.registers.F, 6);
}

bool get_flag_IB(Cpu cpu) {
    return BIT(cpu.registers.F, 7);
}

// *SET THE FLAGS*
void set_flag_Z(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 0, v)
}

void set_flag_C(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 1, v)
}

void set_flag_O(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 2, v)
}

void set_flag_S(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 3, v)
}

void set_flag_BCD(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 4, v)
}

void set_flag_NIBBLE(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 5, v)
}

void set_flag_ID(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 6, v)
}

void set_flag_IB(Cpu *cpu, bool v) {
    BIT_SET(cpu->registers.F, 7, v)
}

void cpu_reset(Cpu *cpu) {
    cpu->registers.A = 0x00;
    cpu->registers.B = 0x00;
    cpu->registers.H = 0x00;
    cpu->registers.L = 0x00;
    cpu->registers.N = 0x20;
    cpu->registers.F = 0x00;
    cpu->registers.E = 0x00;
    cpu->registers.I = 0x00;
    cpu->registers.PC = 0x0000; // ?
    cpu->registers.SP = 0x0000; // ? watch bios dump or something
    cpu->registers.U = 0x00;
    cpu->registers.V = 0x00;
    cpu->registers.X = 0x0000;
    cpu->registers.Xi = 0x00;
    cpu->registers.Y = 0x0000;
    cpu->registers.Yi = 0x00;
}

void cpu_step(Cpu *cpu, Bus bus, Emulator emu) {
    uint8_t opcode;
    if (cpu->registers.PC & 0x8000) { // most significant bit is on?
        opcode = bus_read(bus, reg_VPC(*cpu));
    } else {
        opcode = bus_read(bus, cpu->registers.PC);
    }
    //emu_cycles(&emu, 4); *i think it's no necessary here*
    cpu->registers.PC++;

    switch (opcode) {
        case 0xFF: // NOP
            emu_cycles(&emu, 8);
            break;
        case 0x40: // MOV A, A
            cpu->registers.A = cpu->registers.A;
            emu_cycles(&emu, 4);
            break;
        case 0x41: // MOV A, B
            cpu->registers.A = cpu->registers.B;
            emu_cycles(&emu, 4);
            break;
        case 0x42: // MOV A L
            cpu->registers.A = cpu->registers.L;
            emu_cycles(&emu, 4);
        case 0x43: // MOV A, H
            cpu->registers.A = cpu->registers.H;
            emu_cycles(&emu, 4);
            break;
        case 0x44: { // MOV A, [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC); // immediate 8bit data
            cpu->registers.PC++;
            cpu->registers.A = bus_read(bus, cpu->registers.N + nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x45: // MOV A, [HL]
            cpu->registers.A = bus_read(bus, reg_HL(*cpu));
            emu_cycles(&emu, 8);
            break;
        case 0x46: // MOV A, [X]
            cpu->registers.A = bus_read(bus, cpu->registers.X);
            emu_cycles(&emu, 8);
            break;
        case 0x47: // MOV A, [Y]
            cpu->registers.A = bus_read(bus, cpu->registers.Y);
            emu_cycles(&emu, 8);
            break;
        case 0x48: // MOV B, A
            cpu->registers.B = cpu->registers.A;
            emu_cycles(&emu, 4);
            break;
        case 0x49: // MOV B, B
            cpu->registers.B = cpu->registers.B;
            emu_cycles(&emu, 4);
            break;
        case 0x4A: // MOV B, L
            cpu->registers.B = cpu->registers.L;
            emu_cycles(&emu, 4);
            break;
        case 0x4B: // MOV B, H
            cpu->registers.B = cpu->registers.H;
            emu_cycles(&emu, 4);
            break;
        case 0x4C: { // MOV B, [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.B = bus_read(bus, cpu->registers.N + nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x4D: // MOV B, [HL]
            cpu->registers.B = bus_read(bus, reg_HL(*cpu));
            emu_cycles(&emu, 8);
            break;
        case 0x4E: // MOV B, [X]
            cpu->registers.B = bus_read(bus, cpu->registers.X);
            emu_cycles(&emu, 8);
            break;
        case 0x4F: // MOV B, [Y]
            cpu->registers.B = bus_read(bus, cpu->registers.Y);
            emu_cycles(&emu, 8);
            break;
        case 0x50: // MOV L, A
            cpu->registers.L = cpu->registers.A;
            emu_cycles(&emu, 4);
            break;
        case 0x51: // MOV L, B
            cpu->registers.L = cpu->registers.B;
            emu_cycles(&emu, 4);
            break;
        case 0x52: // MOV L, L
            cpu->registers.L = cpu->registers.L;
            emu_cycles(&emu, 4);
            break;
        case 0x53: // MOV L, H
            cpu->registers.L = cpu->registers.H;
            emu_cycles(&emu, 4);
            break;
        case 0x54: { // MOV L, [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.L = bus_read(bus, cpu->registers.N + nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x55: // MOV L, [HL]
            cpu->registers.L = bus_read(bus, reg_HL(*cpu));
            emu_cycles(&emu, 8);
            break;
        case 0x56: // MOV L, [X]
            cpu->registers.L = bus_read(bus, cpu->registers.X);
            emu_cycles(&emu, 8);
            break;
        case 0x57: // MOV L, [Y]
            cpu->registers.L = bus_read(bus, cpu->registers.Y);
            emu_cycles(&emu, 8);
            break;
        case 0x58: // MOV H, A
            cpu->registers.H = cpu->registers.A;
            emu_cycles(&emu, 4);
            break;
        case 0x59: // MOV H, B
            cpu->registers.H = cpu->registers.B;
            emu_cycles(&emu, 4);
            break;
        case 0x5A: // MOV H, L
            cpu->registers.H = cpu->registers.L;
            emu_cycles(&emu, 4);
            break;
        case 0x5B: // MOV H, H
            cpu->registers.H = cpu->registers.H;
            emu_cycles(&emu, 4);
            break;
        case 0x5C: { // MOV H, [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.H = bus_read(bus, cpu->registers.N + nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x5D: // MOV H, [HL]
            cpu->registers.H = bus_read(bus, reg_HL(*cpu));
            emu_cycles(&emu, 8);
            break;
        case 0x5E: // MOV H, [X]
            cpu->registers.H = bus_read(bus, cpu->registers.X);
            emu_cycles(&emu, 8);
            break;
        case 0x5F: // MOV H, [Y]
            cpu->registers.H = bus_read(bus, cpu->registers.Y);
            emu_cycles(&emu, 8);
            break;
        case 0x60: // MOV [X], A
            bus_write(bus, cpu->registers.X, cpu->registers.A);
            emu_cycles(&emu, 8);
            break;
        case 0x61: // MOV [X], B
            bus_write(bus, cpu->registers.X, cpu->registers.B);
            emu_cycles(&emu, 8);
            break;
        case 0x62: // MOV [X], L
            bus_write(bus, cpu->registers.X, cpu->registers.L);
            emu_cycles(&emu, 8);
            break;
        case 0x63: // MOV [X], H
            bus_write(bus, cpu->registers.X, cpu->registers.H);
            emu_cycles(&emu, 8);
            break;
        case 0x64: { // MOV [X], [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.X, cpu->registers.N + nn);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x65: { // MOV [X], [HL]
            uint8_t value = bus_read(bus, reg_HL(*cpu));
            bus_write(bus, cpu->registers.X, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x66: { // MOV [X], [X]
            uint8_t value = bus_read(bus, cpu->registers.X);
            bus_write(bus, cpu->registers.X, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x67: {// MOV [X], [Y]
            uint8_t value = bus_read(bus, cpu->registers.Y);
            bus_write(bus, cpu->registers.X, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x68: // MOV [HL], A
            bus_write(bus, reg_HL(*cpu), cpu->registers.A);
            emu_cycles(&emu, 8);
            break;
        case 0x69: // MOV [HL], B
            bus_write(bus, reg_HL(*cpu), cpu->registers.B);
            emu_cycles(&emu, 8);
            break;
        case 0x6A: // MOV [HL], L
            bus_write(bus, reg_HL(*cpu), cpu->registers.L);
            emu_cycles(&emu, 8);
            break;
        case 0x6B: // MOV [HL], H
            bus_write(bus, reg_HL(*cpu), cpu->registers.H);
            emu_cycles(&emu, 8);
            break;
        case 0x6C: { // MOV [HL], [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t value = bus_read(bus, cpu->registers.N + nn);
            bus_write(bus, reg_HL(*cpu), value);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x6D: { // MOV [HL], [HL]
            uint8_t value = bus_read(bus, reg_HL(*cpu));
            bus_write(bus, reg_HL(*cpu), value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x6E: { // MOV [HL], [X]
            uint8_t value = bus_read(bus, cpu->registers.X);
            bus_write(bus, reg_HL(*cpu), value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x6F: { // MOV [HL], [Y]
            uint8_t value = bus_read(bus, cpu->registers.Y);
            bus_write(bus, reg_HL(*cpu), value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x70: // MOV [Y], A
            bus_write(bus, cpu->registers.Y, cpu->registers.A);
            emu_cycles(&emu, 8);
            break;
        case 0x71: // MOV [Y], B
            bus_write(bus, cpu->registers.Y, cpu->registers.B);
            emu_cycles(&emu, 8);
            break;
        case 0x72: // MOV [Y], L
            bus_write(bus, cpu->registers.Y, cpu->registers.L);
            emu_cycles(&emu, 8);
            break;
        case 0x73: // MOV [Y], H
            bus_write(bus, cpu->registers.Y, cpu->registers.H);
            emu_cycles(&emu, 8);
            break;
        case 0x74: { // MOV [Y], [N+#nn]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t value = bus_read(bus, cpu->registers.N + nn);
            bus_write(bus, cpu->registers.Y, value);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x75: { // MOV [Y], [HL]
            uint8_t value = bus_read(bus, reg_HL(*cpu));
            bus_write(bus, cpu->registers.Y, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x76: { // MOV [Y], [X]
            uint8_t value = bus_read(bus, cpu->registers.X);
            bus_write(bus, cpu->registers.Y, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x77: { // MOV [Y], [Y]
            uint8_t value = bus_read(bus, cpu->registers.Y);
            bus_write(bus, cpu->registers.Y, value);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x78: { // MOV [N+#nn], A
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.N + nn, cpu->registers.A);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x79: { // MOV [N+#nn], B
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.N + nn, cpu->registers.B);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x7A: { // MOV [N+#nn], L
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.N + nn, cpu->registers.L);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x7B: { // MOV [N+#nn], H
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.N + nn, cpu->registers.H);
            emu_cycles(&emu, 12);
            break;
        }
        case 0x7D: { // MOV [N+#nn], [HL]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t value = bus_read(bus, reg_HL(*cpu));
            bus_write(bus, cpu->registers.N + nn, value);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x7E: { // MOV [N+#nn], [X]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t value = bus_read(bus, cpu->registers.X);
            bus_write(bus, cpu->registers.N + nn, value);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x7F: { // MOV [N+#nn], [Y]
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t value = bus_read(bus, cpu->registers.Y);
            bus_write(bus, cpu->registers.N + nn, value);
            emu_cycles(&emu, 16);
            break;
        }
        case 0x9F: { // MOV F, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.F = nn;
            emu_cycles(&emu, 12);
            break;
        }
        case 0xB0: { // MOV A, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.A = nn;
            emu_cycles(&emu, 8);
            break;
        }
        case 0xB1: { // MOV B, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.B = nn;
            emu_cycles(&emu, 8);
            break;
        }
        case 0xB2: { // MOV L, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.L = nn;
            emu_cycles(&emu, 8);
            break;
        }
        case 0xB3: { // MOV H, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.H = nn;
            emu_cycles(&emu, 8);
            break;
        }
        case 0xB4: { // MOV N, #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            cpu->registers.N = nn;
            emu_cycles(&emu, 8);
            break;
        }
        case 0xB5: { // MOV [HL], #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, reg_HL(*cpu), nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0xB6: { // MOV [X], #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.X, nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0xB7: { // MOV [Y], #nn
            uint8_t nn = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.Y, nn);
            emu_cycles(&emu, 12);
            break;
        }
        case 0xDD: { // MOV [N+#nn], #nn
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            bus_write(bus, cpu->registers.N + nn1, nn2);
            emu_cycles(&emu, 16);
            break;
        }
        case 0xCE:
            uint8_t opcode2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            switch (opcode2) {
                case 0xC4: { // MOV U, #nn
                    uint8_t nn = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    cpu->registers.U = nn;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0xC5: { // MOV I, #nn
                    uint8_t nn = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    cpu->registers.I = nn;
                    emu_cycles(&emu, 12);
                    break;
                }
                case 0xC6: { // MOV XI, #nn
                    uint8_t nn = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    cpu->registers.Xi = nn;
                    emu_cycles(&emu, 12);
                    break;
                }
                case 0xC7: { //MOV YI, #nn
                    uint8_t nn = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    cpu->registers.Yi = nn;
                    emu_cycles(&emu, 12);
                    break;
                }
                case 0x40: { // MOV A, [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    cpu->registers.A = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x41: { // MOV A, [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    cpu->registers.A = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x42: { // MOV A, [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    cpu->registers.A = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x43: { // MOV A, [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    cpu->registers.A = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x48: { // MOV B, [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    cpu->registers.B = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x49:  { // MOV B, [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    cpu->registers.B = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x4A: { // MOV B, [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    cpu->registers.B = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x4B: { // MOV B, [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    cpu->registers.B = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x50: { // MOV L, [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    cpu->registers.L = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x51: { // MOV L, [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    cpu->registers.L = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x52: { // MOV L, [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    cpu->registers.L = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x53: { // MOV L, [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    cpu->registers.L = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x58: { // MOV H, [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    cpu->registers.H = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x59: { // MOV H, [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    cpu->registers.H = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x5A: { // MOV H, [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    cpu->registers.H = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x5B: { // MOV H, [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    cpu->registers.H = value;
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x44: { // MOV [X+#ss], A
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.X + ss, cpu->registers.A);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x45: { // MOV [Y+#ss], A
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.Y + ss, cpu->registers.A);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x46: // MOV [X+L], A
                    bus_write(bus, cpu->registers.X + cpu->registers.L, cpu->registers.A);
                    emu_cycles(&emu, 16);
                    break;
                case 0x47: // MOV [Y+L], A
                    bus_write(bus, cpu->registers.Y + cpu->registers.L, cpu->registers.A);
                    emu_cycles(&emu, 16);
                    break;
                case 0x4C: { // MOV [X+#ss], B
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.X + ss, cpu->registers.B);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x4D: { // MOV [Y+#ss], B
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.Y + ss, cpu->registers.B);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x4E: // MOV [X+L], B
                    bus_write(bus, cpu->registers.X + cpu->registers.L, cpu->registers.B);
                    emu_cycles(&emu, 16);
                    break;
                case 0x4F: //  MOV [Y+L], B
                    bus_write(bus, cpu->registers.Y + cpu->registers.L, cpu->registers.B);
                    emu_cycles(&emu, 16);
                    break;
                case 0x54: { // MOV [X+#ss], L
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.X + ss, cpu->registers.L);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x55: { // MOV [Y+#ss], L
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.Y + ss, cpu->registers.L);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x56: // MOV [X+L], L
                    bus_write(bus, cpu->registers.X + cpu->registers.L, cpu->registers.L);
                    emu_cycles(&emu, 16);
                    break;
                case 0x57: // MOV [Y+L], L
                    bus_write(bus, cpu->registers.Y + cpu->registers.L, cpu->registers.L);
                    emu_cycles(&emu, 16);
                    break;
                case 0x5C: { // MOV [X+#ss], H
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.X + ss, cpu->registers.H);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x5D: { // MOV [Y+#ss], H
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    bus_write(bus, cpu->registers.Y + ss, cpu->registers.H);
                    emu_cycles(&emu, 16);
                    break;
                }
                case 0x5E: // MOV [X+L], H
                    bus_write(bus, cpu->registers.X + cpu->registers.L, cpu->registers.H);
                    emu_cycles(&emu, 16);
                    break;
                case 0x5F: // MOV [Y+L], H
                    bus_write(bus, cpu->registers.Y + cpu->registers.L, cpu->registers.H);
                    emu_cycles(&emu, 16);
                    break;
                case 0x60: { // MOV [HL], [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    bus_write(bus, reg_HL(*cpu), value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x61: { // MOV [HL], [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    bus_write(bus, reg_HL(*cpu), value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x62: { // MOV [HL], [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    bus_write(bus, reg_HL(*cpu), value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x63: { // MOV [HL], [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    bus_write(bus, reg_HL(*cpu), value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x68: { // MOV [X], [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    bus_write(bus, cpu->registers.X, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x69: { // MOV [X], [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    bus_write(bus, cpu->registers.X, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x6A: { // MOV [X], [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    bus_write(bus, cpu->registers.X, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x6B: { // MOV [X], [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    bus_write(bus, cpu->registers.X, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x78: { // MOV [Y], [X+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.X + ss);
                    bus_write(bus, cpu->registers.Y, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x79: { // MOV [Y], [Y+#ss]
                    int8_t ss = (int8_t)bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t value = bus_read(bus, cpu->registers.Y + ss);
                    bus_write(bus, cpu->registers.Y, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x7A: { // MOV [Y], [X+L]
                    uint8_t value = bus_read(bus, cpu->registers.X + cpu->registers.L);
                    bus_write(bus, cpu->registers.Y, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                case 0x7B: { //MOV [Y], [Y+L]
                    uint8_t value = bus_read(bus, cpu->registers.Y + cpu->registers.L);
                    bus_write(bus, cpu->registers.Y, value);
                    emu_cycles(&emu, 20);
                    break;
                }
                default:
                    printf("CE NOT FOUND!\n");
                    break;
            }
            break;
        case 0xB8: { // MOV BA, [#nnnn]
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
            uint8_t value = bus_read(bus, nnnn);
            set_BA(cpu, value);
            emu_cycles(&emu, 20);
            break;
        }
        case 0xB9: { // MOV HL, [#nnnn]
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
            uint8_t value = bus_read(bus, nnnn);
            set_HL(cpu, value);
            emu_cycles(&emu, 20);
            break;
        }
        case 0xBA: { // MOV X, [#nnnn]
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
            cpu->registers.X = bus_read(bus, nnnn);
            emu_cycles(&emu, 20);
            break;
        }
        case 0xBB: { // MOV Y, [#nnnn]
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
            cpu->registers.Y = bus_read(bus, nnnn);
            emu_cycles(&emu, 20);
            break;
        }
        case 0xCF:
            uint8_t opecode3 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            switch (opecode3) {
                case 0x78: { // MOV SP, [#nnnn]
                    uint8_t nn1 = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint8_t nn2 = bus_read(bus, cpu->registers.PC);
                    cpu->registers.PC++;
                    uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
                    cpu->registers.SP = bus_read(bus, nnnn);
                    emu_cycles(&emu, 24);
                    break;
                }
            }
            break;
        case 0xBC: { // MOV [#nnnn], BA
            uint8_t nn1 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint8_t nn2 = bus_read(bus, cpu->registers.PC);
            cpu->registers.PC++;
            uint16_t nnnn = ((uint16_t)nn1 << 8) | nn2;
            bus_write(bus, nnnn, reg_BA(*cpu));
            emu_cycles(&emu, 20);
            break;
        }
    }
}

void cpu_debug(Cpu cpu) {}