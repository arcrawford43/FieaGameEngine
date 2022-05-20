#include "Attributed.h"

namespace FieaGameEngine
{
	bool Attributed::IsAttribute(const std::string& name)
	{
		return (Find(name) != nullptr);
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name)
	{
		return (IsAttribute(name) && !IsPrescribedAttribute(name));
	}

	Attributed::IteratorPair Attributed::GetAttributes()
	{
		return { _vector.begin(), _vector.end() };
	}

	Attributed::ConstIteratorPair Attributed::GetAttributes() const
	{
		return { _vector.begin(), _vector.end() };
	}

	Attributed::IteratorPair Attributed::GetPrescribedAttributes()
	{
		return { _vector.begin(), _vector.GetIterator(TypeManager::GetSignature(this->TypeIdInstance()).Size() + 1) };
	}

	Attributed::ConstIteratorPair Attributed::GetPrescribedAttributes() const
	{
		return { _vector.begin(), _vector.GetIterator(TypeManager::GetSignature(this->TypeIdInstance()).Size() + 1) };
	}

	Attributed::IteratorPair Attributed::GetAuxiliaryAttributes()
	{
		return { _vector.GetIterator(TypeManager::GetSignature(this->TypeIdInstance()).Size() + 1), _vector.end() };
	}

	Attributed::ConstIteratorPair Attributed::GetAuxiliaryAttributes() const
	{
		return { _vector.GetIterator(TypeManager::GetSignature(this->TypeIdInstance()).Size() + 1), _vector.end() };
	}
}