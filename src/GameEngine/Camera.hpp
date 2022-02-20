#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "GameObject.hpp"
#include "Transform.hpp"

namespace GameEngine {
    class Camera : public GameObject {
    public:
        Camera(std::string name, Transform transform) : GameObject(name, transform){};

        void update();

        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
        };

        KeyMappings _keys{};
        float _moveSpeed{3.f};
        float _lookSpeed{1.5f};
    };
}