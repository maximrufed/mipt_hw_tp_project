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
    body_ = std::shared_ptr<b2Body>(world.CreateBody(&bodyDef), [](b2Body*){});

    // init fixture
    b2PolygonShape staticBox;
    b2Vec2 center(0, 0);
    staticBox.SetAsBox(sizeX_ * 0.5, sizeY_ * 0.5, center, 0);

    b2FixtureDef fixtureBody;
    fixtureBody.shape = &staticBox;
    fixtureBody.density = 1.0f;
    fixtureBody.friction = 0.3f;

    fixtureBody.filter.categoryBits = 0x0004;
    fixtureBody.filter.maskBits = 0xFFFF;

    body_->CreateFixture(&fixtureBody);
}

float Wall::getSizeX() const {
    return sizeX_;
}

float Wall::getSizeY() const {
    return sizeY_;
}

b2Vec2 Wall::getPosition() const {
    return body_->GetPosition();
}
