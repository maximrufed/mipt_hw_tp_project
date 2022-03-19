#include "bullet.h"

void Bullet::die()
{
    alive_ = false;
}

void Bullet::setBulletID(int id)
{
    bulletID_ = id;
}

void Bullet::setTankID(int id)
{
    tankID_ = id;
}

void Bullet::setWeaponID(int id)
{
    weaponID_ = id;
}

int Bullet::getBulletID()
{
    return bulletID_;
}

int Bullet::getTankID()
{
    return tankID_;
}

int Bullet::getWeaponID()
{
    return weaponID_;
}
