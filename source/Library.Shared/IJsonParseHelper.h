#pragma once
#include "JsonParseCoordinator.h"
#include "RTTI.h"
#include "string.h"
#include "gsl/gsl"
#include "json\json.h"

namespace FieaGameEngine
{
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI)
		
	public:
		/// <summary>
		/// Function that is called before each parse by the coordinator. No base implementation
		/// </summary>
		virtual void Initialize() {};

		/// <summary>
		/// Function that is called on each helper on each Json key value pair
		/// </summary>
		/// <param name="data">shared data from the coordinator</param>
		/// <param name="key">string key from json</param>
		/// <param name="value">json value from json</param>
		/// <param name="isArray">bool saying whether json is array</param>
		/// <returns>return true if this handler knows how to handle this request</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) = 0;

		/// <summary>
		/// Handler that is called only if StartHandler returns true for this helper
		/// </summary>
		/// <param name="data">shared data from the coordinator</param>
		/// <param name="key">string key from json</param>
		/// <param name="value">json value from json</param>
		/// <param name="isArray">bool saying whether json is array</param>
		virtual void EndHandler(JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) = 0;

		/// <summary>
		/// A "virtual" constructor that creates a new of the actual type
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<IJsonParseHelper*> Create() const = 0;

		/// <summary>
		/// Virtual defaulted destructor
		/// </summary>
		virtual ~IJsonParseHelper() = default;
	};
}

