#include "weaponBullet.h"

WeaponBullet::WeaponBullet(int id)
{
    id_ = id;
}

std::vector<Bullet *> WeaponBullet::fire(b2World &world, Tank &tank, int &nextBulletID)
{
    if (nBulletsLeft_ <= 0)
    {
        return {};
    }

    std::vector<Bullet *> result;

    float angleRad = tank.getBody()->GetAngle() - 1.57;
    b2Vec2 pos = tank.getBody()->GetPosition();
    float length = tank.getSizeGunY() + bulletRadius_;
    pos.x += cos(angleRad) * length;
    pos.y += sin(angleRad) * length;

    Bullet *bullet = new BulletBasicTimer(world, bulletRadius_, bulletLiveTime_, pos, bulletVelocity_, angleRad);
    bullet->setWeaponID(id_);
    bullet->setTankID(tank.getTankID());
    bullet->setBulletID(nextBulletID++);
    result.push_back(bullet);

    nBulletsLeft_--;

    return result;
}

bool WeaponBullet::isDead()
{
    return false;
}

void WeaponBullet::step(float timeStep)
{
}

void WeaponBullet::bulletDie()
{
    std::cout << "left++" << std::endl;
    nBulletsLeft_++;
}
