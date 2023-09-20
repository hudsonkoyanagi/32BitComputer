For time being, store instructions manually using the DEV insert and update cycle count for number of instructions.

##  "Hardware"
___
8 general purpose registers (R0-R7)  
Instruciton Register (IR)  
Program Counter (PC)  
Link Register (LR)   
Stack Pointer (SP)

32 bit data bus / word size  
32 bit address bus


## ALU Operations
___
Op Codes:
* AND = 0x00
* ORR = 0x01
* XOR = 0x02
* LSL = 0x03
* LSR = 0x04
* ADD = 0x05
* SUB = 0x06
* MLT = 0x07
* DIV = 0x08
* ASR = 0x09

Functions:
* Rd, Rs (0b00)
* Rd, Rs, Rs (0b01)
* Rd, imm (0b10)
* Rd, Rs, imm (0b11)

< op>{S} Rd, Rs  
0000 0000   00   S   ddd   sss  ZZZ ZZZZ ZZZZ ZZZZ

< op>{S} Rd, Rs, Rs  
0000 0000   01   S   ddd   sss  sss ZZZZ ZZZZ ZZZZ

< op>{S} Rd, imm16     
0000 0000   10   S   ddd   ZZ   iiii iiii iiii iiii

< op>{S} Rd, Rs, imm12 | Rd = Rs + imm12  
0000 0000   11   S   ddd   sss  ZZZ iiii iiii iiii
## Data Movement
___
### MV, #10, 0x0A
Move data between registers or out immediate value in a register

Variants:
* MOV Rd, Rs  
  0000 1010 0 ddd Z sss ZZZZ ZZZZ ZZZZ ZZZZ

* MOV Rd, imm20  
  0000 1010 1 ddd iiii iiii iiii iiii iiii

### LDR #11, 0x0B
Load data from memory into register.  
Register indirect only
Data Types:
* (W)ord 32bits
* (B)yte 8bits
* (H)half word 16 bits

Variants:
* LDR{type} Rd, Rs
  0000 1011 0 ddd tttt Z SSS ZZZZ ZZZZ ZZZZ
* LDR{type} Rd, Rs, #off12  
  0000 1011 1 ddd tttt Z sss iiii iiii iiii

### STR #12, 0x0C
Store value in register into memory (value from Rd into address in Rs)  
Variants:
* STR Rd, Rs   
  00000 1100 0 ddd tttt Z sss ZZZZ ZZZZ ZZZZ
* STR Rd, Rs, #off16
  00000 1100 1 ddd tttt Z sss iiii iiii iiii
## Control Flow

### JMP #13, 0x0D
Set PC to specified address with option to link
Variants:
* JMP{L} Rd  
  0000 1101 L ddd 0 ZZZ ZZZZ ZZZZ ZZZZ zZZZZ
* JMP{L} Rd, off16  
  0000 1101 L ddd 1 ZZZ iiii iiii iiii iiii

