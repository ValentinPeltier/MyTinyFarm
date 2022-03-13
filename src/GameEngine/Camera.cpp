#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../GraphicsEngine/Application.hpp"
#include "Clock.hpp"
#include "Game.hpp"

namespace GameEngine {
    Camera::Camera() {
        _window = GraphicsEngine::Application::getInstance()->getWindow();

        glfwSetCursorPosCallback(_window, cursorPositionCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);
        glfwSetScrollCallback(_window, scrollCallback);

        updateCameraView();
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    void Camera::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        Camera::getInstance()->handleCursorPosition({xpos, ypos});
    }

    void Camera::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        bool shouldDisableCursor =
            glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS ||
            glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

        glfwSetInputMode(
            window,
            GLFW_CURSOR,
            shouldDisableCursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        Camera::getInstance()->handleScroll(yoffset);
    }
#pragma GCC diagnostic pop

    void Camera::handleCursorPosition(glm::vec2 position) {
        if (_cursorPosition == glm::vec2{-1.f, -1.f}) {
            _cursorPosition = position;
            return;
        }

        const float dTime = Clock::getDeltaTime();
        const glm::vec2 dPosition = position - _cursorPosition;

        // Rotation
        if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            _transform.rotation += _lookSpeed * dTime * glm::vec3(-dPosition.y, dPosition.x, 0.f);
        }

        _transform.rotation.x =
            glm::clamp(_transform.rotation.x, -glm::radians(90.f), -glm::radians(10.f));
        _transform.rotation.y = glm::mod(_transform.rotation.y, glm::two_pi<float>());

        // Position
        const float yaw = _transform.rotation.y;
        const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
        const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};

        if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            _transform.position += _moveSpeed * dTime *
                                   (float)glm::pow(-_transform.position.y, 1.1f) *
                                   (dPosition.y * forwardDir - dPosition.x * rightDir);
        }

        updateCameraView();

        _cursorPosition = position;
    }

    void Camera::handleScroll(float delta) {
        const float dTime = Clock::getDeltaTime();

        glm::vec3 target = _transform.position + delta * _zoomSpeed * dTime * _transform.forward();

        // Clamp scroll value
        const glm::vec3& a = _transform.position;
        const glm::vec3& b = target;
        if (target.y > _maxYPosition) {
            const float t = (_maxYPosition - b.y) / (a.y - b.y);
            target = {(a.x - b.x) * t + b.x, _maxYPosition, (a.z - b.z) * t + b.z};
        } else if (target.y < _minYPosition) {
            const float t = (_minYPosition - b.y) / (a.y - b.y);
            target = {(a.x - b.x) * t + b.x, _minYPosition, (a.z - b.z) * t + b.z};
        }

        _transform.position = target;

        updateCameraView();
    }

    void Camera::updateCameraView() {
        GraphicsEngine::Application::getInstance()->getCamera()->setViewYXZ(
            _transform.position,
            _transform.rotation);
    }
}