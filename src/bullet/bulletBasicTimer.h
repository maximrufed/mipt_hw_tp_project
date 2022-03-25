#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>

#include "classData.h"
#include "bullet.h"
#include "constants.h"

class BulletBasicTimer : public Bullet
{
private:
    b2Body *body_ = nullptr;
    float timer_ = 0;
    float radius_ = 0;

public:
    BulletBasicTimer(b2World &world, float radius, float aliveSeconds, b2Vec2 position, float velocity, float angleRad);

    void step(float timeStep) override;

    bool isDead() override;

    void debug_draw(sf::RenderWindow &window) override;

    void die() override;

    ~BulletBasicTimer() override;
};
