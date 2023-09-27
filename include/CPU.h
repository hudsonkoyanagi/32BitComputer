//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_CPU_H
#define INC_32BITCOMPUTER_CPU_H
#include "Registers.h"
#include "Memory.h"
#include "definitions.h"

class CPU {
public:
    CPU();
    void reset(Word stackBase);
    void reset(Memory& mem, Word stackBase);
    void fetch(Memory& mem, bool debug = false);
    void execute(Memory& mem, bool debug = false);
    void setFlags(bool c, bool z, bool n, bool v);
    void DEV_printReg();
    Registers registers;

private:


    Word PC;
    Word SP;
    Word IR;
    Word LR;

    bool C = false;
    bool Z = false;
    bool N = false;
    bool V = false;

    void U_ALU_OP(Byte opCode, Word instr);
};


#endif //INC_32BITCOMPUTER_CPU_H
