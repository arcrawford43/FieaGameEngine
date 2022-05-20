#include "pch.h"
#include "Attributed.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed)

	Attributed::Attributed(size_t typeID)
	{
		Populate(typeID);
	}

	Attributed::Attributed(const Attributed& other) :
		Scope(other)
	{
		size_t typeID = other.TypeIdInstance();

		Repopulate(typeID);
	}

	Attributed& Attributed::operator=(const Attributed& other)
	{
		Scope::operator=(other);

		size_t typeID = other.TypeIdInstance();

		Repopulate(typeID);

		return *this;
	}

	Attributed::Attributed(Attributed&& other) :
		Scope(std::move(other))
	{
		size_t typeID = other.TypeIdInstance();

		Repopulate(typeID);
	}

	Attributed& Attributed::operator=(Attributed&& other)
	{
		Scope::operator=(std::move(other));

		size_t typeID = other.TypeIdInstance();

		Repopulate(typeID);

		return *this;
	}


	void Attributed::Populate(size_t typeID)
	{
		(*this)["this"s] = this;
		uint8_t* thisByte = reinterpret_cast<uint8_t*>(this);
		
		const Vector<Signature>& sigList = TypeManager::GetSignature(typeID);


		for (auto sig : sigList)
		{
			if (sig._type == DatumTypes::Table)
			{
				Datum& datum = Append(sig._name);
				datum.SetType(sig._type);
			}
			else
			{
				Datum& datum = Append(sig._name);
				datum.SetType(sig._type);
				datum.SetStorage(reinterpret_cast<void*>(thisByte + sig._offset), sig._size);
			}
		}
	}

	void Attributed::Repopulate(size_t typeID)
	{
		(*this)["this"s] = this;

		const Vector<Signature>& sigList = TypeManager::GetSignature(typeID);

		uint8_t* thisByte = reinterpret_cast<uint8_t*>(this);
		for (auto sig : sigList)
		{
			if (sig._type != DatumTypes::Table)
			{
				Datum& datum = Append(sig._name);
				datum.SetType(sig._type);
				datum.SetStorage(reinterpret_cast<void*>(thisByte + sig._offset), sig._size);
			}
		}
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name)
	{
		if (name == "this"s)
		{
			return true;
		}

		if (!IsAttribute(name))
		{
			return false;
		}

		auto sigList = TypeManager::GetSignature(TypeIdInstance());

		for (const auto sig : sigList)
		{
			if (sig._name == name)
			{
				return true;
			}
		}

		return false;

	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::runtime_error("This name already exists as a prescribed Attribute");
		}

		return Append(name);
	}
}
