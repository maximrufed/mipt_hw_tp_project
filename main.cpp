#include <iostream>
#include <memory>
#include "box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <filesystem>

#include "game.h"
#include "basic_sfml_graphics.h"
#include "sfml_event_manager.h"

int s[4];

int main_loop(std::shared_ptr<Graphics> graphics, std::shared_ptr<EventManager> manager, int nTanks) {
    auto game = std::make_shared<BasicGame>(graphics);
    manager->setGame(game);
    game->start(nTanks);
    float want_fps = 60;
    sf::Clock loop_timer;

    int gameState = 0;
    sf::Clock timerEnd;

    while (graphics->isOpen()) {
        manager->input();

        // physics step()
        game->step(1.f / want_fps);

        // render
        game->draw();

        graphics->setScore(std::vector<int>(s, s + nTanks));
        
        graphics->display();

        sf::Int32 frame_duration = loop_timer.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / want_fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        loop_timer.restart();

        int res = game->getResult();

        if (gameState == 1) {
            if (timerEnd.getElapsedTime().asSeconds() >= 4) {
                if (res > 0) {
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

int main(int argc, char** argv) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1400, 1200), "Tanks in Labyrinth", sf::Style::Default, settings);
    auto graphics = std::make_shared<BasicSfmlGraphics>(window, std::filesystem::path(argv[0]).parent_path().string());
    auto manager = std::make_shared<SfmlEventManager>(window);
    int nTanks = graphics->menu(4);
    while (true) {
        int res = main_loop(graphics, manager, nTanks);
        if (res != 0) {
            s[res - 1]++;
        }

        if (!graphics->isOpen())
            break;
    }

    std::cout << "done" << std::endl;
    return 0;
}
