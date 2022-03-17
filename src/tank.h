#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "weapon.h"
#include "bullet.h"

#include <iostream>
#include <vector>
#include <string>

class Weapon;
class Bullet;

class Tank
{
private:
    int id_;
    b2Body *body_;
    float sizeX_ = 30;
    float sizeY_ = 45;
    float sizeGunX_ = 8;
    float sizeGunY_ = 32;
    float linearVelocity_ = 400;
    float angularVelocity_ = 4;

    float currentMove_ = 0;     // 1 or -1
    float currentRotation_ = 0; // 1 or -1
    std::string color_ = "";

    Weapon *weapon_;

    void createTank(b2World &world, b2Vec2 position);

public:
    Tank(b2World &world, b2Vec2 position, Weapon *weapon);
    void move(float direction);
    void rotate(float direction);
    std::vector<Bullet *> fire(b2World &world);
    void hit();
    void step(float timeStep);
    void setColor(std::string color);

    void debug_draw(sf::RenderWindow &window);

    void setWeapon(Weapon *weapon);

    float getSizeGunX();
    float getSizeGunY();
    b2Body *getBody();
};
