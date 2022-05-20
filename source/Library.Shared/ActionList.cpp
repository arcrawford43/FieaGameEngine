#include "pch.h"
#include "ActionList.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);
	ActionList::ActionList() :
		Action(ActionList::TypeIdClass())
	{
		_actions = Find("actions");
		assert(_actions != nullptr);
	}

	ActionList::ActionList(size_t typeID) :
		Action(typeID)
	{
		_actions = Find("actions");
		assert(_actions != nullptr);
	}

	const Vector<Signature> ActionList::Signatures()
	{
		return Vector<Signature>
		{
			{ "actions", DatumTypes::Table, 0, 0 }
		};
	}

	ActionList* ActionList::Clone() const
	{
		return new ActionList(*this);
	}

	bool ActionList::Equals(const RTTI* rhs) const
	{
		const ActionList* rhsAL = rhs->As<ActionList>();
		if (rhsAL == nullptr)
		{
			return false;
		}

		assert(_actions);
		assert(rhsAL->_actions);
		return Name() == rhsAL->Name() &&
			*_actions == *(rhsAL->_actions);
	}

	std::string ActionList::ToString() const
	{
		return "ActionList: "s + Name();
	}

	void ActionList::Update(const GameTime& gameTime)
	{
		assert(_actions);
		for (size_t i = 0; i < _actions->Size(); ++i)
		{
			Scope* child = _actions->GetTable(i);
			assert(child->Is(Action::TypeIdClass()));

			Action* childAction = static_cast<Action*>(child);
			childAction->Update(gameTime);
		}
	}
}
