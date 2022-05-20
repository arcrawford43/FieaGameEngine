#pragma once
#include "RTTI.h"
#include "Datum.h"
#include "Hashmap.h"
#include "Vector.h"
#include <cstddef>
#include "Factory.h"

namespace FieaGameEngine
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)
	public:
		/// <summary>
		/// Constructor for scope
		/// </summary>
		/// <param name="capacity">initial capacity for the scope</param>
		explicit Scope(std::size_t capacity = 11);

		/// <summary>
		/// Destructor for scope. Destroys all child scopes and informs parent of deletion
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="rhs">Scope being copied</param>
		Scope(const Scope& rhs);

		/// <summary>
		/// Copy assignment operator
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		Scope& operator=(const Scope& rhs);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">Scope being moved</param>
		Scope(Scope&& rhs);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		Scope& operator=(Scope&& rhs);

		/// <summary>
		/// Comparison operator ==
		/// </summary>
		/// <param name="rhs">Scope being compared </param>
		/// <returns></returns>
		bool operator==(const Scope& rhs) const;

		/// <summary>
		/// Comparison operator ==
		/// </summary>
		/// <param name="rhs">Scope being compared </param>
		/// <returns></returns>
		bool operator!=(const Scope& rhs) const;

		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Finds the key if it exists in local scope
		/// </summary>
		/// <param name="key"> to be found</param>
		/// <returns>Datum pointer nullptr if not found</returns>
		Datum* Find(const std::string& key);

		/// <summary>
		/// Finds the key if it exists in local scope
		/// </summary>
		/// <param name="key"> to be found</param>
		/// <returns>Datum pointer nullptr if not found</returns>
		const Datum* Find(const std::string& key) const;

		/// <summary>
		/// Finds the key if it exists in local scope or any ancestral scope
		/// </summary>
		/// <param name="key">to be found</param>
		/// <param name="scope"> output parameter that is the scope that the key was found in</param>
		/// <returns></returns>
		Datum* Search(const std::string& key, Scope*& scope);

		/// <summary>
		/// Finds the key if it exists in local scope or any ancestral scope
		/// </summary>
		/// <param name="key">to be found</param>
		/// <param name="scope"> output parameter that is the scope that the key was found in</param>
		/// <returns></returns>
		const Datum* Search(const std::string& key, const Scope*& scope) const;

		/// <summary>
		/// Finds the key if it exists in local scope or any ancestral scope
		/// </summary>
		/// <param name="key">to be found</param>
		/// <returns></returns>
		Datum* Search(const std::string& key);

		/// <summary>
		/// Finds the key if it exists in local scope or any ancestral scope
		/// </summary>
		/// <param name="key">to be found</param>
		/// <returns></returns>
		const Datum* Search(const std::string& key) const;

		/// <summary>
		/// Return the datum associated with the key default create one if one doesn't exist
		/// </summary>
		/// <param name="key"> to be added/found</param>
		/// <returns>reference to the found or newly added Datum</returns>
		Datum& Append(const std::string& key);

		/// <summary>
		/// Adds a scope at the key addresss. Creates a Datum if one does not exist
		/// </summary>
		/// <param name="key">key to be added</param>
		/// <returns>Scope that was added</returns>
		Scope& AppendScope(const std::string& key);

		/// <summary>
		/// Scope adopts a new child and adds it to its local scope
		/// </summary>
		/// <param name="child"></param>
		/// <param name="key"></param>
		void Adopt(Scope& child, const std::string key);

		/// <summary>
		/// Returns a pointer to the parent of the scope
		/// </summary>
		/// <returns>the parent pointer</returns>
		inline Scope* GetParent() const;

		/// <summary>
		/// Return the datum associated with the key default create one if one doesn't exist
		/// </summary>
		/// <param name="key"> to be added/found</param>
		/// <returns>reference to the found or newly added Datum</returns>
		inline Datum& operator[](const std::string& key);

		/// <summary>
		/// Returns the datum at that index based on order of insertion
		/// </summary>
		/// <param name="index">index to be retrieved</param>
		/// <returns>Datum that was inserted at that index order</returns>
		inline Datum& operator[](std::size_t index);

		/// <summary>
		/// Returns the const datum at that index based on order of insertion
		/// </summary>
		/// <param name="index">index to be retrieved</param>
		/// <returns>Datum that was inserted at that index order</returns>
		inline const Datum& operator[](std::size_t index) const;

		/// <summary>
		/// Finds the Scope contained 
		/// </summary>
		/// <param name="child"></param>
		/// <returns></returns>
		std::pair<Datum*, std::size_t> FindContainedScope(const Scope* child);

		/// <summary>
		/// Clears the Scope
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns whether scope is an ancestor of the Scope this is called on
		/// </summary>
		/// <param name="scope"></param>
		/// <returns></returns>
		bool IsAncestorOf(const Scope& scope) const;

		/// <summary>
		/// Returns whether scope is a descendant of the Scope this is called on
		/// </summary>
		/// <param name="scope"></param>
		/// <returns></returns>
		bool IsDescendantOf(const Scope& scope) const;

		friend Attributed;
	protected:
		void Orphan();
		virtual Scope* Clone() const;
		Scope* _parent{ nullptr };

	private:
		Vector<typename Hashmap<std::string, Datum>::PairType*> _vector;
		Hashmap<std::string, Datum> _map;
		bool _isExternal{ false };
	};

	ConcreteFactory(Scope, Scope)
}

#include "Scope.inl"

