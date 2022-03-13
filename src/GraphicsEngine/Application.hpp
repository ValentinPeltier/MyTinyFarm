#pragma once

#include <glfw.hpp>

#include "Camera.hpp"
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

        static Application *getInstance() {
            static Application instance;
            return &instance;
        }

        GLFWwindow *getWindow() { return window.getGLFWwindow(); }
        Camera *getCamera() { return &camera; }

        void run();

    private:
        Application();
        ~Application();

        void loadGameObjects();

        Window window{WIDTH, HEIGHT, "My Tiny Farm"};
        Device device{window};
        Renderer renderer{window, device};
        Camera camera{};

        // note: order of declarations matters
        std::unique_ptr<DescriptorPool> globalPool{};
        GameObject::Map gameObjects;
    };
}
