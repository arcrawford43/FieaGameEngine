#pragma once
#include "EventQueue.h"

namespace FieaGameEngine
{
	class GameState
	{
	public:
		static void DestroyActions();
		static void CreateActions();
		inline static EventQueue QueueEvents;
	};
}

