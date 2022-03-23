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
    // physics
    Tank *tank_ = nullptr;

    const float bulletSize_ = 1.5;

    int nBulletsLeft_ = 3;

    // all about graphics

public:
    WeaponMine(Tank *tank, int id);

    std::vector<Bullet *> fire(b2World &world, int &nextBulletID) override;

    void step(float timeStep) override;

    void bulletDie() override;

    void setTank(Tank *tank);

    void debug_draw(sf::RenderWindow &window) override;

    ~WeaponMine();
};
