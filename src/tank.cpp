#include "tank.h"

#include <iostream>

Tank::Tank(b2World &world)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(100.0f, 100.0f);
    body_ = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(sizeX_ / 2, sizeY_ / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body_->CreateFixture(&fixtureDef);
}

void Tank::move(float direction)
{
    currentMove_ = direction;
}

void Tank::rotate(float direction)
{
    currentRotation_ = direction;
}

void Tank::fire()
{
}

void Tank::hit()
{
}

void Tank::step()
{
    std::cerr << color_ << " : " << body_->GetPosition().x << " " << body_->GetPosition().y << " " << body_->GetAngle() << std::endl;

    // apply current Move and Rotation
    body_->SetAngularVelocity(angularVelocity_ * currentRotation_);
    float angle_radians = 1.57 - body_->GetAngle();
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
    float RADIAN_IN_DEGREES = 57.3f;

    sf::RectangleShape rectangle;

    b2Vec2 positoin = body_->GetPosition();
    float rotation = body_->GetAngle();

    rectangle.setPosition(sf::Vector2f(positoin.x, positoin.y));
    // rectangle.setRotation((2 - rotation) * RADIAN_IN_DEGREES);
    rectangle.setRotation(360 - (rotation * RADIAN_IN_DEGREES));
    rectangle.setSize(sf::Vector2f(sizeX_, sizeY_));
    rectangle.setOrigin(sf::Vector2f(sizeX_ / 2, sizeY_ / 2));

    if (color_ == "0")
    {
        // red
        rectangle.setFillColor(sf::Color(224, 26, 79, 255));
    }
    else
    {
        rectangle.setFillColor(sf::Color(66, 0, 57, 255));
    }

    // std::cerr << "tank draw" << std::endl;

    window.draw(rectangle);
}
