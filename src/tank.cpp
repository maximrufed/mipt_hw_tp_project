#include "tank.h"

#include <iostream>

Tank::Tank(b2World &world, b2Vec2 position, float angleRad, int id)
{
    id_ = id;

    // -------------------------------create tank-----------------------------------------------

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    body_ = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    b2Vec2 center(0, 0);
    dynamicBox.SetAsBox(sizeX_ * 0.5, sizeY_ * 0.5, center, 0);
    b2FixtureDef fixtureBody;
    fixtureBody.shape = &dynamicBox;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.3f;
    fixtureBody.filter.categoryBits = 0x0001;
    fixtureBody.filter.maskBits = 0xFFFF;

    body_->CreateFixture(&fixtureBody);
    body_->SetTransform(position, angleRad);

    ClassData *tankData = new ClassData("tank", this);
    body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);

    // --------------------------------------end-----------------------------------------------
}

void Tank::move(float direction)
{
    currentMove_ += direction;
}

void Tank::rotate(float direction)
{
    currentRotation_ -= direction;
}

std::vector<Bullet *> Tank::fire(b2World &world, int &nextBulletID)
{
    if (weapon_ != nullptr)
        return weapon_->fire(world, nextBulletID);
    else
        return {};
}

void Tank::hit()
{
    // std::cout << "hit" << std::endl;
    alive_ = false;
}

void Tank::step(float timeStep)
{
    if (weapon_ != nullptr)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (weapon_ != nullptr)
        {
            delete weapon_;
            weapon_ = nullptr;
        }
    }
}

void Tank::setColor(std::string color)
{
    color_ = color;
}

bool Tank::isDead()
{
    return !alive_;
}

void Tank::debug_draw(sf::RenderWindow &window)
{
    b2Vec2 position = body_->GetPosition();
    float rotation = body_->GetAngle();

    {
        sf::RectangleShape rectangle(sf::Vector2f(sizeX_ * graphics::SCALE, sizeY_ * graphics::SCALE));
        if (color_ == "0")
        {
            rectangle.setFillColor(sf::Color(164, 36, 59, 255));
        }
        else
        {
            rectangle.setFillColor(sf::Color(51, 80, 92, 255));
        }
        // rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
        rectangle.rotate(rotation * graphics::DEG);
        rectangle.setOrigin(sizeX_ * 0.5 * graphics::SCALE, sizeY_ * 0.5 * graphics::SCALE);
        window.draw(rectangle);
    }

    // draw weapon
    if (weapon_ != nullptr)
    {
        weapon_->debug_draw(window);
    }

    // {
    //     sf::RectangleShape rectangle(sf::Vector2f(sizeGunX_ * graphics::SCALE, sizeGunY_ * graphics::SCALE));
    //     rectangle.setFillColor(sf::Color::Cyan);
    //     rectangle.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
    //     rectangle.setOrigin(sizeGunX_ * 0.5 * graphics::SCALE, sizeGunY_ * graphics::SCALE);
    //     rectangle.rotate(rotation * graphics::DEG);
    //     window.draw(rectangle);
    // }
}

void Tank::setWeapon(Weapon *weapon)
{
    if (weapon_ != nullptr)
    {
        delete weapon_;
        weapon_ = nullptr;
    }
    weapon_ = weapon;
}

b2Body *Tank::getBody()
{
    return body_;
}

int Tank::getTankID()
{
    return id_;
}

void Tank::setTankID(int id)
{
    id_ = id;
}

void Tank::bulletDie(int weaponID)
{
    if (weapon_ == nullptr)
        return;

    if (weapon_->getID() == weaponID)
    {
        weapon_->bulletDie();
    }
}

Tank::~Tank()
{
    delete weapon_;
    body_->GetWorld()->DestroyBody(body_);
    body_ = nullptr;
}

float Tank::getSizeX()
{
    return sizeX_;
}

float Tank::getSizeY()
{
    return sizeY_;
}

bool Tank::isWeaponDead()
{
    if (weapon_ == nullptr)
        return true;
    return weapon_->isDead();
}
