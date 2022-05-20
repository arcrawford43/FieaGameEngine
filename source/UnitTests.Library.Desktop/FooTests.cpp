#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(FooTests)
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

		TEST_METHOD(Constructor)
		{
			UnitTests::Foo foo{ 1 };
			Assert::AreEqual(int32_t(1), foo.Data());
		}

		TEST_METHOD(CopyConstructor)
		{
			UnitTests::Foo foo{ 1 };
			UnitTests::Foo fooCopy{ foo };
			Assert::AreEqual(foo, fooCopy);
			Assert::AreNotSame(foo, fooCopy);
			Assert::AreNotSame(foo.Data(), fooCopy.Data());
		}

		TEST_METHOD(AssignmentOperator)
		{
			UnitTests::Foo foo{ 1 };
			UnitTests::Foo fooCopy{ 2 };
			Assert::AreNotEqual(foo, fooCopy);
			
			fooCopy = foo;
			Assert::AreEqual(foo, fooCopy);
			Assert::AreNotSame(foo, fooCopy);
			Assert::AreNotSame(foo.Data(), fooCopy.Data());
		}

		TEST_METHOD(Data)
		{
			UnitTests::Foo foo{ 1 };
			Assert::AreEqual(int32_t(1), foo.Data());

			const UnitTests::Foo constFoo{ 2 };
			Assert::AreEqual(int32_t(2), constFoo.Data());
		}

		TEST_METHOD(EqualToOperator)
		{
			UnitTests::Foo foo{ 1 };
			UnitTests::Foo fooCopy{ foo };
			Assert::AreEqual(foo, fooCopy);
			
			UnitTests::Foo foo2{ 2 };
			Assert::AreNotEqual(foo, foo2);

			Assert::AreEqual(foo, foo);
		}

		TEST_METHOD(NotEqualToOperator)
		{
			UnitTests::Foo foo{ 1 };
			UnitTests::Foo fooCopy{ foo };
			Assert::IsFalse(foo != fooCopy);

			UnitTests::Foo foo2{ 2 };
			Assert::IsTrue(foo != foo2);
		}

	private:
	static _CrtMemState _startMemState;
};

_CrtMemState FooTests::_startMemState;
}