#include "weaponBuckshot.h"

WeaponBuckshot::WeaponBuckshot(Tank *tank, int id)
{
    id_ = id;
    tank_ = tank;

    // create fixture
    b2PolygonShape dynamicBox;
    b2Vec2 center(0, -sizeGunY_ * 0.5);
    dynamicBox.SetAsBox(sizeGunX_ * 0.5, sizeGunY_ * 0.5, center, 0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    fixtureDef.filter.categoryBits = 0x0001;
    fixtureDef.filter.maskBits = 0xFFFD;

    b2Body *bodyTank = tank->getBody();

    fixture_ = bodyTank->CreateFixture(&fixtureDef);

    // ClassData *tankData = new ClassData("tank", this);
    // body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);
}

std::vector<Bullet *> WeaponBuckshot::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0 || tank_ == nullptr)
    {
        return {};
    }

    std::vector<Bullet *> result;

    for (int i = 0; i < bulletAmount_; ++i)
    {

        float angleRad = tank_->getBody()->GetAngle() - 1.57 + ((math::getRand() % 100) * 1) / 300.f;
        b2Vec2 pos = tank_->getBody()->GetPosition();
        float length = sizeGunY_ + bulletRadius_ + 0.2;
        pos.x += cos(angleRad) * length;
        pos.y += sin(angleRad) * length;

        Bullet *bullet = new BulletBasicTimer(world, bulletRadius_, bulletLiveTime_, pos, bulletVelocity_, angleRad);
        bullet->setWeaponID(id_);
        bullet->setTankID(tank_->getTankID());
        bullet->setBulletID(nextBulletID++);
        result.push_back(bullet);
    }
    nBulletsLeft_--;

    if (nBulletsLeft_ <= 0)
    {
        alive_ = false;
    }

    return result;
}

void WeaponBuckshot::step(float timeStep) {}

void WeaponBuckshot::bulletDie() {}

void WeaponBuckshot::debug_draw(sf::RenderWindow &window)
{
    b2Vec2 position = tank_->getBody()->GetPosition();
    float rotation = tank_->getBody()->GetAngle();

    {
        sf::RectangleShape rectangle(sf::Vector2f(sizeGunX_ * graphics::SCALE, sizeGunY_ * graphics::SCALE));
        rectangle.setFillColor(sf::Color::Cyan);
        rectangle.setPosition(position.x * graphics::SCALE, position.y * graphics::SCALE);
        rectangle.rotate(rotation * graphics::DEG);
        rectangle.setOrigin(sizeGunX_ * 0.5 * graphics::SCALE, sizeGunY_ * graphics::SCALE);
        window.draw(rectangle);
    }
}

WeaponBuckshot::~WeaponBuckshot()
{
    tank_->getBody()->DestroyFixture(fixture_);
    fixture_ = nullptr;
    tank_ = nullptr;
}

void WeaponBuckshot::setTank(Tank *tank)
{
    tank_ = tank;
}

b2Fixture *WeaponBuckshot::getFixture()
{
    return fixture_;
}
