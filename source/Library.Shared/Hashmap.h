#pragma once
#include <stdexcept>
#include <cstddef>
#include <functional>
#include <assert.h>
#include <utility>
#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData>
	class Hashmap final
	{
	public:
		using PairType = std::pair<const TKey, TData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;
		using EqualityFunctor = std::function<bool(const TKey&, const TKey&)>;
		using HashFunctor = std::function<std::size_t(const TKey&)>;

		/// <summary>
		/// Default Destructor
		/// </summary>
		~Hashmap() = default;

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">
		/// Hashmap being copied
		/// </param>
		Hashmap(const Hashmap & other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Hashmap being copied</param>
		/// <returns>Hashmap being copied to</returns>
		Hashmap& operator=(const Hashmap & other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">Hashmap being moved</param>
		Hashmap(Hashmap && rhs) noexcept = default;

		/// <summary>
		/// Move Assignmenmt Operator
		/// </summary>
		/// <param name="rhs">Hashmap being moved</param>
		/// <returns>Hashmap being moved to</returns>
		Hashmap& operator=(Hashmap && rhs) noexcept = default;

		/// <summary>
		/// Constructor for Hashmap
		/// </summary>
		/// <param name="numBuckets">Number of buckets for Hashmap defaults to 11</param>
		/// <param name="hashFunctor">Hash Function to be used. Can be defaulted if using data that can be compared using a memory comparision</param>
		/// <param name="equalityFunctor">Equality function to be used can be defaulted if data supports std::equal_to</param>
		explicit Hashmap(std::size_t numBuckets = 11, HashFunctor hashFunctor = DefaultHash<TKey>(), EqualityFunctor equalityFunctor = std::equal_to<TKey>());

		explicit Hashmap(std::initializer_list<PairType> initList, std::size_t numBuckets = 11, HashFunctor hashFunctor = DefaultHash<TKey>(), EqualityFunctor equalityFunctor = std::equal_to<TKey>());
		class Iterator
		{
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = PairType;
			using reference = PairType&;
			using pointer = PairType*;
			using iterator_category = std::forward_iterator_tag;

			/// <summary>
			/// Default constructor
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Default copy constructor
			/// </summary>
			/// <param name="other"></param>
			Iterator(const Iterator& other) = default;

			/// <summary>
			/// Default assignment operator
			/// </summary>
			/// <param name="other">Iterator being copied</param>
			/// <returns>Iterator being assigned</returns>
			Iterator& operator=(const Iterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other Iterator being moved</param>
			Iterator(Iterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other Iterator being moved</param>
			/// <returns></returns>
			Iterator& operator=(Iterator&& other) = default;

			/// <summary>
			/// Default destructor
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// Compares if two Iterators are equivalent
			/// </summary>
			/// <param name="other">Iterator being compared to</param>
			/// <returns>true if equivalent and false if not</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Compares if two Iterators are not equivalent
			/// </summary>
			/// <param name="other">Iterator being compared to</param>
			/// <returns>true if not equivalent and false if equivalent/returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Preiterates Iterator to the next element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate Iterator with no container
			/// </exception>
			/// <returns>Returns Iterator</returns>
			Iterator& operator++();

			/// <summary>
			/// Postiterates Iterator to the next element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate Iterator with no container
			/// </exception>
			/// <returns>Returns copy of Iterator before iteration</returns>
			Iterator operator++(int);

			/// <summary>
			/// Dereferences iterator to get data
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot dereference Iterator with no container
			/// </exception>
			/// /// <exception cref="std::out_of_range">
			/// Cannot dereference Iterator out of range
			/// </exception>
			/// <returns>Returns data that Iterator refers to</returns>
			PairType& operator*() const;

			/// <summary>
			/// Dereferences iterator to get a pointer to data
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot dereference Iterator with no container
			/// </exception>
			/// /// <exception cref="std::out_of_range">
			/// Cannot dereference Iterator out of range
			/// </exception>
			/// <returns>Returns pointer to the data that Iterator refers to</returns>
			PairType* operator->() const;

			friend Hashmap;
		private:
			Iterator(Hashmap& owner, size_t index = 0, const typename ChainType::Iterator& chainIterator = ChainType::Iterator::Iterator());
			std::size_t _index{ 0 };
			Hashmap* _owner{ nullptr };
			typename ChainType::Iterator _chainIterator;
		};

		class ConstIterator
		{
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = PairType;
			using reference = PairType&;
			using pointer = PairType*;
			using iterator_category = std::forward_iterator_tag;

			/// <summary>
			/// Default constructor
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Default copy constructor
			/// </summary>
			/// <param name="other"></param>
			ConstIterator(const ConstIterator& other) = default;

			/// <summary>
			/// Default assignment operator
			/// </summary>
			/// <param name="other">ConstIterator being copied</param>
			/// <returns>ConstIterator being assigned</returns>
			ConstIterator& operator=(const ConstIterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other ConstIterator being moved</param>
			ConstIterator(ConstIterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other ConstIterator being moved</param>
			/// <returns></returns>
			ConstIterator& operator=(ConstIterator&& other) = default;

			/// <summary>
			/// Default destructor
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// Compares if two Iterators are equivalent
			/// </summary>
			/// <param name="other">ConstIterator being compared to</param>
			/// <returns>true if equivalent and false if not</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Compares if two Iterators are not equivalent
			/// </summary>
			/// <param name="other">ConstIterator being compared to</param>
			/// <returns>true if not equivalent and false if equivalent/returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Preiterates ConstIterator to the next element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate ConstIterator with no container
			/// </exception>
			/// <returns>Returns ConstIterator</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postiterates ConstIterator to the next element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate ConstIterator with no container
			/// </exception>
			/// <returns>Returns copy of ConstIterator before iteration</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Dereferences ConstIterator to get data
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot dereference ConstIterator with no container
			/// </exception>
			/// /// <exception cref="std::out_of_range">
			/// Cannot dereference ConstIterator out of range
			/// </exception>
			/// <returns>Returns data that ConstIterator refers to</returns>
			const PairType& operator*() const;

			/// <summary>
			/// Dereferences ConstIterator to get a pointer to data
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot dereference ConstIterator with no container
			/// </exception>
			/// /// <exception cref="std::out_of_range">
			/// Cannot dereference ConstIterator out of range
			/// </exception>
			/// <returns>Returns pointer to the data that ConstIterator refers to</returns>
			const PairType* operator->() const;

			/// <summary>
			/// Constructs a ConstIterator that refers to same Hashmap and element as original Iterator
			/// </summary>
			/// <param name="it">Iterator being used to construct ConstIterator</param>
			ConstIterator(const Iterator & it);

			friend Hashmap;
		private:
			ConstIterator(const Hashmap& owner, size_t index = 0, const typename ChainType::ConstIterator& chainIterator = ChainType::ConstIterator::ConstIterator());
			std::size_t _index{ 0 };
			const Hashmap* _owner{ nullptr };
			typename ChainType::ConstIterator _chainIterator;
		};
		
		/// <summary>
		/// Returns Iterator that refers to the beginning of Hashmap
		/// </summary>
		/// <returns>Iterator that refers to beginning of List</returns>
		Iterator begin();

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of Hashmap
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of Hashmap
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns Iterator that refers to one element after the last element of Hashmap
		/// </summary>
		/// <returns>Iterator that refers to one element after the last element of Hashmap</returns>
		Iterator end();

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of Hashmap
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of Hashmap</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of Hashmap
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of Hashmap</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Returns an Iterator to the corresponding key
		/// Returns end() if not found
		/// </summary>
		/// <param name="key">key to be found</param>
		/// <returns>Iterator pointint to key</returns>
		Iterator Find(const TKey& key);

		/// <summary>
		/// Returns a ConstIterator to the corresponding key
		/// Returns cend() if not found
		/// </summary>
		/// <param name="key">key to be found</param>
		/// <returns>ConstIterator pointing to key</returns>
		ConstIterator Find(const TKey& key) const;

		/// <summary>
		/// Inserts a key value pair into the Hashmap
		/// </summary>
		/// <param name = "pair">pair to be inserted </param>
		/// <returns> Iterator pointing to key location and bool indicating whether pair was inserted</returns>
		std::pair<Iterator, bool> Insert(const PairType& pair);

		/// <summary>
		/// Inserts a key value pair into the Hashmap
		/// </summary>
		/// <param name = "pair">pair to be inserted </param>
		/// <returns> Iterator pointing to key location and bool indicating whether pair was inserted</returns>
		std::pair<Iterator, bool> Insert(PairType&& pair);

		/// <summary>
		/// Returns a reference to the key provided. 
		/// Adds a default constructed TData if one is not present 
		/// TData must have a default constructor to use this operator
		/// </summary>
		/// <param name="key">key to return</param>
		/// <returns>Returns a reference to the data that the key points to</returns>
		TData& operator[](const TKey& key);

		/// <summary>
		/// Removes a pair from the Hashmap based on the key passed in
		/// Does nothing if key is not in Hashmap
		/// </summary>
		/// <param name="key">key to remove</param>
		/// <returns>Returns a bool to inform user if key was successfully removed</returns>
		bool Remove(const TKey&);

		/// <summary>
		/// Returns the amount of elements in the Hashmap
		/// </summary>
		/// <returns>The amount of elements in the Hashmap</returns>
		std::size_t Size() const;

		/// <summary>
		/// Informs user if key is in map
		/// </summary>
		/// <param name="key">key to check</param>
		/// <returns>Returns a bool to inform user if key is in Hashmap</returns>
		bool ContainsKey(const TKey&) const;

		/// <summary>
		/// Informs user if key is in map
		/// </summary>
		/// <param name="key">key to check</param>
		/// <param name="outData">output parameter for a data reference</param>
		/// <returns>Returns a bool to inform user if key is in Hashmap</returns>
		bool ContainsKey(const TKey&, TData& outData);

		/// <summary>
		/// Returns a reference to the key provided.
		/// </summary>
		/// <exception cref="runtime_error">Cannot find the key in the Hashmap</exception>
		/// <param name="key">key to return</param>
		/// <returns>Returns a reference to the data that the key points to</returns>
		TData& At(const TKey& key);

		/// <summary>
		/// Returns a const reference to the key provided.
		/// </summary>
		/// <exception cref="runtime_error">Cannot find the key in the Hashmap</exception>
		/// <param name="key">key to return</param>
		/// <returns>Returns a const reference to the data that the key points to</returns>
		const TData& At(const TKey& key) const;

		/// <summary>
		/// Returns the amount of items in the list divided by the number of buckets
		/// </summary>
		float LoadFactor() const;

		/// <summary>
		/// Cleans out all of the buckets
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the percentage of buckets that have at least one item in them
		/// </summary>
		float Capacity() const;

		/// <summary>
		/// Rehashes the map with a new number of buckets and a new hashFunctor
		/// </summary>
		/// <param name="newNumBuckets">The new amount of buckets after Rehash</param>
		/// <param name="newHashFunctor">The new hash functor if one is provided</param>
		void Rehash(std::size_t newNumBuckets, HashFunctor newHashFunctor);

		/// <summary>
		/// Rehashes the map with a new number of buckets
		/// </summary>
		/// <param name="newNumBuckets">The new amount of buckets after Rehash</param>
		void Rehash(std::size_t newNumBuckets);

		size_t NumberBuckets() const;

		
	private:
		std::size_t Hash(const TKey& key) const;
		std::pair<Iterator, bool> Find(const TKey& key, std::size_t index);
		std::pair<ConstIterator, bool> Find(const TKey& key, std::size_t index) const;

		BucketType _buckets;
		HashFunctor _hashFunctor;
		EqualityFunctor _equalityFunctor;
		std::size_t _size;
		std::size_t _emptyBuckets;
	};
}
#include "Hashmap.inl"