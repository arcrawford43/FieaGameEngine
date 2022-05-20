#include "pch.h"
#include "Scope.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(ScopeTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD(Append)
		{
			Scope scope;
			Datum& d = scope.Append("Hi"s);
			d.PushBack(1);
			Assert::AreEqual(d, scope.Append("Hi"s));
		}

		TEST_METHOD(AppendScope)
		{
			Scope parent;
			Scope& child1 = parent.AppendScope("Hi");
			Assert::AreEqual((*(parent.Find("Hi"s)))[0], child1);
			child1.Append("Hello");

			Scope& child2 = parent.AppendScope("Hi");
			Assert::AreEqual((*(parent.Find("Hi"s)))[1], child2);

			Datum& child3 = parent.Append("World");
			child3.PushBack(1);
			auto Func = [&] {parent.AppendScope("World"); };
			Assert::ExpectException<std::runtime_error>(Func);

		}

		TEST_METHOD(Adopt)
		{
			Scope parent1, parent2;
			Scope* child = new Scope();
			parent1.Adopt(*child, "Hi"s);
			Assert::AreEqual((*(parent1.Find("Hi"s)))[0], *child);
			parent2.Adopt(*child, "Hello"s);
			Assert::AreEqual((*(parent2.Find("Hello"s)))[0], *child);
			Assert::AreEqual((*(parent1.Find("Hi"s))).Size(), 0_z);
			auto Func = [&] {child->Adopt(parent2, "World"); };
			Assert::ExpectException<std::runtime_error>(Func);
			auto Func2 = [&] {child->Adopt(*child, "Hello"); };
			Assert::ExpectException<std::runtime_error>(Func2);
			
		}

		TEST_METHOD(FindContainedScope)
		{
			Scope parent;
			{
				auto [datumptr, index] = parent.FindContainedScope(&parent);
				Assert::AreEqual(datumptr, static_cast<Datum*>(nullptr));
				Assert::AreEqual(index, 0_z);
			}

			parent.Append("Hi"s);
			Scope& child1 = parent.AppendScope("Hello"s);
			Scope& child2 = parent.AppendScope("Hello"s);
			{
				auto [datumptr, index] = parent.FindContainedScope(&parent);
				Assert::AreEqual(datumptr, static_cast<Datum*>(nullptr));
				Assert::AreEqual(index, 0_z);
			}
			{
				auto [datumptr1, index1] = parent.FindContainedScope(&child1);
				Assert::AreEqual(&(*datumptr1)[index1], &child1);
				Assert::AreEqual(index1, 0_z);

				auto [datumptr2, index2] = parent.FindContainedScope(&child2);
				Assert::AreEqual(&(*datumptr2)[index2], &child2);
				Assert::AreEqual(index2, 1_z);
				Assert::AreEqual(datumptr1, datumptr2);
			}

		}
		TEST_METHOD(Find)
		{
			Scope scope;
			scope.Append("Hello"s);
			const Scope constScope = scope;
			Assert::AreEqual(*(constScope.Find("Hello"s)), Datum());
			Assert::AreEqual(constScope.Find("Hi"s), static_cast<const Datum*>(nullptr));
		}

		TEST_METHOD(Search)
		{
			{
				Scope* child = new Scope();
				Scope parent;
				Scope* result;
				Datum& d = child->Append("Hello"s);
				d.PushBack(1);
				Assert::AreEqual(*(child->Search("Hello"s)), d);
				Assert::AreEqual(*(child->Search("Hello"s, result)), d);
				Assert::AreEqual(result, child);
				Assert::AreEqual(child->Search("Hi"s), static_cast<Datum*>(nullptr));
				Assert::AreEqual(child->Search("Hi"s, result), static_cast<Datum*>(nullptr));
				Assert::AreEqual(result, static_cast<Scope*>(nullptr));

				parent.Adopt(*child, "Hi"s);
				Assert::AreEqual((child->Search("Hi"s))->GetTable(), child);
				Assert::AreEqual((child->Search("Hi"s, result))->GetTable(), child);
				Assert::AreEqual(result, &parent);

			}

			{
				Scope* nonConstChild = new Scope();
				Scope parent;
				const Scope* result;
				Datum& d = nonConstChild->Append("Hello"s);
				d.PushBack(1);
				const Scope* child = nonConstChild;
				Assert::AreEqual(*(child->Search("Hello"s)), d);
				Assert::AreEqual(*(child->Search("Hello"s, result)), d);
				Assert::AreEqual(result, child);
				Assert::AreEqual(child->Search("Hi"s), static_cast<const Datum*>(nullptr));
				Assert::AreEqual(child->Search("Hi"s, result), static_cast<const Datum*>(nullptr));
				Assert::AreEqual(result, static_cast<const Scope*>(nullptr));

				parent.Adopt(*nonConstChild, "Hi"s);
				Assert::AreEqual((child->Search("Hi"s))->GetTable(), child);
				Assert::AreEqual((child->Search("Hi"s, result))->GetTable(), child);
				Assert::AreEqual(result, const_cast<const Scope*>( &parent));

			}
		}

		TEST_METHOD(CopySemantics)
		{
			{
				Scope parent1;
				parent1.AppendScope("Hello");
				Datum& d = parent1.Append("Hi");
				d.PushBack(1);
				Scope parent2 = parent1;
				Assert::AreEqual(*(parent1.Find("Hello")), *(parent2.Find("Hello")));
				Assert::AreEqual(*(parent1.Find("Hi")), *(parent2.Find("Hi")));
				Assert::AreEqual(parent1, parent2);

			}

			{
				Scope parent1, parent2;
				parent1.AppendScope("Hello");
				Datum& d = parent1.Append("Hi");
				d.PushBack(1);
				parent2 = parent1;
				Assert::AreEqual(*(parent1.Find("Hello")), *(parent2.Find("Hello")));
				Assert::AreEqual(*(parent1.Find("Hi")), *(parent2.Find("Hi")));
				Assert::AreEqual(parent1, parent2);

			}
		}

		TEST_METHOD(MoveSemantics)
		{
			{
				Scope grandparent;
				Scope& parent1 = grandparent.AppendScope("World");
				Scope& child1 = parent1.AppendScope("Hello");
				Datum& d = parent1.Append("Hi");
				d.PushBack(1);
				Scope parent2 = std::move(parent1);
				Assert::AreEqual(&child1, (parent2.Find("Hello"))->GetTable());
				Assert::AreEqual(&d, (parent2.Find("Hi")));
				Assert::AreEqual(parent2.GetParent(), &grandparent);
				delete& parent1;
			}

			{
				Scope grandparent;
				Scope parent2;
				Scope& parent1 = grandparent.AppendScope("World");
				Scope& child1 = parent1.AppendScope("Hello");
				Datum& d = parent1.Append("Hi");
				d.PushBack(1);
				parent2 = std::move(parent1);
				Assert::AreEqual(&child1, (parent2.Find("Hello"))->GetTable());
				Assert::AreEqual(&d, (parent2.Find("Hi")));
				Assert::AreEqual(parent2.GetParent(), &grandparent);
				delete& parent1;
			}

		}

		TEST_METHOD(ComparisonOperator)
		{
			Scope scope1, scope2;
			Assert::AreEqual(scope1, scope1);
			Assert::AreEqual(scope1, scope2);
			scope1.Append("Hello");
			Assert::IsTrue(scope1 != scope2);
			Assert::IsFalse(scope1 != scope1);
			Assert::AreNotEqual(scope1, scope2);
			Foo foo = 1;
			Assert::IsFalse(scope1.Equals(&foo));

			scope2.AppendScope("Hello");
			Assert::AreNotEqual(scope1, scope2);
			
		}

		TEST_METHOD(InlinedFunctions)
		{
			Scope scope;
			const Scope* ptr = &scope;
			Datum& d1 = scope["Hello"];
			Assert::AreSame(d1, scope.Append("Hello"));

			Datum& d2 = scope["Hi"];
			Assert::AreSame(scope[0], d1);
			Assert::AreSame(ptr->operator[](1), d2);

			Scope& child = scope.AppendScope("child");
			Scope& grandchild = child.AppendScope("grandchild");

			Assert::IsTrue(scope.IsAncestorOf(grandchild));
			Assert::IsFalse(scope.IsDescendantOf(grandchild));
			Assert::IsTrue(grandchild.IsDescendantOf(scope));
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

		

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState ScopeTests::_startMemState;
}