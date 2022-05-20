#include "Factory.h"

namespace FieaGameEngine
{
	template <typename T>
	const Factory<T>* Factory<T>::Find(const std::string& ClassName)
	{
		const Factory* result = nullptr;
		sFactoryMap.ContainsKey(ClassName, result);
		return result;
	}

	template <typename T>
	gsl::owner<T*> Factory<T>::Create(const std::string& ClassName)
	{
		const Factory<T>* factory = Find(ClassName);
		if (factory == nullptr)
		{
			return nullptr;
		}
		return factory->Create();
	}

	template <typename T>
	void Factory<T>::Add(const Factory& ConcreteFactory)
	{
		auto [iterator, didInsert] = sFactoryMap.Insert(std::make_pair(ConcreteFactory.ClassName(), &ConcreteFactory));
		
		if (!didInsert)
		{
			throw std::runtime_error("Only one Factory of this type can exist");
		}
	}

	template <typename T>
	void Factory<T>::Remove(const Factory& ConcreteFactory)
	{
		sFactoryMap.Remove(ConcreteFactory.ClassName());
	}
}
