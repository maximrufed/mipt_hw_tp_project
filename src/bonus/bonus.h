#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "box2d/box2d.h"
#include "constants.h"
#include "tank.h"

class Bonus {
   protected:
    bool alive_ = true;

   public:
    virtual void step(float timeStep) = 0;

    virtual bool isDead();

    virtual void apply(Tank* tank) = 0;

    virtual void debug_draw(sf::RenderWindow& window) = 0;

    virtual ~Bonus();
};
