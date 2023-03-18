#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "CPU.h"
#include "fileStructure.h"
#include "gui.h"
#include <array>
#include <iostream>

int main()
{
    const int width = 1280;
    const int height = 640;

    // Initialize the screen as a 2D boolean array
    std::array<std::array<bool, height>, width> screen = {{false}};
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    sf::SoundBuffer buffer;
    buffer.loadFromFile("Audio/sound.wav");
    sf::Sound Beep;
    Beep.setBuffer(buffer);
    Beep.setLoop(true);

    Chip8 Cpu(window, screen);
    Gui popup(Cpu, window);

    ImGui::SFML::Init(window);
    sf::Clock deltaClock;
    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        if (Cpu.delay_timer > 0)
        {
          Cpu.delay_timer -=1;
        }

        if (Cpu.sound_timer > 0)
        {
          if(Beep.getStatus() != sf::Sound::Status::Playing)
            Beep.play();
          Cpu.sound_timer -=1;
        }else{
          Beep.stop();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }


        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear(sf::Color(popup.backgroundColor[0]*255, popup.backgroundColor[1]*255, popup.backgroundColor[2]*255));
        popup.Popup();
        // Add fetch and decode calls
        if(!popup.show_popup)
        {
          for (int x = 0; x < width; x++)
          {
              for (int y = 0; y < height; y++)
              {
                  if (screen[x][y])
                  {
                      sf::RectangleShape pixel(sf::Vector2f(popup.pixelSize, popup.pixelSize));
                      pixel.setFillColor(sf::Color(popup.pixelColor[0]*255, popup.pixelColor[1]*255, popup.pixelColor[2]*255));
                      pixel.setPosition(x * (popup.pixelSize + popup.pixelGap), y * (popup.pixelSize + popup.pixelGap));
                      window.draw(pixel);
                  }
              }
          }

          for (int i = 0; i < popup.instructionsPerFrame; i++)
          {
              Cpu.decode(Cpu.fetch());
          }
        }
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
