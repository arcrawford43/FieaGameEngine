#pragma once
#include "AttributedFoo.h"
namespace UnitTests
{
	class AttributedDerivedFoo : public AttributedFoo
	{
		RTTI_DECLARATIONS(AttributedDerivedFoo, AttributedFoo)

	public:

		AttributedDerivedFoo();

		~AttributedDerivedFoo() = default;

		static const FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();

		AttributedDerivedFoo* Clone() const override;

		bool Equals(const RTTI * rhs) const override;

		std::string ToString() const override;

		std::int32_t DerivedInt;

		std::int32_t Int;
	};
}

