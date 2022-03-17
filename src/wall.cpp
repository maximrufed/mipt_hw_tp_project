#include "wall.h"

Wall::Wall(b2World &world, b2Vec2 p1, b2Vec2 p2)
{
    sizeX_ = abs(p1.x - p2.x);
    sizeY_ = abs(p1.y - p2.y);
    // std::cerr << "New Wall " << (p1.x + p2.x) * 0.5 << " " << (p1.y + p2.y) * 0.5 << std::endl;

    // init body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set((p1.x + p2.x) * 0.5, (p1.y + p2.y) * 0.5);
    bodyDef.bullet = true;
    body_ = world.CreateBody(&bodyDef);

    // init fixture
    b2PolygonShape staticBox;
    b2Vec2 center(0, 0);
    staticBox.SetAsBox(sizeX_ * 0.5, sizeY_ * 0.5, center, 0);

    b2FixtureDef fixtureBody;
    fixtureBody.shape = &staticBox;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.3f;

    body_->CreateFixture(&fixtureBody);
}

void Wall::debug_draw(sf::RenderWindow &window)
{
    b2Vec2 position = body_->GetPosition();

    sf::RectangleShape rectangle(sf::Vector2f(sizeX_, sizeY_));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(position.x, position.y);
    const float DEG = 57.2977f;
    rectangle.setOrigin(sizeX_ * 0.5, sizeY_ * 0.5);
    window.draw(rectangle);
}
