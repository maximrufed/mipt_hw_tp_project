#include "weaponBuckshot.h"

WeaponBuckshot::WeaponBuckshot(std::shared_ptr<Tank> tank, int id)
{
    id_ = id;
    tank_ = tank;

    // create fixture
    b2PolygonShape dynamicBox;
    b2Vec2 center(0, -graphics::weaponBuckshotSizeY * 0.5);
    dynamicBox.SetAsBox(graphics::weaponBuckshotSizeX * 0.5, graphics::weaponBuckshotSizeY * 0.5, center, 0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    fixtureDef.filter.categoryBits = 0x0001;
    fixtureDef.filter.maskBits = 0xFFFD;

    auto bodyTank = tank->getBody();

    fixture_ = std::shared_ptr<b2Fixture>(bodyTank->CreateFixture(&fixtureDef), [](b2Fixture*){});

    // ClassData *tankData = new ClassData("tank", this);
    // body_->GetUserData().pointer = reinterpret_cast<uintptr_t>(tankData);
}

std::vector<std::shared_ptr<Bullet>> WeaponBuckshot::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0 || !tank_)
    {
        return {};
    }

    std::vector<std::shared_ptr<Bullet>> result;

    for (int i = 0; i < bulletAmount_; ++i)
    {

        float angleRad = tank_->getBody()->GetAngle() - 1.57 + ((math::getRand() % 100) * 1) / 300.f;
        b2Vec2 pos = tank_->getBody()->GetPosition();
        float length = graphics::weaponBuckshotSizeY + graphics::buckshotBulletRadius + 0.2;
        pos.x += cos(angleRad) * length;
        pos.y += sin(angleRad) * length;

        auto bullet = std::make_shared<BulletBasicTimer>(world, graphics::buckshotBulletRadius, bulletLiveTime_, pos, bulletVelocity_, angleRad);
        bullet->setWeaponID(id_);
        bullet->setTankID(tank_->getTankID());
        bullet->setBulletID(nextBulletID++);
        result.push_back(std::move(bullet));
    }
    nBulletsLeft_--;

    if (nBulletsLeft_ <= 0) {
        alive_ = false;
    }

    return result;
}

void WeaponBuckshot::step(float timeStep) {}

void WeaponBuckshot::bulletDie() {}

WeaponBuckshot::~WeaponBuckshot()
{
    tank_->getBody()->DestroyFixture(fixture_.get());
}

void WeaponBuckshot::setTank(std::shared_ptr<Tank> tank)
{
    tank_ = tank;
}

std::shared_ptr<b2Fixture> WeaponBuckshot::getFixture()
{
    return fixture_;
}
