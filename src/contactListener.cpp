#include "contactListener.h"

void ContactListener::BeginContact(b2Contact *contact)
{ /* handle begin event */
    std::cerr << " contact " << std::endl;
    const b2Body *bodyA = contact->GetFixtureA()->GetBody();
    const b2Body *bodyB = contact->GetFixtureB()->GetBody();

    ClassData *dataA = reinterpret_cast<ClassData *>(bodyA->GetUserData().pointer);
    ClassData *dataB = reinterpret_cast<ClassData *>(bodyB->GetUserData().pointer);

    if (dataA == nullptr || dataB == nullptr)
        return;

    std::cout << "collide " << dataA->type << " " << dataB->type << std::endl;
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
