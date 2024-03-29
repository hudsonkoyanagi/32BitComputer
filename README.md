For time being, store instructions manually using the DEV insert and update cycle count for number of instructions.
Memory size can be modified in include/settings.h
##  "Hardware"
___


8 general purpose registers (R0-R7)  
Instruction Register (IR)  
Program Counter (PC)  
Link Register (LR)   
Stack Pointer (SP)

32 bit data bus / word size  
32 bit address bus

Flags: C, V, N, Z

PC starts at 0x1000

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

< op>{S} Rd, Rs  (Rd += Rs)
0000 0000   00   S   ddd   sss  ZZZ ZZZZ ZZZZ ZZZZ

< op>{S} Rd, Rs, Rs  (Rd = Rs + Rs
0000 0000   01   S   ddd   sss  sss ZZZZ ZZZZ ZZZZ

< op>{S} Rd, imm16 (Rd += imm16)
0000 0000   10   S   ddd   ZZ   iiii iiii iiii iiii 

< op>{S} Rd, Rs, imm12 ( Rd = Rs + imm12 )  
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

CMV
1111 0000 0 ddd Z sss COND ZZZZ ZZZ ZZZZ
1111 0000 1 ddd ZZZZ  COND ZZZZ iiii iiii

### LDR #11, 0x0B
Load data from memory into register.  
(Register indirect addressing only)
Data Types:
* (W)ord 32bits (default)
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
___
## Control Flow

### JMP #13, 0x0D
Set PC to specified address with option to set LR to current PC + 4 (i.e. link). 
Signed 12 bit immediate offset to register value also available.
Variants:
* JMP{L} Rd  
  0000 1101 L ddd 0 ZZZ COND ZZZZ ZZZZ zZZZZ
* JMP{L} Rd, off12  
  0000 1101 L ddd 1 ZZZ COND iiii iiii iiii

Conditions (COND):
* 0000: JMP  
  *Direct Flag Checks*:
* 0001: JZ : Z = 1
* 0010: JNZ : Z = 0
* 0011: JN : N = 1
* 0100: JC : C = 1
* 0101: JV : V = 1
* 0110:
* 0111:   
  *Signed*:
* 1000: JGT : Z = 0 & N = V
* 1001: JLT : N != V
* 1010: JGE : N = V
* 1011: JLE : Z = 1 | N != V  
  *Unsigned*:
* 1100: JHI : C = 1 & Z = 0
* 1101: JLO : C = 0
* 1110: JHE : C = 1
* 1111: JLE : C = 0 OR Z = 1

### RET #14, 0x0E
Return from subroutine by jumping to address in LR (does not clear LR)

0000 1110 ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ


___
## Stack
### PUSH (#16, 0x10) and POP (#17, 0x11)
Registers are encoded using a bit mask. R0 is the LSB and R15 is MSB in the 16 bit R mask.
example:
  PUSH {R1-R10} => 0000 0011 1111 1111
Push a value onto stack from a register.
Pop a value off the stack and into a register.

The stack is a empty ascending stack, this means the SP is always pointing to an empty value and SP - 4 is the top of stack

0001 0000 ZZZZ ZZZZ RRRR RRRR RRRR RRRR   

0001 0001 ZZZZ ZZZZ RRRR RRRR RRRR RRRR

### PSLR (#18, 0x12) 
Push link register onto the stack.
0001 0010 ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ

(could be combined into normal PUSH/POP, plenty of empty space)

### PPLR (#19, 0x13) 
Pop the current stack value in the LR.
0001 0011 ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ ZZZZ

### CMP (#20, 0x14)
Sets flags based on the result of the signed subtraction of R1 - R2
0001 0100 Z111 Z222 0000 0000 0000 0000



TODOS:
- Add jump by signed offset
- Compare instr
- Signed ALU ops
- 64 bit mult and div
- floating point ops
- ROM with start up code??
- addressing modes?
  - how much mem to use?
- IO:
  - keyboard
  - terminal
  - 