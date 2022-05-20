#include "pch.h"
#include "SList.h"
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
	TEST_CLASS(SListTests)
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
			SList<Foo> list;
			Assert::AreEqual((size_t)0, list.Size());
			auto frontFunc = [&] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(frontFunc);
			auto backFunc = [&] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(backFunc);
		}
		
		TEST_METHOD(PushFront)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushFront(fooObject1);
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject1, list.Back());
			Assert::AreEqual((size_t)1, list.Size());

			list.PushFront(fooObject2);
			Assert::AreEqual(fooObject2, list.Front());
			Assert::AreEqual(fooObject1, list.Back());
			Assert::AreEqual((size_t)2, list.Size());
		}
		
		TEST_METHOD(PushBack)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject1, list.Back());
			Assert::AreEqual((size_t)1, list.Size());

			list.PushBack(fooObject2);
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject2, list.Back());
			Assert::AreEqual((size_t)2, list.Size());
		}

		TEST_METHOD(PopFront)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PopFront();

			Assert::AreEqual(fooObject2, list.Front());
			Assert::AreEqual(fooObject2, list.Back());
			Assert::AreEqual((size_t)1, list.Size());

			list.PopFront();
			Assert::IsTrue(list.IsEmpty());

			auto func = [&] {list.PopFront(); };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(PopBack)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);

			list.PopBack();
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject2, list.Back());
			Assert::AreEqual((size_t)2, list.Size());

			list.PopBack();
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject1, list.Back());
			Assert::AreEqual((size_t)1, list.Size());

			list.PopBack();
			Assert::IsTrue(list.IsEmpty());

			auto func = [&] {list.PopBack(); };
			Assert::ExpectException<std::runtime_error>(func);
		}
		
		TEST_METHOD(IsEmpty)
		{
			SList<Foo> list;
			Assert::IsTrue(list.IsEmpty());

			Foo fooObject1(1);
			list.PushBack(fooObject1);
			Assert::IsFalse(list.IsEmpty());

			list.PopBack();
			Assert::IsTrue(list.IsEmpty());
		}

		TEST_METHOD(Clear)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.Clear();
			Assert::IsTrue(list.IsEmpty());

			list.Clear();
			Assert::IsTrue(list.IsEmpty());

			list.PushBack(fooObject2);
			list.Clear();
			Assert::IsTrue(list.IsEmpty());
		}

		TEST_METHOD(AssignmentOperator)
		{
			SList<Foo> list1;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			list1.PushBack(fooObject1);
			list1.PushBack(fooObject2);
			list1.PushBack(fooObject3);
			SList<Foo> list2;
			list2 = list1;
			Assert::AreEqual(list1.Size(), list2.Size());
			while (!list1.IsEmpty())
			{
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
				list1.PopFront();
				list2.PopFront();
			}
			list1.PushBack(fooObject1);
			list1.PushBack(fooObject2);
			list2 = list1;
			list1.Clear();
			Assert::AreEqual(fooObject1, list2.Front());
			Assert::AreEqual(fooObject2, list2.Back());
			Assert::AreEqual((size_t)2, list2.Size());

			list2 = list1;
			Assert::IsTrue(list2.IsEmpty());
		}

		TEST_METHOD(CopyConstructor)
		{
			SList<Foo> list1;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			list1.PushBack(fooObject1);
			list1.PushBack(fooObject2);
			list1.PushBack(fooObject3);
			SList<Foo> list2{ list1 };
			Assert::AreEqual(list1.Size(), list2.Size());

			while (!list1.IsEmpty())
			{
				Assert::AreEqual(list1.Front(), list2.Front());
				Assert::AreEqual(list1.Back(), list2.Back());
				list1.PopFront();
				list2.PopFront();
			}

			list1.PushBack(fooObject1);
			list1.PushBack(fooObject2);
			SList<Foo> list3{ list1 };
			list1.Clear();
			Assert::AreEqual(fooObject1, list3.Front());
			Assert::AreEqual(fooObject2, list3.Back());
			Assert::AreEqual((size_t)2, list3.Size());

			SList<Foo> list4{ list1 };
			Assert::IsTrue(list4.IsEmpty());
		}

		TEST_METHOD(Front)
		{
			SList<Foo> list;
			auto func = [&] {list.Front(); };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushFront(fooObject1);
			Assert::AreEqual(fooObject1, list.Front());

			list.PushFront(fooObject2);
			Assert::AreEqual(fooObject2, list.Front());

			Foo& fooObject = list.Front();
			fooObject = fooObject1;
			Assert::AreEqual(fooObject1, list.Front());
		}

		TEST_METHOD(ConstFront)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			{
				const SList<Foo> constList{ list };
				auto func = [&] {constList.Front(); };
				Assert::ExpectException<std::runtime_error>(func);
			}
			{
				list.PushFront(fooObject1);
				const SList<Foo> constList{ list };
				Assert::AreEqual(fooObject1, constList.Front());
			}
			{
				list.PushFront(fooObject2);
				const SList<Foo> constList{ list };
				Assert::AreEqual(fooObject2, list.Front());
			}
			{
				const SList<Foo> constList{ list };
				const Foo& fooObject = constList.Front();
				Assert::AreEqual(fooObject, fooObject2);
			}
		}

		TEST_METHOD(Back)
		{
			SList<Foo> list;
			auto func = [&] {list.Back(); };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			Foo fooObject2(2);
			list.PushBack(fooObject1);
			Assert::AreEqual(fooObject1, list.Back());

			list.PushBack(fooObject2);
			Assert::AreEqual(fooObject2, list.Back());

			Foo& fooObject = list.Back();
			fooObject = fooObject1;
			Assert::AreEqual(fooObject1, list.Back());
		}

		TEST_METHOD(ConstBack)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			{
				const SList<Foo> constList{ list };
				auto func = [&] {constList.Back(); };
				Assert::ExpectException<std::runtime_error>(func);
			}
			{
				list.PushBack(fooObject1);
				const SList<Foo> constList{ list };
				Assert::AreEqual(fooObject1, constList.Back());
			}
			{
				list.PushBack(fooObject2);
				const SList<Foo> constList{ list };
				Assert::AreEqual(fooObject2, list.Back());
			}
			{
				const SList<Foo> constList{ list };
				const Foo& fooObject = constList.Back();
				Assert::AreEqual(fooObject, fooObject2);
			}
		}

		TEST_METHOD(Size)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Assert::AreEqual((size_t)0, list.Size());

			list.PushBack(fooObject1);
			Assert::AreEqual((size_t)1, list.Size());

			list.PushBack(fooObject2);
			Assert::AreEqual((size_t)2, list.Size());

			list.PopBack();
			Assert::AreEqual((size_t)1, list.Size());

			list.PopBack();
			Assert::AreEqual((size_t)0, list.Size());
		}

		TEST_METHOD(InsertAfter)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			SList<Foo>::Iterator it;
			bool didInsert = list.InsertAfter(fooObject1, it);
			Assert::IsFalse(didInsert);

			it = list.begin();
			didInsert = list.InsertAfter(fooObject1, it);
			Assert::IsTrue(didInsert);
			Assert::AreEqual(fooObject1, list.Front());

			it = list.begin();
			didInsert = list.InsertAfter(fooObject2, it);
			Assert::IsTrue(didInsert);
			Assert::AreEqual(fooObject2, list.Back());
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(size_t(2), list.Size());

			it = list.begin();
			didInsert = list.InsertAfter(fooObject3, it);
			Assert::IsTrue(didInsert);
			Assert::AreEqual(size_t(3), list.Size());
		}

		TEST_METHOD(Remove)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			Foo fooObject4(4);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);
			list.PushBack(fooObject4);
			bool didRemove = list.Remove(fooObject1);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, list.Front());

			didRemove = list.Remove(fooObject1);
			Assert::IsFalse(didRemove);
			didRemove = list.Remove(fooObject3);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, list.Front());
			Assert::AreEqual(fooObject4, list.Back());

			didRemove = list.Remove(fooObject4);
			Assert::IsTrue(didRemove);
			Assert::AreEqual(fooObject2, list.Front());
			Assert::AreEqual(fooObject2, list.Back());
			Assert::AreEqual(size_t(1), list.Size());
			
			list.Clear();
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);
			list.PushBack(fooObject4);
			typename SList<Foo>::Iterator it = list.Find(fooObject2);
			list.Remove(it);
			Assert::AreEqual(fooObject1, list.Front());
			Assert::AreEqual(fooObject4, list.Back());
			Assert::AreEqual(size_t(3), list.Size());
			it = list.Find(fooObject1);
			list.Remove(it);
			Assert::AreEqual(fooObject3, list.Front());
			Assert::AreEqual(fooObject4, list.Back());
			Assert::AreEqual(size_t(2), list.Size());
			it = list.Find(fooObject4);
			list.Remove(it);
			Assert::AreEqual(fooObject3, list.Front());
			Assert::AreEqual(fooObject3, list.Back());
			Assert::AreEqual(size_t(1), list.Size());

		}

		TEST_METHOD(Find)
		{
			SList<Foo> list;
			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			Foo fooObject4(4);
			Foo fooObject5(5);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);
			list.PushBack(fooObject4);

			SList<Foo>::Iterator it = list.Find(fooObject1);
			Assert::AreEqual(fooObject1, *it);
			it = list.Find(fooObject2);
			Assert::AreEqual(fooObject2, *it);
			it = list.Find(fooObject5);
			Assert::AreEqual(list.end(), it);

			const SList<Foo>* constListRef = &list;
			SList<Foo>::ConstIterator constIt = constListRef->Find(fooObject1);
			Assert::AreEqual(fooObject1, *constIt);
			constIt = constListRef->Find(fooObject2);
			Assert::AreEqual(fooObject2, *constIt);
		}

		TEST_METHOD(begin)
		{
			SList<Foo> list;
			SList<Foo>::Iterator it = list.begin();
			auto func = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			list.PushFront(fooObject1);
			it = list.begin();
			Assert::AreEqual(*it, fooObject1);

			Foo fooObject2(2);
			list.PushFront(fooObject2);
			Assert::AreEqual(*it, fooObject1);
			it = list.begin();
			Assert::AreEqual(*it, fooObject2);

			const SList<Foo>* constListRef = &list;
			SList<Foo>::ConstIterator constIt = constListRef->begin();
			Assert::AreEqual(*constIt, fooObject2);
		}

		TEST_METHOD(cbegin)
		{
			SList<Foo> list;
			SList<Foo>::ConstIterator it = list.cbegin();
			auto func = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			list.PushFront(fooObject1);
			it = list.cbegin();
			Assert::AreEqual(*it, fooObject1);

			Foo fooObject2(2);
			list.PushFront(fooObject2);
			Assert::AreEqual(*it, fooObject1);
			it = list.cbegin();
			Assert::AreEqual(*it, fooObject2);
		}

		TEST_METHOD(end)
		{
			SList<Foo> list;
			SList<Foo>::Iterator it = list.end();
			auto func = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			list.PushFront(fooObject1);
			it = list.end();
			Assert::ExpectException<std::runtime_error>(func);
			SList<Foo>::Iterator it2 = list.begin();
			Assert::AreNotEqual(it, it2);

			const SList<Foo>* constListRef = &list;
			SList<Foo>::ConstIterator constIt = constListRef->end();
			auto func2 = [&] {*constIt; };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(cend)
		{
			SList<Foo> list;
			SList<Foo>::ConstIterator it = list.cend();
			auto func = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func);

			Foo fooObject1(1);
			list.PushFront(fooObject1);
			it = list.cend();
			Assert::ExpectException<std::runtime_error>(func);
			SList<Foo>::ConstIterator it2 = list.cbegin();
			Assert::AreNotEqual(it, it2);
		}
		TEST_METHOD(Iterator)
		{
		
			SList<Foo> list;
			size_t size = 0;
			for (SList<Foo>::Iterator it = list.begin(); it != list.end(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);
			size = 0;
			for (SList<Foo>::Iterator it = list.begin(); it != list.end(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			size = 0;
			for (SList<Foo>::Iterator it = list.begin(); !(it == list.end()); it++, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			SList<Foo>::Iterator it;
			auto func1 = [&] {*it; };
			Assert::ExpectException<std::runtime_error>(func1);
			it = list.begin();
			Assert::AreEqual(*it, fooObject1);

			SList<Foo>::Iterator it2;
			auto func2 = [&] {++it2;};
			Assert::ExpectException<std::runtime_error>(func2);
		}

		TEST_METHOD(ConstIterator)
		{

			SList<Foo> list;
			size_t size = 0;
			for (SList<Foo>::ConstIterator it = list.cbegin(); it != list.cend(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			list.PushBack(fooObject1);
			list.PushBack(fooObject2);
			list.PushBack(fooObject3);
			size = 0;
			for (SList<Foo>::ConstIterator it = list.cbegin(); it != list.cend(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			size = 0;
			for (SList<Foo>::ConstIterator it = list.cbegin(); !(it == list.cend()); it++, ++size)
			{
			}
			Assert::AreEqual(size, list.Size());

			SList<Foo>::ConstIterator constIt1 = list.cbegin();
			Assert::AreEqual(*constIt1, fooObject1);

			SList<Foo>::ConstIterator constIt;
			auto func1 = [&] {*constIt; };
			Assert::ExpectException<std::runtime_error>(func1);

			constIt = list.begin();
			SList<Foo>::ConstIterator constIt2{ constIt };
			Assert::AreEqual(*constIt2, fooObject1);

			SList<Foo>::ConstIterator constIt3;
			auto func = [&] {++constIt3; };
			Assert::ExpectException<std::runtime_error>(func);
		}

		private: 
			static _CrtMemState _startMemState;
	};

	_CrtMemState SListTests::_startMemState;
}