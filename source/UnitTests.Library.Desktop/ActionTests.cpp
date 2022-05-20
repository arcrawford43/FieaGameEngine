#include "pch.h"
#include "Foo.h"
#include "ToStringSpecialization.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include <crtdbg.h>
#include "JsonTableParseHelper.h"
#include "JsonParseCoordinator.h"
#include "ActionCreateAction.h"
#include "Avatar.h"
#include "GameState.h"
#include "ActionListForEach.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace UnitTestsLibraryDesktop
{
	TEST_CLASS(ActionTests)
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

		TEST_METHOD(ActionCreateActionTest)
        {
        std::string filename = "Content/ActionCreateActionTest.json";

        GameObject gameObject;
        JsonTableParseHelper::SharedData sharedData(&gameObject);

        JsonTableParseHelper scopeParser;

        JsonParseCoordinator parseManager(sharedData);
        parseManager.AddHelper(scopeParser);



        GameTime gameTime;
        parseManager.ParseFromFile(filename);

        Datum* children = sharedData._rootScope->Find("children");
        Assert::IsNotNull(children);
        Avatar* testHero = children->GetTable()->As<Avatar>();
        Assert::IsNotNull(testHero);


        Datum* health = testHero->Find("Health");
        Assert::IsNotNull(health);
        Assert::AreEqual(health->GetInteger(), 100);

        GameObject* level = sharedData._rootScope->As<GameObject>();
        Assert::IsNotNull(level);

        Datum* actionsDatum = testHero->Find("actions");
        Assert::IsNotNull(actionsDatum);
        Assert::AreEqual(size_t(1), actionsDatum->Size());

        level->Update(gameTime);
        GameState::CreateActions();

        Assert::AreEqual(size_t(2), actionsDatum->Size());

        Datum* targetDatum = actionsDatum->GetTable(1)->Find("target");
        targetDatum->Set("Health");

        Assert::AreEqual(health->GetInteger(), 99);

        level->Update(gameTime);
        GameState::CreateActions();

        Assert::AreEqual(health->GetInteger(), 99);
		}

		TEST_METHOD(ActionDestroyActionTest)
		{
			const std::string filename = R"(Content\ActionDestroyActionTest.json)";

			GameObject gameObject;
			JsonTableParseHelper::SharedData sharedData(&gameObject);

			JsonTableParseHelper scopeParser;

			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);


			GameTime gameTime;

			parseManager.ParseFromFile(filename);

			Datum* children = sharedData._rootScope->Find("children");
			Assert::IsNotNull(children);
			Avatar* testAvatar = children->GetTable()->As<Avatar>();
			Assert::IsNotNull(testAvatar);


			Datum* health = testAvatar->Find("Health");
			Assert::IsNotNull(health);
			Assert::AreEqual(health->GetInteger(), 100);

			GameObject* level = sharedData._rootScope->As<GameObject>();
			Assert::IsNotNull(level);

			Datum* actionsDatum = testAvatar->Find("actions");
			Assert::IsNotNull(actionsDatum);
			Assert::AreEqual(size_t(2), actionsDatum->Size());

			level->Update(gameTime);
			GameState::CreateActions();
			GameState::DestroyActions();

			Assert::AreEqual(size_t(1), actionsDatum->Size());
			Assert::AreEqual(health->GetInteger(), 102);

			level->Update(gameTime);
			GameState::CreateActions();
			GameState::DestroyActions();

			Assert::AreEqual(health->GetInteger(), 102);
		}

		TEST_METHOD(ActionForEachTest)
		{
			const std::string filename = R"(Content\ActionForEach.json)";

			GameObject gameObject;
			JsonTableParseHelper::SharedData sharedData( &gameObject);

			JsonTableParseHelper scopeParser;

			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);

			GameTime gameTime;

			parseManager.ParseFromFile(filename);

			Datum* children = sharedData._rootScope->Find("children");
			Assert::IsNotNull(children);
			Avatar* ava = children->GetTable()->As<Avatar>();
			Assert::IsNotNull(ava);


			Datum* health = ava->Find("Health");
			Assert::IsNotNull(health);
			Assert::AreEqual(health->GetInteger(), 100);

			GameObject* world = sharedData._rootScope->As<GameObject>();
			Assert::IsNotNull(world);

			world->Update(gameTime);
			Assert::AreEqual(health->GetInteger(), 102);

			world->Update(gameTime);
			Assert::AreEqual(health->GetInteger(), 104);

			world->Update(gameTime);
			Assert::AreEqual(health->GetInteger(), 106);
		}
	private:
		static _CrtMemState _startMemState;
	};

	_CrtMemState ActionTests::_startMemState;
}