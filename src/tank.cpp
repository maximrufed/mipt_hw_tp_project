#include "tank.h"

#include <iostream>

Tank::Tank(b2World &world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(100.0f, 100.0f);
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

        body_->CreateFixture(&fixtureGun);
    }
}

void Tank::move(float direction)
{
    currentMove_ += direction;
}

void Tank::rotate(float direction)
{
    currentRotation_ -= direction;
}

void Tank::fire()
{
}

void Tank::hit()
{
}

void Tank::step()
{
    // std::cerr << color_ << " : " << body_->GetPosition().x << " " << body_->GetPosition().y << " " << body_->GetAngle() << std::endl;

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

    // float RADIAN_IN_DEGREES = 57.3f;

    // sf::RectangleShape rectangle;

    // b2Vec2 position = body_->GetPosition();
    // float rotation = body_->GetAngle();

    // rectangle.setPosition(sf::Vector2f(position.x - sizeX_ / (float)2, position.y - sizeY_ / (float)2));
    // // rectangle.setRotation((2 - rotation) * RADIAN_IN_DEGREES);
    // rectangle.setRotation(rotation * (float)(180.0 / M_PI));
    // rectangle.setSize(sf::Vector2f(sizeX_, sizeY_));
    // rectangle.setOrigin(sf::Vector2f(sizeX_ / 2, sizeY_ / 2));

    // if (color_ == "0")
    // {
    //     // red
    //     rectangle.setFillColor(sf::Color(224, 26, 79, 255));
    // }
    // else
    // {
    //     rectangle.setFillColor(sf::Color(66, 0, 57, 255));
    // }

    // // std::cerr << "tank draw" << std::endl;

    // window.draw(rectangle);
}
