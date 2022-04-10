#include "tank.h"

Tank::Tank(b2World &world, b2Vec2 position, float angleRad, int id)
{
    id_ = id;

    // -------------------------------create tank-----------------------------------------------

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    body_ = std::shared_ptr<b2Body>(world.CreateBody(&bodyDef), [](b2Body*){});
    b2PolygonShape dynamicBox;
    b2Vec2 center(0, 0);
    dynamicBox.SetAsBox(graphics::tankSizeX * 0.5, graphics::tankSizeY * 0.5, center, 0);
    b2FixtureDef fixtureBody;
    fixtureBody.shape = &dynamicBox;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.3f;
    fixtureBody.filter.categoryBits = 0x0001;
    fixtureBody.filter.maskBits = 0xFFFF;

    body_->CreateFixture(&fixtureBody);
    body_->SetTransform(position, angleRad);

    ClassData* tankData = new ClassData("tank", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);

    // --------------------------------------end-----------------------------------------------
}

void Tank::move(float direction) {
    currentMove_ += direction;
}

void Tank::rotate(float direction) {
    currentRotation_ -= direction;
}

std::vector<std::shared_ptr<Bullet>> Tank::fire(b2World &world, int &nextBulletID)
{
    if (weapon_)
        return weapon_->fire(world, nextBulletID);
    else
        return {};
}

void Tank::hit() {
    // std::cout << "hit" << std::endl;
    alive_ = false;
}

void Tank::step(float timeStep)
{
    if (weapon_)
    {
        weapon_->step(timeStep);
    }

    // apply current Move and Rotation
    body_->SetAngularVelocity(angularVelocity_ * currentRotation_);
    float angle_radians = 1.57 + body_->GetAngle();
    body_->SetLinearVelocity(b2Vec2(cos(angle_radians) * currentMove_ * linearVelocity_,
                                    sin(angle_radians) * currentMove_ * linearVelocity_));

    currentMove_ = 0;
    currentRotation_ = 0;
}

bool Tank::isDead()
{
    return !alive_;
}

b2Vec2 Tank::getPosition() const {
    return body_->GetPosition();
}

float Tank::getRotation() const {
    return body_->GetAngle();
}

void Tank::setWeapon(std::shared_ptr<Weapon> weapon)
{
    weapon_ = weapon;
}

std::shared_ptr<b2Body> Tank::getBody()
{
    return body_;
}

int Tank::getTankID() const
{
    return id_;
}

void Tank::setTankID(int id) {
    id_ = id;
}

void Tank::bulletDie(int weaponID)
{
    if (!weapon_)
        return;

    if (weapon_->getID() == weaponID) {
        weapon_->bulletDie();
    }
}

Tank::~Tank()
{
    body_->GetWorld()->DestroyBody(body_.get());
}

bool Tank::isWeaponDead()
{
    if (!weapon_)
        return true;
    return weapon_->isDead();
}

std::shared_ptr<Weapon> Tank::getWeapon() const {
    return weapon_;
}