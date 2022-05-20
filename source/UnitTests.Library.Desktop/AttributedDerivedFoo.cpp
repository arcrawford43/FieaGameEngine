#include "pch.h"
#include "AttributedDerivedFoo.h"

using namespace FieaGameEngine;
using namespace std::string_literals;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedDerivedFoo)

	AttributedDerivedFoo::AttributedDerivedFoo() :
	AttributedFoo(AttributedDerivedFoo::TypeIdClass())
	{
	}

	const Vector<Signature> AttributedDerivedFoo::Signatures()
	{
		return Vector<Signature>
		{
			{ "DerivedInt", DatumTypes::Integer, 1, offsetof(AttributedDerivedFoo, DerivedInt) },
			{ "Int", DatumTypes::Integer, 1, offsetof(AttributedDerivedFoo, Int) }
		};
	}

	AttributedDerivedFoo* AttributedDerivedFoo::Clone() const
	{
		return new AttributedDerivedFoo(*this);
	}

	bool AttributedDerivedFoo::Equals(const RTTI* rhs) const
	{
		const AttributedDerivedFoo* rhsFoo = rhs->As<AttributedDerivedFoo>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return DerivedInt == rhsFoo->DerivedInt;
	}

	std::string AttributedDerivedFoo::ToString() const
	{
		return "AttributedDerivedFoo"s;
	}
}
