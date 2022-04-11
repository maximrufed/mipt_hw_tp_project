#pragma once

#include "box2d/box2d.h"

#include "box2d/box2d.h"
#include "constants.h"

#include <iostream>

class Wall
{
private:
    b2Body* body_ = nullptr;

    float sizeX_ = 0;
    float sizeY_ = 0;

   public:
    Wall(b2World& world, b2Vec2 p1, b2Vec2 p2);

    float getSizeX() const;

    float getSizeY() const;

    b2Vec2 getPosition() const;
};
