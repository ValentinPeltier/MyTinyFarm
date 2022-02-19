#include "Clock.hpp"

#include <chrono>

namespace GameEngine {
    void Clock::start() { currentTime = std::chrono::high_resolution_clock::now(); }

    void Clock::update() {
        auto now = std::chrono::high_resolution_clock::now();

        // Update deltaTime and currentTime values
        deltaTime =
            std::chrono::duration<float, std::chrono::seconds::period>(now - currentTime).count();
        currentTime = now;
    }
}