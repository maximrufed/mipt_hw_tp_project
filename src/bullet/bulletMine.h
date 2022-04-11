#pragma once

#include "box2d/box2d.h"

#include <iostream>

#include "box2d/box2d.h"
#include "bullet.h"
#include "constants.h"

class Bullet;

class BulletMine : public Bullet
{
private:
    b2Body* body_ = nullptr;
    int state_ = 0;
    float timer_ = 0;
    float size_ = 0;

    // state = 0 timer = 2
    // not collision

    // state = 1 timer = 0
    // collition & tank

   public:
    BulletMine(b2World& world, float size, b2Vec2 position, float angleRad);

    void step(float timeStep) override;

    bool isDead() override;

    void die() override;

    b2Vec2 getPosition() const;

    float getRotation() const;

    ~BulletMine() override;
};
