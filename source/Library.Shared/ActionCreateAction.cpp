#include "pch.h"
#include "ActionCreateAction.h"

using namespace std::string_literals;
using namespace std;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionCreateAction);
	ActionCreateAction::ActionCreateAction() :
		Action(ActionCreateAction::TypeIdClass())
	{
	}

	ActionCreateAction::ActionCreateAction(size_t typeID) :
		Action(typeID)
	{
	}

	const Vector<Signature> ActionCreateAction::Signatures()
	{
		return Vector<Signature>
		{
			{ "actionName", DatumTypes::String, 1, offsetof(ActionCreateAction, _actionName) },
			{ "instanceName", DatumTypes::String, 1, offsetof(ActionCreateAction, _instanceName) },
			{ "targetName", DatumTypes::String, 1, offsetof(ActionCreateAction, _targetName) }
		};
	}

	ActionCreateAction* ActionCreateAction::Clone() const
	{
		return new ActionCreateAction(*this);
	}

	bool ActionCreateAction::Equals(const RTTI* rhs) const
	{
		const ActionCreateAction* rhsACA = rhs->As<ActionCreateAction>();
		if (rhsACA == nullptr)
		{
			return false;
		}

		return Name() == rhsACA->Name() &&
			_actionName == rhsACA->_actionName &&
			_targetName == rhsACA->_targetName &&
			_instanceName == rhsACA->_instanceName;

	}

	std::string ActionCreateAction::ToString() const
	{
		return "ActionCreateAction: "s + Name();
	}

	void ActionCreateAction::Update(const GameTime& /*gameTime*/)
	{
		Scope* scope = Factory<Scope>::Create(_actionName);
		assert(scope->Is(Action::TypeIdClass()));
		Action* action = static_cast<Action*>(scope);
		action->SetName(_instanceName);
		Scope* search = this;

		while (search->GetParent() != nullptr)
		{
			search = search->GetParent();
			Datum* Name = search->Find("name"s);
			if (Name != nullptr && Name->Type() == DatumTypes::String && Name->GetString() == _targetName)
			{
				sQue.PushBack(std::make_pair(search, action));
				break;
			}

			Datum* actions = search->Find("action"s);
			if (actions != nullptr && actions->Type() == DatumTypes::Table)
			{
				for (size_t i = 0; i < actions->Size(); ++i)
				{
					Scope* childScope = actions->GetTable(i);
					assert(childScope->Is(Action::TypeIdClass()));
					Action* childAction = static_cast<Action*>(childScope);
					if (childAction->Name() == _targetName)
					{
						sQue.PushBack(std::make_pair(search, action));
						return;
					}
				}
			}

			Datum* children = search->Find("children"s);
			if (children != nullptr && children->Type() == DatumTypes::Table)
			{
				for (size_t i = 0; i < children->Size(); ++i)
				{
					Scope* childScope = children->GetTable(i);
					assert(childScope->Is(Action::TypeIdClass()));
					Action* childAction = static_cast<Action*>(childScope);
					if (childAction->Name() == _targetName)
					{
						sQue.PushBack(std::make_pair(search, action));
						return;
					}
				}
			}
		}
	}
}
