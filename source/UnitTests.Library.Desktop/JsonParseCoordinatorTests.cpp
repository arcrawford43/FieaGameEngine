#include "pch.h"
#include "JsonIntegerParseHelper.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(JsonCoordinatorTest)
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

		TEST_METHOD(SingleInt)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "int": 1
            })";

			Assert::IsFalse(sharedData.InitializeCalled);
			Assert::IsFalse(helper.InitializeCalled);
			coor.Parse(json);
			Assert::IsTrue(sharedData.InitializeCalled);
			Assert::IsTrue(helper.InitializeCalled);
			Assert::AreEqual(sharedData.Data[0], 1);
		}

		TEST_METHOD(ArrayInt)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "intArray": [1, 2, 3, 4]
            })";

			Assert::IsFalse(sharedData.InitializeCalled);
			Assert::IsFalse(helper.InitializeCalled);
			coor.Parse(json);
			Assert::IsTrue(sharedData.InitializeCalled);
			Assert::IsTrue(helper.InitializeCalled);
			Assert::AreEqual(sharedData.Data[0], 1);
			Assert::AreEqual(sharedData.Data[1], 2);
			Assert::AreEqual(sharedData.Data[2], 3);
			Assert::AreEqual(sharedData.Data[3], 4);
		}

		TEST_METHOD(ObjectInt)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "int": 1,
                 "parent" : {
                    "int": [2, 3, 4]
                  },
				"int2": 2
            })";

			Assert::IsFalse(sharedData.InitializeCalled);
			Assert::IsFalse(helper.InitializeCalled);
			coor.Parse(json);
			Assert::IsTrue(sharedData.InitializeCalled);
			Assert::IsTrue(helper.InitializeCalled);
			Assert::AreEqual(sharedData.Data[0], 1);
			Assert::AreEqual(sharedData.Data[1], 2);
		}

		TEST_METHOD(Clone)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "int": 1
            })";

			Assert::IsFalse(sharedData.InitializeCalled);
			Assert::IsFalse(helper.InitializeCalled);
			coor.Parse(json);
			Assert::IsTrue(sharedData.InitializeCalled);
			Assert::IsTrue(helper.InitializeCalled);
			Assert::AreEqual(sharedData.Data[0], 1);

			JsonParseCoordinator* clone = coor.Clone();
			auto Func1 = [&] {clone->AddHelper(helper); };
			Assert::ExpectException<std::runtime_error>(Func1);

			auto Func2 = [&] {clone->RemoveHelper(helper); };
			Assert::ExpectException<std::runtime_error>(Func2);

			auto Func3 = [&] {*clone = std::move(coor); };
			Assert::ExpectException<std::runtime_error>(Func3);

			auto Func4 = [&] {clone->SetSharedData(sharedData); };
			Assert::ExpectException<std::runtime_error>(Func4);

			delete clone;
		}

		TEST_METHOD(AddAndRemove)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };

			coor.AddHelper(helper);

			std::string json = R"({
                 "int": 1
            })";

			coor.Parse(json);
			Assert::AreEqual(sharedData.Data[0], 1);

			coor.RemoveHelper(helper);
			coor.Parse(json);
			Assert::IsTrue(sharedData.Data.IsEmpty());
		}

		TEST_METHOD(SetData)
		{
			JsonIntegerParseHelper helper;
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator coor{ sharedData };
			coor.AddHelper(helper);

			std::string json = R"({
                 "int": 1
            })";

			coor.Parse(json);
			sharedData.Data[0];
			Assert::AreSame(sharedData.Data, coor.GetSharedData().As<JsonIntegerParseHelper::SharedData>()->Data);
			JsonIntegerParseHelper::SharedData sharedData2;
			coor.SetSharedData(sharedData2);
			coor.Parse(json);
			Assert::AreSame(sharedData2.Data, coor.GetSharedData().As<JsonIntegerParseHelper::SharedData>()->Data);
		}

		TEST_METHOD(MoveSemantics)
		{
			{
				JsonIntegerParseHelper helper;
				JsonIntegerParseHelper::SharedData sharedData;
				JsonParseCoordinator coor{ sharedData };
				coor.AddHelper(helper);

				std::string json = R"({
				"int": 1
				})";

				coor.Parse(json);

				JsonParseCoordinator movedCoor = std::move(coor);
				Assert::AreEqual(movedCoor.GetSharedData().As< JsonIntegerParseHelper::SharedData>()->Data[0], 1);
				movedCoor.Parse(json);
				Assert::AreEqual(movedCoor.GetSharedData().As< JsonIntegerParseHelper::SharedData>()->Data[0], 1);
			}

			{
				JsonIntegerParseHelper helper;
				JsonIntegerParseHelper::SharedData sharedData;
				JsonParseCoordinator coor{ sharedData };
				coor.AddHelper(helper);

				std::string json = R"({
				"int": 1
				})";

				coor.Parse(json);

				JsonParseCoordinator movedCoor{ sharedData };
				movedCoor = std::move(coor);
				Assert::AreEqual(movedCoor.GetSharedData().As< JsonIntegerParseHelper::SharedData>()->Data[0], 1);
				movedCoor.Parse(json);
				Assert::AreEqual(movedCoor.GetSharedData().As< JsonIntegerParseHelper::SharedData>()->Data[0], 1);
			}

			{
				JsonIntegerParseHelper helper;
				JsonIntegerParseHelper::SharedData sharedData;
				JsonParseCoordinator coor{ sharedData };
				coor.AddHelper(helper);

				std::string json = R"({
				"int": 1
				})";

				coor.Parse(json);

				JsonParseCoordinator* clone = coor.Clone();
				JsonParseCoordinator movedCoor = std::move(*clone);
				movedCoor.Parse(json);
				Assert::AreEqual(movedCoor.GetSharedData().As< JsonIntegerParseHelper::SharedData>()->Data[0], 1);
				delete clone;
			}
		}


	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState JsonCoordinatorTest::_startMemState;
}