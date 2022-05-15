#include "sfml_event_manager.h"

SfmlEventManager::SfmlEventManager(std::shared_ptr<sf::RenderWindow> window): window_(window) {}

void SfmlEventManager::setGame(std::shared_ptr<BasicGame> game) {
    game_ = game;
}

void SfmlEventManager::input() {
    sf::Event event;
    while (window_->pollEvent(event))
    {
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window_->close();
            break;

            // key pressed
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
            {
                game_->tank_fire(0);
            }
            else if (event.key.code == sf::Keyboard::Q)
            {
                game_->tank_fire(1);
            }
            break;

            // we don't process other types of events
        default:
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window_->close();
    }

    // -----------------------------First Tank----------------------------------------------

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        game_->tank_rotate(0, 1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        game_->tank_rotate(0, -1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        game_->tank_move(0, -1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        game_->tank_move(0, 1);
    }

    // -----------------------------Second Tank----------------------------------------------

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        game_->tank_rotate(1, 1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        game_->tank_rotate(1, -1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        game_->tank_move(1, -1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        game_->tank_move(1, 1);
    }
}