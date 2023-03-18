#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CPU.h"
#include <array>
#include <iostream>

int main()
{
    const int width = 64;
    const int height = 32;

    // Initialize the screen as a 2D boolean array
    std::array<std::array<bool, height>, width> screen = {{false}};
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    sf::SoundBuffer buffer;
    buffer.loadFromFile("Audio/sound.wav");
    sf::Sound Beep;
    Beep.setBuffer(buffer);
    Beep.setLoop(true);
    Chip8 Cpu(window, screen);
    Cpu.loadRom("Roms/Pong (alt).ch8");
    //Cpu.loadRom("Roms/IBM Logo.ch8");
    //Cpu.loadRom("Roms/SCTEST.CH8");
    //Cpu.loadRom("Roms/tetris.ch8");
    //Cpu.loadRom("Roms/test_opcode.ch8");
    //Cpu.decode(0xF065);
    //Cpu.loadRom("Roms/chip8-test-suite.ch8");
    //Cpu.loadRom("Roms/random_number_test.ch8");
    //Cpu.loadRom("Roms/Maze (alt) [David Winter, 199x].ch8");
    //Cpu.decode(Cpu.fetch());
    //Cpu.fetch();

    //Cpu.OP_6XNN(3, 152);
    //Cpu.OP_FX33(3);
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
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        const int pixelSize = 1;
        const float pixelGap = 0;

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                if (screen[x][y])
                {
                    sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
                    pixel.setFillColor(sf::Color::White);
                    pixel.setPosition(x * (pixelSize + pixelGap), y * (pixelSize + pixelGap));
                    window.draw(pixel);
                }
            }
        }


        // Add fetch and decode calls
        for (int i = 0; i < 10; i++)
        {
            Cpu.decode(Cpu.fetch());
        }

        window.display();
    }

    return 0;
}
