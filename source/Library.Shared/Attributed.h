#pragma once
#include "RTTI.h"
#include "Scope.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		using IteratorPair = std::pair<typename Vector<typename Hashmap<std::string, Datum>::PairType*>::Iterator, typename Vector<typename Hashmap<std::string, Datum>::PairType*>::Iterator>;
		using ConstIteratorPair = std::pair<typename Vector<typename Hashmap<std::string, Datum>::PairType*>::ConstIterator, typename Vector<typename Hashmap<std::string, Datum>::PairType*>::ConstIterator>;

		/// <summary>
		/// Constructor for attributed that must be called in children using the childs type ID
		/// </summary>
		Attributed(std::size_t typeID);
		
		/// <summary>
		/// Destructor clears out all of heap allocated memory
		/// </summary>
		~Attributed() override = default;

		/// <summary>
		/// Copy Constructor for Attribute
		/// </summary>
		/// <param name="other">Attribute being copied</param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Copy Assignment for Attribute
		/// </summary>
		/// <param name="other">Attribute being copied</param>
		/// <returns></returns>
		Attributed& operator=(const Attributed& other);

		/// <summary>
		/// Move Constructor for Attribute
		/// </summary>
		/// <param name="other">Attribute being moved</param>
		Attributed(Attributed&& other);

		/// <summary>
		/// Move Assignment for Attribute
		/// </summary>
		/// <param name="other">Attribute being moved</param>
		/// <returns></returns>
		Attributed& operator=(Attributed&& other);

		/// <summary>
		/// Populate function that adds that replicates the signature in the scope
		/// </summary>
		/// <param name="typeID"></param>
		void Populate(size_t typeID);

		/// <summary>
		/// Returns if this name is an attribute
		/// </summary>
		/// <param name="name">string to be found in scope</param>
		/// <returns></returns>
		inline bool IsAttribute(const std::string& name);

		/// <summary>
		/// Returns if this name is a prescribed attribute
		/// </summary>
		/// <param name="name">string to be found in scope</param>
		/// <returns></returns>
		bool IsPrescribedAttribute(const std::string& name);

		/// <summary>
		/// Returns if this name is an auxiliary attribute
		/// </summary>
		/// <param name="name">string to be found in scope</param>
		/// <returns></returns>
		inline bool IsAuxiliaryAttribute(const std::string& name);

		/// <summary>
		/// Adds an auxiliary attribute
		/// </summary>
		/// <exception cref="std::runtime_error">
		/// Cannot add an auxiliary attribute that is already a prescribed attribute
		/// </exception>
		/// <param name="name">name that is added</param>
		/// <returns></returns>
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/// <summary>
		/// Gives all attributes using Iterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline IteratorPair GetAttributes();

		/// <summary>
		/// Gives all attributes using ConstIterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline ConstIteratorPair GetAttributes() const;
		
		/// <summary>
		/// Gives all Prescribed attributes using Iterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline IteratorPair GetPrescribedAttributes();

		/// <summary>
		/// Gives all Prescribed attributes using ConstIterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline ConstIteratorPair GetPrescribedAttributes() const;
		
		/// <summary>
		/// Gives all Auxiliary attributes using Iterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline IteratorPair GetAuxiliaryAttributes();

		/// <summary>
		/// Gives all Auxiliary attributes using ConstIterators
		/// </summary>
		/// <returns>Pair with first being inclusive begin
		/// And end being exclive end</returns>
		inline ConstIteratorPair GetAuxiliaryAttributes() const;

	protected:
		Attributed* Clone() const override = 0;
	
	private:
		void Repopulate(size_t typeID);

	};
}

#include "Attributed.inl"

