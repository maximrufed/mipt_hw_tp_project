#include "contactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{ /* handle begin event */
    const b2Body *bodyA = contact->GetFixtureA()->GetBody();
    const b2Body *bodyB = contact->GetFixtureB()->GetBody();

    ClassData* dataA = reinterpret_cast<ClassData*>(bodyA->GetUserData().pointer);
    ClassData* dataB = reinterpret_cast<ClassData*>(bodyB->GetUserData().pointer);

    if (dataA == nullptr || dataB == nullptr)
        return;

    if (dataA->type != "tank")
        std::swap(dataA, dataB);

    if (dataA->type == "tank" && dataB->type == "bullet")
    {
        Tank* tank = static_cast<Tank*>(dataA->pointer);
        tank->hit();
        Bullet* bullet = static_cast<Bullet*>(dataB->pointer);
        bullet->die();
    }

    if (dataA->type == "tank" && dataB->type == "bonus")
    {
        Tank* tank = reinterpret_cast<Tank*>(dataA->pointer);
        Bonus* bonus = reinterpret_cast<Bonus*>(dataB->pointer);
        bonus->apply(std::shared_ptr<Tank>(std::shared_ptr<Tank>(), tank));
    }
}

void ContactListener::EndContact(b2Contact *contact)
{ /* handle end event */
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{ /* handle pre-solve event */
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{ /* handle post-solve event */
}
