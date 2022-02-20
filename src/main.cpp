
#include "GraphicsEngine/Application.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    try {
        GraphicsEngine::Application::getInstance()->run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}