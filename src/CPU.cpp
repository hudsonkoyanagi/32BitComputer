//
// Created by Hudson Koyanagi on 9/18/23.
//

#include "../include/CPU.h"
#include <iostream>
#include "../include/masks.h"
#include "../include/opcodes.h"
#include "../include/utils.h"

CPU::CPU() {
    this->reset();
}

void CPU::reset(Word stackBase) {
    SP = stackBase;
    PC = IR = LR = 0;
    C = Z = N = V = false; // carry, zero, negative, overflow
    registers.clearAll();
}

void CPU::reset(Memory& mem, Word stackBase) {
    SP = stackBase;
    SP = PC = IR = LR = 0;
    C = Z = N = V = false; // carry, zero, negative, overflow
    registers.clearAll();
    mem.clear();
}

void CPU::setFlags(bool c, bool z, bool n, bool v) {
    this->C = c;
    this->Z = z;
    this->N = n;
    this->V = v;
}

// loads word pointed to by PC into IR
// increments PC (by 4)
void CPU::fetch(Memory& mem, bool debug) {

    Word instr = mem[PC] << 24;
    instr += mem[PC+1] << 16;
    instr += mem[PC+2] << 8;
    instr += mem[PC+3];

    if(debug) {
        std::cout << "Fetched " << std::hex << instr  << " from " << PC << std::endl;
    }

    IR = instr;
    PC+=4; // TODO handle over run
}

// TODO: set flags
void CPU::U_ALU_OP(Byte opCode, Word instr) {
    Byte fn = kutils::instrToByte(instr, ALU_FN_MASK, 22);
    Byte sf = kutils::instrToByte(instr,ALU_S_MASK, 21);
    Byte rd = kutils::instrToByte(instr,ALU_RD_MASK, 18);
    Byte rs1 = kutils::instrToByte(instr, ALU_RS1_MASK, 15);
    Word a;
    Word b;

    if(fn == 0) {
        a = registers[rd];
        b = registers[rs1];
    } else if (fn == 1) {
        Byte rs12 = kutils::instrToByte(instr, ALU_RS2_MASK, 12);
        a = registers[rs1];
        b = registers[rs12];
    } else if (fn == 2) {
        a = registers[rd];
        b = kutils::instrToWord(instr, ALU_I16_MASK);
    } else {
        a = registers[rs1];
        b = kutils::instrToWord(instr, ALU_I12_MASK);
    }

    Word result;

    switch(opCode) {
        case INS_AND:
            if(sf) {
                C = false;
                V = false;
            }
            result = a & b;
            break;
        case INS_ORR:
            if(sf) {
                C = false;
                V = false;
            }
            result = a | b;
            break;
        case INS_XOR:
            if(sf) {
                C = false;
                V = false;
            }
            result = a ^ b;
            break;
        case INS_ADD:

            if(sf) {
                uint64_t u_sum = (uint64_t) a + (uint64_t) b;
                int64_t i_sum = (int)u_sum;
                int signed_a = (int) a;
                int signed_b = (int) b;
                C = u_sum > 0xFFFFFFFF;
                // parity check instead of MSB check
                V = (signed_a > 0 && signed_b > 0 && i_sum < 0) || (signed_a < 0 && signed_b < 0 && i_sum > 0);
            }
            result = a + b;
            break;
        case INS_SUB:
            if(sf) {

            }
            result = a - b;
            break;
        case INS_MLT:
            if(sf) {

            }
            result = a * b;
            break;
        case INS_DIV:
            if(sf) {

            }
            result = a / b;
            break;
        case INS_LSL:
            if(sf) {
                C = false;
                V = false;
            }
            result = a << b;
            break;
        case INS_LSR:
            if(sf) {
                C = false;
                V = false;
            }
            result = a >> b;
            break;
        case INS_ASR:
            if(sf) {
                C = (a >> 31) & 1; // carry = bit shifted out
                V = false;
            }
            result = (Word) ((int) a >> (int) b);
            break;
        default:
            std::cout << "Unknown ALU instruction: " << std::hex << opCode << "\n";
            exit(1); // TODO: check if this causes mem leak
            break;
    }
    if(sf) {
        Z = result == 0;
        N = (result >> 31) & 1; // check msb for negative
    }

    registers[rd] = result;
}

