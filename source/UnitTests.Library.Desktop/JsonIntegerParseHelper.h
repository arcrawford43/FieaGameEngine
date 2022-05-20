#pragma once
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"

namespace UnitTests
{
	class JsonIntegerParseHelper final : public FieaGameEngine::IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonIntegerParseHelper, FieaGameEngine::IJsonParseHelper)

	public:
		class SharedData final : public FieaGameEngine::JsonParseCoordinator::SharedData
		{
			RTTI_DECLARATIONS(SharedData, FieaGameEngine::JsonParseCoordinator::SharedData)

		public:

			virtual void Initialize() override;
			virtual gsl::owner<SharedData*> Create() const override;

			FieaGameEngine::Vector<std::int32_t> Data;

			bool InitializeCalled = false;
			std::size_t MaxDepth = 0;
		};

		virtual void Initialize() override;
		virtual gsl::owner<IJsonParseHelper*> Create() const override;
		virtual bool StartHandler(FieaGameEngine::JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) override;
		virtual void EndHandler(FieaGameEngine::JsonParseCoordinator::SharedData& data, const std::string& key, Json::Value& value, size_t arrayIndex) override;

		bool InitializeCalled = false;
		std::size_t StartHandlerCount = 0;
		std::size_t EndHandlerCount = 0;
	private:
		bool mParsingData = false;
	};
}

