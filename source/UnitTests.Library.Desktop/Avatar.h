#pragma once
#include "GameObject.h"
#include "GameTime.h"

namespace UnitTests
{
	class Avatar : public FieaGameEngine::GameObject
	{
		RTTI_DECLARATIONS(Avatar, GameObject)
		
	public:
		Avatar();

		~Avatar() = default;

		void Update(const FieaGameEngine::GameTime& gameTime) override;

		static const FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();

		Avatar* Clone() const override;

		bool Equals(const RTTI * rhs) const override;

		std::string ToString() const override;

		std::int32_t Health{ 100 };

		std::int32_t Step{ -1 };
	};

	ConcreteFactory(Avatar, FieaGameEngine::Scope)
}

