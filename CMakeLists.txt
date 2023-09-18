cmake_minimum_required(VERSION 3.26)
project(32BitComputer)

set(CMAKE_CXX_STANDARD 17)

add_executable(32BitComputer main.cpp
        src/Memory.cpp
        include/Memory.h
        src/CPU.cpp
        include/CPU.h
        src/Console.cpp
        include/Console.h
        src/Registers.cpp
        include/Registers.h
        include/definitions.h
        include/masks.h
        include/opcodes.h
)
