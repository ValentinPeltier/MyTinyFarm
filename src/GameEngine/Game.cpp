#include "Game.hpp"

#include <iostream>

#include "Camera.hpp"
#include "Clock.hpp"

namespace GameEngine {
    Game::Game() {
        // Initialize camera
        Camera::getInstance();

        // Add a clock as a game object
        addGameObject(new Clock("clock"));
    }

    void Game::update() {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); it++) {
            it->second->update();
        }
    }

    std::shared_ptr<GameObject> Game::addGameObject(GameObject* gameObject) {
        auto result = gameObjects.emplace(gameObject->getName(), gameObject);

        if (!result.second) {
            return nullptr;
        }

        return result.first->second;
    }

    bool Game::removeGameObject(std::shared_ptr<GameObject> gameObject) {
        return gameObjects.erase(gameObject->getName()) == 1;
    }

    std::shared_ptr<GameObject> Game::getGameObject(std::string name) {
        auto result = gameObjects.find(name);

        if (result == gameObjects.end()) {
            return nullptr;
        }

        return result->second;
    }
}