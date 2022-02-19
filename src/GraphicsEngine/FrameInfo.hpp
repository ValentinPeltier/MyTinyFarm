#pragma once

#include "Camera.hpp"
#include "GameObject.hpp"

// lib
#include <vulkan/vulkan.h>

namespace GraphicsEngine {

    struct GlobalUbo {
        glm::mat4 projection{1.f};
        glm::mat4 view{1.f};
    };

    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        Camera &camera;
        VkDescriptorSet globalDescriptorSet;
        GameObject::Map &gameObjects;
    };
}
