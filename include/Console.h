//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_CONSOLE_H
#define INC_32BITCOMPUTER_CONSOLE_H
#include "definitions.h"
#include "Memory.h"
class Console {
public:
    Console(Word CONSOLE_MAP_START, Word CONSOLE_MAP_END);
    void print(Memory& mem);
private:
    Word map_start;
    Word map_end;
};


#endif //INC_32BITCOMPUTER_CONSOLE_H
