//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_OPCODES_H
#define INC_32BITCOMPUTER_OPCODES_H
#include "definitions.h"

static constexpr Byte INS_AND = 0x00;
static constexpr Byte INS_ORR = 0x01;
static constexpr Byte INS_XOR = 0x02;
static constexpr Byte INS_LSL = 0x03;
static constexpr Byte INS_LSR = 0x04;
static constexpr Byte INS_ADD = 0x05;
static constexpr Byte INS_SUB = 0x06;
static constexpr Byte INS_MLT = 0x07;
static constexpr Byte INS_DIV = 0x08;
static constexpr Byte INS_ASR = 0x09;

static constexpr Byte INS_MOV = 0x0A;
static constexpr Byte INS_LDR = 0x0B;
static constexpr Byte INS_STR = 0x0C;

static constexpr Byte INS_JMP = 0x0D;

static constexpr Byte INS_RET = 0x0E;

static constexpr Byte INS_PUSH = 0x10;
static constexpr Byte INS_POP = 0x11;

#endif //INC_32BITCOMPUTER_OPCODES_H
