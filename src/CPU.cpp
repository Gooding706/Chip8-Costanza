#include <iostream>
#include <cstdint>
#include <stdint.h>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "CPU.h"

std::uint8_t CHIP8_FONTSET[80] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const std::uint8_t keymap[16] = {
sf::Keyboard::X,   // Key 0
sf::Keyboard::Num1,   // Key 1
sf::Keyboard::Num2,   // Key 2
sf::Keyboard::Num3,   // Key 3
sf::Keyboard::Q,   // Key 4
sf::Keyboard::W,   // Key 5
sf::Keyboard::E,   // Key 6
sf::Keyboard::A,   // Key 7
sf::Keyboard::S,   // Key 8
sf::Keyboard::D,   // Key 9
sf::Keyboard::Z,   // Key A
sf::Keyboard::C,   // Key B
sf::Keyboard::Num4,   // Key C
sf::Keyboard::R,   // Key D
sf::Keyboard::F,   // Key E
sf::Keyboard::V    // Key F
};

enum Register {
  V0,
  V1,
  V2,
  V3,
  V4,
  V5,
  V6,
  V7,
  V8,
  V9,
  VA,
  VB,
  VC,
  VD,
  VE,
  VF,
};

Chip8::Chip8(sf::RenderWindow& window, std::array<std::array<bool, height>, width>& screen) : window(window), screen(screen)
{
    srand(time(NULL));

    PC = 512;
    I = 0;
    for (int i = 0; i < 80; i++)
    {
        memory[i] = CHIP8_FONTSET[i];
    }
}

void Chip8::loadRom(const char* path)
{
  std::fstream f1;
  f1.open(path, std::ios::in | std::ios::binary);
  for (int i = 512; i < MEMORY_SIZE; i++) {
    if (f1.eof()) {
      break;
    }
    f1.read((char *)&memory[i], sizeof(uint8_t));
  }
}



uint16_t Chip8::fetch()
{
    uint8_t opcode_hi = memory[PC];
    uint8_t opcode_lo = memory[PC + 1];
    PC += 2;  // increment PC here

    return (opcode_hi << 8) | opcode_lo;
}

void Chip8::decode(uint16_t opcode)
{
    uint8_t X = (opcode & 0x0F00u) >> 8u;
    uint8_t Y = (opcode >> 4) & 0x0F;
    uint8_t N = opcode & 0x0F;
    uint8_t NN = opcode & 0xFF;
    uint16_t NNN = opcode & 0xFFF;

    //Hold your breath ... giant switch statement approaching
    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x00FF) {
                case 0x00E0:
                    OP_00E0();
                    break;
                case 0x00EE:
                    OP_00EE();
                    break;
          }
          break;
      case 0x1000:
          OP_1NNN(NNN);
          break;
      case 0x2000:
          OP_2NNN(NNN);
          break;
      case 0x3000:
          OP_3XNN(X, NN);
          break;
      case 0x4000:
          OP_4XNN(X, NN);
          break;
      case 0x5000:
          OP_5XY0(X, Y);
          break;
      case 0x6000:
          OP_6XNN(X, NN);
          break;
      case 0x7000:
          OP_7XNN(X, NN);
          break;
      case 0x8000:
          switch (opcode & 0x000F) {
              case 0x0000:
                  OP_8XY0(X, Y);
                  break;
              case 0x0001:
                  OP_8XY1(X, Y);
                  break;
              case 0x0002:
                  OP_8XY2(X, Y);
                  break;
              case 0x0003:
                  OP_8XY3(X, Y);
                  break;
              case 0x0004:
                  OP_8XY4(X, Y);
                  break;
              case 0x0005:
                  OP_8XY5(X, Y);
                  break;
              case 0x0006:
                  OP_8XY6(X, Y);
                  break;
              case 0x0007:
                  OP_8XY7(X, Y);
                  break;
              case 0x000E:
                  OP_8XYE(X, Y);
                  break;
          }
          break;
      case 0x9000:
          OP_9XY0(X, Y);
          break;
      case 0xA000:
          OP_ANNN(NNN);
          break;
      case 0xB000:
          OP_BNNN(NNN);
          break;
      case 0xC000:
          OP_CXNN(X, NN);
          break;
      case 0xD000:
          OP_DXYN(X, Y, N);
          //PC += 2;
          break;
      case 0xE000:
          switch (opcode & 0x00FF) {
              case 0x009E:
                  OP_EX9E(X);
                  break;
              case 0x00A1:
                  OP_EXA1(X);
                  break;
          }
          break;
      case 0xF000:
          switch (opcode & 0x00FF) {
              case 0x0007:
                  OP_FX07(X);
                  break;
              case 0x000A:
                  OP_FX0A(X);
                  break;
              case 0x0015:
                  OP_FX15(X);
                  break;
              case 0x0018:
                  OP_FX18(X);
                  break;
              case 0x001E:
                  OP_FX1E(X);
                  break;
              case 0x0029:
                  OP_FX29(X);
                  break;
              case 0x0033:
                  OP_FX33(X);
                  break;
              case 0x0055:
                  OP_FX55(X);
                  break;
              case 0x0065:
                  OP_FX65(X);
                  break;
                  case 0xF000:
            switch (opcode & 0x00FF) {
                case 0x0007:
                    OP_FX07(X);
                    break;
                case 0x000A:
                    OP_FX0A(X);
                    break;
                case 0x0015:
                    OP_FX15(X);
                    break;
                case 0x0018:
                    OP_FX18(X);
                    break;
                case 0x001E:
                    OP_FX1E(X);
                    break;
                case 0x0029:
                    OP_FX29(X);
                    break;
                case 0x0033:
                    OP_FX33(X);
                    break;
                case 0x0055:
                    OP_FX55(X);
                    break;
                case 0x0065:
                    OP_FX65(X);
                    break;
                default:
                    printf("Unknown opcode: 0x%X\n", opcode);
                    break;
            }
            break;
        default:
            printf("Unknown opcode: 0x%X\n", opcode);
            break;
    }
}
}
void Chip8::push(std::uint16_t value)
{
    if (sp >= stack.size())
    {
        std::cout << "Cities crumble, towns cry you hit a stack overflow\n";
        return;
    }
    stack[sp++] = value;
}

