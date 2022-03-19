#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>

#include "bullet.h"
#include "constants.h"

class BulletMine : public Bullet
{
private:
    b2Body *body_ = nullptr;
    float size_ = 0;
    int state_ = 0;
    float timer_ = 0;

    // state = 0 timer = 2
    // not collision

    // state = 1 timer = 0
    // collition & tank

public:
    BulletMine(b2World &world, float size, b2Vec2 position, float angleRad);

    void step(float timeStep) override;

    bool isDead() override;

    void debug_draw(sf::RenderWindow &window) override;

    void die() override;

    void destroy(b2World &world) override;
};
