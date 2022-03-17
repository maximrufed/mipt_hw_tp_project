#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "weapon.h"

class Weapon;

class Bullet
{
protected:
    Weapon *weapon_ = nullptr;

public:
    virtual void step(float timeStep) = 0;

    virtual bool isDead() = 0;

    virtual void debug_draw(sf::RenderWindow &window) = 0;
};
