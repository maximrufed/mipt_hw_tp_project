#pragma once

#include "box2d/box2d.h"

#include <iostream>

#include "box2d/box2d.h"
#include "bullet.h"
#include "classData.h"
#include "constants.h"

class BulletBasicTimer : public Bullet
{
private:
    std::shared_ptr<b2Body> body_;
    float timer_ = 0;
    float radius_ = 0;

   public:
    BulletBasicTimer(b2World& world, float radius, float aliveSeconds, b2Vec2 position, float velocity, float angleRad);

    void step(float timeStep) override;

    bool isDead() override;

    void die() override;

    b2Vec2 getPosition() const;

    float getRadius() const;

    ~BulletBasicTimer() override;
};
