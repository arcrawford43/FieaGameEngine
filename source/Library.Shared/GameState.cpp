#include "pch.h"
#include "GameState.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"

using namespace std::string_literals;
namespace FieaGameEngine
{
	void GameState::CreateActions()
	{
		for (size_t i = 0; i < ActionCreateAction::sQue.Size(); ++i)
		{
			auto [parent, child] = ActionCreateAction::sQue[i];
			parent->Adopt(*child, "actions"s);
		}
		ActionCreateAction::sQue.Clear();
	}

	void GameState::DestroyActions()
	{
		for (size_t i = 0; i < ActionDestroyAction::sQue.Size(); ++i)
		{
			delete ActionDestroyAction::sQue[i];
		}
		ActionDestroyAction::sQue.Clear();
	}
}