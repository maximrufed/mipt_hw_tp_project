#include <iostream>
#include "box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <unistd.h>

#include "src/game.h"

int main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 1020), "My window");

    BasicGame game = BasicGame();
    game.start(2);

    float want_fps = 60;
    sf::Clock loop_timer;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            // key pressed
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                {
                    game.tank_fire(0);
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    game.tank_fire(1);
                }
                break;

            // we don't process other types of events
            default:
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        // -----------------------------First Tank----------------------------------------------

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

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        // {
        //     game.tank_fire(0);
        // }

        // -----------------------------Second Tank----------------------------------------------

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

        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        // {
        //     game.tank_fire(1);
        // }

        // -------------------------------------------------------------------------

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
