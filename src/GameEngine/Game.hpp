#pragma once

#include "GameObject.hpp"

namespace GameEngine {
    class Game {
    public:
        static Game* getInstance() {
            static Game instance;
            return &instance;
        }
        ~Game();
        /**
         * Singletons should not be cloneable.
         */
        Game(const Game&) = delete;
        /**
         * Singletons should not be assignable.
         */
        void operator=(const Game&) = delete;

        void update();

        GameObject* getRootGameObject() { return _rootGameObject; }

    private:
        Game();

        GameObject* _rootGameObject = nullptr;
    };
}