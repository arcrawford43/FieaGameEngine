#include "pch.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	Hashmap<std::size_t, Vector<Signature>> TypeManager::_registry;
	const Vector<Signature>& TypeManager::GetSignature(size_t typeID)
	{
		auto it = _registry.Find(typeID);
		if (it == _registry.end())
		{
			throw std::runtime_error("This type is not registered");
		}

		return (*it).second;
	}
}
