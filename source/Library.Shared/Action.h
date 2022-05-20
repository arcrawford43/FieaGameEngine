#pragma once
#include "Attributed.h"
#include "GameTime.h"

namespace FieaGameEngine
{
    class Action : public Attributed
    {
        RTTI_DECLARATIONS(Action, Attributed)

    public:
        Action();
        virtual void Update(const GameTime& gameTime) = 0;
        inline const std::string& Name() const;
        inline void SetName(std::string name);
        static const Vector<Signature> Signatures();

    protected:
        Action(size_t typeID);
    private:
        std::string _name;
    };
}

#include "Action.inl"