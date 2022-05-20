#include "Datum.h"

namespace FieaGameEngine
{
	inline std::size_t Datum::Size() const
	{
		return _size;
	}

	inline DatumTypes Datum::Type() const
	{
		return _type;
	}

	inline std::size_t Datum::Capacity() const
	{
		return _capacity;
	}

	inline bool Datum::IsExternalStorage() const
	{
		return _isExternalStorage;
	}
}
