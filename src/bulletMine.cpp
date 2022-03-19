#include "bulletMine.h"

BulletMine::BulletMine(b2World &world, float size, b2Vec2 position, float angleRad)
{
    // here is creating mine
    size_ = size;
    state_ = 0;
    timer_ = 2;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.bullet = true;

    body_ = world.CreateBody(&bodyDef);

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

    ClassData *tankData = new ClassData("bulletMine", this);
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

void BulletMine::debug_draw(sf::RenderWindow &window)
{
    if (state_ == 1)
        return;
    b2Vec2 position = body_->GetPosition();
    float rotation = body_->GetAngle();

    sf::RectangleShape rectangle(sf::Vector2f(size_, size_));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(position.x, position.y);
    const float DEG = 57.2977f;
    rectangle.rotate(rotation * DEG);
    rectangle.setOrigin(size_ * 0.5, size_ * 0.5);
    window.draw(rectangle);
}

void BulletMine::die()
{
    alive_ = false;
}

void BulletMine::destroy(b2World &world)
{
    world.DestroyBody(body_);
}
