#include "Scope.h"
namespace FieaGameEngine
{
	inline Scope* Scope::GetParent() const
	{
		return _parent;
	}

	inline Datum& Scope::operator[](const std::string& key)
	{
		return Append(key);
	}

	inline Datum& Scope::operator[](std::size_t index)
	{
		return _vector[index]->second;
	}

	inline const Datum& Scope::operator[](std::size_t index) const
	{
		return _vector[index]->second;
	}

	inline bool Scope::IsAncestorOf(const Scope& scope) const
	{
		bool result = false;
		Scope* parent = scope._parent;
		while (parent != nullptr)
		{
			if (parent == this)
			{
				result = true;
				break;
			}
			parent = parent->_parent;
		}

		return result;
	}

	inline bool Scope::IsDescendantOf(const Scope& scope) const
	{
		return scope.IsAncestorOf(*this);
	}
}
