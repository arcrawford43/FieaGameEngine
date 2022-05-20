#include "JsonParseCoordinator.h"
#include "assert.h"

namespace FieaGameEngine
{
	inline const JsonParseCoordinator& JsonParseCoordinator::SharedData::GetJsonParseCoordinator() const
	{
		return *_JsonParseCoordinator;
	}

	inline void JsonParseCoordinator::SharedData::IncrementDepth()
	{
		++_nestingDepth;
	}

	inline void JsonParseCoordinator::SharedData::DecrementDepth()
	{
		assert(_nestingDepth != 0);
		--_nestingDepth;
	}
	
	inline size_t JsonParseCoordinator::SharedData::Depth() const
	{
		return _nestingDepth;
	}

	inline void JsonParseCoordinator::SharedData::SetJsonParseCoordinator(const JsonParseCoordinator& jsonParseCoordinator)
	{
		_JsonParseCoordinator = &jsonParseCoordinator;
	}

	inline JsonParseCoordinator::SharedData& JsonParseCoordinator::GetSharedData()
	{
		return *_data;
	}

}