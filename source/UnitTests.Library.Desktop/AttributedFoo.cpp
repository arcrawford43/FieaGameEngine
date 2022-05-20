#include "pch.h"
#include "AttributedFoo.h"


using namespace FieaGameEngine;
using namespace std::string_literals;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo() :
		Attributed(AttributedFoo::TypeIdClass())
	{
	}

	AttributedFoo::AttributedFoo(size_t typeID) :
		Attributed(typeID)
	{
	}

	const Vector<Signature> AttributedFoo::Signatures()
	{
		return Vector<Signature>
		{
			{ "Int", DatumTypes::Integer, 1, offsetof(AttributedFoo, Int) },
			{ "Float", DatumTypes::Float, 1, offsetof(AttributedFoo, Float) },
			{ "Str", DatumTypes::String, 1, offsetof(AttributedFoo, Str) },
			{ "Vec", DatumTypes::Vector, 1, offsetof(AttributedFoo, Vec) },
			{ "Mat", DatumTypes::Matrix, 1, offsetof(AttributedFoo, Mat) },
			{ "IntArray", DatumTypes::Integer, ARRAY_SIZE, offsetof(AttributedFoo, IntArray) },
			{ "FloatArray", DatumTypes::Float, ARRAY_SIZE, offsetof(AttributedFoo, FloatArray) },
			{ "StrArray", DatumTypes::String, ARRAY_SIZE, offsetof(AttributedFoo, StrArray) },
			{ "VecArray", DatumTypes::Vector, ARRAY_SIZE, offsetof(AttributedFoo, VecArray) },
			{ "MatArray", DatumTypes::Matrix, ARRAY_SIZE, offsetof(AttributedFoo, MatArray) },
			{ "NestedScope", DatumTypes::Table, 0, 0 },
			{ "NestedScopeArray", DatumTypes::Table, 0, 0 }
		};
	}

	AttributedFoo* AttributedFoo::Clone() const
	{
		return new AttributedFoo(*this);
	}

	bool AttributedFoo::Equals(const RTTI* rhs) const
	{
		const AttributedFoo* rhsFoo = rhs->As<AttributedFoo>();
		if (rhsFoo == nullptr)
		{
			return false;
		}

		return Int == rhsFoo->Int &&
			Float == rhsFoo->Float &&
			Str == rhsFoo->Str &&
			Vec == rhsFoo->Vec &&
			Mat == rhsFoo->Mat &&
			std::equal(std::begin(IntArray), std::end(IntArray), std::begin(rhsFoo->IntArray)) &&
			std::equal(std::begin(FloatArray), std::end(FloatArray), std::begin(rhsFoo->FloatArray)) &&
			std::equal(std::begin(StrArray), std::end(StrArray), std::begin(rhsFoo->StrArray)) &&
			std::equal(std::begin(VecArray), std::end(VecArray), std::begin(rhsFoo->VecArray)) &&
			std::equal(std::begin(MatArray), std::end(MatArray), std::begin(rhsFoo->MatArray)) &&
			*((*this).Find("NestedScope"s)) == *((*rhsFoo).Find("NestedScope"s)) &&
			*((*this).Find("NestedScopeArray"s)) == *((*rhsFoo).Find("NestedScopeArray"s));
	}

	std::string AttributedFoo::ToString() const
	{
		return "AttributedFoo"s;
	}
}
