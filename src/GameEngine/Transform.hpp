#pragma once

#include <glm/glm.hpp>
#include <string>

namespace GameEngine {
    struct Transform {
        glm::vec3 position;
        glm::vec3 rotation;
        float scale = 1.f;

        std::string toString() {
            const char* format =
                "Position (%.2f, %.2f, %.2f) ; Rotation (%.2f, %.2f, %.2f) ; Scale (%.2f)";
            int size = snprintf(
                nullptr,
                0,
                format,
                position.x,
                position.y,
                position.z,
                rotation.x,
                rotation.y,
                rotation.z,
                scale);
            char result[size + 1];
            snprintf(
                result,
                size + 1,
                format,
                position.x,
                position.y,
                position.z,
                rotation.x,
                rotation.y,
                rotation.z,
                scale);

            return result;
        }
    };
}