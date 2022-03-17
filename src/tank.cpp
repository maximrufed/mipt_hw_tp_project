#include "tank.h"

#include <iostream>

void Tank::createTank(b2World &world, b2Vec2 position)
{
}

Tank::Tank(b2World &world, b2Vec2 position, Weapon *weapon, int id)
{
    id_ = id;
    weapon_ = weapon;

    // -------------------------------create tank-----------------------------------------------

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.bullet = true;

    body_ = world.CreateBody(&bodyDef);

    {
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
    }

    {
        b2PolygonShape dynamicBox;
        b2Vec2 center(0, -sizeGunY_ * 0.5);
        dynamicBox.SetAsBox(sizeGunX_ * 0.5, sizeGunY_ * 0.5, center, 0);

        b2FixtureDef fixtureGun;
        fixtureGun.shape = &dynamicBox;
        fixtureGun.density = 1.0f;
        fixtureGun.friction = 0.3f;

        fixtureGun.filter.categoryBits = 0x0001;
        fixtureGun.filter.maskBits = 0xFFFF;

        body_->CreateFixture(&fixtureGun);
    }

    ClassData *tankData = new ClassData("tank", id);
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
    return weapon_->fire(world, *this, nextBulletID);
}

void Tank::hit()
{
    alive_ = false;
}

void Tank::step(float timeStep)
{
    weapon_->step(timeStep);

    // apply current Move and Rotation
    body_->SetAngularVelocity(angularVelocity_ * currentRotation_);
    float angle_radians = 1.57 + body_->GetAngle();
    body_->SetLinearVelocity(b2Vec2(cos(angle_radians) * currentMove_ * linearVelocity_, sin(angle_radians) * currentMove_ * linearVelocity_));

    currentMove_ = 0;
    currentRotation_ = 0;
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
        sf::RectangleShape rectangle(sf::Vector2f(sizeX_, sizeY_));
        if (color_ == "0")
        {
            rectangle.setFillColor(sf::Color(224, 26, 79, 255));
        }
        else
        {
            rectangle.setFillColor(sf::Color(66, 0, 57, 255));
        }
        // rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition(position.x, position.y);
        const float DEG = 57.2977f;
        rectangle.rotate(rotation * DEG);
        rectangle.setOrigin(sizeX_ * 0.5, sizeY_ * 0.5);
        window.draw(rectangle);
    }

    {
        sf::RectangleShape rectangle(sf::Vector2f(sizeGunX_, sizeGunY_));
        rectangle.setFillColor(sf::Color::Cyan);
        rectangle.setPosition(position.x, position.y);
        const float DEG = 57.2977f;
        rectangle.setOrigin(sizeGunX_ * 0.5, sizeGunY_);
        rectangle.rotate(rotation * DEG);
        window.draw(rectangle);
    }
}

void Tank::setWeapon(Weapon *weapon)
{
    weapon_ = weapon;
}

float Tank::getSizeGunX()
{
    return sizeGunX_;
}

float Tank::getSizeGunY()
{
    return sizeGunY_;
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
    std::cout << "bullet Die | weaponID = " << weaponID << std::endl;
    std::cout << "weapon_->ID = " << weapon_->getID() << std::endl;
    if (weapon_->getID() == weaponID)
    {
        weapon_->bulletDie();
    }
}
