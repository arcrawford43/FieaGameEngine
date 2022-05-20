#pragma once
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Scope.h"
#include "RTTI.h"
#include "SList.h"


namespace FieaGameEngine
{
	class JsonTableParseHelper : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTableParseHelper, IJsonParseHelper)

	private:
		struct Frame final
		{
			Scope* Scope;
			std::string Key;
		};
	public:

		class SharedData : public JsonParseCoordinator::SharedData
		{
			RTTI_DECLARATIONS(SharedData, JsonParseCoordinator::SharedData)

		public:
			/// <summary>
			/// Constructor that takes in the pointer for the root scope in shared data
			/// </summary>
			SharedData(Scope* rootScope);

			/// <summary>
			/// Initialize function that clears scope so that it is ready to be paresed
			/// </summary>
			virtual void Initialize() override;

			/// <summary>
			/// Create function that creates a new shared data
			/// </summary>
			virtual gsl::owner<SharedData*> Create() const override;

			/// <summary>
			/// Pass in the root scope
			/// </summary>
			void SetRootScope(Scope* rootScope);

			Scope* _rootScope{ nullptr };

		private:
			SharedData() = default;
			friend JsonTableParseHelper;
			SList<Frame> _stackFrame{};
		};

		/// <summary>
		/// Initialize function for the helper
		/// </summary>
		virtual void Initialize() override;

		/// <summary>
		/// Creates a new helper
		/// </summary>
		virtual gsl::owner<IJsonParseHelper*> Create() const override;

		/// <summary>
		/// Start handler that can handle scopes
		/// </summary>
		virtual bool StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) override;

		/// <summary>
		/// End Handler that handles scopes
		/// </summary>
		virtual void EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) override;

	private:
		bool _ParsingData{ false };
		inline static Hashmap<std::string, DatumTypes> _typeMap{
			std::make_pair("integer", DatumTypes::Integer),
			std::make_pair("float", DatumTypes::Float),
			std::make_pair("vector", DatumTypes::Vector),
			std::make_pair("matrix", DatumTypes::Matrix),
			std::make_pair("string", DatumTypes::String),
			std::make_pair("table", DatumTypes::Table)
		};
	};
}

