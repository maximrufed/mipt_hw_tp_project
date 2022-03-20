#include "weaponMine.h"

WeaponMine::WeaponMine(int id)
{
    id_ = id;
}

std::vector<Bullet *> WeaponMine::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0)
        return {};

    std::vector<Bullet *> result;

    float angleRad = tank_->getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank_->getBody()->GetPosition();
    float length = tank_->getSizeGunY() + bulletSize_ * 0.5 + 0.2;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    Bullet *bullet = new BulletMine(world, bulletSize_, pos, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank_->getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(bullet);

    nBulletsLeft_--;

    if (nBulletsLeft_ <= 0)
        alive_ = false;

    return result;
}

void WeaponMine::step(float timeStep)
{
    // nothing
}

void WeaponMine::bulletDie()
{
    // nothing
}
