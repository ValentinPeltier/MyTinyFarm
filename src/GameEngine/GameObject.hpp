#pragma once

#include <map>
#include <string>

#include "Transform.hpp"

namespace GameEngine {
    class GameObject {
    public:
        /**
         * @brief Instantiate a new GameObject object with default transform values.
         *
         * @param name The name of the game object
         */
        GameObject(std::string name) : _name{name} {}

        /**
         * @brief Instantiate a new GameObject object
         *
         * @param name The name of the game object
         * @param transform The initial transform value of the game object
         */
        GameObject(std::string name, Transform transform) : _name{name}, _transform{transform} {}

        /**
         * @brief Unallocate children memory.
         */
        virtual ~GameObject();

        /**
         * @brief Returns the name of the game object.
         *
         * @return The name of the game object
         */
        const std::string& getName() const { return _name; }

        /**
         * @brief Returns the full name of the game object.
         * Each full name is unique.
         * It represents the game object position in the game objects tree structure,
         * with each game object being delimited by a slash.
         * A full name always starts with a slash.
         *
         * @return The full name of the game object
         */
        std::string getFullName() const;

        /**
         * @brief Returns the parent game object in the game objects tree structure.
         *
         * @return The parent game object
         */
        GameObject* getParent() const { return _parent; }

        /**
         * @brief Adds a child to the game object.
         * The child position will be based on its parent position.
         *
         * @param gameObject The child game object
         * @return A pointer to the child game object.
         * Equals to nullptr if the name is already taken or for std::map related reasons.
         */
        GameObject* addChild(GameObject* gameObject);

        /**
         * @brief Returns the specified child according to its name.
         *
         * @param name The name of the child game object
         * @return A pointer to the child game object.
         * Equals to nullptr if the child doesn't exist.
         */
        GameObject* getChild(std::string name);

        /**
         * @brief Removes the specified game object from the game objects tree structure.
         *
         * @param gameObject The game object to remove
         * @return true if the game object has been removed, false otherwise
         */
        static bool removeGameObject(GameObject* gameObject);

        /**
         * @brief Call update method on itself and then on each of its children.
         */
        void updateItselfAndChildren();

    private:
        GameObject();

        /**
         * @brief Customizable function called every frame.
         */
        virtual void update() {}

        /**
         * @brief Removes any slash in the name.
         *
         * @param name A pointer to the name to be sanitized
         */
        void sanitizeName(std::string* name);

        std::string _name;
        GameObject* _parent = nullptr;
        std::map<std::string, GameObject*> children{};

        Transform _transform{};
    };
}