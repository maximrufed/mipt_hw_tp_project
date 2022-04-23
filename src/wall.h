#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "box2d/box2d.h"
#include "constants.h"

class Wall {
   private:
    b2Body* body_;

    float sizeX_ = 0;
    float sizeY_ = 0;

   public:
    Wall(b2World& world, b2Vec2 p1, b2Vec2 p2);

    void debug_draw(sf::RenderWindow& window);
};
