#include <LiquidCrystal.h>
/*
 * 8-bit Computer Programmer with LCD Display
 * Arduino UNO + 74HC595 Shift Registers + 16x2 LCD
 * 
 * Pin Configuration:
 */

// Pin definitions for shift registers
#define SHIFT_CLK   2   // -> Shift Register Clock (SRCLK)
#define LATCH_CLK   3   // -> Output Register Clock (RCLK/Latch)
#define DATA_PIN    4   // -> Serial Data Input (SER)
#define WRITE_PIN   5  // -> Write Enable (to RAM) : Active LOW

// Pin definitions for LCD 
#define DB7 8           
#define DB6 9           
#define DB5 10
#define DB4 11 
#define E   12          // -> LCD E (Enable)
#define RS  13          // -> LCD RS (Register Select)

// Opcode table
// modify the table based on your opocode structure
#define NOP 0b00000000
#define LDA 0b00010000
#define ADD 0b00100000
#define SUB 0b00110000
#define STA 0b01000000
#define LDI 0b01010000
#define JMP 0b10000000
#define JC  0b10010000
#define JZ  0b10100000
#define OUT 0b11100000
#define HLT 0b11110000

LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);

// Program to load into RAM
// Format: {address, instruction}
const byte program[][2] = {
  {0x0, 0x00}, 
  {0x1, 0x00}, 
  {0x2, 0x00}, 
  {0x3, 0x00},  
  {0x4, 0x00},
  {0x5, 0x00},  
  {0x6, 0x00},  
  {0x7, 0x00},  
  {0x8, 0x00},
  {0x9, 0x00},  
  {0xA, 0x00},  
  {0xB, 0x00}, 
  {0xC, 0x00},  
  {0xD, 0x00},  
  {0xE, 0x00},  
  {0xF, 0x01}   
};

const int programSize = sizeof(program) / sizeof(program[0]);

void setup() {
  // Initialize pins
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(LATCH_CLK, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(WRITE_PIN, OUTPUT);

  digitalWrite(SHIFT_CLK, LOW);
  digitalWrite(LATCH_CLK, LOW);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(WRITE_PIN, HIGH);  // active LOW

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("8-bit Computer");
  lcd.setCursor(0, 1);
  lcd.print("Programmer v1.0");

  delay(1000);
  lcd.clear();

  // Program the RAM
  programRAM();

  // Display completion message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Program written:");
  lcd.setCursor(0, 1);
  // your program name
  lcd.print("X");

}

void loop() {
}

void programRAM() {
  for (int i = 0; i < programSize; i++) {
    byte address = program[i][0];
    byte instruction = program[i][1];

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Address: 0x");
    if (address < 0x10) lcd.print("0");
    lcd.print(address, HEX);

    lcd.setCursor(0, 1);
    lcd.print("Code: 0x");
    lcd.print(instruction, HEX);

    shiftOut12Bits(address, instruction);

    delay(250);
    digitalWrite(WRITE_PIN, LOW);
    delay(100); 
    digitalWrite(WRITE_PIN, HIGH);
    delay(250);  
  }
}

void shiftOut12Bits(byte address, byte instruction) {
  digitalWrite(LATCH_CLK, LOW);

  // Shift out ADDRESS first (4 bits) - goes to second shift register
  for (int i = 3; i >= 0; i--) {
    digitalWrite(DATA_PIN, (address >> i) & 0x01);
    delay(10);  // Slow down for visibility
    digitalWrite(SHIFT_CLK, HIGH);
    delay(10);
    digitalWrite(SHIFT_CLK, LOW);
  }

  // Shift out INSTRUCTION (8 bits) - stays in first shift register
  for (int i = 7; i >= 0; i--) {
    digitalWrite(DATA_PIN, (instruction >> i) & 0x01);
    delay(10);  // Slow down for visibility
    digitalWrite(SHIFT_CLK, HIGH);
    delay(10);
    digitalWrite(SHIFT_CLK, LOW);
  }

  digitalWrite(LATCH_CLK, HIGH);
  delay(10);
  digitalWrite(LATCH_CLK, LOW);
}