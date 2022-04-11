#pragma once
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bulletBasicTimer.h"
#include "constants.h"
#include "tank.h"
#include "weapon.h"

class WeaponBuckshot : public Weapon {
   private:
    // physics
    b2Fixture* fixture_ = nullptr;
    std::shared_ptr<Tank> tank_;

    const float bulletLiveTime_ = 1.5;
    const float bulletVelocity_ = 50;
    const float bulletAmount_ = 3;

    int nBulletsLeft_ = 3;

    // all about graphics

public:
    WeaponBuckshot(std::shared_ptr<Tank> tank, int id);

    std::vector<std::shared_ptr<Bullet>> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void setTank(std::shared_ptr<Tank>);

    b2Fixture* getFixture();

    ~WeaponBuckshot();
};
