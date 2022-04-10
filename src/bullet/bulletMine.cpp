#include "bulletMine.h"

BulletMine::BulletMine(b2World &world, float size, b2Vec2 position, float angleRad)
{
    // here is creating mine
    size_ = size;
    state_ = 0;
    timer_ = 2;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.bullet = true;

    body_ = std::shared_ptr<b2Body>(world.CreateBody(&bodyDef), [](b2Body*){});

    {
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(size * 0.5, size * 0.5);

        b2FixtureDef fixtureBody;
        fixtureBody.shape = &dynamicBox;
        fixtureBody.density = 1.0f;
        fixtureBody.friction = 0.3f;
        fixtureBody.isSensor = true;

        fixtureBody.filter.categoryBits = 0x0002;
        fixtureBody.filter.maskBits = 0x0000;

        body_->CreateFixture(&fixtureBody);
    }

    body_->SetTransform(position, angleRad);

    ClassData *tankData = new ClassData("bullet", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);
}

void BulletMine::step(float timeStep)
{
    if (state_ == 0)
    {
        timer_ -= timeStep;
        if (timer_ <= 0)
        {
            state_ = 1;
            auto filterData = body_->GetFixtureList()[0].GetFilterData();
            filterData.maskBits = 0x0001;
            body_->GetFixtureList()[0].SetFilterData(filterData);
        }
    }
}

bool BulletMine::isDead()
{
    return !alive_ || (state_ == 2 && timer_ <= 0);
}

void BulletMine::die()
{
    alive_ = false;
}

b2Vec2 BulletMine::getPosition() const {
    return body_->GetPosition();
}


float BulletMine::getRotation() const {
    return body_->GetAngle();
}

BulletMine::~BulletMine()
{
    body_->GetWorld()->DestroyBody(body_.get());
}
