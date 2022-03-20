#include "weapon.h"

bool Weapon::isDead()
{
    return !alive_;
}

void Weapon::setTank(Tank *tank)
{
    tank_ = tank;
}

int Weapon::getID()
{
    return id_;
}
void Weapon::setID(int id)
{
    id_ = id;
}
