#include "weapon.h"

bool Weapon::isDead()
{
    return !alive_;
}

int Weapon::getID()
{
    return id_;
}
void Weapon::setID(int id)
{
    id_ = id;
}
