#pragma once
#include <cstdint>
#include "Hashmap.h"
#include "RTTI.h"
#include "Factory.h"

namespace UnitTests
{
	using namespace std::string_literals;
	class Foo : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI)
	public:
		Foo(std::int32_t data);
		Foo();
		Foo(const Foo& other);
		Foo& operator=(const Foo& other);
		~Foo();

		int32_t& Data();
		const int32_t& Data() const;

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		std::string ToString() const override;

		virtual bool Equals(const RTTI* rhs) const override;

	private:
		std::int32_t* mData;
	};

	ConcreteFactory(Foo, FieaGameEngine::RTTI)

}

namespace FieaGameEngine
{
	template <>
	struct DefaultHash<UnitTests::Foo> final
	{
		std::size_t operator()(const UnitTests::Foo& key)
		{
			return key.Data();
		}
	};
}


