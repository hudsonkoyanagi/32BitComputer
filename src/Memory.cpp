//
// Created by Hudson Koyanagi on 9/18/23.
//

#include "../include/Memory.h"
#include <cassert>
#include <iostream>


Byte Memory::operator[]( Word addr) {
    assert(addr <= MEM_SIZE);
    return data[addr];
}

void Memory::DEV_storeWord(Word addr, Word val) {

    data[addr] =  (val >> 24) & 0xFF;
    data[addr+1] = (val >> 16) & 0xFF;
    data[addr+2] = (val >> 8) & 0xFF;
    data[addr+3] = val & 0xFF;
}

Word Memory::DEV_getWord(Word addr) {
    assert(addr <= MEM_SIZE-4);
    return (data[addr] << 24) + (data[addr+1] << 16) + (data[addr+2] << 8) + data[addr+3];
}

void Memory::clear() {
    for(Byte& b : data) b = 0;
}

Word Memory::retrieveBySize(Word addr, uint8_t size) {
    assert(size <= 4);
    if(size == 0) size++;
    Word result = 0;
    for(int i = 0; i < size; i++) {
        result += (data[addr+i]) << ((size-i-1)*8);
    }
    std::cout << "Retrieved: " << result << std::endl;
    std::cout << "At address : " << addr << std::endl;
    std::cout << "Of size: " << (int)size << std::endl;
    return result;
}

void Memory::storeWord(Word addr, Word val) {
    assert(addr <= MEM_SIZE-4);
    data[addr] =  (val >> 24) & 0xFF;
    data[addr+1] = (val >> 16) & 0xFF;
    data[addr+2] = (val >> 8) & 0xFF;
    data[addr+3] = val & 0xFF;
}