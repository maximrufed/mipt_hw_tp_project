#include "weaponMine.h"

WeaponMine::WeaponMine(int id)
{
    id_ = id;
}

std::vector<Bullet *> WeaponMine::fire(b2World &world, Tank &tank, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0)
        return {};

    std::vector<Bullet *> result;

    // float angleRad = tank.getBody()->GetAngle() - 1.57;
    // b2Vec2 pos = tank.getBody()->GetPosition();
    // float length = tank.getSizeGunY() + bulletRadius_ + 0.1;
    // pos.x += cos(angleRad) * length;
    // pos.y += sin(angleRad) * length;

    // Bullet *bullet = new BulletBasicTimer(world, bulletRadius_, bulletLiveTime_, pos, bulletVelocity_, angleRad);
    // bullet->setWeaponID(id_);
    // bullet->setTankID(tank.getTankID());
    // bullet->setBulletID(nextBulletID++);
    // result.push_back(bullet);

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
