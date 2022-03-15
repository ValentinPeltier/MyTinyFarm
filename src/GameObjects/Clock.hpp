#pragma once

#include <chrono>
#include <string>

#include "GameObject.hpp"

namespace GameObjects {
    class Clock : public GameObject {
    public:
        Clock(std::string name) : GameObject(name) {}

        static float getDeltaTime() { return _deltaTime; };

    private:
        static float _deltaTime;
        static std::chrono::_V2::system_clock::time_point _currentTime;

        virtual void update() override;
    };

}