#include "weaponMine.h"

WeaponMine::WeaponMine(std::shared_ptr<Tank> tank, int id)
{
    id_ = id;
    tank_ = tank;
}

std::vector<std::shared_ptr<Bullet>> WeaponMine::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0)
        return {};

    std::vector<std::shared_ptr<Bullet>> result;

    float angleRad = tank_->getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank_->getBody()->GetPosition();
    float length = (graphics::tankSizeY + graphics::mineBulletSize) * 0.5 + 0.2;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    auto bullet = std::make_shared<BulletMine>(world, graphics::mineBulletSize, pos, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank_->getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(std::move(bullet));

    nBulletsLeft_--;

    if (nBulletsLeft_ <= 0)
        alive_ = false;

    return result;
}

void WeaponMine::step(float timeStep) {
    // nothing
}

void WeaponMine::bulletDie() {
    // nothing
}

WeaponMine::~WeaponMine()
{
}

void WeaponMine::setTank(std::shared_ptr<Tank> tank)
{
    tank_ = tank;
}
