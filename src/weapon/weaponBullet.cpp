#include "weaponBullet.h"

WeaponBullet::WeaponBullet(b2World &world, std::shared_ptr<Tank> tank, int id)
{
    id_ = id;
    tank_ = tank;

    // create fixture
    b2PolygonShape dynamicBox;
    b2Vec2 center(0, -graphics::weaponBulletSizeY * 0.5);
    dynamicBox.SetAsBox(graphics::weaponBulletSizeX * 0.5, graphics::weaponBulletSizeY * 0.5, center, 0);

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

std::vector<std::shared_ptr<Bullet>> WeaponBullet::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0 || !tank_)
    {
        return {};
    }

    std::vector<std::shared_ptr<Bullet>> result;

    float angleRad = tank_->getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank_->getBody()->GetPosition();
    float length = graphics::weaponBulletSizeY + graphics::bulletRadius + 0.1;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    auto bullet = std::make_shared<BulletBasicTimer>(world, graphics::bulletRadius, bulletLiveTime_, pos, bulletVelocity_, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank_->getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(std::move(bullet));

    nBulletsLeft_--;

    return result;
}

void WeaponBullet::step(float timeStep) {
}

void WeaponBullet::bulletDie() {
    nBulletsLeft_++;
}

WeaponBullet::~WeaponBullet()
{
    tank_->getBody()->DestroyFixture(fixture_.get());
}

void WeaponBullet::setTank(std::shared_ptr<Tank> tank)
{
    tank_ = tank;
}

std::shared_ptr<b2Fixture> WeaponBullet::getFixture()
{
    return fixture_;
}
