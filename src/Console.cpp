//
// Created by Hudson Koyanagi on 9/18/23.
//

#include "../include/Console.h"
#include <iostream>

Console::Console(Word CONSOLE_MAP_START, Word CONSOLE_MAP_END) {
    this->map_start = CONSOLE_MAP_START;
    this->map_end = CONSOLE_MAP_END;
}

void Console::print(Memory& mem) {
    for(int i = this->map_start; i < map_end; i+=4) {
        std::cout << (char)mem.DEV_getWord(i);
    }
    std::cout << std::endl;
}