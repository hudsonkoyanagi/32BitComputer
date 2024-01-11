//
// Created by Hudson Koyanagi on 9/24/23.
//

#ifndef INC_32BITCOMPUTER_UTILS_H
#define INC_32BITCOMPUTER_UTILS_H

#include "./definitions.h"

namespace kutils {
    bool is_MSb(Word i); // checks if ms-bit is set
    Byte instrToByte(Word instr, Word mask, int shift); // applies bit mask to instr, shift right, returns least sig 8 bits
    Word instrToWord(Word instr, Word mask, int shift=0); // applies 32 bit mask to 32 bit instruction, shifts right
    bool overflow(Word unsigned_a, Word unsigned_b, int result); // checks if overflow occured (result must be signed)
    bool carry(Word unsigned_a, Word unsigned_b, int result);
}
#endif //INC_32BITCOMPUTER_UTILS_H
