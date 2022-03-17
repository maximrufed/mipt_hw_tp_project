#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bullet.h"
#include "bulletBasicTimer.h"
#include "tank.h"

class WeaponBullet : public Weapon
{
private:
    const float bulletRadius_ = 5;
    const float bulletLiveTime_ = 3;
    const float bulletVelocity_ = 400;

    int nBulletsLeft_ = 5;

public:
    WeaponBullet(int id);

    std::vector<Bullet *> fire(b2World &world, Tank &tank, int &nextBulletID) override;

    bool isDead() override;

    void step(float timeStep) override;

    void bulletDie() override;
};
