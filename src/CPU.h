#pragma once
#include <cstdint>
#include <stdint.h>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

class Chip8
{
  private:
    //private variables
    static const std::uint16_t MEMORY_SIZE = 4096; //the ram size of the chip8
    std::array<std::uint8_t, MEMORY_SIZE> memory = {0}; //memory array
    static const int height = 640; //screen height
    static const int width = 1280; //screen width
    std::array<std::array<bool, height>, width>& screen; //Screen bool array
    sf::RenderWindow& window; //Sfml window
    std::array<std::uint16_t, 16> stack;  // 16-level stack
    std::uint8_t sp = 0;  // stack pointer
    std::uint16_t I; //index register (12 bits on the hardware, 16 bits for emulation sake)
    std::uint16_t PC; //Program counter, defines memory adress of current instruction
    std::uint8_t registers[16] = {0}; //16 registers for the chip8
  public:
    //Public variables
    std::uint8_t delay_timer = 0;//used to delay specific events
    std::uint8_t sound_timer = 0;//used to specify how long sounds will play for

  public:
    //Emulation functions
    Chip8(sf::RenderWindow& window, std::array<std::array<bool, height>, width>& screen);
    void loadRom(const char* path);
    uint16_t fetch();
    void decode(uint16_t opcode);

  public:
    //stack functions
    void push(std::uint16_t value);
    std::uint16_t pop();


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
