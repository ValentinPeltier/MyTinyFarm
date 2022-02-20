#pragma once

#include "Descriptors.hpp"
#include "Device.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

// std
#include <memory>
#include <vector>

namespace GraphicsEngine {
    class Application {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        static Application &getInstance() {
            static Application instance;
            return instance;
        }

        void run();

    private:
        Application();
        ~Application();

        void loadGameObjects();

        Window window{WIDTH, HEIGHT, "Vulkan Tutorial"};
        Device device{window};
        Renderer renderer{window, device};

        // note: order of declarations matters
        std::unique_ptr<DescriptorPool> globalPool{};
        GameObject::Map gameObjects;
    };
}
