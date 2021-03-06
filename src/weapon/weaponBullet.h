#pragma once
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bulletBasicTimer.h"
#include "constants.h"
#include "tank.h"
#include "weapon.h"

class WeaponBullet : public Weapon {
   private:
    // physics
    b2Fixture* fixture_ = nullptr;
    std::shared_ptr<Tank> tank_;

    const float bulletLiveTime_ = 15;
    const float bulletVelocity_ = 18;

    int nBulletsLeft_ = 5;

    // all about graphics

public:
    WeaponBullet(b2World &world, std::shared_ptr<Tank> tank, int id);

    std::vector<std::shared_ptr<Bullet>> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void setTank(std::shared_ptr<Tank> tank);

    b2Fixture* getFixture();

    ~WeaponBullet();
};
