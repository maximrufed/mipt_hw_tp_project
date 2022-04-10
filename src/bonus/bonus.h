#pragma once

#include "box2d/box2d.h"

#include <string>
#include <memory>

#include "constants.h"
#include "tank.h"

class Bonus
{
protected:
    bool alive_ = true;
public:
    virtual void step(float timeStep) = 0;

    virtual bool isDead();

    virtual void apply(std::shared_ptr<Tank> tank) = 0;

    virtual b2Vec2 getPosition() const = 0;

    virtual float getRotation() const = 0;

    virtual ~Bonus();
};
