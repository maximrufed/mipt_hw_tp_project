#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <string>

#include "constants.h"

struct ClassData
{
    std::string type = ""; // tank bullet
    void *pointer;

    ClassData(std::string type, void *pointer) : type(type), pointer(pointer){};
};
