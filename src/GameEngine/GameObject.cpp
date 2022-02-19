#include "GameObject.hpp"

namespace GameEngine {
    GameObject::GameObject(std::string name) : _name{name} {
        std::cout << "GameObject ctor(" + name + ")\n";
    }
}