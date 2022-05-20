#include "pch.h"
#include "AttributedDerivedFoo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(AttributedTests)
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

		TEST_METHOD(Attributes)
		{
			{
				AttributedFoo foo;

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));

				Assert::AreEqual(&foo, foo["this"].GetPointer()->As<AttributedFoo>());
			}

			{
				AttributedDerivedFoo foo;

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAttribute("DerivedInt"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("DerivedInt"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("DerivedInt"));

				Assert::AreEqual(&foo, foo["this"].GetPointer()->As<AttributedDerivedFoo>());

				Assert::AreSame(foo.Int, foo["Int"].GetInteger());
			}
		}

		TEST_METHOD(AuxiliaryAttributes)
		{
			AttributedFoo foo;

			foo.AppendAuxiliaryAttribute("AuxInt");
			Assert::IsTrue(foo.IsAttribute("AuxInt"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxInt"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxInt"));

			auto func = [&] {foo.AppendAuxiliaryAttribute("Int"); };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(ExternalAssignment)
		{
			AttributedFoo foo;

			Datum* d = foo.Find("Int");
			Assert::AreEqual(1_z, d->Size());
			Assert::AreSame(d->GetInteger(), foo.Int);

			int a = 1;
			d->Set(a);
			Assert::AreEqual(a, d->GetInteger());
			Assert::AreEqual(a, foo.Int);

			std::string str = "Hello World";
			foo["Str"] = str;
			Assert::AreEqual(str, foo.Str);

		}
		
		TEST_METHOD(CopySemantics)
		{
			{
				AttributedFoo foo1;

				foo1.AppendAuxiliaryAttribute("AuxInt") = 5;
				foo1.Int = 10;
				foo1.Str = "Hello World"s;

				AttributedFoo foo = foo1;

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAttribute("AuxInt"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));
				Assert::IsFalse(foo.IsPrescribedAttribute("AuxInt"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxInt"));

				Assert::IsTrue(foo.Equals(&foo1));

				foo.Int = 5;
				foo1.Int = 6;

				Assert::AreNotEqual(foo, foo1);
				Assert::AreNotSame(foo["Int"].GetInteger(), foo1["Int"].GetInteger());
				Assert::AreEqual(foo["Int"].GetInteger(), 5);
			}
			{
				AttributedFoo foo1;
				AttributedFoo foo;

				foo.AppendAuxiliaryAttribute("AuxFloat") = 5.0f;

				foo1.AppendAuxiliaryAttribute("AuxInt") = 5;
				foo1.Int = 10;
				foo1.Str = "Hello World"s;

				foo = foo1;

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAttribute("AuxInt"));
				Assert::IsFalse(foo.IsAttribute("AuxFloat"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));
				Assert::IsFalse(foo.IsPrescribedAttribute("AuxInt"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxInt"));

				Assert::IsTrue(foo.Equals(&foo1));

				foo.Int = 5;
				foo1.Int = 6;

				Assert::AreNotEqual(foo, foo1);
				Assert::AreNotSame(foo["Int"].GetInteger(), foo1["Int"].GetInteger());
				Assert::AreEqual(foo["Int"].GetInteger(), 5);
			}
		}
		
		TEST_METHOD(MoveSemantics)
		{
			{
				AttributedFoo foo1;

				foo1.AppendAuxiliaryAttribute("AuxInt") = 5;
				foo1.Int = 10;
				foo1.Str = "Hello World"s;

				AttributedFoo foo = std::move(foo1);

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAttribute("AuxInt"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));
				Assert::IsFalse(foo.IsPrescribedAttribute("AuxInt"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxInt"));

				foo.Int = 5;

				Assert::AreEqual(foo["Int"].GetInteger(), 5);
			}
			{
				AttributedFoo foo1;
				AttributedFoo foo;

				foo.AppendAuxiliaryAttribute("AuxFloat") = 5.0f;

				foo1.AppendAuxiliaryAttribute("AuxInt") = 5;
				foo1.Int = 10;
				foo1.Str = "Hello World"s;

				foo = std::move(foo1);

				Assert::IsTrue(foo.IsAttribute("this"));
				Assert::IsTrue(foo.IsAttribute("Int"));
				Assert::IsTrue(foo.IsAttribute("Float"));
				Assert::IsTrue(foo.IsAttribute("Str"));
				Assert::IsTrue(foo.IsAttribute("Vec"));
				Assert::IsTrue(foo.IsAttribute("Mat"));
				Assert::IsTrue(foo.IsAttribute("IntArray"));
				Assert::IsTrue(foo.IsAttribute("FloatArray"));
				Assert::IsTrue(foo.IsAttribute("StrArray"));
				Assert::IsTrue(foo.IsAttribute("VecArray"));
				Assert::IsTrue(foo.IsAttribute("MatArray"));
				Assert::IsTrue(foo.IsAttribute("NestedScope"));
				Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAttribute("AuxInt"));
				Assert::IsFalse(foo.IsAttribute("AuxFloat"));

				Assert::IsTrue(foo.IsPrescribedAttribute("this"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Int"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Float"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Str"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Vec"));
				Assert::IsTrue(foo.IsPrescribedAttribute("Mat"));
				Assert::IsTrue(foo.IsPrescribedAttribute("IntArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("FloatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("StrArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("VecArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("MatArray"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
				Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));
				Assert::IsFalse(foo.IsPrescribedAttribute("AuxInt"));

				Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Int"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Float"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Str"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Vec"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("Mat"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("IntArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("FloatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("StrArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("VecArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("MatArray"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
				Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
				Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxInt"));


				foo.Int = 5;

				Assert::AreEqual(foo["Int"].GetInteger(), 5);
			}
		}

		TEST_METHOD(AttributeGetters)
		{
			AttributedFoo foo;

			foo.AppendAuxiliaryAttribute("Hi"s);
			foo.AppendAuxiliaryAttribute("Hello"s);

			{
				auto [begin, end] = foo.GetAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "this"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 15_z);
			}

			{
				auto [begin, end] = foo.GetPrescribedAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "this"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 13_z);
			}

			{
				auto [begin, end] = foo.GetAuxiliaryAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "Hi"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 2_z);
			}

			const AttributedFoo constFoo = foo;

			{
				auto [begin, end] = constFoo.GetAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "this"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 15_z);
			}


			{
				auto [begin, end] = constFoo.GetPrescribedAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "this"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 13_z);
			}

			{
				auto [begin, end] = constFoo.GetAuxiliaryAttributes();
				size_t i = 0;
				Assert::AreEqual((*begin)->first, "Hi"s);
				for (; begin != end; ++begin)
				{
					++i;
				}
				Assert::AreEqual(i, 2_z);
			}
		}

		TEST_METHOD(RTTITest)
		{
			AttributedFoo a;

			RTTI* rtti = &a;
			Assert::IsFalse(rtti->Is("Foo"s));
			Assert::IsTrue(rtti->Is("AttributedFoo"s));
			Assert::IsTrue(rtti->Is("Attributed"s));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(AttributedFoo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Attributed::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(AttributedFoo::TypeIdClass(), rtti->TypeIdInstance());

			Foo* b = rtti->As<Foo>();
			Assert::IsNull(b);

			AttributedFoo* f = rtti->As<AttributedFoo>();
			Assert::IsNotNull(f);
			Assert::AreEqual(&a, f);

			Attributed* fAsAttributed = rtti->As<Attributed>();
			Assert::IsNotNull(fAsAttributed);
			Assert::AreEqual(static_cast<Attributed*>(&a), fAsAttributed);

			RTTI* r = rtti->QueryInterface(Foo::TypeIdClass());
			Assert::IsNull(r);
			r = rtti->QueryInterface(AttributedFoo::TypeIdClass());
			Assert::IsNotNull(r);
			r = rtti->QueryInterface(Attributed::TypeIdClass());
			Assert::IsNotNull(r);

			AttributedFoo otherFoo;
			Assert::IsTrue(rtti->Equals(&otherFoo));

			Foo anotherFoo(100);
			Assert::IsFalse(rtti->Equals(&anotherFoo));

			Assert::AreEqual("AttributedFoo"s, r->ToString());
		}

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState AttributedTests::_startMemState;
}