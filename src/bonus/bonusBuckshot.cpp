#include "bonusBuckshot.h"

BonusBuckshot::BonusBuckshot(b2World &world, b2Vec2 position, float angleRad, int *nextWeaponID) : nextWeaponID_(nextWeaponID)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;

    body_ = std::shared_ptr<b2Body>(world.CreateBody(&bodyDef), [](b2Body*){});

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(graphics::bonusSize * 0.5, graphics::bonusSize * 0.5);

    b2FixtureDef fixtureBody;
    fixtureBody.shape = &dynamicBox;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.3f;
    fixtureBody.filter.categoryBits = 0x0008;
    fixtureBody.filter.maskBits = 0x0001;
    fixtureBody.isSensor = true;

    body_->CreateFixture(&fixtureBody);
    body_->SetTransform(position, angleRad);

    ClassData *tankData = new ClassData("bonus", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);
}

void BonusBuckshot::step(float timeStep)
{
    if (tank_)
    {
        auto weapon = std::make_shared<WeaponBuckshot>(tank_, (*nextWeaponID_)++);
        tank_->setWeapon(weapon);
        tank_.reset();
        alive_ = false;
    }
}

void BonusBuckshot::apply(std::shared_ptr<Tank> tank)
{
    if (alive_)
    {
        tank_ = tank;
    }
}

b2Vec2 BonusBuckshot::getPosition() const {
    return body_->GetPosition();
}

float BonusBuckshot::getRotation() const {
    return body_->GetAngle();
}

BonusBuckshot::~BonusBuckshot()
{
    body_->GetWorld()->DestroyBody(body_.get());
}
