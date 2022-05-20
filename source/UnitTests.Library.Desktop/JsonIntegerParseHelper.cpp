#include "pch.h"
#include "JsonIntegerParseHelper.h"
#include <stdexcept>
#include <cassert>

using namespace FieaGameEngine;
using namespace std;
namespace UnitTests
{
	RTTI_DEFINITIONS(JsonIntegerParseHelper)
	RTTI_DEFINITIONS(JsonIntegerParseHelper::SharedData)
	gsl::owner<IJsonParseHelper*> JsonIntegerParseHelper::Create() const
	{
		return new JsonIntegerParseHelper();
	}

	void JsonIntegerParseHelper::Initialize()
	{
		IJsonParseHelper::Initialize();
		InitializeCalled = true;
		StartHandlerCount = 0;
		EndHandlerCount = 0;
	}

	gsl::owner<JsonIntegerParseHelper::SharedData*> JsonIntegerParseHelper::SharedData::Create() const
	{
		return new JsonIntegerParseHelper::SharedData();
	}

	void JsonIntegerParseHelper::SharedData::Initialize()
	{
		MaxDepth = 0;
		Data.Clear();
		InitializeCalled = true;
	}

	bool JsonIntegerParseHelper::StartHandler(JsonParseCoordinator::SharedData& data, const string& key, Json::Value& value, size_t arrayIndex)
	{
		arrayIndex;
		key;
		JsonIntegerParseHelper::SharedData* sharedData = data.As<JsonIntegerParseHelper::SharedData>();
		if (sharedData == nullptr || !value.isInt())
		{
			return false;
		}

		if (mParsingData)
		{
			throw std::runtime_error("Cannot start another element when already parsing an integer");
		}

		mParsingData = true;

		return true;
	}

	void JsonIntegerParseHelper::EndHandler(JsonParseCoordinator::SharedData& data, const string& key, Json::Value& value, size_t arrayIndex)
	{
		arrayIndex;
		key;
		JsonIntegerParseHelper::SharedData* sharedData = data.As<JsonIntegerParseHelper::SharedData>();

		assert(value.isInt() && sharedData != nullptr && mParsingData == true);

		sharedData->Data.PushBack(value.asInt());
		mParsingData = false;
	}
}
