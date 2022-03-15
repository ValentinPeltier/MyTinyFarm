#include "GameObject.hpp"

#include <algorithm>

#include "Game.hpp"

namespace GameObjects {
    GameObject::~GameObject() {
        // Call destructor on all children
        for (auto child = children.begin(); child != children.end(); child++) {
            delete child->second;
        }
    }

    std::string GameObject::getFullName() const {
        if (_parent == nullptr) return _name;

        std::string parentFullname = _parent->getFullName();
        if (parentFullname == "/") parentFullname = "";

        return parentFullname + std::string("/") + _name;
    }

    GameObject* GameObject::addChild(GameObject* gameObject) {
        sanitizeName(&gameObject->_name);
        gameObject->_game = _game;

        auto result = children.emplace(gameObject->getFullName(), gameObject);

        if (!result.second) {
            return nullptr;
        }

        // Assign parent
        result.first->second->_parent = this;

        return result.first->second;
    }

    GameObject* GameObject::getChild(std::string name) {
        auto result = children.find(name);

        if (result == children.end()) {
            return nullptr;
        }

        return result->second;
    }

    bool GameObject::removeGameObject(GameObject* gameObject) {
        // Find the parent
        GameObject* parent = gameObject->getParent();

        // Remove the specified game object from its children
        return parent->children.erase(gameObject->getName()) == 1;
    }

    void GameObject::updateItselfAndChildren() {
        update();

        // Call update method on every children
        for (auto it = children.begin(); it != children.end(); it++) {
            it->second->updateItselfAndChildren();
        }
    }

    void GameObject::sanitizeName(std::string* name) {
        name->erase(std::remove(name->begin(), name->end(), '/'), name->end());
    }
}