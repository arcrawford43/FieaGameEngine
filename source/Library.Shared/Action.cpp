#include "pch.h"
#include "Action.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action)

	Action::Action() :
		Attributed(Action::TypeIdClass())
	{
	}

	Action::Action(size_t typeID) :
		Attributed(typeID)
	{
	}

	const Vector<Signature> Action::Signatures()
	{
		return Vector<Signature>
		{
			{ "name", DatumTypes::String, 1, offsetof(Action, _name) },
		};
	}
}