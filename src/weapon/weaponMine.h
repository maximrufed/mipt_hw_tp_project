#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bullet.h"
#include "bulletMine.h"
#include "tank.h"
#include "constants.h"

class WeaponMine : public Weapon
{
private:
    const float bulletSize_ = 15;

    int nBulletsLeft_ = 30;

public:
    WeaponMine(int id);

    std::vector<Bullet *> fire(b2World &world, Tank &tank, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;
};
