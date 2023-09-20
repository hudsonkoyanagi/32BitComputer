cmake_minimum_required(VERSION 3.26)
project(32BitComputer)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)
include_directories(include)

include_directories(/opt/homebrew/Cellar/sfml/2.6.0/include)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(/opt/homebrew/Cellar/sfml/2.6.0/include)


add_executable(32BitComputer src/main.cpp
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

target_link_libraries(32BitComputer sfml-graphics sfml-window sfml-system)