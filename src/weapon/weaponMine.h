#pragma once
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bulletMine.h"
#include "constants.h"

class WeaponMine : public Weapon
{
private:
    // physics
    std::shared_ptr<Tank> tank_;

    int nBulletsLeft_ = 3;

    // all about graphics

public:
    WeaponMine(std::shared_ptr<Tank> tank, int id);

    std::vector<std::shared_ptr<Bullet>> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void setTank(std::shared_ptr<Tank> tank);

    ~WeaponMine();
};
