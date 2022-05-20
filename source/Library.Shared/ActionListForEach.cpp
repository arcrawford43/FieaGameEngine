#include "pch.h"
#include "ActionListForEach.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListForEach);
	ActionListForEach::ActionListForEach() :
		ActionList(ActionListForEach::TypeIdClass())
	{
	}

	ActionListForEach::ActionListForEach(size_t typeID) :
		ActionList(typeID)
	{
	}

	const Vector<Signature> ActionListForEach::Signatures()
	{
		return Vector<Signature>
		{
			{ "target", DatumTypes::String, 1, offsetof(ActionListForEach, _target) },
			{ "index", DatumTypes::Integer, 1, offsetof(ActionListForEach, _index) }
		};
	}

	ActionListForEach* ActionListForEach::Clone() const
	{
		return new ActionListForEach(*this);
	}

	bool ActionListForEach::Equals(const RTTI* rhs) const
	{
		const ActionListForEach* rhsADA = rhs->As<ActionListForEach>();
		if (rhsADA == nullptr)
		{
			return false;
		}

		return Name() == rhsADA->Name() &&
			_target == rhsADA->_target &&
			ActionList::Equals(rhsADA);

	}

	std::string ActionListForEach::ToString() const
	{
		return "ActionListForEach: "s + Name();
	}

	void ActionListForEach::Update(const GameTime& gameTime)
	{
		Datum* datum = Search(_target);

		for (_index = 0; _index < datum->Size(); ++_index)
		{
			ActionList::Update(gameTime);
		}
	}
}