#include "bulletBasicTimer.h"

BulletBasicTimer::BulletBasicTimer(b2World &world, float radius, float aliveSeconds, b2Vec2 position, float velocity,
                                   float angleRad)
{
    timer_ = aliveSeconds;
    radius_ = radius;

    // create body_ as circle
    // TODO

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.bullet = true;
    body_ = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    // b2Vec2 center(0, 0);
    shape.m_p.Set(0, 0);
    shape.m_radius = radius;

    b2FixtureDef fixtureBody;
    fixtureBody.shape = &shape;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.f;
    fixtureBody.restitution = 1.f;

    fixtureBody.filter.categoryBits = 0x0002;
    fixtureBody.filter.maskBits = 0x0005;

    body_->CreateFixture(&fixtureBody);

    ClassData *tankData = new ClassData("bullet", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);

    // apply velocity and angleRad
    body_->SetLinearVelocity(b2Vec2(cos(angleRad) * velocity, sin(angleRad) * velocity));
}

void BulletBasicTimer::step(float timeStep)
{
    timer_ -= timeStep;
}

bool BulletBasicTimer::isDead()
{
    if ((!alive_) || (timer_ <= 0))
    {
        // delete myself
        return true;
    }
    return false;
}

void BulletBasicTimer::die()
{
    alive_ = false;
}

b2Vec2 BulletBasicTimer::getPosition() const {
    return body_->GetPosition();
}

float BulletBasicTimer::getRadius() const {
    return radius_;
}

BulletBasicTimer::~BulletBasicTimer()
{
    delete reinterpret_cast<ClassData*>(body_->GetUserData().pointer);
    std::cout << "really delete bulletBasicTimer" << std::endl;
    body_->GetWorld()->DestroyBody(body_);
    body_ = nullptr;
}
