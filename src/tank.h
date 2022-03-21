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
    float sizeGunX_ = 0.8;
    float sizeGunY_ = 3.2;
    float linearVelocity_ = 15;
    float angularVelocity_ = 6;

    float currentMove_ = 0;     // 1 or -1
    float currentRotation_ = 0; // 1 or -1
    std::string color_ = "";

    Weapon *weapon_;

public:
    Tank(b2World &world, b2Vec2 position, float angleRad, Weapon *weapon, int id);
    void move(float direction);
    void rotate(float direction);
    std::vector<Bullet *> fire(b2World &world, int &nextBulletID);
    void hit();
    void step(float timeStep);
    void setColor(std::string color);

    bool isDead();

    void destroy(b2World &world);

    void debug_draw(sf::RenderWindow &window);

    void setWeapon(Weapon *weapon);

    float getSizeGunX();
    float getSizeGunY();
    b2Body *getBody();

    int getTankID();
    void setTankID(int id);

    void bulletDie(int weaponID);
};
