#include "Clock.hpp"

namespace GameEngine {
    float Clock::_deltaTime = 0.f;

    std::chrono::_V2::system_clock::time_point Clock::_currentTime =
        std::chrono::high_resolution_clock::now();

    void Clock::update() {
        auto now = std::chrono::high_resolution_clock::now();

        // Update deltaTime and currentTime values
        _deltaTime =
            std::chrono::duration<float, std::chrono::seconds::period>(now - _currentTime).count();
        _currentTime = now;
    }
}