#include "pch.h"
#include "GameObject.h"
#include "Action.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject)

	GameObject::GameObject() :
		Attributed(GameObject::TypeIdClass())
	{
		_children = Find("children");
		_actions = Find("actions");
		assert(_children != nullptr);
		assert(_actions != nullptr);
	}

	GameObject::GameObject(size_t typeID) :
		Attributed(typeID)
	{
		_children = Find("children");
		_actions = Find("actions");
		assert(_children != nullptr);
		assert(_actions != nullptr);
	}

	void GameObject::Update(const GameTime& gameTime)
	{
		assert(_children);
		for (size_t i = 0; i < _children->Size(); ++i)
		{
			Scope* child = _children->GetTable(i);
			assert(child->Is(GameObject::TypeIdClass()));

			GameObject* childGO = static_cast<GameObject*>(child);
			childGO->Update(gameTime);
		}

		assert(_actions);
		for (size_t i = 0; i < _actions->Size(); ++i)
		{
			Scope* child = _actions->GetTable(i);
			assert(child->Is(Action::TypeIdClass()));

			Action* childAction = static_cast<Action*>(child);
			childAction->Update(gameTime);
		}
	}

	const Vector<Signature> GameObject::Signatures()
	{
		return Vector<Signature>
		{
			{ "name", DatumTypes::String, 1, offsetof(GameObject, _name) },
			{ "position", DatumTypes::Vector, 1, offsetof(GameObject, _transform._position) },
			{ "rotation", DatumTypes::Vector, 1, offsetof(GameObject, _transform._rotation) },
			{ "scale", DatumTypes::Vector, 1, offsetof(GameObject, _transform._scale) },
			{ "children", DatumTypes::Table, 0, 0 },
			{ "actions", DatumTypes::Table,0, 0 }
		};
	}

	GameObject* GameObject::Clone() const
	{
		return new GameObject(*this);
	}

	bool GameObject::Equals(const RTTI* rhs) const
	{
		const GameObject* rhsGO = rhs->As<GameObject>();
		if (rhsGO == nullptr)
		{
			return false;
		}

		return _name == rhsGO->_name &&
			_transform._position == rhsGO->_transform._position &&
			_transform._rotation == rhsGO->_transform._rotation &&
			_transform._scale == rhsGO->_transform._scale &&
			*((*this).Find("children")) == *((*rhsGO).Find("children"));
	}

	std::string GameObject::ToString() const
	{
		return "GameObject: " + _name;
	}
}