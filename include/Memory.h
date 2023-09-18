//
// Created by Hudson Koyanagi on 9/18/23.
//

#ifndef INC_32BITCOMPUTER_MEMORY_H
#define INC_32BITCOMPUTER_MEMORY_H
#include "definitions.h"

class Memory {
public:
    static constexpr unsigned int MEM_SIZE = 256* 256; // 2^16 limit to not abuse memory
    Byte operator[](Word addr);

    // addr: initial offset
    // size: number of bytes, max = 4
    // will treat size=0 as a size=1
    Word retrieveBySize(Word addr, uint8_t size);
    void storeWord(Word addr, Word val);

    void clear();

    void DEV_storeWord(Word addr, Word val);
    Word DEV_getWord(Word addr);
private:
    Byte data[MEM_SIZE];
};


#endif //INC_32BITCOMPUTER_MEMORY_H
