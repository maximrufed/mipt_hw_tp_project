#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"

#include <string>

// #include "game.h"

struct ClassData
{
    std::string type = ""; // tank bullet
    int id;

    ClassData(std::string type, int id) : type(type), id(id){};
};
