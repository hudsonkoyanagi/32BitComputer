#include "../include/CPU.h"
#include "../include/Console.h"
#include "../include/utils.h"
#include <iostream>



int main() {
    // 400 byte console map
    const Word CONSOLE_MAP_START = 0xE000;
    const Word CONSOLE_MAP_END = 0xE640;

    CPU cpu = CPU();
    Memory mem = Memory();
    cpu.reset(mem, 0x0FFF);
    cpu.registers[1] = UINT32_MAX;
    mem.DEV_storeWord(0x1008, 0b00000101101001000000000000011111);


    int CYCLES = 4;
    bool DEBUG = true; // change to macro def or move to settings?

    for(int i = 0; i < CYCLES; i++) {
        if(DEBUG) {
            std::cout << "cycle: " << i << std::endl;
            cpu.DEV_printReg();
        }
        cpu.fetch(mem, DEBUG);
        cpu.execute(mem, DEBUG);
        if(DEBUG) std::cout << "\n";
    }
    return 0;
}
