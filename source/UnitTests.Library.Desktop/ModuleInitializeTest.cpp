#include "pch.h"
#include "AttributedDerivedFoo.h"
#include "TypeManager.h"
#include <CppUnitTestAssert.h>
#include <CppUnitTest.h>
#include "Avatar.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionIncrement.h"
#include "ActionListForEach.h"
#include "Event.h"
#include "EventSupportStructs.h"

using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std::string_literals;

TEST_MODULE_INITIALIZE(Init)
{
	TypeManager::RegisterType<AttributedFoo, Attributed>();
	TypeManager::RegisterType<AttributedDerivedFoo, AttributedFoo>();
	TypeManager::RegisterType<GameObject, Attributed>();
	TypeManager::RegisterType<Avatar, GameObject>();
	TypeManager::RegisterType<Action, Attributed>();
	TypeManager::RegisterType<ActionList, Action>();
	TypeManager::RegisterType<ActionIncrement, Action>();
	TypeManager::RegisterType<ActionCreateAction, Action>();
	TypeManager::RegisterType<ActionDestroyAction, Action>();
	TypeManager::RegisterType<ActionListForEach, ActionList>();

	new AvatarFactory;
	new GameObjectFactory;
	new ScopeFactory;
	new ActionListFactory;
	new ActionListForEachFactory;
	new ActionCreateActionFactory;
	new ActionDestroyActionFactory;
	new ActionIncrementFactory;

	ActionCreateAction::sQue.Reserve(100);
	ActionDestroyAction::sQue.Reserve(100);
}

TEST_MODULE_CLEANUP(clean)
{
	delete Factory<Scope>::Find("Avatar"s);
	delete Factory<Scope>::Find("GameObject"s);
	delete Factory<Scope>::Find("Scope"s);
	delete Factory<Scope>::Find("ActionList"s);
	delete Factory<Scope>::Find("ActionListForEach"s);
	delete Factory<Scope>::Find("ActionCreateAction"s);
	delete Factory<Scope>::Find("ActionDestroyAction"s);
	delete Factory<Scope>::Find("ActionIncrement"s);
}