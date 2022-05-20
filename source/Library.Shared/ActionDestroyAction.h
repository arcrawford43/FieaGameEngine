#pragma once
#include "Action.h"
namespace FieaGameEngine
{
    class ActionDestroyAction :
        public Action
    {
        RTTI_DECLARATIONS(ActionDestroyAction, Action)

    public:
        void Update(const GameTime& gameTime) override;
        ActionDestroyAction();
        static const Vector<Signature> Signatures();
        ActionDestroyAction* Clone() const override;
        bool Equals(const RTTI* rhs) const override;
        std::string ToString() const override;

        inline static Vector<Action*> sQue;
    protected:
        ActionDestroyAction(size_t typeID);
    private:
        std::string _instanceName;
        std::string _targetName;
    };
    ConcreteFactory(ActionDestroyAction, Scope)
}