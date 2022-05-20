#pragma once
#include <stdexcept>
#include <cstddef>
#include <functional>
#include <assert.h>

namespace FieaGameEngine
{
	/// <summary>
	/// A singly linked list class template
	/// </summary>
	template <typename T>
	class SList final
	{
	private:
		struct Node final
		{
			T Data;
			Node* Next;
			Node(const T& data, Node* next = nullptr);
		};
	public:
		/// <summary>
		/// Returns reference to front of list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		/// <returns>Reference to front of list</returns>
		T& Front();

		/// <summary>
		/// Returns const reference to front of list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		/// <returns>Const reference to front of list</returns>
		const T& Front() const;

		/// <summary>
		/// Returns reference to back of list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		/// <returns>Reference to back of list</returns>
		T& Back();

		/// <summary>
		/// Returns const reference to back of list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		/// <returns>Const reference to back of list</returns>
		const T& Back() const;


		/// <summary>
		/// Removes first element from the list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		void PopFront();

		/// <summary>
		/// Removes last element from the list
		/// </summary>
		/// <exception cref="std::runtime_error"> 
		/// Cannot access empty list
		/// </exception>
		void PopBack();

		/// <summary>
		/// Returns if list is empty
		/// </summary>
		/// <returns>bool representing if list is empty</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns the size of the list
		/// </summary>
		/// <returns>size_t that is the size of the list</returns>
		const std::size_t& Size() const;

		/// <summary>
		/// Instantiates a list by copying another list
		/// </summary>
		/// <param name="list">the list being copied</param>
		SList(const SList &other);

		/// <summary>
		/// Constructor that instantiates an empty list
		/// </summary>
		SList();

		/// <summary>
		/// Assignment operator that deep copies a list based off another list
		/// </summary>
		/// <param name="list">list being copied rhs of assignnment operator</param>
		/// <returns>lhs of assignment operator list being copied to</returns>
		SList& operator= (const SList &other);

		/// <summary>
		/// Clears the list. Makes it empty
		/// </summary>
		void Clear();

		/// <summary>
		/// Clears list and destructs it
		/// </summary>
		~SList();

		/// <summary>
		/// Iterator class for the SList to traverse the list and change elements
		/// </summary>
		class Iterator
		{
		public:
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
			/// <param name="other">SList being copied</param>
			/// <returns>Slist being assigned</returns>
			Iterator& operator=(const Iterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other SList being moved</param>
			Iterator(Iterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other SList being moved</param>
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
			/// Preiterates Iterator to the next element in the SList
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate Iterator with no container
			/// </exception>
			/// <returns>Returns Iterator</returns>
			Iterator& operator++();

			/// <summary>
			/// Postiterates Iterator to the next element in the SList
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
			/// /// <exception cref="std::runtime_error">
			/// Cannot dereference Iterator pointint to end()
			/// </exception>
			/// <returns>Returns data that Iterator refers to</returns>
			T& operator*() const;

			friend SList;
		private:
			Iterator(const SList& owner, Node* node = nullptr);
			Node* _node{ nullptr };
			const SList* _owner{ nullptr };
		};

		/// <summary>
		/// ConstIterator class for the SList to traverse the list
		/// </summary>
		class ConstIterator
		{
		public:
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
			/// <param name="other">SList being copied</param>
			/// <returns>Slist being assigned</returns>
			ConstIterator& operator=(const ConstIterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other SList being moved</param>
			ConstIterator(ConstIterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other SList being moved</param>
			/// <returns></returns>
			ConstIterator& operator=(ConstIterator&& other) = default;

			/// <summary>
			/// Default destructor
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// Compares if two ConstIterators are equivalent
			/// </summary>
			/// <param name="other">ConstIterator being compared to</param>
			/// <returns>true if equivalent and false if not</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Compares if two ConstIterators are not equivalent
			/// </summary>
			/// <param name="other">ConstIterator being compared to</param>
			/// <returns>true if not equivalent and false if equivalent/returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Preiterates ConstIterator to the next element in the SList
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate ConstIterator with no container
			/// </exception>
			/// <returns>Returns ConstIterator</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postiterates ConstIterator to the next element in the SList
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
			/// /// <exception cref="std::runtime_error">
			/// Cannot dereference ConstIterator pointint to end()
			/// </exception>
			/// <returns>Returns const data reference that ConstIterator refers to</returns>
			const T& operator*() const;

			/// <summary>
			/// Constructs a ConstIterator that refers to same SList and element as original Iterator
			/// </summary>
			/// <param name="it">Iterator being used to construct ConstIterator</param>
			ConstIterator(const Iterator& it);
			friend SList;
		private:
			ConstIterator(const SList& owner, Node* node = nullptr);
			Node* _node{ nullptr };
			const SList* _owner{ nullptr };
		};

		/// <summary>
		/// Returns Iterator that refers to the beginning of SList
		/// </summary>
		/// <returns>Iterator that refers to beginning of List</returns>
		Iterator begin();

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of SList
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of SList
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns Iterator that refers to one element after the last element of SList
		/// </summary>
		/// <returns>Iterator that refers to one element after the last element of SList</returns>
		Iterator end();

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of SList
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of SList</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of SList
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of SList</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Finds first T value in SList
		/// </summary>
		/// <param name="value">T value to be found</param>
		/// <param name="equalityFunc">Opitional function to determine equivalence</param>
		/// <returns>Returns ConstIterator that refers to found value will be end() if not found</returns>
		ConstIterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>()) const;
		
		/// <summary>
		/// Finds first element equivalent to T value in SList
		/// </summary>
		/// <param name="value">T value to be found</param>
		/// <param name="equalityFunc">Opitional function to determine equivalence</param>
		/// <returns>Returns Iterator that refers to found value will be end() if not found</returns>
		Iterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>());

		/// <summary>
		/// Removes first element equivalent to T value in SList
		/// </summary>
		/// <param name="value">T value to be removed</param>
		/// <param name="equalityFunc">Opitional function to determine equivalence</param>
		/// <returns>true if found and removed and false if not found</returns>
		bool Remove(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>());

		/// <summary>
		/// Removes an element that the iterator points to
		/// </summary>
		/// <param name="it">Iterator to be removed</param>
		void Remove(const Iterator& it);

		/// <summary>
		/// Inserts element after an iterator in SList
		/// </summary>
		/// <param name="value">Value to be inserted</param>
		/// <param name="it">Iterator for value to be inserted after</param>
		/// <returns>true if successfully inserted</returns>
		bool InsertAfter(const T& value, const Iterator& it);

		/// <summary>
		/// Adds a data element to the front of the list
		/// </summary>
		/// <param name="data">data to add to front of list</param>
		/// <returns>Returns Iterator pointing to added data</returns>
		Iterator PushFront(const T& data);

		/// <summary>
		/// Adds a data element to the back of the list
		/// </summary>
		/// <param name="data">data to back to front of list</param>
		/// <returns>Returns Iterator pointing to added data</returns>
		Iterator PushBack(const T& data);

	private:
		size_t _size;
		Node* _front;
		Node* _back;
	};

}

#include "SList.inl"