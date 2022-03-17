#include "bulletBasicTimer.h"

BulletBasicTimer::BulletBasicTimer(b2World &world, float radius, float aliveSeconds, b2Vec2 position, float velocity, float angleRad)
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

    body_->CreateFixture(&fixtureBody);

    // apply velocity and angleRad
    body_->SetLinearVelocity(b2Vec2(cos(angleRad) * velocity, sin(angleRad) * velocity));
}

void BulletBasicTimer::step(float timeStep)
{
    timer_ -= timeStep;
}

bool BulletBasicTimer::isDead()
{
    // TODO
    if (timer_ <= 0)
    {
        // delete myself
        return true;
    }
    return false;
}

void BulletBasicTimer::debug_draw(sf::RenderWindow &window)
{

    b2Vec2 position = body_->GetPosition();

    sf::CircleShape circle(radius_);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(position.x, position.y);
    circle.setOrigin(radius_, radius_);
    window.draw(circle);
}
