#include "weaponBullet.h"

WeaponBullet::WeaponBullet(int id)
{
    id_ = id;
    // here
}

std::vector<Bullet *> WeaponBullet::fire(b2World &world, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0 || tank_ == nullptr)
    {
        return {};
    }

    std::vector<Bullet *> result;

    float angleRad = tank_->getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank_->getBody()->GetPosition();
    float length = tank_->getSizeGunY() + bulletRadius_ + 0.1;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    Bullet *bullet = new BulletBasicTimer(world, bulletRadius_, bulletLiveTime_, pos, bulletVelocity_, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank_->getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(bullet);

    nBulletsLeft_--;

    return result;
}

void WeaponBullet::step(float timeStep)
{
}

void WeaponBullet::bulletDie()
{
    nBulletsLeft_++;
}
