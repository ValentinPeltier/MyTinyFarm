#pragma once

#include <iostream>
#include <string>

#include "GameObject.hpp"

namespace GameEngine {
    class Camera : public GameObject {
    public:
        Camera(std::string name);
    };
}