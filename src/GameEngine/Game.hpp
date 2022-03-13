#pragma once

#include "GameObject.hpp"

namespace GameEngine {
    class GameObject;

    class Game {
    public:
        Game();
        ~Game();

        void update();

    private:
        GameObject* _rootGameObject;
    };
}