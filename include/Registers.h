//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_REGISTERS_H
#define INC_32BITCOMPUTER_REGISTERS_H
#include "definitions.h"

class Registers {
public:
    Word& operator[](uint8_t reg);
    void clearAll();
private:
    Word registers[8];
};


#endif //INC_32BITCOMPUTER_REGISTERS_H
