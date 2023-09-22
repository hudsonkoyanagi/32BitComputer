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
    void reset(Memory& mem);
    void fetch(Memory& mem, bool debug = false);
    void execute(Memory& mem, bool debug = false);
    void setFlags(bool c, bool z, bool n, bool v);
    void DEV_printReg();

private:
    Registers registers;

    Word PC;
    Word SP;
    Word IR;
    Word LR;

    bool C = false;
    bool Z = false;
    bool N = false;
    bool V = false;
    static Byte instrToByte(Word instr, Word mask, int shift);
    static Word instrToWord(Word instr, Word mask, int shift);
    void ALU_OP(Byte opCode, Word instr);
};


#endif //INC_32BITCOMPUTER_CPU_H
