#include "bulletMine.h"

BulletMine::BulletMine(b2World &world, float size, b2Vec2 position, float angleRad)
{
    // here is creating mine
    size_ = size;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.bullet = true;
    bodyDef.angularVelocity = angleRad;

    body_ = world.CreateBody(&bodyDef);

    {
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(size * 0.5, size * 0.5);

        b2FixtureDef fixtureBody;
        fixtureBody.shape = &dynamicBox;
        fixtureBody.density = 1.0f;
        fixtureBody.friction = 0.3f;

        fixtureBody.filter.categoryBits = 0x0008;
        fixtureBody.filter.maskBits = 0x0001;

        body_->CreateFixture(&fixtureBody);
    }

    ClassData *tankData = new ClassData("bullet", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);
}

void BulletMine::step(float timeStep)
{
    // nothing
}

bool BulletMine::isDead()
{
    return !alive_;
}

void BulletMine::debug_draw(sf::RenderWindow &window)
{
    // TODO
}

void BulletMine::die()
{
    alive_ = false;
}

void BulletMine::destroy(b2World &world)
{
    world.DestroyBody(body_);
}
