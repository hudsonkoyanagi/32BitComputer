#include "include/CPU.h"
#include "include/Memory.h"
#include "include/Console.h"
#include <iostream>


int main() {
    // 400 byte console map
    const Word CONSOLE_MAP_START = 0xE000;
    const Word CONSOLE_MAP_END = 0xE640;
    Console console = Console(CONSOLE_MAP_START, CONSOLE_MAP_END);

    CPU cpu = CPU();
    Memory mem = Memory();
    cpu.reset(mem);

    for(int i = CONSOLE_MAP_START; i < CONSOLE_MAP_END; i+=4) {
        mem.DEV_storeWord(i, 72);
    }

    mem.DEV_storeWord(0x1110,0xA); // load array starting at 0x1110
    mem.DEV_storeWord(0x1114,0xB); //  [A, B, C, D]
    mem.DEV_storeWord(0x1118,0xC);
    mem.DEV_storeWord(0x111C,0xD);

    mem.DEV_storeWord(0x1004, 0b00001010111000000001000100010000); // MOV R6, 0x1110

    mem.DEV_storeWord(0x1008, 0b00001011000100100110000000000000); // LDR R1, R6
    mem.DEV_storeWord(0x100C, 0b00000101100110000000000000000100); // ADD R6, #4

    mem.DEV_storeWord(0x1010, 0b00001011001000100110000000000000); // LDR R2, R6
    mem.DEV_storeWord(0x1014, 0b00000101100110000000000000000100); // ADD R6, #4

    mem.DEV_storeWord(0x1018, 0b00001011001100100110000000000000); // LDR R3, R6
    mem.DEV_storeWord(0x101C, 0b00000101100110000000000000000100); // ADD R6, #4

    mem.DEV_storeWord(0x1020, 0b00001011010000100110000000000000); // LDR R4, R6
    int CYCLES = 8;
    for(int i = 0; i < CYCLES; i++) {
        cpu.fetch(mem);
        cpu.execute(mem);
        console.print(mem);
        //cpu.DEV_printReg();
    }
    return 0;

    return 0;
}
