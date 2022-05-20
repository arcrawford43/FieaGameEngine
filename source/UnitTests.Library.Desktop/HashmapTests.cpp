#include "pch.h"
#include "Hashmap.h"
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
	TEST_CLASS(HashmapTests)
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

		TEST_METHOD(DefaultHashInt)
		{
			DefaultHash<int> hashFunction;
			int a = 0;
			int aa = a;
			int b = 1;
			int c = 2;
			std::size_t hashA = hashFunction(a);
			std::size_t hashAA = hashFunction(aa);
			std::size_t hashB = hashFunction(b);
			std::size_t hashC = hashFunction(c);

			Assert::AreEqual(hashA, hashAA);
			Assert::AreNotEqual(hashA, hashB);
			Assert::AreNotEqual(hashA, hashC);
			Assert::AreNotEqual(hashB, hashC);
		}

		TEST_METHOD(DefaultHashString)
		{
			DefaultHash<std::string> hashFunction;
			std::string hello = "hello";
			std::string hello2 = hello;
			std::string hello3 = "hello";
			std::string world = "world";
			std::string Austin = "Austin";
			std::size_t hashHello = hashFunction(hello);
			std::size_t hashHello2 = hashFunction(hello2);
			std::size_t hashHello3 = hashFunction(hello3);
			std::size_t hashWorld = hashFunction(world);
			std::size_t hashAustin = hashFunction(Austin);

			Assert::AreEqual(hashHello, hashHello2);
			Assert::AreEqual(hashHello, hashHello3);
			Assert::AreNotEqual(hashHello, hashWorld);
			Assert::AreNotEqual(hashHello, hashAustin);
			Assert::AreNotEqual(hashWorld, hashAustin);
		}

		TEST_METHOD(DefaultHashConstString)
		{
			DefaultHash<const std::string> hashFunction;
			std::string hello = "hello";
			std::string hello2 = hello;
			std::string hello3 = "hello";
			std::string world = "world";
			std::string Austin = "Austin";
			std::size_t hashHello = hashFunction(hello);
			std::size_t hashHello2 = hashFunction(hello2);
			std::size_t hashHello3 = hashFunction(hello3);
			std::size_t hashWorld = hashFunction(world);
			std::size_t hashAustin = hashFunction(Austin);

			Assert::AreEqual(hashHello, hashHello2);
			Assert::AreEqual(hashHello, hashHello3);
			Assert::AreNotEqual(hashHello, hashWorld);
			Assert::AreNotEqual(hashHello, hashAustin);
			Assert::AreNotEqual(hashWorld, hashAustin);
		}

		TEST_METHOD(DefaultHashCStyleString)
		{
			DefaultHash<char*> hashFunction;
			char *hello = "hello";
			char *hello2 = hello;
			char *hello3 = "hello";
			char *world = "world";
			char *Austin = "Austin";
			std::size_t hashHello = hashFunction(hello);
			std::size_t hashHello2 = hashFunction(hello2);
			std::size_t hashHello3 = hashFunction(hello3);
			std::size_t hashWorld = hashFunction(world);
			std::size_t hashAustin = hashFunction(Austin);

			Assert::AreEqual(hashHello, hashHello2);
			Assert::AreEqual(hashHello, hashHello3);
			Assert::AreNotEqual(hashHello, hashWorld);
			Assert::AreNotEqual(hashHello, hashAustin);
			Assert::AreNotEqual(hashWorld, hashAustin);
		}

		TEST_METHOD(DefaultHashConstCStyleString)
		{
			DefaultHash<const char*> hashFunction;
			char* hello = "hello";
			char* hello2 = hello;
			char* hello3 = "hello";
			char* world = "world";
			char* Austin = "Austin";
			std::size_t hashHello = hashFunction(hello);
			std::size_t hashHello2 = hashFunction(hello2);
			std::size_t hashHello3 = hashFunction(hello3);
			std::size_t hashWorld = hashFunction(world);
			std::size_t hashAustin = hashFunction(Austin);

			Assert::AreEqual(hashHello, hashHello2);
			Assert::AreEqual(hashHello, hashHello3);
			Assert::AreNotEqual(hashHello, hashWorld);
			Assert::AreNotEqual(hashHello, hashAustin);
			Assert::AreNotEqual(hashWorld, hashAustin);
		}

		TEST_METHOD(DefaultHashFoo)
		{
			DefaultHash<Foo> hashFunction;
			Foo a = 0;
			Foo aa = a;
			Foo b = 1;
			Foo c = 2;
			std::size_t hashA = hashFunction(a);
			std::size_t hashAA = hashFunction(aa);
			std::size_t hashB = hashFunction(b);
			std::size_t hashC = hashFunction(c);

			Assert::AreEqual(hashA, hashAA);
			Assert::AreNotEqual(hashA, hashB);
			Assert::AreNotEqual(hashA, hashC);
			Assert::AreNotEqual(hashB, hashC);
		}

		TEST_METHOD(Constructor)
		{
			Hashmap<UnitTests::Foo, int> hash;
			Assert::AreEqual(size_t(0), hash.Size());
			Assert::AreEqual(0.0f, hash.LoadFactor());
			Assert::AreEqual(0.0f, hash.Capacity());

			Hashmap<UnitTests::Foo, int> hash2{ 5 };
			Assert::AreEqual(size_t(0), hash2.Size());
			Assert::AreEqual(0.0f, hash2.LoadFactor());
			Assert::AreEqual(0.0f, hash2.Capacity());

			Hashmap<UnitTests::Foo, int> hash3{ 0 };
			hash3.Insert(std::make_pair(2, 2));
			Assert::AreEqual(size_t(1), hash3.Size());
			Assert::AreEqual(0.5f, hash3.LoadFactor());
			Assert::AreEqual(50.0f, hash3.Capacity());
		}

		TEST_METHOD(Insert)
		{
			Hashmap<UnitTests::Foo, int> hash;
			std::pair<typename Hashmap<UnitTests::Foo, int>::Iterator, bool> result = hash.Insert(std::make_pair(1, 1));
			Assert::IsTrue(result.second);
			Assert::AreEqual((*(result.first)).first, UnitTests::Foo(1));
			Assert::AreEqual((*(result.first)).second, 1);
			Assert::AreEqual(100.0f / 11.0f, hash.Capacity());
			Assert::AreEqual(1.0f / 11.0f, hash.LoadFactor());

			result = hash.Insert(std::make_pair(1, 5));
			Assert::IsFalse(result.second);
			Assert::AreEqual((*(result.first)).first, UnitTests::Foo(1));
			Assert::AreEqual((*(result.first)).second, 1);
			Assert::AreEqual(100.0f / 11.0f, hash.Capacity());
			Assert::AreEqual(1.0f / 11.0f, hash.LoadFactor());

			result = hash.Insert(std::make_pair(12, 5));
			Assert::IsTrue(result.second);
			Assert::AreEqual((*(result.first)).first, UnitTests::Foo(12));
			Assert::AreEqual((*(result.first)).second, 5);
			Assert::AreEqual(100.0f / 11.0f, hash.Capacity());
			Assert::AreEqual(2.0f / 11.0f, hash.LoadFactor());

			result = hash.Insert(std::make_pair(2, 8));
			Assert::IsTrue(result.second);
			Assert::AreEqual((*(result.first)).first, UnitTests::Foo(2));
			Assert::AreEqual((*(result.first)).second, 8);
			Assert::AreEqual(200.0f / 11.0f, hash.Capacity());
			Assert::AreEqual(3.0f / 11.0f, hash.LoadFactor());
		}

		TEST_METHOD(Find)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			hash.Insert(std::make_pair(2, 2));
			hash.Insert(std::make_pair(3, 3));
			typename Hashmap<Foo, int>::Iterator it = hash.Find(Foo(1));
			Assert::AreEqual((*it).first, Foo(1));
			Assert::AreEqual((*it).second, 1);
			it = hash.Find(Foo(2));
			Assert::AreEqual((*it).first, Foo(2));
			Assert::AreEqual((*it).second, 2);

			it = hash.Find(Foo(4));
			Assert::AreEqual(it, hash.end());

			const Hashmap<UnitTests::Foo, int> hash2 = hash;
			typename Hashmap<Foo, int>::ConstIterator constIt = hash2.Find(Foo(1));
			Assert::AreEqual((*constIt).first, Foo(1));
			Assert::AreEqual((*constIt).second, 1);
			constIt = hash2.Find(Foo(2));
			Assert::AreEqual((*constIt).first, Foo(2));
			Assert::AreEqual((*constIt).second, 2);

			constIt = hash2.Find(Foo(5));
			Assert::AreEqual(constIt, hash2.end());
		}

		TEST_METHOD(IndexOperator)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			Assert::AreEqual(hash[1], 1);

			hash[2] = 25;
			Assert::AreEqual(hash.At(2), 25);
		}

		TEST_METHOD(At)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			Assert::AreEqual(hash.At(1), 1);
			auto atFunc = [&] {hash.At(2); };
			Assert::ExpectException<std::runtime_error>(atFunc);

			const Hashmap<UnitTests::Foo, int> hash2 = hash;
			Assert::AreEqual(hash2.At(1), 1);
			auto atConstFunc = [&] {hash2.At(2); };
			Assert::ExpectException<std::runtime_error>(atConstFunc);
		}

		TEST_METHOD(Remove)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			Assert::IsTrue(hash.Remove(1));
			Assert::AreEqual(size_t(0), hash.Size());


			Assert::IsFalse(hash.Remove(1));
		}

		TEST_METHOD(Clear)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			hash.Insert(std::make_pair(2, 2));
			hash.Clear();
			Assert::AreEqual(hash.Size(), size_t(0));
			Assert::AreEqual(hash.begin(), hash.end());
		}

		TEST_METHOD(ContainsKey)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 5));
			Assert::IsTrue(hash.ContainsKey(1));
			Assert::IsFalse(hash.ContainsKey(2));

			int a;
			hash.ContainsKey(1, a);
			Assert::AreEqual(a, 5);
			hash.ContainsKey(2, a);
			Assert::AreEqual(a, 5);
		}

		TEST_METHOD(BeginAndEnd)
		{
			Hashmap<UnitTests::Foo, int> hash;
			Assert::AreEqual(hash.begin(), hash.end());
			Assert::AreEqual(hash.cbegin(), hash.cend());
			const Hashmap<UnitTests::Foo, int> hash2 = hash;
			Assert::AreEqual(hash2.begin(), hash2.end());


			hash.Insert(std::make_pair(1, 1));
			const Hashmap<UnitTests::Foo, int> hash3 = hash;
			Assert::AreNotEqual(hash3.begin(), hash3.end());
			Assert::AreNotEqual(hash.begin(), hash.end());
			Assert::AreNotEqual(hash.cbegin(), hash.cend());
		}

		TEST_METHOD(Iterator)
		{
			Hashmap<Foo, int> hash;

			Foo fooObject1(1);
			Foo fooObject2(2);
			Foo fooObject3(3);
			hash.Insert(std::make_pair(fooObject1, 1));
			typename Hashmap<Foo, int>::Iterator it3 = hash.begin();
			Assert::AreEqual(it3->first, fooObject1);
			++it3;
			Assert::AreEqual(it3, hash.end());
			hash.Insert(std::make_pair(fooObject2, 2));
			hash.Insert(std::make_pair(fooObject3, 3));
			size_t size = 0;
			for (Hashmap<Foo, int>::Iterator it = hash.begin(); it != hash.end(); ++it, ++size)
			{
			}
			Assert::AreEqual(size, hash.Size());

			size = 0;
			for (Hashmap<Foo, int>::Iterator it = hash.begin(); !(it == hash.end()); it++, ++size)
			{
			}

			size = 0;
			for (Hashmap<Foo, int>::ConstIterator it = hash.begin(); !(it == hash.end()); it++, ++size)
			{
			}
			Assert::AreEqual(size, hash.Size());

			size = 0;
			for (Hashmap<Foo, int>::ConstIterator it = hash.begin(); !(it == hash.end()); ++it, ++size)
			{
			}
			Assert::AreEqual(size, hash.Size());

			Hashmap<Foo, int>::Iterator it;
			Hashmap<Foo, int>::ConstIterator it2;
			auto func11 = [&] {*it; };
			auto func12 = [&] {*it2; };
			Assert::ExpectException<std::runtime_error>(func11);
			Assert::ExpectException<std::runtime_error>(func12);
			
			auto func21 = [&] {++it; };
			auto func22 = [&] {++it2; };
			Assert::ExpectException<std::runtime_error>(func21);
			Assert::ExpectException<std::runtime_error>(func22);

			auto func31 = [&] {*it; };
			auto func32 = [&] {*it2; };
			Assert::ExpectException<std::runtime_error>(func31);
			Assert::ExpectException<std::runtime_error>(func32);

			auto func41 = [&] {it->first; };
			auto func42 = [&] {it2->first; };
			Assert::ExpectException<std::runtime_error>(func41);
			Assert::ExpectException<std::runtime_error>(func42);
		}

		TEST_METHOD(Rehash)
		{
			Hashmap<UnitTests::Foo, int> hash;
			hash.Insert(std::make_pair(1, 1));
			hash.Insert(std::make_pair(2, 2));
			hash.Insert(std::make_pair(3, 3));
			hash.Rehash(0);
			hash.Rehash(15);

			typename Hashmap<Foo, int>::Iterator it = hash.Find(Foo(1));
			Assert::AreEqual((*it).first, Foo(1));
			Assert::AreEqual((*it).second, 1);
			it = hash.Find(Foo(2));
			Assert::AreEqual((*it).first, Foo(2));
			Assert::AreEqual((*it).second, 2);
			it = hash.Find(Foo(3));
			Assert::AreEqual((*it).first, Foo(3));
			Assert::AreEqual((*it).second, 3);

			hash.Rehash(0, DefaultHash<Foo>());
			hash.Rehash(20, DefaultHash<Foo>());

			it = hash.Find(Foo(1));
			Assert::AreEqual((*it).first, Foo(1));
			Assert::AreEqual((*it).second, 1);
			it = hash.Find(Foo(2));
			Assert::AreEqual((*it).first, Foo(2));
			Assert::AreEqual((*it).second, 2);
			it = hash.Find(Foo(3));
			Assert::AreEqual((*it).first, Foo(3));
			Assert::AreEqual((*it).second, 3);
		}

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState HashmapTests::_startMemState;
}