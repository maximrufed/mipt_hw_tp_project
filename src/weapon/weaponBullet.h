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
    // physics
    b2Fixture *fixture_ = nullptr;
    Tank *tank_ = nullptr;

    const float bulletRadius_ = 0.5;
    const float bulletLiveTime_ = 15;
    const float bulletVelocity_ = 30;

    int nBulletsLeft_ = 5;

    // all about graphics

    float sizeGunX_ = 0.8;
    float sizeGunY_ = 3.2;

public:
    WeaponBullet(b2World &world, Tank *tank, int id);

    std::vector<Bullet *> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void debug_draw(sf::RenderWindow &window) override;

    void setTank(Tank *tank);

    b2Fixture *getFixture();

    ~WeaponBullet();
};
