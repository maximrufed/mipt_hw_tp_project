#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "box2d/box2d.h"
#include "bullet.h"
#include "constants.h"
#include "tank.h"

class Tank;
class Bullet;

class Weapon {
   protected:
    int alive_ = true;
    int id_ = -1;

   public:
    virtual std::vector<Bullet*> fire(b2World& world, int& nextBulletID) = 0;

    virtual bool isDead();

    virtual void step(float timeStep) = 0;

    int getID();
    void setID(int id);

    virtual void bulletDie() = 0;

    virtual void debug_draw(sf::RenderWindow& window) = 0;

    virtual ~Weapon();
};
