//
// Created by Hudson Koyanagi on 9/18/23.
//

#include "../include/Registers.h"
#include <cassert>

Word& Registers::operator[](uint8_t reg) {
    assert(reg < 8);
    return registers[reg];
}

void Registers::clearAll() {
    for(Word& w : this->registers) w = 0;
}