#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "bullet.h"

class Weapon
{
public:
    // here is position and direction
    virtual void fire() = 0;

    virtual void idDead() = 0;
};

class WeaponBasicBullet : public Weapon
{
public:
    // rigidbody
    int bulletNo;

    void fire() override;

    void idDead() override;
};
