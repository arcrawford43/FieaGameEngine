#pragma once
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "Hashmap.h"
#include "Datum.h"
#include <CppUnitTest.h>
#include "RTTI.h"
#include <string>
#include "AttributedDerivedFoo.h"
#include "Event.h"
#include "EventPublisher.h"

using namespace std::string_literals;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<FieaGameEngine::EventPublisher>(FieaGameEngine::EventPublisher* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Event<UnitTests::Foo>>(FieaGameEngine::Event<UnitTests::Foo>* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::SList<UnitTests::Foo>::Iterator>(const FieaGameEngine::SList<UnitTests::Foo>::Iterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (std::runtime_error)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::SList<UnitTests::Foo>::ConstIterator>(const FieaGameEngine::SList<UnitTests::Foo>::ConstIterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (std::runtime_error)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<UnitTests::Foo>::Iterator>(const FieaGameEngine::Vector<UnitTests::Foo>::Iterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (...)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<UnitTests::Foo>::ConstIterator>(const FieaGameEngine::Vector<UnitTests::Foo>::ConstIterator& t)
	{
		try
		{
			return ToString(*t);
		}
		catch (...)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Hashmap<UnitTests::Foo, int>::Iterator>(const FieaGameEngine::Hashmap<UnitTests::Foo, int>::Iterator& t)
	{
		try
		{
			RETURN_WIDE_STRING((*t).first.Data() << ", " << (*t).second);
		}
		catch (...)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Hashmap<UnitTests::Foo, int>::ConstIterator>(const FieaGameEngine::Hashmap<UnitTests::Foo, int>::ConstIterator& t)
	{
		try
		{
			RETURN_WIDE_STRING((*t).first.Data() << ", " << (*t).second);
		}
		catch (...)
		{
			return L"end()"s;
		}
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::DatumTypes>(const FieaGameEngine::DatumTypes& t)
	{
		RETURN_WIDE_STRING(static_cast<int>(t));
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::DatumTypes>(const FieaGameEngine::DatumTypes* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::DatumTypes>(FieaGameEngine::DatumTypes* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Datum>(const FieaGameEngine::Datum& t)
	{
		t;
		RETURN_WIDE_STRING("Datum");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Datum>(const FieaGameEngine::Datum* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Datum>(FieaGameEngine::Datum* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4& t)
	{
		t;
		RETURN_WIDE_STRING("Vec4");
	}

	template<>
	inline std::wstring ToString<glm::vec4>(const glm::vec4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::vec4>(glm::vec4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4& t)
	{
		t;
		RETURN_WIDE_STRING("Mat4");
	}

	template<>
	inline std::wstring ToString<glm::mat4>(const glm::mat4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<glm::mat4>(glm::mat4* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::RTTI>(const FieaGameEngine::RTTI& t)
	{
		t;
		RETURN_WIDE_STRING("RTTI");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::RTTI>(const FieaGameEngine::RTTI* t)
	{
		t;
		RETURN_WIDE_STRING("RTTI");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::RTTI>(FieaGameEngine::RTTI* t)
	{
		t;
		RETURN_WIDE_STRING("RTTI");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(const FieaGameEngine::Scope& t)
	{
		t;
		RETURN_WIDE_STRING("Scope");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(const FieaGameEngine::Scope* t)
	{
		t;
		RETURN_WIDE_STRING("Scope");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Scope>(FieaGameEngine::Scope* t)
	{
		t;
		RETURN_WIDE_STRING("Scope");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(const UnitTests::AttributedFoo& t)
	{
		t;
		RETURN_WIDE_STRING("AttributedFoo");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(const UnitTests::AttributedFoo* t)
	{
		t;
		RETURN_WIDE_STRING("AttributedFoo");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedFoo>(UnitTests::AttributedFoo* t)
	{
		t;
		RETURN_WIDE_STRING("AttributedFoo");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedDerivedFoo>(const UnitTests::AttributedDerivedFoo& t)
	{
		t;
		RETURN_WIDE_STRING("AttributedDerivedFoo");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedDerivedFoo>(const UnitTests::AttributedDerivedFoo* t)
	{
		t;
		RETURN_WIDE_STRING("AttributedDerivedFoo");
	}

	template<>
	inline std::wstring ToString<UnitTests::AttributedDerivedFoo>(UnitTests::AttributedDerivedFoo* t)
	{
		t;
		RETURN_WIDE_STRING("AttributedDerivedFoo");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Attributed>(const FieaGameEngine::Attributed& t)
	{
		t;
		RETURN_WIDE_STRING("Attributed");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Attributed>(const FieaGameEngine::Attributed* t)
	{
		t;
		RETURN_WIDE_STRING("Attributed");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Attributed>(FieaGameEngine::Attributed* t)
	{
		t;
		RETURN_WIDE_STRING("Attributed");
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<int>>(const FieaGameEngine::Vector<int>& t)
	{
		RETURN_WIDE_STRING(t[0]);
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<int>>(const FieaGameEngine::Vector<int>* t)
	{
		RETURN_WIDE_STRING(t->operator[](0));
	}

	template<>
	inline std::wstring ToString<FieaGameEngine::Vector<int>>(FieaGameEngine::Vector<int>* t)
	{
		RETURN_WIDE_STRING(t->operator[](0));
	}
	 
	
}