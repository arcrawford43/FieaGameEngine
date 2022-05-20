#pragma once
#include <cstddef>
#include <string>

namespace FieaGameEngine
{
	inline std::size_t AdditiveHash(const std::uint8_t* data, std::size_t size)
	{
		std::size_t hash = 29;

		for (std::size_t i = 0; i < size; ++i)
		{
			hash += data[i];
		}
		return hash;
	}

	template <typename TKey>
	struct DefaultHash final
	{
		std::size_t operator()(const TKey& key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(&key), sizeof(TKey));
		}
	};

	template <>
	struct DefaultHash<std::string> final
	{
		std::size_t operator()(const std::string& key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key.c_str()), key.size());
		}
	};

	template <>
	struct DefaultHash<const std::string> final
	{
		std::size_t operator()(const std::string& key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key.c_str()), key.size());
		}
	};

	template <>
	struct DefaultHash<char*> final
	{
		std::size_t operator()(const char* key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key), strlen(key));
		}
	};

	template <>
	struct DefaultHash<const char*> final
	{
		std::size_t operator()(const char* key)
		{
			return AdditiveHash(reinterpret_cast<const std::uint8_t*>(key), strlen(key));
		}
	};
}