// Executes instruction in IR
void CPU::execute(Memory& mem, bool debug) {
    if(debug) {
        std::cout << "Executing instruction: " << std::hex << IR << std::endl;
    }
    Byte opCode = kutils::instrToByte(IR, OP_CODE_MASK, 24);
    if(opCode <= INS_ASR){
        U_ALU_OP(opCode, IR);
        return;
    }

    switch(opCode){
        case INS_MOV: {
            const Byte fun = kutils::instrToByte(IR, MOV_FUN_MASK, 23);
            const Byte rgd = kutils::instrToByte(IR, MOV_RGD_MASK, 20);
            if (fun == 0) {
                const Byte rgs = kutils::instrToByte(IR, MOV_RGS_MASK, 16);
                registers[rgd] = registers[rgs];
            } else {
                const Word imm = kutils::instrToWord(IR, MOV_IMM_MASK);
                registers[rgd] = imm;
            }
            break;
        }
        case INS_LDR: {
            const Byte func = kutils::instrToByte(IR, LDR_FUN_MASK, 23);
            const Byte type = kutils::instrToByte(IR, LDR_TYP_MASK, 16);
            const Byte rgd = kutils::instrToByte(IR, LDR_RGD_MASK, 20);
            const Byte rgs = kutils::instrToByte(IR, LDR_RSD_MASK, 12);
            //Multiplies type by two to get byte size, 2 = Word, 1 = Half Word,( 0 = Byte handled in function)
            if(func == 0) {
                registers[rgd] = mem.retrieveBySize(registers[rgs], type*2);
            } else {
                Word offset = kutils::instrToWord(IR, LDR_I12_MASK);
                registers[rgd] = mem.retrieveBySize(registers[rgs]+offset, type*2);
            }
            break;
        }
        case INS_STR : {
            // Type not implemented for now, since registers are Words
            // simpler this way for now
            const Byte func = kutils::instrToByte(IR, LDR_FUN_MASK, 23);
            // const Byte type = kutils::instrToByte(IR, LDR_TYP_MASK, 16);
            const Byte rgd = kutils::instrToByte(IR, LDR_RGD_MASK, 20);
            const Byte rgs = kutils::instrToByte(IR, LDR_RSD_MASK, 12);
            if(func == 0) {
                mem.storeWord(registers[rgs], registers[rgd]);
            } else {
                Word offset = kutils::instrToWord(IR, LDR_I16_MASK);
                mem.storeWord(registers[rgs]+offset, registers[rgd]);
            }
            break;
        }
        // TODO: implement conditional jmps
        case INS_JMP: {

            const Byte link = kutils::instrToByte(IR, JMP_LNK_MASK, 23);
            const Byte rgd = kutils::instrToByte(IR, JMP_RGD_MASK, 20);
            const Word offset = kutils::instrToWord(IR, JMP_OFF_MASK);
            const Byte fun = kutils::instrToByte(IR, JMP_FUN_MASK, 19);
            const Byte cond = kutils::instrToByte(IR, JMP_CND_MASK, 12);
            switch(cond) {
                case(0): {
                    break;
                }
                case(1): {

                }
            }

            if(link) {
                LR = PC;
            }
            if(fun == 0) {
                PC = registers[rgd];
            } else if(fun == 1) {
                PC = registers[rgd] + offset;
            } else{
                printf("Not valid JMP function %d: \n", fun);
                exit(EXIT_FAILURE); // check if this causes memory leak
            }
        }
        case INS_RET: {
            PC = LR;
            break;
        }
        case INS_POP: {

        }
        case INS_PUSH: {

        }
        default:
            std::cout << "Unknown instruction: " << std::hex << opCode << "\n";
            break;
    }
}

// Only prints registers with non-zero vals
void CPU::DEV_printReg() {
    std::cout << "PC: " << std::hex << PC << std::endl;
    std::cout << "SP: " << std::hex << SP << std::endl;
    std::cout << "IR: " << std::hex << IR << std::endl;
    std::cout <<  "C:" << C << " Z:" << Z << " N:" <<  N << " V:" << V << std::endl;
    for(int i = 0; i < 8; i++){
        if(registers[i])
            std::cout << "R" << i << ": " << std::hex << registers[i] << std::endl;
    }
}