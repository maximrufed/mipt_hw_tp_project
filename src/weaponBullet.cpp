#include "weaponBullet.h"

WeaponBullet::WeaponBullet()
{
    // init
}

std::vector<Bullet *> WeaponBullet::fire(b2World &world, Tank &tank)
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

    result.push_back(new BulletBasicTimer(world, bulletRadius_, bulletLiveTime_, pos, bulletVelocity_, angleRad));

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
