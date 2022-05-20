#pragma once
#include "Action.h"

namespace FieaGameEngine
{
    class ActionIncrement : public Action
    {
        RTTI_DECLARATIONS(ActionIncrement, Action)

    public:
        void Update(const GameTime& gameTime) override;
        ActionIncrement();
        static const Vector<Signature> Signatures();
        ActionIncrement* Clone() const override;
        bool Equals(const RTTI* rhs) const override;
        std::string ToString() const override;

    protected:
        ActionIncrement(size_t typeID);
    private:
        float _step{ 1.0f };
        std::string _target;
        Datum* _cacheTarget{ nullptr };
        bool _dirtyTarget{ true };
    };
    ConcreteFactory(ActionIncrement, Scope)
}
