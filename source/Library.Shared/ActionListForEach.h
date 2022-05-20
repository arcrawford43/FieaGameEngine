#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
    class ActionListForEach :
        public ActionList
    {
        RTTI_DECLARATIONS(ActionListForEach, ActionList)

    public:
        void Update(const GameTime& gameTime) override;
        ActionListForEach();
        static const Vector<Signature> Signatures();
        ActionListForEach* Clone() const override;
        bool Equals(const RTTI* rhs) const override;
        std::string ToString() const override;

        inline static Vector<Action*> sQue;
    protected:
        ActionListForEach(size_t typeID);
    private:
        size_t _index;
        std::string _target;
    };
    ConcreteFactory(ActionListForEach, Scope)
}

