#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include "tank.h"
#include "bullet.h"
#include "classData.h"
#include "constants.h"
#include "bonus.h"

#include <iostream>

class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact);

    void EndContact(b2Contact *contact);

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};
