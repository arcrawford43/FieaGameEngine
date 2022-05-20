#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:
		ActionList();
		void Update(const GameTime& gameTime) override;
		static const Vector<Signature> Signatures();
		ActionList* Clone() const override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

	protected:
		ActionList(size_t typeID);
	private:
		Datum* _actions;
	};

	ConcreteFactory(ActionList, Scope)
}

