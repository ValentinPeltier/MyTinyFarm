#pragma once

#include <glfw.hpp>
#include <glm/glm.hpp>

#include "Transform.hpp"

namespace GameEngine {
    class Camera {
    public:
        static Camera* getInstance() {
            static Camera instance;
            return &instance;
        }

        static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        void handleCursorPosition(glm::vec2 position);
        void handleScroll(float delta);

        void updateCameraView();

    private:
        Camera();

        float _moveSpeed{4.f};
        float _lookSpeed{5.f};
        float _zoomSpeed{2000.f};

        float _maxYPosition{-2.f};
        float _minYPosition{-20.f};

        Transform _transform{{10.f, -4.f, -11.f}, {-.2f, 5.5f, .0f}};
        glm::vec2 _cursorPosition{-1.f, -1.f};

        GLFWwindow* _window;
    };
}