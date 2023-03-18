#include <SFML/Graphics.hpp>
#include "CPU.h"
#include <array>
#include <iostream>

int main()
{
    const int width = 500;
    const int height = 500;

    // Initialize the screen as a 2D boolean array
    std::array<std::array<bool, height>, width> screen = {{false}};
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");

    Chip8 Cpu(window, screen);
    //Cpu.loadRom("Pong (alt).ch8");
    Cpu.loadRom("IBM Logo.ch8");
    //Cpu.loadRom("SCTEST.CH8");
    //Cpu.loadRom("tetris.ch8");
    //Cpu.loadRom("test_opcode.ch8");
    //Cpu.loadRom("random_number_test.ch8");
    //Cpu.loadRom("Maze (alt) [David Winter, 199x].ch8");
    //Cpu.decode(Cpu.fetch());
    //Cpu.fetch();



    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        if (Cpu.delay_timer > 0)
        {
          Cpu.delay_timer -=1;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        const int pixelSize = 10;
        const int pixelGap = 1;

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
                else
                {
                    // Draw a black pixel
                    sf::RectangleShape pixel(sf::Vector2f(pixelSize, pixelSize));
                    pixel.setFillColor(sf::Color::Black);
                    pixel.setPosition(x * (pixelSize + pixelGap), y * (pixelSize + pixelGap));
                    window.draw(pixel);
                }
            }
        }


        // Add fetch and decode calls
        for (int i = 0; i < 100; i++)
        {
            Cpu.decode(Cpu.fetch());
        }

        window.display();
    }

    return 0;
}
