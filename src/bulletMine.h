#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <iostream>

#include "bullet.h"

class BulletMine : public Bullet
{
private:
    b2Body *body_ = nullptr;
    float size_ = 0;
    // bool activate_ = false;
    // float timer_ = 0;

public:
    BulletMine(b2World &world, float radius, b2Vec2 position, float angleRad);

    void step(float timeStep) override;

    bool isDead() override;

    void debug_draw(sf::RenderWindow &window) override;

    void die() override;

    void destroy(b2World &world) override;
};
