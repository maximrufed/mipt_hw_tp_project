#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <vector>

#include "bullet.h"
#include "tank.h"

class Tank;
class Bullet;

class Weapon
{
public:
    virtual std::vector<Bullet *> fire(b2World &world, Tank &tank) = 0;

    virtual bool isDead() = 0;

    virtual void step(float timeStep) = 0;
};
