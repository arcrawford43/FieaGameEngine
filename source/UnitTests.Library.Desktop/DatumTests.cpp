#include "pch.h"
#include "Datum.h"
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
	void InitDatumArray(Datum* dat, Foo* f)
	{
		dat[0] = 1;
		dat[1] = 1.0f;
		dat[2] = glm::vec4{ 1.0f };
		dat[3] = glm::mat4{ 1.0f };
		//dat[4] = glm::mat4{ 1.0f };
		dat[4] = std::string{ "Hello World" };;
		RTTI* temp = f;
		dat[5] = *temp;
	}
	void PushBackDatumArray(Datum* dat, Foo* f)
	{
		dat[0].PushBack( 2);
		dat[1].PushBack( 2.0f);
		dat[2].PushBack(glm::vec4{ 2.0f });
		dat[3].PushBack(glm::mat4{ 2.0f });
		//dat[4] = glm::mat4{ 1.0f };
		dat[4].PushBack(std::string{ "Bye World" });
		RTTI* temp = f;
		dat[5].PushBack(*temp);
	}
	TEST_CLASS(DatumTests)
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
			Datum d;
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), 0_z);
			Assert::IsFalse(d.IsExternalStorage());
		}

		TEST_METHOD(TypecastConstructors)
		{
			Foo f = 1;
			std::string a = "Hello"s;
			Datum dat[7]{1, 1.0f, glm::vec4(1.0f), glm::mat4(1.0f), "Hi"s, f, a};
			for (int i = 0; i < 7; ++i)
			{
				Assert::AreEqual(dat[i].Size(), 1_z);
				Assert::IsFalse(dat[i].IsExternalStorage());
			}
		}

		TEST_METHOD(CopyConstructor)
		{
			Datum d;
			Datum e = d;
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), 0_z);
			Assert::IsFalse(d.IsExternalStorage());
			Assert::AreEqual(e.Type(), DatumTypes::Unknown);
			Assert::AreEqual(e.Size(), 0_z);
			Assert::IsFalse(e.IsExternalStorage());

			Datum dat[6];
			Foo f = 1;
			InitDatumArray(dat, &f);
			for (int i = 0; i < 5; ++i)
			{
				Datum dat2 = dat[i];
				Assert::AreEqual(dat2.Type(), dat[i].Type());
				Assert::AreEqual(dat2.Size(), dat[i].Size());
				Assert::IsFalse(dat2.IsExternalStorage());
				Assert::AreEqual(dat2, dat[i]);
				Assert::AreEqual(dat2.ToString(), dat[i].ToString());
			}
			
			Datum dat2 = dat[5];
			Assert::AreEqual(dat2.Type(), dat[5].Type());
			Assert::AreEqual(dat2.Size(), dat[5].Size());
			Assert::IsFalse(dat2.IsExternalStorage());
			Assert::AreEqual(dat2, dat[5]);
			Assert::AreEqual(dat2.GetPointer(), dat[5].GetPointer());

			Datum dat3;
			int data[2] = { 0, 1 };
			dat3.SetStorage(data, 2);
			Datum dat4 = dat3;
			Assert::AreEqual(dat4.Type(), dat3.Type());
			Assert::AreEqual(dat4.Size(), dat3.Size());
			Assert::IsTrue(dat4.IsExternalStorage());
			Assert::AreEqual(dat4, dat3);
			Assert::AreEqual(dat4.ToString(), dat3.ToString());
		}

		TEST_METHOD(CopyAssignment)
		{
			Datum d;
			Datum e = d;
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), 0_z);
			Assert::IsFalse(d.IsExternalStorage());
			Assert::AreEqual(e.Type(), DatumTypes::Unknown);
			Assert::AreEqual(e.Size(), 0_z);
			Assert::IsFalse(e.IsExternalStorage());

			Datum dat[6];
			Foo f = 1;
			InitDatumArray(dat, &f);
			Datum dat2;
			for (int i = 0; i < 5; ++i)
			{
				dat2 = dat[i];
				Assert::AreEqual(dat2.Type(), dat[i].Type());
				Assert::AreEqual(dat2.Size(), dat[i].Size());
				Assert::IsFalse(dat2.IsExternalStorage());
				Assert::AreEqual(dat2, dat[i]);
				Assert::AreEqual(dat2.ToString(), dat[i].ToString());
			}
			dat2 = dat[5];
			Assert::AreEqual(dat2.Type(), dat[5].Type());
			Assert::AreEqual(dat2.Size(), dat[5].Size());
			Assert::IsFalse(dat2.IsExternalStorage());
			Assert::AreEqual(dat2, dat[5]);
			Assert::AreEqual(dat2.GetPointer(), dat[5].GetPointer());

			Datum dat3;
			int data[2] = { 0, 1 };
			dat3.SetStorage(data, 2);
			Datum dat4;
			dat4= dat3;
			Assert::AreEqual(dat4.Type(), dat3.Type());
			Assert::AreEqual(dat4.Size(), dat3.Size());
			Assert::IsTrue(dat4.IsExternalStorage());
			Assert::AreEqual(dat4, dat3);
			Assert::AreEqual(dat4.ToString(), dat3.ToString());

			
			dat4 = dat2;
			Assert::AreEqual(dat4.Type(), dat2.Type());
			Assert::AreEqual(dat4.Size(), dat2.Size());
			Assert::IsFalse(dat4.IsExternalStorage());
			Assert::AreEqual(dat4, dat2);
			Assert::AreEqual(dat4.GetPointer(), dat2.GetPointer());

			dat3.SetStorage(data, 2);
			dat2 = dat3;
			Assert::AreEqual(dat2.Type(), dat3.Type());
			Assert::AreEqual(dat2.Size(), dat3.Size());
			Assert::IsTrue(dat2.IsExternalStorage());
			Assert::AreEqual(dat2, dat3);
			Assert::AreEqual(dat2.ToString(), dat3.ToString());
		}
		
		TEST_METHOD(MoveSemantics)
		{
			Datum d;
			Datum e = std::move(d);
			Assert::AreEqual(d.Type(), DatumTypes::Unknown);
			Assert::AreEqual(d.Size(), 0_z);
			Assert::IsFalse(d.IsExternalStorage());
			Assert::AreEqual(e.Type(), DatumTypes::Unknown);
			Assert::AreEqual(e.Size(), 0_z);
			Assert::IsFalse(e.IsExternalStorage());

			{
				Datum dat[6];
				Datum datMove[6];
				Foo f = 1;
				InitDatumArray(dat, &f);
				InitDatumArray(datMove, &f);
				for (int i = 0; i < 5; ++i)
				{
					Datum dat2 = std::move(datMove[i]);
					Assert::AreEqual(dat2.Type(), dat[i].Type());
					Assert::AreEqual(dat2.Size(), dat[i].Size());
					Assert::IsFalse(dat2.IsExternalStorage());
					Assert::AreEqual(dat2, dat[i]);
					Assert::AreEqual(dat2.ToString(), dat[i].ToString());
				}
				Datum dat2 = datMove[5];
				Assert::AreEqual(dat2.Type(), dat[5].Type());
				Assert::AreEqual(dat2.Size(), dat[5].Size());
				Assert::IsFalse(dat2.IsExternalStorage());
				Assert::AreEqual(dat2, dat[5]);
				Assert::AreEqual(dat2.GetPointer(), dat[5].GetPointer());
			}

			Datum dat[6];
			Datum datMove[6];
			Foo f = 1;
			InitDatumArray(dat, &f);
			InitDatumArray(datMove, &f);
			Datum dat2;
			for (int i = 0; i < 5; ++i)
			{
				dat2 = std::move(datMove[i]);
				Assert::AreEqual(dat2.Type(), dat[i].Type());
				Assert::AreEqual(dat2.Size(), dat[i].Size());
				Assert::IsFalse(dat2.IsExternalStorage());
				Assert::AreEqual(dat2, dat[i]);
				Assert::AreEqual(dat2.ToString(), dat[i].ToString());
			}
			dat2 = datMove[5];
			Assert::AreEqual(dat2.Type(), dat[5].Type());
			Assert::AreEqual(dat2.Size(), dat[5].Size());
			Assert::IsFalse(dat2.IsExternalStorage());
			Assert::AreEqual(dat2, dat[5]);
			Assert::AreEqual(dat2.GetPointer(), dat[5].GetPointer());
		}

		TEST_METHOD(ScalarAssignmentOperator)
		{
			{
				Datum d;
				d = 1;
				Assert::AreEqual(d.Type(), DatumTypes::Integer);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(2); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Integer);
				d = 1;
				Assert::AreEqual(d.Type(), DatumTypes::Integer);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(2); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Float);
				auto Func = [&] {d.operator=(2); };
				Assert::ExpectException<std::runtime_error>(Func);
			}

			{
				Datum d;
				d = 1.0f;
				Assert::AreEqual(d.Type(), DatumTypes::Float);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(2.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Float);
				d = 1.0f;
				Assert::AreEqual(d.Type(), DatumTypes::Float);
				Assert::AreEqual(d.Size(), 1_z);
				d.Resize(2);
				Assert::IsFalse(d.IsExternalStorage());
				auto Func = [&] {d.operator=(2.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				auto Func = [&] {d.operator=(2.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}

			{
				Datum d;
				d = glm::vec4{ 1.0f };
				Assert::AreEqual(d.Type(), DatumTypes::Vector);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(glm::vec4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				d = glm::vec4{ 1.0f };
				Assert::AreEqual(d.Type(), DatumTypes::Vector);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(glm::vec4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				auto Func = [&] {d.operator=(glm::vec4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}

			{
				Datum d;
				d = glm::mat4{ 1.0f };
				Assert::AreEqual(d.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(glm::mat4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Matrix);
				d = glm::mat4{ 1.0f };
				Assert::AreEqual(d.Type(), DatumTypes::Matrix);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(glm::mat4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				auto Func = [&] {d.operator=(glm::mat4{ 1.0f }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}

			{
				Datum d;
				d = std::string{ "Hello" };
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(std::string{ "Hello" }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				d = std::string{ "Hello" };
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(std::string{ "Hello" }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				auto Func = [&] {d.operator=(std::string{ "Hello" }); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			std::string a = "Hello"s;
			{
				Datum d;
				d = a;
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(a); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				d = a;
				Assert::AreEqual(d.Type(), DatumTypes::String);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(a); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				auto Func = [&] {d.operator=(a); };
				Assert::ExpectException<std::runtime_error>(Func);
			}

			{
				Datum d;
				Foo f = 2;
				d = f;
				Assert::AreEqual(d.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				Foo f = 2;
				d = f;
				Assert::AreEqual(d.Type(), DatumTypes::Pointer);
				Assert::AreEqual(d.Size(), 1_z);
				Assert::IsFalse(d.IsExternalStorage());
				d.Resize(2);
				auto Func = [&] {d.operator=(f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				Foo f = 2;
				auto Func = [&] {d.operator=(f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
		}

		TEST_METHOD(ComparisonOperators)
		{
			{
				Datum dat[6];
				Foo f = 1;
				InitDatumArray(dat, &f);
				Datum dat2;
				dat2 = f;
				Assert::IsTrue(reinterpret_cast<RTTI*>(&f) == dat2.GetPointer());
				dat2.GetPointer()->ToString();
				for (int i = 0; i < 6; ++i)
				{
					dat2 = (dat[i]);
					Assert::AreEqual(dat2, dat[i]);
					Assert::IsFalse(dat2 != dat[i]);
				}
			}
			{
				Datum dat[6];
				Datum dat2[6];
				Foo f = 1;
				InitDatumArray(dat, &f);
				Foo f2 = 2;
				PushBackDatumArray(dat2, &f2);
				for (int i = 0; i < 6; ++i)
				{
					Assert::AreNotEqual(dat2[i], dat[i]);
					Assert::IsTrue(dat2[i] != dat[i]);
				}
			}
			{
				Datum dat[6];
				Datum dat2[6];
				Foo f = 1;
				InitDatumArray(dat, &f);
				Foo f2 = 2;
				PushBackDatumArray(dat2, &f2);
				PushBackDatumArray(dat2, &f2);
				for (int i = 0; i < 6; ++i)
				{
					Assert::AreNotEqual(dat2[i], dat[i]);
					Assert::IsTrue(dat2[i] != dat[i]);
				}
			}

		}

		TEST_METHOD(ScalarComparisonOperator)
		{
			{
				Datum d;
				d = 1;
				Assert::IsTrue(d == 1);
				Assert::IsFalse(d != 1);
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == 2);
				Assert::IsTrue(d != 2);
			}
			{
				Datum d;
				d = 1;
				d.PushBack(2);
				Assert::IsFalse(d == 1);
			}
			{
				Datum d;
				d = 1.0f;
				Assert::IsFalse(d == 1);
			}

			{
				Datum d;
				d = 1.0f;
				Assert::IsTrue(d == 1.0f);
				Assert::IsFalse(d != 1.0f);
			}
			{
				Datum d;
				d = 1.0f;
				Assert::IsFalse(d == 2.0f);
				Assert::IsTrue(d != 2.0f);
			}
			{
				Datum d;
				d = 1.0f;
				d.PushBack(2.0f);
				Assert::IsFalse(d == 1.0f);
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == 1.0f);
			}

			{
				Datum d;
				d = glm::vec4{1.0f};
				Assert::IsTrue(d == glm::vec4{1.0f});
				Assert::IsFalse(d != glm::vec4{1.0f});
			}
			{
				Datum d;
				d = glm::vec4{1.0f};
				Assert::IsFalse(d == glm::vec4{2.0f});
				Assert::IsTrue(d != glm::vec4{2.0f});
			}
			{
				Datum d;
				d = glm::vec4{1.0f};
				d.PushBack(glm::vec4{2.0f});
				Assert::IsFalse(d == glm::vec4{1.0f});
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == glm::vec4{1.0f});
			}

			{
				Datum d;
				d = glm::mat4{ 1.0f };
				Assert::IsTrue(d == glm::mat4{ 1.0f });
				Assert::IsFalse(d != glm::mat4{ 1.0f });
			}
			{
				Datum d;
				d = glm::mat4{ 1.0f };
				Assert::IsFalse(d == glm::mat4{ 2.0f });
				Assert::IsTrue(d != glm::mat4{ 2.0f });
			}
			{
				Datum d;
				d = glm::mat4{ 1.0f };
				d.PushBack(glm::mat4{ 2.0f });
				Assert::IsFalse(d == glm::mat4{ 1.0f });
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == glm::mat4{ 1.0f });
			}

			{
				Datum d;
				d = std::string("Hi");
				Assert::IsTrue(d == std::string("Hi"));
				Assert::IsFalse(d != std::string("Hi"));
			}
			{
				Datum d;
				d = std::string("Hi");
				Assert::IsFalse(d == std::string("Hello"));
				Assert::IsTrue(d != std::string("Hello"));
			}
			{
				Datum d;
				d = std::string("Hi");
				d.PushBack(std::string("Hello"));
				Assert::IsFalse(d == std::string("Hi"));
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == std::string("Hi"));
			}


			Foo f = 1;
			Foo f2 = 2;
			{
				Datum d;
				d = f2;
				Assert::IsTrue(d == &f2);
				Assert::IsFalse(d != &f2);
			}
			{
				Datum d;
				d = f2;
				Assert::IsFalse(d == &f);
				Assert::IsTrue(d != &f);
			}
			{
				Datum d;
				d = f2;
				d.PushBack(f);
				Assert::IsFalse(d == &f2);
			}
			{
				Datum d;
				d = 1;
				Assert::IsFalse(d == &f2);
			}
		}

		TEST_METHOD(Reserve)
		{
			{
				Datum d;
				int a;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.Reserve(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				auto Func = [&] {d.Reserve(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
		}

		TEST_METHOD(SetType)
		{
			Datum d;
			auto Func = [&] {d.SetType(DatumTypes::Unknown); };
			Assert::ExpectException<std::runtime_error>(Func);

			d.SetType(DatumTypes::Integer);
			Assert::AreEqual(d.Type(), DatumTypes::Integer);
			auto Func2 = [&] {d.SetType(DatumTypes::Float); };
			Assert::ExpectException<std::runtime_error>(Func2);
		}

		TEST_METHOD(Resize)
		{
			{
				Datum d;
				int a;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.Resize(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				auto Func = [&] {d.Resize(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d[6];
				Foo f = 1;
				InitDatumArray(d, &f);
				for (int i = 0; i < 6; ++i)
				{
					d[i].Resize(5);
					Assert::AreEqual(d[i].Size(), 5_z);
					Assert::AreEqual(d[i].Capacity(), 5_z);
				}
				
				Assert::AreEqual(d[0].GetInteger(2), 0);
				Assert::AreEqual(d[1].GetFloat(2), 0.0f);
				Assert::AreEqual(d[2].GetVector(2), glm::vec4{ 0.0f });
				Assert::AreEqual(d[3].GetMatrix(2), glm::mat4{ 0.0f });
				Assert::AreEqual(d[4].GetString(2), std::string(""));
				Assert::AreEqual(d[5].GetPointer(2), static_cast<RTTI*>( nullptr));

				for (int i = 0; i < 6; ++i)
				{
					d[i].Resize(1);
					Assert::AreEqual(d[i].Size(), 1_z);
					Assert::AreEqual(d[i].Capacity(), 1_z);
				}
			}
		}

		TEST_METHOD(Set)
		{
			{
				Datum d;
				auto Func = [&] {d.Set(1, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2);
				Assert::AreEqual(d.GetInteger(), 2);
			}
			{
				Datum d;
				auto Func = [&] {d.Set(1.0f, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1.0f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2.0f);
				Assert::AreEqual(d.GetFloat(), 2.0f);
			}
			{
				Datum d;
				auto Func = [&] {d.Set(glm::vec4(1.0f), 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::vec4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::vec4(2.0f));
				Assert::AreEqual(d.GetVector(), glm::vec4(2.0f));
			}
			{
				Datum d;
				auto Func = [&] {d.Set(glm::mat4(1.0f), 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::mat4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::mat4(2.0f));
				Assert::AreEqual(d.GetMatrix(), glm::mat4(2.0f));
			}
			{
				Datum d;
				auto Func = [&] {d.Set("Hello"s, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack("Hello"s);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set("Hi"s);
				Assert::AreEqual(d.GetString(), "Hi"s);
			}
			{
				Datum d;
				std::string a = "Hello"s;
				std::string b = "Hi"s;
				auto Func = [&] {d.Set(a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack("Hello"s);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(b);
				Assert::AreEqual(d.GetString(), "Hi"s);
			}
			{
				Datum d;
				Foo f = 1;
				Foo f2 = 2;
				auto Func = [&] {d.Set(f, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(f2);
				Assert::AreEqual(d.GetPointer(), reinterpret_cast<RTTI*>(&f2));
			}
		}

		TEST_METHOD(Get)
		{
			{
				Datum d;
				auto Func = [&] {d.GetInteger(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2);
				Assert::AreEqual(d.GetInteger(), 2);
			}
			{
				Datum d;
				auto Func = [&] {d.GetFloat(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1.0f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2.0f);
				Assert::AreEqual(d.GetFloat(), 2.0f);
			}
			{
				Datum d;
				auto Func = [&] {d.GetVector(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::vec4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::vec4(2.0f));
				Assert::AreEqual(d.GetVector(), glm::vec4(2.0f));
			}
			{
				Datum d;
				auto Func = [&] {d.GetMatrix( 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::mat4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::mat4(2.0f));
				Assert::AreEqual(d.GetMatrix(), glm::mat4(2.0f));
			}
			{
				Datum d;
				auto Func = [&] {d.GetString( 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack("Hello"s);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set("Hi"s);
				Assert::AreEqual(d.GetString(), "Hi"s);
			}
			{
				Datum d;
				Foo f = 1;
				Foo f2 = 2;
				auto Func = [&] {d.GetPointer(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(f2);
				Assert::AreEqual(d.GetPointer(), reinterpret_cast<RTTI*>(&f2));
			}
			{
				Datum d;
				const Datum& e = d;
				auto Func = [&] {e.GetInteger(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2);
				Assert::AreEqual(e.GetInteger(), 2);
			}
			{
				Datum d;
				const Datum& e = d;
				auto Func = [&] {e.GetFloat(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1.0f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(2.0f);
				Assert::AreEqual(e.GetFloat(), 2.0f);
			}
			{
				Datum d;
				const Datum& e = d;
				auto Func = [&] {e.GetVector(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::vec4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::vec4(2.0f));
				Assert::AreEqual(e.GetVector(), glm::vec4(2.0f));
			}
			{
				Datum d;
				const Datum& e = d;
				auto Func = [&] {e.GetMatrix(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::mat4(1.0f));
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(glm::mat4(2.0f));
				Assert::AreEqual(e.GetMatrix(), glm::mat4(2.0f));
			}
			{
				Datum d;
				const Datum& e = d;
				auto Func = [&] {e.GetString(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack("Hello"s);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set("Hi"s);
				Assert::AreEqual(e.GetString(), "Hi"s);
			}
			{
				Datum d;
				const Datum& e = d;
				Foo f = 1;
				Foo f2 = 2;
				auto Func = [&] {e.GetPointer(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(f);
				Assert::ExpectException<std::out_of_range>(Func);
				d.Set(f2);
				Assert::AreEqual(e.GetPointer(), reinterpret_cast<const RTTI*>(&f2));
			}
		}

		TEST_METHOD(PushBack)
		{
			{
				Datum d;
				int a = 1;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack(1); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.PushBack(1);
				d.PushBack(1);
				d.PushBack(1);
				d.PushBack(1);
				d.PushBack(1);
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				Datum d;
				float a = 1.0f;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack(1.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack(1.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.PushBack(1.0f);
				d.PushBack(1.0f);
				d.PushBack(1.0f);
				d.PushBack(1.0f);
				d.PushBack(1.0f);
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				Datum d;
				glm::vec4 a = glm::vec4(1.0f);
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack(glm::vec4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack(glm::vec4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.PushBack(glm::vec4(1.0f));
				d.PushBack(glm::vec4(1.0f));
				d.PushBack(glm::vec4(1.0f));
				d.PushBack(glm::vec4(1.0f));
				d.PushBack(glm::vec4(1.0f));
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				Datum d;
				glm::mat4 a = glm::mat4(1.0f);
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack(glm::mat4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack(glm::mat4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.PushBack(glm::mat4(1.0f));
				d.PushBack(glm::mat4(1.0f));
				d.PushBack(glm::mat4(1.0f));
				d.PushBack(glm::mat4(1.0f));
				d.PushBack(glm::mat4(1.0f));
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				Datum d;
				std::string a = "Hello"s;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack("Hello"s); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack("Hello"s); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.PushBack("Hello"s);
				d.PushBack("Hello"s);
				d.PushBack("Hello"s);
				d.PushBack("Hello"s);
				d.PushBack("Hello"s);
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				std::string a = "Hello"s;
				Datum d;
				d.SetStorage(&a, 1);
				auto Func = [&] {d.PushBack(a); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				std::string a = "Hello"s;
				Datum d;
				d.SetType(DatumTypes::Pointer);
				auto Func = [&] {d.PushBack(a); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				std::string a = "Hello"s;
				Datum d;
				d.PushBack(a);
				d.PushBack(a);
				d.PushBack(a);
				d.PushBack(a);
				d.PushBack(a);
				Assert::AreEqual(d.Size(), 5_z);
			}

			{
				Datum d;
				Foo f = 1;
				RTTI *f2 = &f;
				d.SetStorage(&f2, 1);
				auto Func = [&] {d.PushBack(f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				Foo f = 1;
				d.SetType(DatumTypes::Integer);
				auto Func = [&] {d.PushBack(f); };
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				Foo f = 1;
				d.PushBack(f);
				d.PushBack(f);
				d.PushBack(f);
				d.PushBack(f);
				d.PushBack(f);
				Assert::AreEqual(d.Size(), 5_z);
			}
		}

		TEST_METHOD(PopBack)
		{
			{
				Datum d;
				int a;
				auto Func = [&] {d.PopBack(); };
				Assert::ExpectException<std::runtime_error>(Func);

				d.SetType(DatumTypes::Integer);
				d.PopBack();

				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
		}
		
		TEST_METHOD(Front)
		{
			{
				Datum d = 1;
				const Datum& e = d;
				Assert::AreEqual(d.FrontInteger(), 1);
				Assert::AreEqual(e.FrontInteger(), 1);
				Assert::AreEqual(d.BackInteger(), 1);
				Assert::AreEqual(e.BackInteger(), 1);
			}

			{
				Datum d = 1.0f;
				const Datum& e = d;
				Assert::AreEqual(d.FrontFloat(), 1.0f);
				Assert::AreEqual(e.FrontFloat(), 1.0f);
				Assert::AreEqual(d.BackFloat(), 1.0f);
				Assert::AreEqual(e.BackFloat(), 1.0f);
			}

			{
				Datum d = glm::vec4(1.0f);
				const Datum& e = d;
				Assert::AreEqual(d.FrontVector(), glm::vec4(1.0f));
				Assert::AreEqual(e.FrontVector(), glm::vec4(1.0f));
				Assert::AreEqual(d.BackVector(), glm::vec4(1.0f));
				Assert::AreEqual(e.BackVector(), glm::vec4(1.0f));
			}

			{
				Datum d = glm::mat4(1.0f);
				const Datum& e = d;
				Assert::AreEqual(d.FrontMatrix(), glm::mat4(1.0f));
				Assert::AreEqual(e.FrontMatrix(), glm::mat4(1.0f));
				Assert::AreEqual(d.BackMatrix(), glm::mat4(1.0f));
				Assert::AreEqual(e.BackMatrix(), glm::mat4(1.0f));
			}

			{
				Datum d = "Hello"s;
				const Datum& e = d;
				Assert::AreEqual(d.FrontString(), "Hello"s);
				Assert::AreEqual(e.FrontString(), "Hello"s);
				Assert::AreEqual(d.BackString(), "Hello"s);
				Assert::AreEqual(e.BackString(), "Hello"s);
			}

			{
				Foo f = 1;
				Datum d = f;
				const Datum& e = d;
				d.FrontPointer();
				Assert::AreEqual(d.FrontPointer(), reinterpret_cast<RTTI*>( &f));
				Assert::AreEqual(e.FrontPointer(), reinterpret_cast<const RTTI*>(&f));
				Assert::AreEqual(d.BackPointer(), reinterpret_cast<RTTI*>(&f));
				Assert::AreEqual(e.BackPointer(), reinterpret_cast<const RTTI*>(&f));
			}
		}

		TEST_METHOD(Remove)
		{
			{
				Datum d;
				auto Func = [&] {d.Remove(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				int a = 1;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Integer);
				Assert::IsFalse(d.Remove(1));
				d.PushBack(1);
				d.PushBack(2);
				d.PushBack(3);
				Assert::IsFalse(d.Remove(4));
				Assert::IsTrue(d.Remove(1));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontInteger(), 2);
				d.BackInteger();
				Assert::AreEqual(d.BackInteger(), 3);
			}

			{
				Datum d;
				auto Func = [&] {d.Remove(1.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
				float a = 1.0f;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Float);
				Assert::IsFalse(d.Remove(1.0f));
				d.PushBack(1.0f);
				d.PushBack(2.0f);
				d.PushBack(3.0f);
				Assert::IsFalse(d.Remove(4.0f));
				Assert::IsTrue(d.Remove(1.0f));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontFloat(), 2.0f);
				d.BackFloat();
				Assert::AreEqual(d.BackFloat(), 3.0f);
			}

			{
				Datum d;
				auto Func = [&] {d.Remove(glm::vec4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
				glm::vec4 a = glm::vec4(1.0f);
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Vector);
				Assert::IsFalse(d.Remove(glm::vec4(1.0f)));
				d.PushBack(glm::vec4(1.0f));
				d.PushBack(glm::vec4(2.0f));
				d.PushBack(glm::vec4(3.0f));
				Assert::IsFalse(d.Remove(glm::vec4(4.0f)));
				Assert::IsTrue(d.Remove(glm::vec4(1.0f)));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontVector(), glm::vec4(2.0f));
				d.BackVector();
				Assert::AreEqual(d.BackVector(), glm::vec4(3.0f));
			}

			{
				Datum d;
				auto Func = [&] {d.Remove(glm::mat4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
				glm::mat4 a = glm::mat4(1.0f);
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::Matrix);
				Assert::IsFalse(d.Remove(glm::mat4(1.0f)));
				d.PushBack(glm::mat4(1.0f));
				d.PushBack(glm::mat4(2.0f));
				d.PushBack(glm::mat4(3.0f));
				Assert::IsFalse(d.Remove(glm::mat4(4.0f)));
				Assert::IsTrue(d.Remove(glm::mat4(1.0f)));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontMatrix(), glm::mat4(2.0f));
				d.BackMatrix();
				Assert::AreEqual(d.BackMatrix(), glm::mat4(3.0f));
			}

			{
				Datum d;
				auto Func = [&] {d.Remove("1"s); };
				Assert::ExpectException<std::runtime_error>(Func);
				std::string a = "1"s;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Datum d;
				d.SetType(DatumTypes::String);
				Assert::IsFalse(d.Remove("1"s));
				d.PushBack("1"s);
				d.PushBack("2"s);
				d.PushBack("3"s);
				Assert::IsFalse(d.Remove("4"s));
				Assert::IsTrue(d.Remove("1"s));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontString(), "2"s);
				d.BackString();
				Assert::AreEqual(d.BackString(), "3"s);
			}

			{
				Datum d;
				Foo f1 = 1;
				Foo f2 = 2;
				Foo f3 = 3;
				Foo f4 = 4;
				auto Func = [&] {d.Remove(f1); };
				Assert::ExpectException<std::runtime_error>(Func);
				RTTI* a = &f1;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
			{
				Foo f1 = 1;
				Foo f2 = 2;
				Foo f3 = 3;
				Foo f4 = 4;
				Datum d;
				d.SetType(DatumTypes::Pointer);
				Assert::IsFalse(d.Remove(f1));
				d.PushBack(f1);
				d.PushBack(f2);
				d.PushBack(f3);
				Assert::IsFalse(d.Remove(f4));
				Assert::IsTrue(d.Remove(f1));
				Assert::AreEqual(d.Size(), 2_z);
				Assert::AreEqual(d.FrontPointer(),reinterpret_cast<RTTI*>( &f2));
				d.BackPointer();
				Assert::AreEqual(d.BackPointer(), reinterpret_cast<RTTI*>(&f3));
			}
		}

		TEST_METHOD(RemoveAt)
		{
			{
				Datum d;
				auto Func = [&] {d.RemoveAt(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				int a = 1;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}

			Datum d[6];
			Foo f = 1;
			InitDatumArray(d, &f);
			PushBackDatumArray(d, &f);
			for (int i = 0; i < 6; ++i)
			{
				Assert::IsFalse(d[i].RemoveAt(2));
				Assert::IsTrue(d[i].RemoveAt(1));
				Assert::AreEqual(d[i].Size(), 1_z);
			}
		}

		TEST_METHOD(Find)
		{
			{
				Datum d;
				auto Func = [&] {d.Find(1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1);
				Assert::IsTrue(d.Find(1) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find(2) == std::make_pair(1_z, false));
			}

			{
				Datum d;
				auto Func = [&] {d.Find(1.0f); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(1.0f);
				Assert::IsTrue(d.Find(1.0f) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find(2.0f) == std::make_pair(1_z, false));
			}

			{
				Datum d;
				auto Func = [&] {d.Find(glm::vec4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::vec4(1.0f));
				Assert::IsTrue(d.Find(glm::vec4(1.0f)) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find(glm::vec4(2.0f)) == std::make_pair(1_z, false));
			}

			{
				Datum d;
				auto Func = [&] {d.Find(glm::mat4(1.0f)); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(glm::mat4(1.0f));
				Assert::IsTrue(d.Find(glm::mat4(1.0f)) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find(glm::mat4(2.0f)) == std::make_pair(1_z, false));
			}

			{
				Datum d;
				auto Func = [&] {d.Find("Hello"s); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack("Hello"s);
				Assert::IsTrue(d.Find("Hello"s) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find("Hi"s) == std::make_pair(1_z, false));
			}

			{
				Foo f1 = 1;
				Foo f2 = 2;
				Datum d;
				auto Func = [&] {d.Find(f1); };
				Assert::ExpectException<std::runtime_error>(Func);
				d.PushBack(f1);
				Assert::IsTrue(d.Find(f1) == std::make_pair(0_z, true));
				Assert::IsTrue(d.Find(f2) == std::make_pair(1_z, false));
			}
		}

		TEST_METHOD(ToAndFromString)
		{
			{
				Datum d1;
				auto Func = [&] {d1.ToString(); };
				Assert::ExpectException<std::runtime_error>(Func);
				Datum d[6];
				Foo f = 1;
				InitDatumArray(d, &f);
				for (int i = 0; i < 5; ++i)
				{
					d[i].PushBackFromString(d[i].ToString(0));
					Assert::AreEqual(d[i].ToString(0), d[i].ToString(1));
					d[i].Resize(3);
					d[i].SetFromString(d[i].ToString(0), 2);
					Assert::AreEqual(d[i].ToString(0), d[i].ToString(2));
				}
				Assert::AreEqual(d[5].ToString(0), "1"s);
				d[5].Resize(3);
				auto Func2 = [&] {d[5].ToString(2); };
				Assert::ExpectException<std::runtime_error>(Func2);
			}
			{
				Datum d;
				auto Func = [&] {d.PushBackFromString("1"s); };
				Assert::ExpectException<std::runtime_error>(Func);
				auto Func2 = [&] {d.SetFromString("1"s); };
				Assert::ExpectException<std::runtime_error>(Func2);
				int a = 1;
				d.SetStorage(&a, 1);
				Assert::ExpectException<std::runtime_error>(Func);
			}
		}

		TEST_METHOD(Clear)
		{
			Datum d;
			int a = 1;
			d.SetStorage(&a, 1);
			auto Func = [&] {d.Clear(); };
			Assert::ExpectException<std::runtime_error>(Func);
		}

		TEST_METHOD(SetStorage)
		{
			{
				int a = 1;
				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<int*>(nullptr) , 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = 1;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);
				
				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetInteger());
			}

			{
				float a = 1.0f;
				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<float*>(nullptr), 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = 1.0f;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);

				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetFloat());
			}

			{
				glm::vec4 a ( 1.0f);
				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<glm::vec4*>(nullptr), 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = a;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);

				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetVector());
			}

			{
				glm::mat4 a(1.0f);
				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<glm::mat4*>(nullptr), 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = a;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);

				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetMatrix());
			}

			{
				std::string a("1"s);
				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<std::string*>(nullptr), 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = a;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);

				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetString());
			}

			{
				Foo f = 1;
				RTTI* a = &f;

				Datum d;
				auto Func2 = [&] {d.SetStorage(static_cast<RTTI**>(nullptr), 1); };
				Assert::ExpectException<std::runtime_error>(Func2);
				d = *a;
				auto Func = [&] {d.SetStorage(&a, 1); };
				Assert::ExpectException<std::runtime_error>(Func);

				Datum d2;
				d2.SetStorage(&a, 1);
				Assert::AreEqual(a, d2.GetPointer());
			}
		}
		
	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState DatumTests::_startMemState;
}