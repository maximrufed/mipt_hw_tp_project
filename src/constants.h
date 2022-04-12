#pragma once

#include <SFML/Graphics.hpp>
#include <random>

#include "box2d/box2d.h"

namespace math {
// init random
extern std::random_device rd;
extern std::mt19937 rng;
extern std::uniform_int_distribution<int> uni;

extern int getRand();
};  // namespace math

namespace graphics {
const float SCALE = 10;  // 1 meter = 10 pixels
const float DEG = 57.2977f;
}  // namespace graphics
