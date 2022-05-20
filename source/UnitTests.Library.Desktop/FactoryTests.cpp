#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>
#include "Factory.h"
#include "RTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(FactoryTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(CleanUp)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leak!");
			}
#endif
		}

		TEST_METHOD(AddRemoveFactory)
		{
			const Factory<RTTI>* foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNull(foundFactory);
			{
				const FooFactory fooFactory;
				foundFactory = Factory<RTTI>::Find("Foo"s);
				Assert::IsNotNull(foundFactory);
			}
			foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNull(foundFactory);
		}

		TEST_METHOD(ProductCreation)
		{
			RTTI* rtti = Factory<RTTI>::Create("Foo"s);
			Assert::IsNull(rtti);
			{
				FooFactory fooFactory;

				rtti = Factory<RTTI>::Create("Foo"s);
				Assert::IsNotNull(rtti);

				Foo* foo = rtti->As<Foo>();
				Assert::IsNotNull(foo);

				delete foo;
			}
			rtti = Factory<RTTI>::Create("Foo"s);
			Assert::IsNull(rtti);
		}

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState FactoryTests::_startMemState;
}