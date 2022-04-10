#pragma once

#include <SFML/graphics.hpp>
#include "box2d/box2d.h"

#include "weapon.h"
// #include "bullet.h"
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
    std::shared_ptr<b2Body> body_;
    float linearVelocity_ = 15;
    float angularVelocity_ = 6;

    float currentMove_ = 0;     // 1 or -1
    float currentRotation_ = 0; // 1 or -1
    std::string color_ = "";

    std::shared_ptr<Weapon> weapon_;

public:
    Tank(b2World &world, b2Vec2 position, float angleRad, int id);

    void move(float direction);

    void rotate(float direction);

    std::vector<std::shared_ptr<Bullet>> fire(b2World &world, int &nextBulletID);

    void hit();

    void step(float timeStep);

    bool isDead();

    bool isWeaponDead();

    void setWeapon(std::shared_ptr<Weapon> weapon);

    std::shared_ptr<b2Body> getBody();

    int getTankID() const;

    void setTankID(int id);

    void bulletDie(int weaponID);

    ~Tank();

    float getRotation() const;
    
    b2Vec2 getPosition() const;

    std::shared_ptr<Weapon> getWeapon() const;
};
