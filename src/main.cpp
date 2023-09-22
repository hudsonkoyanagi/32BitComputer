#include "../include/CPU.h"
#include "../include/Console.h"
#include <iostream>


class RenderWindow;

int main() {
    // 400 byte console map
    const Word CONSOLE_MAP_START = 0xE000;
    const Word CONSOLE_MAP_END = 0xE640;
    Console console = Console(CONSOLE_MAP_START, CONSOLE_MAP_END);

    CPU cpu = CPU();
    Memory mem = Memory();
    cpu.reset(mem);


    cpu.setFlags(0,1,1,0);

    int CYCLES = 8;
    bool DEBUG = true;

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
