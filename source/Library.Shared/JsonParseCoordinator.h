#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "gsl\gsl"

#pragma warning (push)
#pragma warning (disable:4635)
#pragma warning (disable:26812)
#include <json/json.h>
#pragma warning (pop)

namespace FieaGameEngine
{
	class IJsonParseHelper;
	class JsonParseCoordinator
	{
	public:
		/// <summary>
		/// Interface that is used to create SharedDatas in each of the helpers
		/// </summary>
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)
		public:

			/// <summary>
			/// A "virtual" constructor that creates a new of the actual type
			/// </summary>
			/// <returns></returns>
			inline virtual gsl::owner<SharedData*> Create() const = 0;

			/// <summary>
			/// Gets the Json Parse coordinator that this shared data belongs to
			/// </summary>
			/// <returns>Coordinator reference</returns>
			inline const JsonParseCoordinator& GetJsonParseCoordinator() const;

			/// <summary>
			/// Increments the depth counter
			/// </summary>
			inline void IncrementDepth();

			/// <summary>
			/// Decrements the depth counter
			/// </summary>
			inline void DecrementDepth();

			/// <summary>
			/// Returns the depth counter
			/// </summary>
			/// <returns>tthe depth counter</returns>
			inline size_t Depth() const;

			/// <summary>
			/// Function called before each parse by the coordinator
			/// </summary>
			virtual void Initialize() {};

			/// <summary>
			/// Defaulted virtual destructor
			/// </summary>
			virtual ~SharedData() = default;
			
		private:
			friend JsonParseCoordinator;
			inline void SetJsonParseCoordinator(const JsonParseCoordinator& jsonParseCoordinator);
			const JsonParseCoordinator* _JsonParseCoordinator{ nullptr };
			size_t _nestingDepth{ 0 };
		};

		/// <summary>
		/// Constructor that sets up shared data
		/// </summary>
		/// <param name="data">shared data passed in</param>
		JsonParseCoordinator(SharedData& data);

		/// <summary>
		/// Destructor that finalizes and deletes any heap allocated memory
		/// </summary>
		~JsonParseCoordinator();

		/// <summary>
		/// Move constructor. other should not be used after
		/// </summary>
		/// <param name="other">object being moved</param>
		JsonParseCoordinator(JsonParseCoordinator&& other);

		/// <summary>
		/// Move Assignment Operator. other should not be used after
		/// </summary>
		/// <param name="other">object being moved</param>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& other);

		/// <summary>
		/// Deleted Copy Constructor
		/// </summary>
		/// <param name="other"></param>
		JsonParseCoordinator(const JsonParseCoordinator& other) = delete;

		/// <summary>
		/// Deleted Copy Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		JsonParseCoordinator& operator=(const JsonParseCoordinator& other) = delete;

		/// <summary>
		/// Creates clone of the coordinator
		/// </summary>
		/// <returns>Heap allocated pointer to the coordinator</returns>
		gsl::owner<JsonParseCoordinator*> Clone() const;

		/// <summary>
		/// Adds a helper to the chain of responsibility
		/// </summary>
		/// <param name="helper">helper being added</param>
		void AddHelper(IJsonParseHelper& helper);

		/// <summary>
		/// Removes a helper to the chain of responsibility
		/// </summary>
		/// <param name="helper">helper being removed</param>
		void RemoveHelper(IJsonParseHelper& helper);

		/// <summary>
		/// Parses a string passed in by using the helpers
		/// </summary>
		/// <param name="jsonString"></param>
		void Parse(const std::string& jsonString);

		/// <summary>
		/// Parses a istream passed in by using the helpers
		/// </summary>
		/// <param name="jsonString"></param>
		void Parse(std::istream& jsonStream);

		/// <summary>
		/// Parses a file passed in by using the helpers
		/// </summary>
		/// <param name="jsonString"></param>
		void ParseFromFile(const std::string& jsonFile);

		/// <summary>
		/// Parses a json value
		/// </summary>
		/// <param name="value"></param>
		void ParseMembers(Json::Value& value);

		/// <summary>
		/// Returns a reference to shared data
		/// </summary>
		/// <returns></returns>
		inline SharedData& GetSharedData();

		/// <summary>
		/// Sets shared data
		/// </summary>
		/// <param name="data"></param>
		void SetSharedData(SharedData& data);

	private:
		JsonParseCoordinator(SharedData& data, bool isClone);
		void PrivateParse(const std::string& key, Json::Value& value, bool isArray);
		void Initialize();
		 
		bool _isClone;
		SharedData* _data;
		Vector<IJsonParseHelper*> _helpers;
	};
}

#include "JsonParseCoordinator.inl"

