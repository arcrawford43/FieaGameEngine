#include "pch.h"
#include "JsonTableParseHelper.h"
#include "Factory.h"

using namespace std;
namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper)
	RTTI_DEFINITIONS(JsonTableParseHelper::SharedData)

	JsonTableParseHelper::SharedData::SharedData(Scope* rootScope)
		:_rootScope(rootScope)
	{
	}

	void JsonTableParseHelper::SharedData::Initialize()
	{
		JsonParseCoordinator::SharedData::Initialize();
		_stackFrame.Clear();
	}

	gsl::owner<JsonTableParseHelper::SharedData*> JsonTableParseHelper::SharedData::Create() const
	{
		return new SharedData;
	}

	void JsonTableParseHelper::SharedData::SetRootScope(Scope* rootScope)
	{
		_rootScope = rootScope;
	}

	void JsonTableParseHelper::Initialize()
	{
		IJsonParseHelper::Initialize();
		_ParsingData = false;
	}

	gsl::owner<IJsonParseHelper*> JsonTableParseHelper::Create() const
	{
		return new JsonTableParseHelper;
	}

	bool JsonTableParseHelper::StartHandler(JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value,size_t arrayIndex)
	{
		if (arrayIndex > 0)
		{
			_ParsingData = !_ParsingData;
		}

		SharedData* sharedData = data.As<SharedData>();
		if (sharedData == nullptr || (!_ParsingData && (!value.isObject() || _typeMap.ContainsKey(key))) || (_ParsingData && !_typeMap.ContainsKey(key)))
		{
			return false;
		}

		if (_ParsingData)
		{
			DatumTypes type = _typeMap[key];
			Frame& frame = sharedData->_stackFrame.Back();

			switch (type)
			{
				case DatumTypes::Table:
				{
					if (value.isMember("class"))
					{
						Json::Value classType = value["class"];
						if (!classType.isString())
						{
							throw std::runtime_error("Key class needs to be of type string");
						}
						Scope* scope = Factory<Scope>::Create(classType.asString());
						std::string name = classType.asString();
						if (scope == nullptr)
						{
							throw std::runtime_error("This is not a valid name of a registerd derived scope in Factory<Scope>");
						}
						frame.Scope->Adopt(*scope, frame.Key);
						sharedData->_stackFrame.PushBack({ scope, ""s });
					}
					else
					{
						sharedData->_stackFrame.PushBack({ &frame.Scope->AppendScope(frame.Key), ""s });
					}
					break;
				}
				case DatumTypes::Integer:
				{
					if (frame.Scope->operator[](frame.Key).IsExternalStorage())
					{
						frame.Scope->operator[](frame.Key).Set(value.asInt(), arrayIndex);
					}
					else
					{
						frame.Scope->operator[](frame.Key).PushBack(value.asInt());
					}
					break;
				}
				case DatumTypes::Float:
				{
					if (frame.Scope->operator[](frame.Key).IsExternalStorage())
					{
						frame.Scope->operator[](frame.Key).Set(value.asFloat(), arrayIndex);
					}
					else
					{
						frame.Scope->operator[](frame.Key).PushBack(value.asFloat());
					}
					break;
				}
				default:
				{
					if (frame.Scope->operator[](frame.Key).IsExternalStorage())
					{
						frame.Scope->operator[](frame.Key).SetFromString(value.asString(), arrayIndex);
					}
					else
					{
						frame.Scope->operator[](frame.Key).SetType(type);
						frame.Scope->operator[](frame.Key).PushBackFromString(value.asString());
					}
					break;
				}
			}
		}

		else
		{
			Scope* parentScope;
			if (sharedData->_stackFrame.IsEmpty())
			{
				parentScope = sharedData->_rootScope;
			}
			else
			{
				parentScope = sharedData->_stackFrame.Back().Scope;
			}

			parentScope->Append(key);
			sharedData->_stackFrame.PushBack({ parentScope, key });
		}
		_ParsingData = !_ParsingData;
		return true;
	}
	
	void JsonTableParseHelper::EndHandler(JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex)
	{
		JsonTableParseHelper::SharedData* sharedData = data.As<JsonTableParseHelper::SharedData>();
		value;
		arrayIndex;
		assert(sharedData != nullptr);

		if (!_typeMap.ContainsKey(key) || _typeMap[key] == DatumTypes::Table)
		{
			sharedData->_stackFrame.PopBack();
		}
	}
}
