#include <iostream>
#include "box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <unistd.h>

#include "src/game.h"

int main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 1020), "My window");

    BasicGame game = BasicGame(2);
    game.start();

    float want_fps = 60;
    sf::Clock loop_timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.tank_rotate(0, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.tank_rotate(0, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game.tank_move(0, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game.tank_move(0, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            game.tank_rotate(1, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            game.tank_rotate(1, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            game.tank_move(1, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            game.tank_move(1, 1);
        }

        // physics step()
        game.step(1.f / want_fps);

        // render
        game.debug_draw(window);

        sf::Int32 frame_duration = loop_timer.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / want_fps) - frame_duration;
        if (time_to_sleep > 0)
        {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        loop_timer.restart();
    }

    return 0;
}

// just test that libraries includes correctly

signed main()
{
    // game();
    main_loop();

    std::cout << "done" << std::endl;
    return 0;
}
