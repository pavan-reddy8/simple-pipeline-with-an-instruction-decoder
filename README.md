

## Simple Pipeline 

Model simple pipeline with the following three stages.  

```
 1 stage for fetch (IF) 
 1 stage for decode (ID) 
 1 stage for execution (EX)  
```
The pipeline supports 4B fixed‐length instructions, which have 1B for opcode, 1B for destination, and 2B 
for two operands. The destination and the left operand are always registers. The right operand can be 
either register or an immediate value.  

```
Opcode (1B)  Destination (1B)  Left Operand (1B)  Right Operand (1B) 
```

The supported instructions have nine different types as follows. The pipeline only supports integer 
arithmetic operations with 16 integer registers (R0 ‐ R15), where each has 4B. All numbers between 0 
and 1 will be discarded (floor).   

```
Mnemonic  Opcode 
```
```
Description 
Destination  Left Operand  Right Operand 
```
```
set  0x00 
```
```
set Rx, #Imm (Set an immediate value to register Rx) 
Register Rx  Immediate value 
```
```
add  0x10 
```
```
add  Rx, Ry, Rz (Compute Rx = Ry + Rz) 
Register Rx  Register Ry  Register Rz 
```
```
add  0x11 
```
```
add  Rx, Ry, #Imm (Compute Rx = Ry + an immediate valve) 
Register Rx  Register Ry  Immediate value 
```
```
sub  0x20 
```
```
sub  Rx, Ry, Rz (Compute Rx = Ry – Rz) 
Register Rx  Register Ry  Register Rz 
```
```
sub  0x21 
```
```
sub  Rx, Ry, #Imm (Compute Rx = Ry ‐ an immediate valve) 
Register Rx  Register Ry  Immediate value 
```
```
mul  0x30 
```
```
mul  Rx, Ry, Rz (Compute Rx = Ry * Rz) 
Register Rx  Register Ry  Register Rz 
```
```
mul  0x31 
```
```
mul  Rx, Ry, #Imm (Compute Rx = Ry * an immediate valve) 
Register Rx  Register Ry  Immediate value 
```
```
div  0x40 
```
```
div  Rx, Ry, Rz (Compute Rx = Ry / Rz) 
Register Rx  Register Ry  Register Rz 
```
```
div  0x41 
```
```
div  Rx, Ry, #Imm (Compute Rx = Ry / an immediate valve) 
Register Rx  Register Ry  Immediate value 
```
An instruction is fetched at the fetch stage. The instruction is decoded at the decode stage, and it is 
executed at the execution stage. The fetch stage fetches one instruction every cycle unless the stage is 
occupied by a stalled instruction. The fetch and decode stage take 1 cycle. However, the execution stage 
requires varied cycles based on instruction types. The set (0x00), add (0x10, 0x11), and sub (0x20, 0x21) 
instructions take  **1 cycle** , mul (0x30, 0x31) instructions take  **2 cycles** , and div (0x40, 0x41) instructions 
take  **4 cycles** .  

Note, this pipeline has no hazards. The registers are read, executed, and updated by one instruction at 
the same stage (no data hazards). Therefore, the pipeline does not need to analyze data dependencies 
between instructions. Also, assume that your register file has two read ports and one write port (no 
structural hazards). Lastly, there are no branch instructions (no control hazards).  






