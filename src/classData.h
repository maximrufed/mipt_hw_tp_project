#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "box2d/box2d.h"
#include "constants.h"

struct ClassData {
    std::string type = "";  // tank bullet
    void* pointer = nullptr;

    ClassData(std::string type, void* pointer) : type(type), pointer(pointer){};
};
