//
// Created by Hudson Koyanagi on 9/24/23.
//
#include "../include/utils.h"
#include "./definitions.h"

bool kutils::is_MSb(Word i) {
    return (int)i < 0;
}

Byte kutils::instrToByte(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}
Word kutils::instrToWord(Word instr, Word mask, int shift) {
    return (instr & mask) >> shift;
}

bool kutils::carry(Word unsigned_a, Word unsigned_b, int result) {
    Word sum = unsigned_a + unsigned_b;
    return (sum < unsigned_a) || (sum < unsigned_b);
}

bool kutils::overflow(Word unsigned_a, Word unsigned_b, int result) {
    int signed_a = (int) unsigned_a;
    int signed_b = (int) unsigned_b;

    return (signed_a > 0 && signed_b > 0 && result < 0) || (signed_a < 0 && signed_b < 0 && result > 0);
}