std::uint16_t Chip8::pop()
{
    if (sp == 0)
    {
        std::cout << "you hit a stack underflow\n";
        return 0;
    }
    return stack[--sp];
}

void Chip8::OP_00E0()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            screen[x][y] = false;
        }
    }
}

void Chip8::OP_00EE()
{
    PC = Chip8::pop();
}

void Chip8::OP_EX9E(std::uint8_t X)
{
  if(registers[X] < 16){
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keymap[registers[X]])))
    {
        PC += 0x02; // Skip next instruction if key is pressed
    }
  }
}

void Chip8::OP_EXA1(std::uint8_t X)
{
  if(registers[X] < 16){
    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keymap[registers[X]])))
    {
      return; // Skip next instruction if key is not pressed
    }else{
      PC += 2;
    }
  }
}

void Chip8::OP_FX07(std::uint8_t X)
{
    registers[X] = delay_timer;
}

void Chip8::OP_FX15(std::uint8_t X)
{
    delay_timer = registers[X];
}

void Chip8::OP_FX18(std::uint8_t X)
{
    sound_timer = registers[X];
}

void Chip8::OP_FX1E(std::uint8_t X)
{
    I += registers[X];
}

void Chip8::OP_FX0A(std::uint8_t X)
{
  bool key_pressed = false;

  // Wait for a key press
  while (!key_pressed) {
      // Check for a SFML event
      sf::Event event;
      while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) {
              window.close();
              exit(0);
          }
          else if (event.type == sf::Event::KeyPressed) {
              // Check if the pressed key corresponds to a Chip8 key
              for (int i = 0; i < 16; i++) {
                  if (keymap[i] == event.key.code) {
                      registers[X] = i;
                      key_pressed = true;
                      break;
                  }
              }
          }
      }
  }
}

void Chip8::OP_FX29(std::uint8_t X)
{
  I = registers[X] * 5;
}

void Chip8::OP_FX33(std::uint8_t X)
{
    memory[I] = (registers[X] - (registers[X] % 100))/100;
    memory[I + 1] = ((registers[X] % 100) - ((registers[X] % 100) % 10))/10;
    memory[I + 2] = (registers[X] % 100) % 10;
}


