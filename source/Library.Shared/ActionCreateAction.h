#pragma once
#include "Action.h"

namespace FieaGameEngine
{
    class ActionCreateAction :
        public Action
    {
        RTTI_DECLARATIONS(ActionCreateAction, Action)

    public:
        void Update(const GameTime& gameTime) override;
        ActionCreateAction();
        static const Vector<Signature> Signatures();
        ActionCreateAction* Clone() const override;
        bool Equals(const RTTI* rhs) const override;
        std::string ToString() const override;

        inline static Vector< std::pair<Scope*, Action*>> sQue;
    protected:
        ActionCreateAction(size_t typeID);
    private:
        std::string _actionName;
        std::string _instanceName;
        std::string _targetName;
    };
    ConcreteFactory(ActionCreateAction, Scope)
}

