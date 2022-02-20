#pragma once

#include <iostream>
#include <string>

#include "GameObject.hpp"
#include "Transform.hpp"

namespace GameEngine {
    class Camera : public GameObject {
    public:
        Camera(std::string name, Transform transform) : GameObject(name, transform){};

        void update();
    };
}