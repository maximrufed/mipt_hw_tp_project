#pragma once

#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <string>

#include "constants.h"
#include "tank.h"
#include "bonus.h"
#include "classData.h"
#include "weaponBuckshot.h"

class BonusBuckshot : public Bonus
{
private:
    b2Body *body_ = nullptr;
    Tank *tank_ = nullptr;

    int *nextWeaponID_ = nullptr;

    const float size_ = 3;

public:
    BonusBuckshot(b2World &world, b2Vec2 position, float angleRad, int *nextWeaponID);

    void step(float timeStep) override;

    void apply(Tank *tank) override;

    void debug_draw(sf::RenderWindow &window) override;

    ~BonusBuckshot() override;
};
