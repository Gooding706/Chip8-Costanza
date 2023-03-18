#include "CPU.h"

class Gui
{
  private:
  int selected_file_index = 0;
  Chip8& Cpu;
  sf::RenderWindow& window;
  public:
    bool show_popup = true;
    float backgroundColor[3] = {0, 0, 0};
    float pixelColor[3] = {1, 1, 1};
    int instructionsPerFrame = 10;
    const int pixelSize = 1280/64;
    const float pixelGap = 0;
  public:
    Gui(Chip8& Cpu, sf::RenderWindow& window);
    void Popup();
};
