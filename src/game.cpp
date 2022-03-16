#include "game.h"

BasicGame::BasicGame(int nTanks) : gravity_(b2Vec2(0.0f, 0.0f)), world_(gravity_)
{
    for (size_t i = 0; i < nTanks; ++i)
    {
        tanks_.push_back(Tank(world_));
        tanks_.back().setColor(std::to_string(i));
    }
}

void BasicGame::start()
{
    // make one tank
}

void BasicGame::step(float timeStep)
{
    for (size_t i = 0; i < tanks_.size(); ++i)
    {
        tanks_[i].step();
    }

    world_.Step(timeStep, 8, 3);
}

void BasicGame::tank_move(int tankID, float direction)
{
    tanks_[tankID].move(direction);
}

void BasicGame::tank_rotate(int tankID, float direction)
{
    tanks_[tankID].rotate(direction);
}

void BasicGame::tank_fire()
{
}

void BasicGame::debug_draw(sf::RenderWindow &window)
{
    window.clear(sf::Color(255, 255, 255, 255));

    // main draw
    for (size_t i = 0; i < tanks_.size(); ++i)
    {
        tanks_[i].debug_draw(window);
    }

    window.display();
}
