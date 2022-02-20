#pragma once

#include <iostream>
#include <string>

#include "Transform.hpp"

namespace GameEngine {
    class GameObject {
    public:
        GameObject(std::string name, Transform transform) : _name{name}, _transform{transform} {};

        virtual void update() {}
        std::string& getName() { return _name; }

    protected:
        std::string _name;
        Transform _transform{};

    private:
        GameObject();
    };
}