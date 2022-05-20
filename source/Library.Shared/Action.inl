#include "Action.h"

namespace FieaGameEngine
{
	inline const std::string& Action::Name() const
	{
		return _name;
	}

	inline void Action::SetName(std::string name)
	{
		_name = std::move(name);
	}
}
