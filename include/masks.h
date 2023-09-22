//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_MASKS_H
#define INC_32BITCOMPUTER_MASKS_H
#include "definitions.h"

const Word OP_CODE_MASK = 0xFF000000;

const Word MOV_FUN_MASK = 0x00800000;
const Word MOV_RGD_MASK = 0x00700000;
const Word MOV_RGS_MASK = 0x00070000;
const Word MOV_IMM_MASK = 0x0000FFFF;

const Word LDR_FUN_MASK = 0x00800000;
const Word LDR_RGD_MASK = 0x00700000;
const Word LDR_TYP_MASK = 0x000F0000;
const Word LDR_RSD_MASK = 0x00007000;
const Word LDR_I12_MASK = 0x00000FFF;
const Word LDR_I16_MASK = 0x0000FFFF;

const Byte LDR_WORD = 0x02; //can be mult by 2 for num bytes
const Byte LDR_HALF = 0x01; //can be mult by 2 for num bytes
const Byte LDR_BYTE = 0x00;

const Word JMP_LNK_MASK = 0x00800000;
const Word JMP_RGD_MASK = 0x00700000;
const Word JMP_OFF_MASK = 0x0000FFFF;
const Word JMP_FUN_MASK = 0x00080000;
const Word JMP_CND_MASK = 0x0000F000;

const Word ALU_OP_MASK = 0xFF000000;
const Word ALU_FN_MASK = 0x00C00000;
const Word ALU_S_MASK  = 0x00200000;
const Word ALU_RD_MASK = 0x001C0000;

const Word ALU_RS1_MASK = 0x00038000;
const Word ALU_RS2_MASK = 0x00007000;
const Word ALU_I16_MASK = 0x0000FFFF;
const Word ALU_I12_MASK = 0x00000FFF;

#endif //INC_32BITCOMPUTER_MASKS_H
