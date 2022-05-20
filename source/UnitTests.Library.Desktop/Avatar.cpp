#include "pch.h"
#include "Avatar.h"

using namespace FieaGameEngine;
using namespace std::string_literals;

namespace UnitTests
{
	RTTI_DEFINITIONS(Avatar)

	Avatar::Avatar() :
	GameObject(Avatar::TypeIdClass())
	{
	}

	void Avatar::Update(const GameTime& gameTime)
	{
		GameObject::Update(gameTime);
		Health += Step;
	}

	const Vector<Signature> Avatar::Signatures()
	{
		return Vector<Signature>
		{
			{ "Health", DatumTypes::Integer, 1, offsetof(Avatar, Health) },
			{ "Step", DatumTypes::Integer, 1, offsetof(Avatar, Step) }
		};
	}

	Avatar* Avatar::Clone() const
	{
		return new Avatar(*this);
	}

	bool Avatar::Equals(const RTTI* rhs) const
	{
		const Avatar* rhsAva = rhs->As<Avatar>();
		if (rhsAva == nullptr)
		{
			return false;
		}

		return Health == rhsAva->Health &&
			GameObject::Equals(rhs);
	}

	std::string Avatar::ToString() const
	{
		return "Avatar: "s + _name;
	}
}