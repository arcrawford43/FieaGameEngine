#pragma once
#include <string>
#include <Datum.h>
#include <Hashmap.h>
#include <cstddef>

namespace FieaGameEngine
{
	struct Signature final
	{
		std::string _name;
		DatumTypes _type;
		std::size_t _size;
		std::size_t _offset;
	};

	class TypeManager final
	{
	public:
		/// <summary>
		/// Returns a vector of signatures based off a TypeID
		/// </summary>
		/// <param name="typeID"></param>
		/// <returns></returns>
		static const Vector<Signature>& GetSignature(size_t typeID);

		/// <summary>
		/// Registers the type child type in the TypeManager
		/// Must have already registered parent type first 
		/// Or parent can be attributed
		/// </summary>
		/// <typeparam name="Tchild">Class being added to registry</typeparam>
		/// <typeparam name="Tparent">Parent of class being added to registry</typeparam>
		template <typename Tchild, typename Tparent>
		static void RegisterType();
	private:
		static Hashmap<std::size_t, Vector<Signature>> _registry;
	};
}

#include "TypeManager.inl"

