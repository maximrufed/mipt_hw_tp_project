#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "weapon.h"
#include "bullet.h"
#include "classData.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <string>

class Weapon;

class Bullet;

class Tank
{
private:
    bool alive_ = true;
    int id_ = -1;
    b2Body *body_ = nullptr;
    float sizeX_ = 3;
    float sizeY_ = 4.5;
    float linearVelocity_ = 15;
    float angularVelocity_ = 6;

    float currentMove_ = 0;     // 1 or -1
    float currentRotation_ = 0; // 1 or -1
    std::string color_ = "";

    Weapon *weapon_ = nullptr;

public:
    Tank(b2World &world, b2Vec2 position, float angleRad, int id);

    void move(float direction);

    void rotate(float direction);

    std::vector<Bullet *> fire(b2World &world, int &nextBulletID);

    void hit();

    void step(float timeStep);

    bool isDead();

    void setWeapon(Weapon *weapon);

    b2Body *getBody();

    int getTankID();

    void setTankID(int id);

    void bulletDie(int weaponID);

    ~Tank();

    // TODO useless
    void setColor(std::string color);

    // TODO graphics
    void debug_draw(sf::RenderWindow &window);

    float getSizeX();

    float getSizeY();
};
