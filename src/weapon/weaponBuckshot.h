#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <vector>

#include "weapon.h"
#include "bullet.h"
#include "bulletBasicTimer.h"
#include "tank.h"
#include "constants.h"

class WeaponBuckshot : public Weapon
{
private:
    // physics
    b2Fixture *fixture_ = nullptr;
    Tank *tank_ = nullptr;

    const float bulletRadius_ = 0.3;
    const float bulletLiveTime_ = 1.5;
    const float bulletVelocity_ = 50;
    const float bulletAmount_ = 3;

    int nBulletsLeft_ = 3;

    // all about graphics

    float sizeGunX_ = 1.5;
    float sizeGunY_ = 3.0;

public:
    WeaponBuckshot(Tank *tank, int id);

    std::vector<Bullet *> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void debug_draw(sf::RenderWindow &window) override;

    void setTank(Tank *tank);

    b2Fixture *getFixture();

    ~WeaponBuckshot();
};
