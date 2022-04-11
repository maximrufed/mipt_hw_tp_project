#pragma once

#include <random>

#include "box2d/box2d.h"

namespace math {
// init random
extern std::random_device rd;
extern std::mt19937 rng;
extern std::uniform_int_distribution<int> uni;

extern int getRand();
};  // namespace math

namespace graphics
{
    const float tankSizeX = 3.12;
    const float tankSizeY = 5.;
    const float weaponBulletSizeX = 22. * .02;
    const float weaponBulletSizeY = 139. * .02;
    const float weaponBuckshotSizeX = 26. * .02;
    const float weaponBuckshotSizeY = 139. * .02;
    const float weaponMineSizeX = 66. * .02;
    const float weaponMineSizeY = 86. * .02;
    const float bulletRadius = .4;
    const float buckshotBulletRadius = .25;
    const float mineBulletSize = 1.5;
    const float wallLength = 10.;
    const float wallWidth = .2;
    const float bonusSize = 3;
    const float textSize = 5;
    const int sizeFieldX = 8;
    const int sizeFieldY = 6;
}
