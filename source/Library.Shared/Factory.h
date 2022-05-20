#pragma once
#include <stdexcept>
#include <assert.h>
#include <gsl\gsl>
#include "Hashmap.h"

namespace FieaGameEngine
{
	/// <summary>
	/// A templated class that is used to dynamically create classes that have a factory registered
	/// </summary>
	template <typename T>
	class Factory
	{
	public:
		/// <summary>
		/// Function that finds the factory that is registered
		/// </summary>
		/// <param name="ClassName">string that is the name of the class</param>
		/// <returns>The Factory that creates this class type</returns>
		static const Factory* Find(const std::string& ClassName);

		/// <summary>
		/// Creates a the type that the string represents
		/// </summary>
		/// <param name="ClassName">Name of the type to be created</param>
		/// <returns></returns>
		static gsl::owner<T*> Create(const std::string& ClassName);

		/// <summary>
		/// Pure Virtual Function to create
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<T*> Create() const = 0;

		/// <summary>
		/// Pure Virtual Function that returns the name of the class as a string
		/// </summary>
		/// <returns></returns>
		virtual const std::string& ClassName() const = 0;

		virtual ~Factory() = default;

	protected:
		static void Add(const Factory& ConcreteFactory);
		static void Remove(const Factory& ConcreteFactory);

	private:
		inline static Hashmap<const std::string, const Factory*> sFactoryMap;
	};
}

#define ConcreteFactory(ConcreteProductType, AbstractProductType)						  \
class ConcreteProductType ## Factory : public FieaGameEngine::Factory<AbstractProductType>\
{																						  \
public:																					  \
	ConcreteProductType ## Factory() :													  \
		_className(#ConcreteProductType)												  \
	{																					  \
		Add(*this);																		  \
	}																					  \
	~ConcreteProductType ## Factory()													  \
	{																					  \
		Remove(*this);																	  \
	}																					  \
	const std::string & ClassName() const override										  \
	{																					  \
		return _className;																  \
	}																					  \
	gsl::owner<ConcreteProductType*> Create() const override							  \
	{																					  \
		return new ConcreteProductType;													  \
	}																					  \
private:																				  \
	std::string _className;																  \
};

#include "Factory.inl"