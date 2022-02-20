#pragma once

#include <map>
#include <memory>
#include <string>

#include "GameObject.hpp"

namespace GameEngine {
    class Game {
    public:
        static Game* getInstance() {
            static Game instance;
            return &instance;
        }

        Game(Game const&) = delete;
        void operator=(Game const&) = delete;

        void update();

        std::shared_ptr<GameObject> addGameObject(GameObject* gameObject);
        bool removeGameObject(std::shared_ptr<GameObject> gameObject);
        std::shared_ptr<GameObject> getGameObject(std::string name);

    private:
        Game();

        std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
    };
}