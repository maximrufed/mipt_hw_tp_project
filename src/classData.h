#pragma once

#include <string>

#include "constants.h"

struct ClassData
{
    std::string type = ""; // tank bullet
    void *pointer = nullptr;

    ClassData(std::string type, void *pointer) : type(type), pointer(pointer) {};
};
