#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#include "box2d/box2d.h"
#include "src/game.h"

int s1 = 0, s2 = 0;

int main_loop(sf::RenderWindow& window) {
    BasicGame game = BasicGame();
    game.start(2);

    float want_fps = 60;
    sf::Clock loop_timer;

    int gameState = 0;
    sf::Clock timerEnd;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                    // key pressed
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space) {
                        game.tank_fire(0);
                    } else if (event.key.code == sf::Keyboard::Q) {
                        game.tank_fire(1);
                    }
                    break;

                    // we don't process other types of events
                default:
                    break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // -----------------------------First Tank----------------------------------------------

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            game.tank_rotate(0, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            game.tank_rotate(0, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            game.tank_move(0, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            game.tank_move(0, 1);
        }

        // -----------------------------Second Tank----------------------------------------------

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            game.tank_rotate(1, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            game.tank_rotate(1, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            game.tank_move(1, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
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

        // draw scoreboard
        sf::Font font;  //шрифт
        font.loadFromFile("../data/CyrilicOld.ttf");
        sf::Text text(std::to_string(s1), font, 50);
        text.setPosition(50, 650);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        window.draw(text);

        text.setPosition(750, 650);
        text.setString(std::to_string(s2));
        text.setFillColor(sf::Color::Blue);
        window.draw(text);

        window.display();

        sf::Int32 frame_duration = loop_timer.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / want_fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        loop_timer.restart();

        int res = game.getResult();

        if (gameState == 1) {
            if (timerEnd.getElapsedTime().asSeconds() >= 4) {
                if (res == 1 || res == 2) {
                    return res;
                } else if (res == -1) {
                    return 0;
                }
            }
        }
        if (gameState == 0) {
            if (res != 0) {
                gameState = 1;
                timerEnd.restart();
            }
        }
    }

    return 0;
}

// just test that libraries includes correctly

signed main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1020), "My window");

    while (true) {
        int res = main_loop(window);
        if (res == 1) {
            s1++;
        } else if (res == 2) {
            s2++;
        }

        if (!window.isOpen())
            break;
    }

    std::cout << "done" << std::endl;
    return 0;
}
