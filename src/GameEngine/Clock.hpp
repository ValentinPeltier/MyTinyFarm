#pragma once

#include <chrono>
#include <string>

#include "GameObject.hpp"

namespace GameEngine {
    class Clock : public GameObject {
    public:
        Clock(std::string name) : GameObject(name, {}) {}

        void update();
        static float getDeltaTime() { return _deltaTime; };

    private:
        static float _deltaTime;
        static std::chrono::_V2::system_clock::time_point _currentTime;
    };

}