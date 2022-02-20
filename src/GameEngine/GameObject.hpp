#pragma once

#include <iostream>
#include <string>

namespace GameEngine {
    class GameObject {
    public:
        GameObject(std::string name) : _name{name} {};

        virtual void update() {}
        std::string& getName() { return _name; }

    private:
        GameObject();
        std::string _name;
    };
}