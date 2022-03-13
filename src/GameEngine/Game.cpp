#include "Game.hpp"

#include "Camera.hpp"
#include "Clock.hpp"
#include "GameObject.hpp"

namespace GameEngine {
    Game::Game() {
        _rootGameObject = new GameObject("/");

        // Initialize camera
        Camera::getInstance();

        // Add a clock
        _rootGameObject->addChild(new Clock("clock"));
    }

    Game::~Game() { delete _rootGameObject; }

    void Game::update() { _rootGameObject->updateItselfAndChildren(); }
}