//
// Created by Hudson Koyanagi on 9/24/23.
//
#include "../include/utils.h"
#include "./definitions.h"

bool kutils::is_MSb(int i) {
    return i < 0;
}
Byte kutils::instrToByte(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}
Word kutils::instrToWord(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}