#include "bonusMine.h"

BonusMine::BonusMine(b2World &world, b2Vec2 position, float angleRad, int *nextWeaponID) : nextWeaponID_(nextWeaponID)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;

    body_ = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(size_ * 0.5, size_ * 0.5);

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

void BonusMine::step(float timeStep)
{
    if (tank_ != nullptr)
    {
        Weapon *weapon = new WeaponMine(tank_, (*nextWeaponID_)++);
        tank_->setWeapon(weapon);
        tank_ = nullptr;
        alive_ = false;
    }
}

void BonusMine::apply(Tank *tank)
{
    tank_ = tank;
}

void BonusMine::debug_draw(sf::RenderWindow &window)
{
    b2Vec2 position = body_->GetPosition();
    float rotation = body_->GetAngle();

    // sf::RectangleShape rectangle(sf::Vector2f(size_ * graphics::SCALE, size_ * graphics::SCALE));
    // rectangle.setFillColor(sf::Color::Magenta);
    // // rectangle.setFillColor(sf::Color::Red);
    // rectangle.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
    // rectangle.rotate(rotation * graphics::DEG);
    // rectangle.setOrigin(size_ * 0.5 * graphics::SCALE, size_ * 0.5 * graphics::SCALE);
    // window.draw(rectangle);

    sf::Texture texture;
    texture.loadFromFile("../data/mine.png");
    texture.setSmooth(true);

    sf::Sprite sprite(texture);

    float spriteX = sprite.getTextureRect().width;

    float spriteY = sprite.getTextureRect().height;

    sprite.setScale((size_ * graphics::SCALE) / spriteX, (size_ * graphics::SCALE) / spriteY);
    sprite.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
    sprite.setRotation(rotation * graphics::DEG);
    sprite.setOrigin(spriteX * 0.5, spriteY * 0.5);

    window.draw(sprite);
}

BonusMine::~BonusMine()
{
    body_->GetWorld()->DestroyBody(body_);
    body_ = nullptr;
}
