# 8-bit Computer Programmer
Arduino-based programmer dedicated for Ben Eater's 8-bit computer using 74595 shift registers and LCD display. The Programmer Outputs 12-bit serial data (address + instruction) and write them to RAM and MAR, making the programming process less cumbersome after each time the 8-bit computer is powered.


<p align="center">
   <img alt="8-bit-computer-programmer" src="https://github.com/user-attachments/assets/2b7561d6-50e1-446a-b6b5-1b24f653d860" />
</p>

## Hardware Requirements
* MCU: Arudino board
* ICs: 2 74595 shift registers
* Display: LCD (optional)

## Architecture of Ben Eater's 8-bit Computer
<p align="center">
   <img width="492" height="337" alt="arch" src="https://github.com/user-attachments/assets/c7fa59af-64d2-4c20-8c4a-61f19a1e94fe" />
</p>

> Info: [Build an 8-bit computer from scratch](https://eater.net/8bit)

## Usage
1. Build the programmer, and wire the shift register output bits to the MAR (4-bit) and RAM (8-bit) inputs, and connect the write enable pin to the write enable input. You may refer to this simulation design. 
> Tinkercad link: [8-bit Computer Programmer](https://www.tinkercad.com/things/5tZBPNd5JHZ/editel?returnTo=%2Fdashboard%2Fdesigns%2Fall&sharecode=fxdi010d1odySHfv4QmJEMUSlhq75w0uU7A7xYLqcXM)
<img width="805" height="500" alt="programmer-tinker" src="https://github.com/user-attachments/assets/39bed15e-2138-4744-a8a0-2a25a89807d5" />
Make sure the 8-bit computer and the programmer share a common ground reference.
> 
2. Modify the opcode table in the arduino program file based on your opocode structure. e.g.,
```
#define LDA 0b00010000
#define ADD 0b00100000
#define SUB 0b00110000
#define STA 0b01000000
#define LDI 0b01010000
```
3. Write your assembly code in the arduino program file and load into the RAM. e.g.,
```
{0x0, ADD|0x0f},  // ADD 15
{0x1, OUT},  
{0x2, JMP},  
...
```
## Completion
![final](https://github.com/user-attachments/assets/32520546-81d9-4271-9890-3a11390856d2)