void Chip8::OP_FX55(std::uint8_t X)
{
  uint8_t Vx = X;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		memory[I + i] = registers[i];
	}
}

void Chip8::OP_FX65(std::uint8_t X)
{
    std::uint8_t Vx = X;
    for (std::uint8_t i = 0; i <= Vx; ++i)
    {
        registers[i] = memory[I + i];
    }
}


void Chip8::OP_1NNN(std::uint16_t NNN)
{
  PC = NNN;
}

void Chip8::OP_2NNN(std::uint16_t NNN)
{
  Chip8::push(PC);
  PC = NNN;
}

void Chip8::OP_3XNN(std::uint8_t X, std::uint8_t NN)
{
  if(registers[X] == NN)
  {
    PC += 0x02;
  }
}

void Chip8::OP_4XNN(std::uint8_t X, std::uint8_t NN)
{
  if(registers[X] != NN)
  {
    PC += 0x02;
  }
}

void Chip8::OP_5XY0(std::uint8_t X, std::uint8_t Y)
{
  if(registers[X] == registers[Y])
  {
    PC += 0x02;
  }
}

void Chip8::OP_9XY0(std::uint8_t X, std::uint8_t Y)
{
  if(registers[X] != registers[Y])
  {
    PC += 0x02;
  }
}

void Chip8::OP_6XNN(std::uint8_t X, std::uint8_t NN)
{
  registers[X] = NN;
}

void Chip8::OP_7XNN(std::uint8_t X, std::uint8_t NN)
{
    registers[X] += NN;
}

void Chip8::OP_8XY0(std::uint8_t X, std::uint8_t Y)
{
  registers[X] = registers[Y];
}

void Chip8::OP_8XY1(std::uint8_t X, std::uint8_t Y)
{
 registers[X] |= registers[Y];
}

void Chip8::OP_8XY2(std::uint8_t X, std::uint8_t Y)
{
  registers[X] &= registers[Y];
}

void Chip8::OP_8XY3(std::uint8_t X, std::uint8_t Y)
{
  registers[X] ^= registers[Y];
}

void Chip8::OP_8XY4(std::uint8_t X, std::uint8_t Y)
{
  registers[X] += registers[Y];
}

void Chip8::OP_8XY5(std::uint8_t X, std::uint8_t Y)
{
  if (registers[X] < registers[Y]) {
    registers[0xF] = 0; // borrow occurred
  } else {
    registers[0xF] = 1;
  }
  registers[X] -= registers[Y];
}

void Chip8::OP_8XY7(std::uint8_t X, std::uint8_t Y)
{
  registers[X] = (registers[Y] - registers[X]);
}

void Chip8::OP_8XY6(std::uint8_t X, std::uint8_t Y)
{
  registers[X] = registers[Y];
  registers[VF] = registers[X] & 0x01; // store the least significant bit in VF
  registers[X] >>= 1; // shift VX right by 1 bit
}

void Chip8::OP_8XYE(std::uint8_t X, std::uint8_t Y)
{
  registers[X] = registers[Y];
  registers[VF] = registers[X] >> 7; // store the most significant bit in VF
  registers[X] <<= 1;
}

void Chip8::OP_ANNN(std::uint16_t NNN)
{
  I = NNN;
}

void Chip8::OP_BNNN(std::uint16_t NNN)
{
  PC = registers[V0] + (NNN & 0x0FFF);
}

void Chip8::OP_CXNN(std::uint8_t X, std::uint8_t NN)
{
 registers[X] = (((std::uint8_t)rand()%256) & NN);
}

void Chip8::OP_DXYN(std::uint8_t X, std::uint8_t Y, std::uint8_t N)
{
  registers[VF] = 0;
  for (int yline = 0; yline < N; yline++) {
      std::uint8_t pixel = memory[I + yline];
      for (int xline = 0; xline < 8; xline++) {
          if ((pixel & (0x80 >> xline)) != 0) {
              int xpos = registers[X] + xline;
              int ypos = registers[Y] + yline;
              if (xpos < 64 && ypos < 32) {
                  if (screen[xpos][ypos] == 1) {
                      registers[VF] = 1;
                  }
                  screen[xpos][ypos] ^= 1;
              }
          }
      }
  }
}
