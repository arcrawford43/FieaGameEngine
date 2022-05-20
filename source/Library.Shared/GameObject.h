#pragma once
#include "Attributed.h"
#include "GameTime.h"
#include "Factory.h"

namespace FieaGameEngine
{
    struct Transform
    {
        glm::vec4 _position;
        glm::vec4 _rotation;
        glm::vec4 _scale;
    };

    class GameObject : public Attributed
    {
        RTTI_DECLARATIONS(GameObject, Attributed)

    public:
        /// <summary>
        /// Constructor
        /// </summary>
        GameObject();

        /// <summary>
        /// Defaulted Destructor
        /// </summary>
        ~GameObject() = default;

        /// <summary>
        /// Signatures method
        /// </summary>
        /// <returns></returns>
        static const Vector<Signature> Signatures();

        /// <summary>
        /// Method that clones the GameObject
        /// </summary>
        /// <returns></returns>
        GameObject* Clone() const override;

        /// <summary>
        /// Equals Method that compares two GameObjects
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        bool Equals(const RTTI* rhs) const override;

        /// <summary>
        /// Update method that calls update on its Children
        /// </summary>
        /// <param name="gameTime"></param>
        virtual void Update(const GameTime& gameTime);

        /// <summary>
        /// To String function
        /// </summary>
        /// <returns></returns>
        std::string ToString() const override;

        std::string _name{ "" };

        Transform _transform{ {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f} };

    protected:
        GameObject(size_t typeID);

    private:
        Datum* _children;
        Datum* _actions;
    };

    ConcreteFactory(GameObject, Scope)
}