#include "pch.h"
#include "ActionIncrement.h"

using namespace std::string_literals;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement)

	void ActionIncrement::Update(const GameTime& /*gameTime*/)
	{
		if (_dirtyTarget)
		{
			_cacheTarget = Search(_target);
			_dirtyTarget = false;
		}

		if (_cacheTarget)
		{
			switch (_cacheTarget->Type())
			{
				case (DatumTypes::Float):
				{
					_cacheTarget->GetFloat() += _step;
					break;
				}
				case (DatumTypes::Integer):
				{
					_cacheTarget->GetInteger() += static_cast<std::int32_t>(_step);
					break;
				}
			}
		}
	}

	ActionIncrement::ActionIncrement() :
		Action(ActionIncrement::TypeIdClass())
	{
	}

	ActionIncrement::ActionIncrement(size_t typeID) :
		Action(typeID)
	{
	}

	const Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector<Signature>
		{
			{ "step", DatumTypes::Float, 1, offsetof(ActionIncrement, _step) },
			{ "target", DatumTypes::String, 1, offsetof(ActionIncrement, _target) }
		};
	}

	ActionIncrement* ActionIncrement::Clone() const
	{
		return new ActionIncrement(*this);
	}

	bool ActionIncrement::Equals(const RTTI* rhs) const
	{
		const ActionIncrement* rhsAI = rhs->As<ActionIncrement>();
		if (rhsAI == nullptr)
		{
			return false;
		}

		return Name() == rhsAI->Name() &&
			_step == rhsAI->_step;
	}

	std::string ActionIncrement::ToString() const
	{
		return "ActionIncrement: "s + Name();
	}
}