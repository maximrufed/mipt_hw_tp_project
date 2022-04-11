#pragma once

#include "box2d/box2d.h"

#include <string>

#include "constants.h"
#include "tank.h"
#include "bonus.h"
#include "classData.h"
#include "weaponMine.h"

class BonusMine : public Bonus
{
private:
    b2Body* body_ = nullptr;
    std::shared_ptr<Tank> tank_;

    int *nextWeaponID_ = nullptr;

public:
    BonusMine(b2World &world, b2Vec2 position, float angleRad, int *nextWeaponID);

    void step(float timeStep) override;

    void apply(std::shared_ptr<Tank> tank) override;

    b2Vec2 getPosition() const override;

    float getRotation() const override;

    ~BonusMine() override;
};
