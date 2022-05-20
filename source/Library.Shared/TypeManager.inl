#include "TypeManager.h"

namespace FieaGameEngine
{
	template <typename Tchild, typename Tparent>
	void TypeManager::RegisterType()
	{
		Vector<Signature> vec;
		if (Tparent::TypeIdClass() != Attributed::TypeIdClass())
		{
			if (!_registry.ContainsKey(Tparent::TypeIdClass()))
			{
				throw std::runtime_error("Parent class is not a registered type");
			}
			vec = (*(_registry.Find(Tparent::TypeIdClass()))).second;
		}
		Vector<Signature> childVec = Tchild::Signatures();
		vec.Reserve(vec.Size() + childVec.Size());

		for (size_t index = 0; index < childVec.Size(); ++index)
		{
			vec.PushBack(childVec[index]);
		}

		_registry[Tchild::TypeIdClass()] = vec;
	}
}