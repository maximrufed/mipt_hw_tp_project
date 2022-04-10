#pragma once

#include "box2d/box2d.h"

#include <memory>
#include "classData.h"
#include "constants.h"
#include "weapon.h"

class Weapon;

class Bullet {
   protected:
    bool alive_ = true;
    std::shared_ptr<Weapon> weapon_;

    int bulletID_ = -1;
    int tankID_ = -1;
    int weaponID_ = -1;

   public:
    virtual void step(float timeStep) = 0;

    virtual bool isDead() = 0;

    virtual void die();

    void setBulletID(int id);

    void setTankID(int id);

    void setWeaponID(int id);

    int getBulletID();

    int getTankID();

    int getWeaponID();

    virtual ~Bullet();
};
