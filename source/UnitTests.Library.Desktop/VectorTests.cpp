#include "pch.h"
#include "Vector.h"
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
	TEST_CLASS(VectorTests)
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
			Vector<Foo> vec;
			Assert::AreEqual((size_t)0, vec.Size());
			auto frontFunc = [&] {vec.Front(); };
			Assert::ExpectException<std::runtime_error>(frontFunc);
			auto backFunc = [&] {vec.Back(); };
			Assert::ExpectException<std::runtime_error>(backFunc);
		}

		TEST_METHOD(ConstructorInitList)
		{
			Vector<Foo> vec{ 1, 2, 3 };
			Assert::AreEqual((size_t)3, vec.Size());
			Assert::AreEqual((Foo)1, vec.Front());
			Assert::AreEqual((Foo)3, vec.Back());
		}

		TEST_METHOD(PushBack)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, vec.Front());
			Assert::AreEqual(fooObject1, vec.Back());
			Assert::AreEqual((size_t)1, vec.Size());

			vec.PushBack(fooObject2);
			Assert::AreEqual(fooObject1, vec.Front());
			Assert::AreEqual(fooObject2, vec.Back());
			Assert::AreEqual((size_t)2, vec.Size());
		}

		TEST_METHOD(PopBack)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);

			vec.PopBack();
			Assert::AreEqual(fooObject1, vec.Front());
			Assert::AreEqual(fooObject2, vec.Back());
			Assert::AreEqual((size_t)2, vec.Size());

			vec.PopBack();
			Assert::AreEqual(fooObject1, vec.Front());
			Assert::AreEqual(fooObject1, vec.Back());
			Assert::AreEqual((size_t)1, vec.Size());

			vec.PopBack();
			Assert::IsTrue(vec.IsEmpty());
		}

		TEST_METHOD(IsEmpty)
		{
			Vector<Foo> vec;
			Assert::IsTrue(vec.IsEmpty());

			Foo fooObject1(1);
			vec.PushBack(fooObject1);
			Assert::IsFalse(vec.IsEmpty());

			vec.PopBack();
			Assert::IsTrue(vec.IsEmpty());
		}

		TEST_METHOD(Clear)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.Clear();
			Assert::IsTrue(vec.IsEmpty());

			vec.Clear();
			Assert::IsTrue(vec.IsEmpty());

			vec.PushBack(fooObject2);
			vec.Clear();
			Assert::IsTrue(vec.IsEmpty());
		}

		TEST_METHOD(AssignmentOperator)
		{
			Vector<Foo> vec1;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);
			vec1.PushBack(fooObject3);
			Vector<Foo> vec2;
			vec2 = vec1;
			Assert::AreEqual(vec1.Size(), vec2.Size());
			while (!vec1.IsEmpty())
			{
				Assert::AreEqual(vec1.Front(), vec2.Front());
				Assert::AreEqual(vec1.Back(), vec2.Back());
				vec1.PopBack();
				vec2.PopBack();
			}
			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);
			vec2 = vec1;
			vec1.Clear();
			Assert::AreEqual(fooObject1, vec2.Front());
			Assert::AreEqual(fooObject2, vec2.Back());
			Assert::AreEqual((size_t)2, vec2.Size());
			vec2 = vec1;
			Assert::IsTrue(vec2.IsEmpty());
		}

		TEST_METHOD(CopyConstructor)
		{
			Vector<Foo> vec1;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);
			vec1.PushBack(fooObject3);
			Vector<Foo> vec2{ vec1 };
			Assert::AreEqual(vec1.Size(), vec2.Size());

			while (!vec1.IsEmpty())
			{
				Assert::AreEqual(vec1.Front(), vec2.Front());
				Assert::AreEqual(vec1.Back(), vec2.Back());
				vec1.PopBack();
				vec2.PopBack();
			}

			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);
			Vector<Foo> vec3{ vec1 };
			vec1.Clear();
			Assert::AreEqual(fooObject1, vec3.Front());
			Assert::AreEqual(fooObject2, vec3.Back());
			Assert::AreEqual((size_t)2, vec3.Size());

			Vector<Foo> vec4{ vec1 };
			Assert::IsTrue(vec4.IsEmpty());
		}

		TEST_METHOD(Front)
		{
			Vector<Foo> vec;
			auto func = [&] {vec.Front(); };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, vec.Front());

			Foo& fooObject = vec.Front();
			fooObject = fooObject1;
			Assert::AreEqual(fooObject1, vec.Front());
		}

		TEST_METHOD(ConstFront)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			{
				const Vector<Foo> constvec{ vec };
				auto func = [&] {constvec.Front(); };
				Assert::ExpectException<std::runtime_error>(func);
			}
			{
				vec.PushBack(fooObject1);
				const Vector<Foo> constvec{ vec };
				Assert::AreEqual(fooObject1, constvec.Front());
			}
			{
				const Vector<Foo> constvec{ vec };
				const Foo& fooObject = constvec.Front();
				Assert::AreEqual(fooObject, fooObject1);
			}
		}

		TEST_METHOD(Back)
		{
			Vector<Foo> vec;
			auto func = [&] {vec.Back(); };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, vec.Back());

			vec.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, vec.Back());

			Foo& fooObject = vec.Back();
			fooObject = fooObject1;
			Assert::AreEqual(fooObject1, vec.Back());
		}

		TEST_METHOD(ConstBack)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			{
				const Vector<Foo> constvec{ vec };
				auto func = [&] {constvec.Back(); };
				Assert::ExpectException<std::runtime_error>(func);
			}
			{
				vec.PushBack(fooObject1);
				const Vector<Foo> constvec{ vec };
				Assert::AreEqual(fooObject1, constvec.Back());
			}
			{
				vec.PushBack(fooObject2);
				const Vector<Foo> constvec{ vec };
				Assert::AreEqual(fooObject2, vec.Back());
			}
			{
				const Vector<Foo> constvec{ vec };
				const Foo& fooObject = constvec.Back();
				Assert::AreEqual(fooObject, fooObject2);
			}
		}

		TEST_METHOD(Size)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Assert::AreEqual((size_t)0, vec.Size());

			vec.PushBack(fooObject1);
			Assert::AreEqual((size_t)1, vec.Size());

			vec.PushBack(fooObject2);
			Assert::AreEqual((size_t)2, vec.Size());

			vec.PopBack();
			Assert::AreEqual((size_t)1, vec.Size());

			vec.PopBack();
			Assert::AreEqual((size_t)0, vec.Size());
		}

		TEST_METHOD(Remove)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			Foo fooObject4(4);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			vec.PushBack(fooObject4);
			bool didRemove = vec.Remove(fooObject1);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, vec.Front());

			didRemove = vec.Remove(fooObject1);
			Assert::IsFalse(didRemove);
			didRemove = vec.Remove(fooObject3);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, vec.Front());
			Assert::AreEqual(fooObject4, vec.Back());

			didRemove = vec.Remove(fooObject4);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, vec.Front());
			Assert::AreEqual(fooObject2, vec.Back());
			Assert::AreEqual(size_t(1), vec.Size());
	
			vec.Clear();
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			vec.PushBack(fooObject4);
			Vector<Foo>::Iterator it2 = vec.Find(fooObject2);
			vec.Remove(it2, vec.end());
			Assert::AreEqual(vec.Find(fooObject2), vec.end());
			Assert::AreEqual(vec.Find(fooObject3), vec.end());
			Assert::AreEqual(vec.Find(fooObject4), vec.end());
			Assert::AreEqual(vec.Size(), size_t(1));

			vec.Clear();
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			vec.PushBack(fooObject4);
			Vector<Foo>::Iterator it1 = vec.Find(fooObject1);
			Vector<Foo>::Iterator it3 = vec.Find(fooObject3);
			vec.Remove(it1, it3);
			Assert::AreEqual(vec.Find(fooObject1), vec.end());
			Assert::AreEqual(vec.Find(fooObject2), vec.end());
			Assert::AreEqual(vec.Size(), size_t(2));
			Assert::AreEqual(vec[0], fooObject3);
			Assert::AreEqual(vec[1], fooObject4);
		}

		TEST_METHOD(Find)
		{
			Vector<Foo> vec;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			Foo fooObject4(4);
			Foo fooObject5(5);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			vec.PushBack(fooObject4);

			Vector<Foo>::Iterator it = vec.Find(fooObject1);
			Assert::AreEqual(fooObject1, *it);
			it = vec.Find(fooObject2);
			Assert::AreEqual(fooObject2, *it);
			it = vec.Find(fooObject5);
			Assert::AreEqual(vec.end(), it);

			const Vector<Foo>* constvecRef = &vec;
			Vector<Foo>::ConstIterator constIt = constvecRef->Find(fooObject1);
			Assert::AreEqual(fooObject1, *constIt);
			constIt = constvecRef->Find(fooObject2);
			Assert::AreEqual(fooObject2, *constIt);
		}

		TEST_METHOD(begin)
		{
			Vector<Foo> vec;
			Vector<Foo>::Iterator it = vec.begin();
			auto func = [&] {*it; };
			Assert::ExpectException<std::out_of_range>(func);

			Foo fooObject1(1);
			vec.PushBack(fooObject1);
			it = vec.begin();
			Assert::AreEqual(*it, fooObject1); 

			const Vector<Foo>* constvecRef = &vec;
			Vector<Foo>::ConstIterator constIt = constvecRef->begin();
			Assert::AreEqual(*constIt, fooObject1);
		}

		TEST_METHOD(cbegin)
		{
			Vector<Foo> vec;
			Vector<Foo>::ConstIterator it = vec.cbegin();
			auto func = [&] {*it; };
			Assert::ExpectException<std::out_of_range>(func);

			Foo fooObject1(1);
			vec.PushBack(fooObject1);
			it = vec.cbegin();
			Assert::AreEqual(*it, fooObject1);
		}

		TEST_METHOD(end)
		{
			Vector<Foo> vec;
			Vector<Foo>::Iterator it = vec.end();
			auto func = [&] {*it; };
			Assert::ExpectException<std::out_of_range>(func);

			Foo fooObject1(1);
			vec.PushBack(fooObject1);
			it = vec.end();
			Assert::ExpectException<std::out_of_range>(func);
			Vector<Foo>::Iterator it2 = vec.begin();
			Assert::AreNotEqual(it, it2);

			const Vector<Foo>* constvecRef = &vec;
			Vector<Foo>::ConstIterator constIt = constvecRef->end();
			auto func2 = [&] {*constIt; };
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(cend)
		{
			Vector<Foo> vec;
			Vector<Foo>::ConstIterator it = vec.cend();
			auto func = [&] {*it; };
			Assert::ExpectException<std::out_of_range>(func);

			Foo fooObject1(1);
			vec.PushBack(fooObject1);
			it = vec.cend();
			Assert::ExpectException<std::out_of_range>(func);
			Vector<Foo>::ConstIterator it2 = vec.cbegin();
			Assert::AreNotEqual(it, it2);
		}
		TEST_METHOD(Iterator)
		{

			Vector<Foo> vec;
			size_t size = 0;
			for (Vector<Foo>::Iterator it = vec.begin(); it != vec.end(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			size = 0;
			for (Vector<Foo>::Iterator it = vec.begin(); it != vec.end(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			size = 0;
			for (Vector<Foo>::Iterator it = vec.begin(); !(it == vec.end()); it++, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			Vector<Foo>::Iterator it;
			auto func1 = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func1);
			it = vec.begin();
			Assert::AreEqual(*it, fooObject1);

			Vector<Foo>::Iterator it2;
			auto func2 = [&] {++it2; };
			Assert::ExpectException<std::runtime_error>(func2);
		}

		TEST_METHOD(ConstIterator)
		{
			Vector<Foo> vec;
			size_t size = 0;
			for (Vector<Foo>::ConstIterator it = vec.cbegin(); it != vec.cend(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			vec.PushBack(fooObject3);
			size = 0;
			for (Vector<Foo>::ConstIterator it = vec.cbegin(); it != vec.cend(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			size = 0;
			for (Vector<Foo>::ConstIterator it = vec.cbegin(); !(it == vec.cend()); it++, ++size)
			{
			}
			Assert::AreEqual(size, vec.Size());

			Vector<Foo>::ConstIterator constIt1 = vec.cbegin();
			Assert::AreEqual(*constIt1, fooObject1);

			Vector<Foo>::ConstIterator constIt;
			auto func1 = [&] {*constIt; };
			Assert::ExpectException<std::runtime_error>(func1);

			constIt = vec.begin();
			Vector<Foo>::ConstIterator constIt2{ constIt };
			Assert::AreEqual(*constIt2, fooObject1);

			Vector<Foo>::ConstIterator constIt3;
			auto func = [&] {++constIt3; };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(BracketOperator)
		{
			Vector<Foo> vec;
			Foo fooObject0(0);
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject0);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);
			
			Assert::AreEqual(vec[0], fooObject0);
			Assert::AreEqual(vec[1], fooObject1);
			Assert::AreEqual(vec[2], fooObject2);
			auto func1 = [&] {vec[3]; };
			Assert::ExpectException<std::out_of_range>(func1);

			const Vector<Foo> vecConst = vec;
			Assert::AreEqual(vecConst[0], fooObject0);
			Assert::AreEqual(vecConst[1], fooObject1);
			Assert::AreEqual(vecConst[2], fooObject2);
			auto func2 = [&] {vecConst[3]; };
			Assert::ExpectException<std::out_of_range>(func2);
		}

		TEST_METHOD(At)
		{
			Vector<Foo> vec;
			Foo fooObject0(0);
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec.PushBack(fooObject0);
			vec.PushBack(fooObject1);
			vec.PushBack(fooObject2);

			Assert::AreEqual(vec.At(0), fooObject0);
			Assert::AreEqual(vec.At(1), fooObject1);
			Assert::AreEqual(vec.At(2), fooObject2);
			auto func1 = [&] {vec.At(3); };
			Assert::ExpectException<std::out_of_range>(func1);

			const Vector<Foo> vecConst = vec;
			Assert::AreEqual(vecConst.At(0), fooObject0);
			Assert::AreEqual(vecConst.At(1), fooObject1);
			Assert::AreEqual(vecConst.At(2), fooObject2);
			auto func2 = [&] {vecConst.At(3); };
			Assert::ExpectException<std::out_of_range>(func2);
		}

		TEST_METHOD(MoveAssignment)
		{
			Vector<Foo> vec1;
			Vector<Foo> vec2;
			Foo fooObject0(0);
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec1.PushBack(fooObject0);
			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);
			
			vec2.PushBack(fooObject2);

			vec1 = std::move(vec1);
			vec2 = std::move(vec1);
			Assert::AreEqual(vec2[0], fooObject0);
			Assert::AreEqual(vec2[1], fooObject1);
			Assert::AreEqual(vec2[2], fooObject2);
			Assert::AreEqual(size_t(0), vec1.Size());
		}

		TEST_METHOD(MoveConstructor)
		{
			Vector<Foo> vec1;
			Foo fooObject0(0);
			Foo fooObject1(1);
			Foo fooObject2(2);
			vec1.PushBack(fooObject0);
			vec1.PushBack(fooObject1);
			vec1.PushBack(fooObject2);

			Vector<Foo> vec2 = std::move(vec1);
			Assert::AreEqual(vec2[0], fooObject0);
			Assert::AreEqual(vec2[1], fooObject1);
			Assert::AreEqual(vec2[2], fooObject2);
			Assert::AreEqual(size_t(0), vec1.Size());
		}

		TEST_METHOD(CapacityAndReserve)
		{
			Vector<Foo> vec;
			Assert::AreEqual(vec.Capacity(), size_t(0));

			vec.Reserve(10);
			Assert::AreEqual(vec.Capacity(), size_t(10));

			vec.Reserve(5);
			Assert::AreEqual(vec.Capacity(), size_t(10));

			vec.Reserve(20);
			Assert::AreEqual(vec.Capacity(), size_t(20));
		}

		TEST_METHOD(Resize)
		{
			Vector<int> vec;
			vec.Resize(20);
			Assert::AreEqual(vec.Capacity(), size_t(20));
			Assert::AreEqual(vec.Size(), size_t(20));
			vec[19];
		}
	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState VectorTests::_startMemState;
}