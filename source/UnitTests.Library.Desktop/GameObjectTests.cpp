#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>
#include "JsonTableParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Avatar.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(GameObjectTests)
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

		TEST_METHOD(Parse)
		{
			GameObject gameObject;
			JsonTableParseHelper::SharedData sharedData(&gameObject);
			JsonParseCoordinator coor(sharedData);
			JsonTableParseHelper helper;
			coor.AddHelper(helper);

			coor.ParseFromFile("Content/GameObjectTest.json"s);

			Assert::AreEqual(gameObject._name, "World"s);
			Assert::AreEqual(gameObject._transform._position, glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f });
			Assert::AreEqual(gameObject._transform._rotation, glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f });
			Assert::AreEqual(gameObject._transform._scale, glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f });

			Avatar* avatar = gameObject.Find("children"s)->GetTable()->As<Avatar>();
			Assert::IsNotNull(avatar);
			Assert::AreEqual(avatar->_name, "Austin"s);
			Assert::AreEqual(avatar->Health, 200);

			GameObject* GO = gameObject.Find("children"s)->GetTable(1)->As<GameObject>();
			Assert::IsNotNull(GO);
			Assert::AreEqual(GO->_name, "GameObjectInArray"s);
		}

		TEST_METHOD(Update)
		{
			GameObject gameObject;
			JsonTableParseHelper::SharedData sharedData(&gameObject);
			JsonParseCoordinator coor(sharedData);
			JsonTableParseHelper helper;
			coor.AddHelper(helper);

			coor.ParseFromFile("Content/GameObjectTest.json"s);

			Avatar* avatar = gameObject.Find("children"s)->GetTable()->As<Avatar>();
			Assert::IsNotNull(avatar);
			Assert::AreEqual(avatar->_name, "Austin"s);
			Assert::AreEqual(avatar->Health, 200);

			GameTime gameTime;
			gameObject.Update(gameTime);

			Assert::AreEqual(avatar->Health, 199);

		}

		TEST_METHOD(OtherJunk)
		{
			GameObject gameObject;
			JsonTableParseHelper::SharedData sharedData(&gameObject);
			JsonParseCoordinator coor(sharedData);
			JsonTableParseHelper helper;
			coor.AddHelper(helper);

			coor.ParseFromFile("Content/GameObjectTest.json"s);
			
			GameObject* gameObject2 = gameObject.Clone();

			Assert::AreEqual(gameObject2->_name, "World"s);
			Assert::AreEqual(gameObject2->_transform._position, glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f });
			Assert::AreEqual(gameObject2->_transform._rotation, glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f });
			Assert::AreEqual(gameObject2->_transform._scale, glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f });

			Avatar* avatar = gameObject2->Find("children"s)->GetTable()->As<Avatar>();
			Assert::IsNotNull(avatar);
			Assert::AreEqual(avatar->_name, "Austin"s);
			Assert::AreEqual(avatar->Health, 200);

			GameObject* GO = gameObject2->Find("children"s)->GetTable(1)->As<GameObject>();
			Assert::IsNotNull(GO);
			Assert::AreEqual(GO->_name, "GameObjectInArray"s);

			Assert::IsTrue(gameObject.Equals(gameObject2));

			GameTime gameTime;

			gameObject.Update(gameTime);
			AttributedFoo foo;
			Assert::IsFalse(gameObject.Equals(gameObject2));
			Assert::IsFalse(gameObject.Equals(&foo));

			Assert::AreEqual("GameObject: World"s, gameObject.ToString());

			delete gameObject2;
		}

	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState GameObjectTests::_startMemState;
}