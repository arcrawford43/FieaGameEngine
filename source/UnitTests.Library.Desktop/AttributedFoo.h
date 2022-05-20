#pragma once
#include "Attributed.h"
#include "Scope.h"
#include "Vector.h"
#include "RTTI.h"
#include "Factory.h"

namespace UnitTests
{
#define ARRAY_SIZE 5
	class AttributedFoo : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, FieaGameEngine::Attributed)
			
	public:

		AttributedFoo();

		~AttributedFoo() = default;

		static const FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();

		AttributedFoo* Clone() const override;

		bool Equals(const RTTI* rhs) const override;

		std::string ToString() const override;

		AttributedFoo(const AttributedFoo& other) = default;

		AttributedFoo& operator=(const AttributedFoo& other) = default;

		AttributedFoo(AttributedFoo&& other) = default;

		AttributedFoo& operator=(AttributedFoo&& other) = default;

		std::int32_t Int{ 0 };
		float Float{ 0.0f };
		std::string Str{ "" };
		glm::vec4 Vec{ 0.0f };
		glm::mat4 Mat{ 0.0f };

		std::int32_t IntArray[ARRAY_SIZE]{ 0 };
		float FloatArray[ARRAY_SIZE]{ 0.0f };
		std::string StrArray[ARRAY_SIZE]{ "" };
		glm::vec4 VecArray[ARRAY_SIZE]{ Vec };
		glm::mat4 MatArray[ARRAY_SIZE]{ Mat };

	protected:
		AttributedFoo(std::size_t typeID);
	};

	ConcreteFactory(AttributedFoo, FieaGameEngine::Scope)
}