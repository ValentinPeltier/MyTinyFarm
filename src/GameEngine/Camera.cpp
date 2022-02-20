#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "../GraphicsEngine/Application.hpp"
#include "Clock.hpp"

namespace GameEngine {
    void Camera::update() {
        float dt = Clock::getDeltaTime();
        GLFWwindow* window = GraphicsEngine::Application::getInstance().getWindow();

        glm::vec3 rotate{0};
        if (glfwGetKey(window, _keys.lookRight) == GLFW_PRESS) rotate.y += 1.f;
        if (glfwGetKey(window, _keys.lookLeft) == GLFW_PRESS) rotate.y -= 1.f;
        if (glfwGetKey(window, _keys.lookUp) == GLFW_PRESS) rotate.x += 1.f;
        if (glfwGetKey(window, _keys.lookDown) == GLFW_PRESS) rotate.x -= 1.f;

        if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
            _transform.rotation += _lookSpeed * dt * glm::normalize(rotate);
        }

        // limit pitch values between about +/- 85ish degrees
        _transform.rotation.x = glm::clamp(_transform.rotation.x, -1.5f, 1.5f);
        _transform.rotation.y = glm::mod(_transform.rotation.y, glm::two_pi<float>());

        float yaw = _transform.rotation.y;
        const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
        const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
        const glm::vec3 upDir{0.f, -1.f, 0.f};

        glm::vec3 moveDir{0.f};
        if (glfwGetKey(window, _keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
        if (glfwGetKey(window, _keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
        if (glfwGetKey(window, _keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
        if (glfwGetKey(window, _keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;
        if (glfwGetKey(window, _keys.moveUp) == GLFW_PRESS) moveDir += upDir;
        if (glfwGetKey(window, _keys.moveDown) == GLFW_PRESS) moveDir -= upDir;

        if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
            _transform.position += _moveSpeed * dt * glm::normalize(moveDir);
        }

        GraphicsEngine::Application::getInstance().getCamera()->setViewYXZ(
            _transform.position,
            _transform.rotation);
    }
}