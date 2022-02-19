#pragma once

#include <chrono>

namespace GameEngine {
    class Clock {
    public:
        void start();
        void update();
        static float getDeltaTime() { return deltaTime; };

    private:
        static float deltaTime;
        static std::chrono::_V2::system_clock::time_point currentTime;
    };
}