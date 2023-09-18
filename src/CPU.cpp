//
// Created by Hudson Koyanagi on 9/18/23.
//

#include "../include/CPU.h"
#include <iostream>
#include "../include/masks.h"
#include "../include/opcodes.h"

Byte CPU::instrToByte(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}
Word CPU::instrToWord(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}


void CPU::reset(Memory& mem) {
    SP = 0x1000;
    PC = 0x1004;
    IR = 0;
    LR = 0;

    C = Z = N = O = 0;
    registers.clearAll();
    mem.clear();
}

// loads word pointed to by PC into IR
// increments PC (by 4)
void CPU::fetch(Memory& mem) {
    Word instr = mem[PC] << 24;
    instr += mem[PC+1] << 16;
    instr += mem[PC+2] << 8;
    instr += mem[PC+3];
    IR = instr;
    PC+=4;
}

void CPU::ALU_OP(Byte opCode, Word instr) {
    Byte op = instrToByte(instr, ALU_OP_MASK, 24);
    Byte fn = instrToByte(instr, ALU_FN_MASK, 22);
    Byte sf = instrToByte(instr,ALU_S_MASK, 21);
    Byte rd = instrToByte(instr,ALU_RD_MASK, 18);
    Byte rs1 = instrToByte(instr, ALU_RS1_MASK, 15);
    Word a;
    Word b;

    if(fn == 0) {
        a = registers[rd];
        b = registers[rs1];
    } else if (fn == 1) {
        Byte rs12 = instrToByte(instr, ALU_RS2_MASK, 12);
        a = registers[rs1];
        b = registers[rs12];
    } else if (fn == 2) {
        a = registers[rd];
        b = instrToWord(instr, ALU_I16_MASK, 0);
    } else {
        a = registers[rs1];
        b = instrToWord(instr, ALU_I12_MASK, 0);
    }

    switch(opCode) {
        case INS_AND:
            registers[rd] = a&b;
            break;
        case INS_ORR:
            registers[rd] = a|b;
            break;
        case INS_XOR:
            registers[rd] = a^b;
            break;
        case INS_ADD:
            registers[rd] = a+b;
            break;
        case INS_SUB:
            registers[rd] = a-b;
            break;
        case INS_MLT:
            registers[rd] = a*b;
            break;
        case INS_DIV:
            registers[rd] = a/b;
            break;
            // TODO: LSL, LSR, ASR
    }

}

void CPU::execute(Memory& mem) {
    std::cout << "Executing instruction: " << std::hex << IR << std::endl;
    Byte opCode = instrToByte(IR, OP_CODE_MASK, 24);
    if(opCode <= INS_ASR){
        ALU_OP(opCode, IR);
        return;
    }

    switch(opCode){
        case INS_MOV: {
            const Byte fun = instrToByte(IR, MOV_FUN_MASK, 23);
            const Byte rgd = instrToByte(IR, MOV_RGD_MASK, 20);
            if (fun == 0) {
                const Byte rgs = instrToByte(IR, MOV_RGS_MASK, 16);
                registers[rgd] = registers[rgs];
            } else {
                const Word imm = instrToWord(IR, MOV_IMM_MASK, 0);
                registers[rgd] = imm;
            }
            break;
        }
        case INS_LDR: {
            const Byte func = instrToByte(IR, LDR_FUN_MASK, 23);
            const Byte type = instrToByte(IR, LDR_TYP_MASK, 16);
            const Byte rgd = instrToByte(IR, LDR_RGD_MASK, 20);
            const Byte rgs = instrToByte(IR, LDR_RSD_MASK, 12);
            //Multiplies type by two to get byte size, 2 = Word, 1 = Half Word,( 0 = Byte handled in function)
            if(func == 0) {
                registers[rgd] = mem.retrieveBySize(registers[rgs], type*2);
            } else {
                Word offset = instrToWord(IR, LDR_I12_MASK, 0);
                registers[rgd] = mem.retrieveBySize(registers[rgs]+offset, type*2);
            }
            break;
        }
        case INS_STR : {
            // Type not implemented for now, since registers are Words
            // simpler this way for now
            const Byte func = instrToByte(IR, LDR_FUN_MASK, 23);
            // const Byte type = instrToByte(IR, LDR_TYP_MASK, 16);
            const Byte rgd = instrToByte(IR, LDR_RGD_MASK, 20);
            const Byte rgs = instrToByte(IR, LDR_RSD_MASK, 12);
            if(func == 0) {
                mem.storeWord(registers[rgs], registers[rgd]);
            } else {
                Word offset = instrToWord(IR, LDR_I16_MASK, 0);
                mem.storeWord(registers[rgs]+offset, registers[rgd]);
            }
            break;
        }
        case INS_JMP: {


            const Byte link = instrToByte(IR, JMP_LNK_MASK, 23);
            const Byte rgd = instrToByte(IR, JMP_RGD_MASK, 20);
            const Word offset = instrToWord(IR, JMP_OFF_MASK, 0);
            const Byte fun = instrToByte(IR, JMP_FUN_MASK, 19);

            if(link) {
                LR = PC;
            }
            if(fun == 0) {
                PC = registers[rgd];
            } else if(fun == 1) {
                PC += offset;
            } else{
                printf("Not valid JMP function %d: \n", fun);
                exit(EXIT_FAILURE);
            }
        }
        default:
            std::cout << "Unknown instruction: " << std::hex << opCode << "\n";
            break;
    }
}

void CPU::DEV_printReg() {
    std::cout << "PC: " << std::hex << PC << std::endl;
    std::cout << "SP: " << std::hex << SP << std::endl;
    std::cout << "IR: " << std::hex << IR << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << "R" << i << ": " << std::hex << registers[i] << std::endl;
    }
}