#include "pch.h"
#include "JsonParseCoordinator.h"
#include "IJsonParseHelper.h"
#include <stdexcept>
#include <istream>
#include <fstream>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonParseCoordinator::SharedData)
	JsonParseCoordinator::JsonParseCoordinator(SharedData& data) :
		_data(&data), _isClone(false)
	{
		_data->SetJsonParseCoordinator(*this);
	}

	JsonParseCoordinator::JsonParseCoordinator(SharedData& data, bool isClone) :
		_data(&data), _isClone(isClone)
	{
		_data->SetJsonParseCoordinator(*this);
	}

	JsonParseCoordinator::~JsonParseCoordinator()
	{
		if (_isClone)
		{
			for (size_t i = 0; i < _helpers.Size(); ++i)
			{
				delete _helpers[i];
			}
			delete _data;
		}
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& other) :
		_isClone(other._isClone), _data(other._data), _helpers(std::move(other._helpers))
	{
		_data->SetJsonParseCoordinator(*this);
		if (_isClone)
		{
			other._data = nullptr;
		}
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& other)
	{
		if (_isClone)
		{
			throw std::runtime_error("Cannot move into a Clone");
		}

		_isClone = other._isClone;
		_data = other._data;
		_helpers = std::move(other._helpers);
		return *this;
	}

	gsl::owner<JsonParseCoordinator*> JsonParseCoordinator::Clone() const
	{
		gsl::owner<JsonParseCoordinator*> clone = new JsonParseCoordinator(*(_data->Create()), true);

		clone->_helpers.Reserve(_helpers.Size());

		for (size_t i = 0; i < _helpers.Size(); ++i)
		{
			clone->_helpers.PushBack(_helpers[i]->Create());
		}

		return clone;
	}

	void JsonParseCoordinator::Initialize()
	{
		for (size_t i = 0; i < _helpers.Size(); ++i)
		{
			_helpers[i]->Initialize();
		}
		_data->Initialize();
	}

	void JsonParseCoordinator::AddHelper(IJsonParseHelper& helper)
	{
		if (_isClone)
		{
			throw std::runtime_error("Cannot add a helper to a Clone");
		}

		_helpers.PushBack(&helper);
	}

	void JsonParseCoordinator::RemoveHelper(IJsonParseHelper& helper)
	{
		if (_isClone)
		{
			throw std::runtime_error("Cannot add a helper to a Clone");
		}

		_helpers.Remove(&helper);
	}

	void JsonParseCoordinator::Parse(const std::string& jsonString)
	{
		std::istringstream jsonStream(jsonString);
		Parse(jsonStream);
	}

	void JsonParseCoordinator::ParseFromFile(const std::string& jsonFile)
	{
		std::ifstream jsonStream(jsonFile, std::ifstream::binary);
		Parse(jsonStream);
	}

	void JsonParseCoordinator::Parse(std::istream& jsonStream)
	{
		Json::Value value;
		jsonStream >> value;
		Initialize();
		ParseMembers(value);
	}

	void JsonParseCoordinator::ParseMembers(Json::Value& value)
	{
		_data->IncrementDepth();
		auto names = value.getMemberNames();

		for (auto key : names)
		{
			PrivateParse(key, value[key], value[key].isArray());
		}

		_data->DecrementDepth();
	}
	
	void JsonParseCoordinator::PrivateParse(const std::string& key, Json::Value& value, bool isArray)
	{
		if (isArray)
		{
			if (value[0].isObject())
			{
				for (std::uint32_t i = 0; i < value.size(); ++i)
				{
					for (size_t j = 0; j < _helpers.Size(); ++j)
					{
						if (_helpers[j]->StartHandler(*_data, key, value[i], i))
						{
							ParseMembers(value[i]);
							_helpers[j]->EndHandler(*_data, key, value[i], i);
							break;
						}
					}
				}
			}

			else
			{
				for (std::uint32_t i = 0; i < value.size(); ++i)
				{
					for (size_t j = 0; j < _helpers.Size(); ++j)
					{
						if (_helpers[j]->StartHandler(*_data, key, value[i], i))
						{
							_helpers[j]->EndHandler(*_data, key, value[i], i);
							break;
						}
					}
				}
			}
		}

		else
		{
			if (value.isObject())
			{
				for (size_t i = 0; i < _helpers.Size(); ++i)
				{
					if (_helpers[i]->StartHandler(*_data, key, value, 0))
					{
						ParseMembers(value);
						_helpers[i]->EndHandler(*_data, key, value, 0);
						break;
					}
				}
			}

			else
			{
				for (size_t i = 0; i < _helpers.Size(); ++i)
				{
					if (_helpers[i]->StartHandler(*_data, key, value, 0))
					{
						_helpers[i]->EndHandler(*_data, key, value, 0);
						break;
					}
				}
			}
		}
	}

	void JsonParseCoordinator::SetSharedData(SharedData& data)
	{
		if (_isClone)
		{
			throw std::runtime_error("Cannot set Shared Data on a Clone");
		}

		_data = &data;
	}
}