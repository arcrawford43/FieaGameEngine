#include "pch.h"
#include "ActionDestroyAction.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionDestroyAction);
	ActionDestroyAction::ActionDestroyAction() :
		Action(ActionDestroyAction::TypeIdClass())
	{
	}

	ActionDestroyAction::ActionDestroyAction(size_t typeID) :
		Action(typeID)
	{
	}

	const Vector<Signature> ActionDestroyAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "targetName", DatumTypes::String, 1, offsetof(ActionDestroyAction, _targetName) }
		};
	}

	ActionDestroyAction* ActionDestroyAction::Clone() const
	{
		return new ActionDestroyAction(*this);
	}

	bool ActionDestroyAction::Equals(const RTTI* rhs) const
	{
		const ActionDestroyAction* rhsADA = rhs->As<ActionDestroyAction>();
		if (rhsADA == nullptr)
		{
			return false;
		}

		return Name() == rhsADA->Name() &&
			_instanceName == rhsADA->_instanceName;

	}

	std::string ActionDestroyAction::ToString() const
	{
		return "ActionDestroyAction: "s + Name();
	}

	void ActionDestroyAction::Update(const GameTime& /*gameTime*/)
	{
		Scope* search = this;

		while (search->GetParent() != nullptr)
		{
			search = search->GetParent();
			Datum* Name = search->Find("name"s);
			if (Name != nullptr && Name->Type() == DatumTypes::String && Name->GetString() == _targetName)
			{
				Action* action = static_cast<Action*>(search);
				sQue.PushBack(action);
				break;
			}

			Datum* actions = search->Find("actions"s);
			if (actions != nullptr && actions->Type() == DatumTypes::Table)
			{
				for (size_t i = 0; i < actions->Size(); ++i)
				{
					Scope* childScope = actions->GetTable(i);
					assert(childScope->Is(Action::TypeIdClass()));
					Action* childAction = static_cast<Action*>(childScope);
					if (childAction->Name() == _targetName)
					{
						sQue.PushBack(childAction);
						return;
					}
				}
			}
		}
	}
}
