#pragma once
#include <cstdint>
#include <stdint.h>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

class Chip8
{
  private:
    static const std::uint16_t MEMORY_SIZE = 4096; // define MEMORY_SIZE as static const member variable
    std::array<std::uint8_t, MEMORY_SIZE> memory = {0};
    static const int height = 32;
    static const int width = 64;
    std::array<std::array<bool, height>, width>& screen;
    sf::RenderWindow& window;
    std::array<std::uint16_t, 16> stack;  // 16-level stack
    std::uint8_t sp = 0;                      // stack pointer

  public:
    std::uint8_t delay_timer = 0;
    std::uint8_t sound_timer = 0;
    Chip8(sf::RenderWindow& window, std::array<std::array<bool, height>, width>& screen);
    void loadRom(const char* path);
    uint16_t fetch();
    void decode(uint16_t opcode);
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

    void push(std::uint16_t value);
    std::uint16_t pop();
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
  std::uint16_t I;
  std::uint16_t PC;
  std::uint8_t registers[16];

  public:
      // instructions
      void OP_00E0();
      void OP_00EE();
      void OP_EX9E(std::uint8_t X);
      void OP_EXA1(std::uint8_t X);
      void OP_FX07(std::uint8_t X);
      void OP_FX15(std::uint8_t X);
      void OP_FX18(std::uint8_t X);
      void OP_FX1E(std::uint8_t X);
      void OP_FX0A(std::uint8_t X);
      void OP_FX29(std::uint8_t X);
      void OP_FX33(std::uint8_t X);
      void OP_FX55(std::uint8_t X);
      void OP_FX65(std::uint8_t X);
      void OP_1NNN(std::uint16_t NNN);
      void OP_2NNN(std::uint16_t NNN);
      void OP_3XNN(std::uint8_t X, std::uint8_t NN);
      void OP_4XNN(std::uint8_t X, std::uint8_t NN);
      void OP_5XY0(std::uint8_t X, std::uint8_t Y);
      void OP_9XY0(std::uint8_t X, std::uint8_t Y);
      void OP_6XNN(std::uint8_t X, std::uint8_t NN);
      void OP_7XNN(std::uint8_t X, std::uint8_t NN);
      void OP_8XY0(std::uint8_t X, std::uint8_t Y);
      void OP_8XY1(std::uint8_t X, std::uint8_t Y);
      void OP_8XY2(std::uint8_t X, std::uint8_t Y);
      void OP_8XY3(std::uint8_t X, std::uint8_t Y);
      void OP_8XY4(std::uint8_t X, std::uint8_t Y);
      void OP_8XY5(std::uint8_t X, std::uint8_t Y);
      void OP_8XY7(std::uint8_t X, std::uint8_t Y);
      void OP_8XY6(std::uint8_t X, std::uint8_t Y);
      void OP_8XYE(std::uint8_t X, std::uint8_t Y);
      void OP_ANNN(std::uint16_t NNN);
      void OP_BNNN(std::uint16_t NNN);
      void OP_CXNN(std::uint8_t X, std::uint8_t NN);
      void OP_DXYN(std::uint8_t X, std::uint8_t Y, std::uint8_t N);
};
