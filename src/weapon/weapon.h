#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>
#include <vector>

#include "bullet.h"
#include "tank.h"
#include "constants.h"

class Tank;
class Bullet;

class Weapon
{
protected:
    b2Body *body_ = nullptr;
    Tank *tank_ = nullptr;
    int alive_ = true;
    int id_ = -1;

public:
    virtual std::vector<Bullet *> fire(b2World &world, int &nextBulletID) = 0;

    virtual bool isDead();

    virtual void step(float timeStep) = 0;

    virtual void setTank(Tank *tank);

    int getID();
    void setID(int id);

    virtual void bulletDie() = 0;
};
