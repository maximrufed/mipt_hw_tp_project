#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bullet.h"
#include "bulletBasicTimer.h"
#include "tank.h"
#include "constants.h"

class WeaponBullet : public Weapon
{
private:
    const float bulletRadius_ = 0.5;
    const float bulletLiveTime_ = 15;
    const float bulletVelocity_ = 16;

    int nBulletsLeft_ = 5;

public:
    WeaponBullet(int id);

    std::vector<Bullet *> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;
};
