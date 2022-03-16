#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "weapon.h"
#include "bullet.h"

#include <iostream>
#include <string>

class Tank
{
private:
    int id_;
    // int lives;
    // rigidbody
    b2Body *body_;
    float sizeX_ = 50;
    float sizeY_ = 70;
    float sizeGunX_ = 16;
    float sizeGunY_ = 50;
    float linearVelocity_ = 400;
    float angularVelocity_ = 4;

    float currentMove_ = 0;     // 1 or -1
    float currentRotation_ = 0; // 1 or -1
    std::string color_ = "";
    // float maxSpeed;
    // Weapon weapon;

public:
    Tank(b2World &world);
    Tank(b2World &world, int color);
    void move(float direction);   // TODO direction
    void rotate(float direction); // TODO direction
    void fire();                  // TODO direction
    void hit();
    void step();
    void setColor(std::string color);

    void debug_draw(sf::RenderWindow &window); // TODO direction
};
