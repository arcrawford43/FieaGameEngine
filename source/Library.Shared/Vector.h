#pragma once
#include <stdexcept>
#include <cstddef>
#include <assert.h>
#include <functional>
#include <utility>

namespace FieaGameEngine
{
	template <typename T>
	class Vector final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = T&;
		using pointer = T*;

		/// <summary>
		/// Constructor
		/// </summary>
		Vector(std::size_t capacity = 0);

		/// <summary>
		/// Constructor using init list
		/// </summary>
		/// <param name="list">List to be pushed back</param>
		Vector(std::initializer_list<T> list);

		/// <summary>
		/// Destructor that frees data
		/// </summary>
		~Vector();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">
		/// Vector being copied
		/// </param>
		Vector(const Vector& other);

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Vector being copied</param>
		/// <returns>Vector being copied to</returns>
		Vector& operator=(const Vector& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">Vector being moved</param>
		Vector(Vector&& rhs) noexcept;

		/// <summary>
		/// Move Assignmenmt Operator
		/// </summary>
		/// <param name="rhs">Vector being moved</param>
		/// <returns>Vector being moved to</returns>
		Vector& operator=(Vector&& rhs) noexcept;

		/// <summary>
		/// Bracket operator returning element at that location in constant time
		/// </summary>
		/// <param name="index">index of element wanted</param>
		/// <exception cref="out_of_range">
		/// Exception if references an index not in Vector</exception>
		/// <returns>Reference to the value requested</returns>
		T& operator[](size_t index);

		/// <summary>
		/// Bracket operator returning const element at that location in constant time
		/// </summary>
		/// <param name="index">index of element wanted</param>
		/// <exception cref="out_of_range">
		/// Exception if references an index not in Vector</exception>
		/// <returns>Const reference to the value requested</returns>
		const T& operator[](size_t index) const;

		/// <summary>
		/// At returns element at that index in constant time
		/// </summary>
		/// <param name="index">index of element wanted</param>
		/// <exception cref="out_of_range">
		/// Exception if references an index not in Vector</exception>
		/// <returns>Reference to the value requested</returns>
		T& At(size_t index);

		/// <summary>
		/// At returns const element at that index in constant time
		/// </summary>
		/// <param name="index">index of element wanted</param>
		/// <exception cref="out_of_range">
		/// Exception if references an index not in Vector</exception>
		/// <returns>Const reference to the value requested</returns>
		const T& At(size_t index) const;

		/// <summary>
		/// Removes last element from Vector
		/// </summary>
		void PopBack();

		/// <summary>
		/// Returns if vector is empty
		/// </summary>
		/// <returns>
		/// true if empty, false if not</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns reference to first element in Vector
		/// </summary>
		/// <exception cref="runtime_error">Cannot access empty Vector</exception>
		/// <returns>Reference to first element in Vector</returns>
		T& Front();

		/// <summary>
		/// Returns const reference to first element in Vector
		/// </summary>
		/// <exception cref="runtime_error">Cannot access empty Vector</exception>
		/// <returns>Const reference to first element in Vector</returns>
		const T& Front() const;

		/// <summary>
		/// Returns reference to last element in Vector
		/// </summary>
		/// <exception cref="runtime_error">Cannot access empty Vector</exception>
		/// <returns>Reference to last element in Vector</returns>
		T& Back();

		/// <summary>
		/// Returns const reference to last element in Vector
		/// </summary>
		/// <exception cref="runtime_error">Cannot access empty Vector</exception>
		/// <returns>Const reference to last element in Vector</returns>
		const T& Back() const;

		/// <summary>
		/// Returns number of elements in Vector
		/// </summary>
		/// <returns>Number of elements in Vector</returns>
		std::size_t Size() const;

		/// <summary>
		/// Returns capacity of Vector
		/// </summary>
		/// <returns>Capacity of Vector</returns>
		std::size_t Capacity() const;

		/// <summary>
		/// Removes all items from Vector
		/// </summary>
		void Clear();

		/// <summary>
		/// Increases capacity of Vector
		/// </summary>
		/// <param name="capacity">Value to increase capacity to</param>
		void Reserve(std::size_t capacity);

		/// <summary>
		/// Resizes the vector. Default constructs elements if elements are added
		/// </summary>
		/// <param name="size">New size for the vector</param>
		void Resize(std::size_t size);

		class Iterator
		{
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T&;
			using pointer = T*;
			using iterator_category = std::bidirectional_iterator_tag;

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
			/// <param name="other">Vector being copied</param>
			/// <returns>Vector being assigned</returns>
			Iterator& operator=(const Iterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other Vector being moved</param>
			Iterator(Iterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other Vector being moved</param>
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
			/// Preiterates Iterator to the previous element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate Iterator with no container
			/// </exception>
			/// <returns>Returns Iterator</returns>
			Iterator& operator--();

			/// <summary>
			/// Postiterates Iterator to the previous element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate Iterator with no container
			/// </exception>
			/// <returns>Returns copy of Iterator before iteration</returns>
			Iterator operator--(int);

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
			T& operator*() const;

			friend Vector;
			Iterator(const Vector& owner, size_t index = 0);
		private:
			std::size_t _index{ 0 };
			const Vector* _owner{ nullptr };
		};

		class ConstIterator
		{
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T&;
			using pointer = T*;
			using iterator_category = std::bidirectional_iterator_tag;

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
			/// <param name="other">Vector being copied</param>
			/// <returns>Vector being assigned</returns>
			ConstIterator& operator=(const ConstIterator& other) = default;

			/// <summary>
			/// Default move constructor
			/// </summary>
			/// <param name="other">Other Vector being moved</param>
			ConstIterator(ConstIterator&& other) = default;

			/// <summary>
			/// Default move assignment operator
			/// </summary>
			/// <param name="other">Other Vector being moved</param>
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
			/// Preiterates ConstIterator to the previous element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate ConstIterator with no container
			/// </exception>
			/// <returns>Returns ConstIterator</returns>
			ConstIterator& operator--();

			/// <summary>
			/// Postiterates ConstIterator to the previous element in the Vector
			/// </summary>
			/// <exception cref="std::runtime_error">
			/// Cannot iterate ConstIterator with no container
			/// </exception>
			/// <returns>Returns copy of ConstIterator before iteration</returns>
			ConstIterator operator--(int);

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
			const T& operator*() const;

			/// <summary>
			/// Constructs a ConstIterator that refers to same Vector and element as original Iterator
			/// </summary>
			/// <param name="it">Iterator being used to construct ConstIterator</param>
			ConstIterator(const Iterator& it);

			friend Vector;
		private:
			ConstIterator(const Vector& owner, size_t index = 0);
			std::size_t _index{ 0 };
			const Vector* _owner{ nullptr };
		};

		/// <summary>
		/// Returns Iterator that refers to the beginning of Vector
		/// </summary>
		/// <returns>Iterator that refers to beginning of List</returns>
		Iterator begin();

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of Vector
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns ConstIterator that refers to the beginning of Vector
		/// </summary>
		/// <returns>ConstIterator that refers to beginning of List</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns Iterator that refers to one element after the last element of Vector
		/// </summary>
		/// <returns>Iterator that refers to one element after the last element of Vector</returns>
		Iterator end();

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of Vector
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of Vector</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns ConstIterator that refers to one element after the last element of Vector
		/// </summary>
		/// <returns>ConstIterator that refers to one element after the last element of Vector</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Add value to back of Vector
		/// </summary>
		/// <param name="value">value being appended to Vector</param>
		/// <returns>Returns Iterator pointing to added element</returns>
		Iterator PushBack(const T& value);

		/// <summary>
		/// Add value to back of Vector
		/// </summary>
		/// <param name="value">value being appended to Vector</param>
		/// <returns>Returns Iterator pointing to added element</returns>
		Iterator PushBack(T&& value);

		/// <summary>
		/// Finds an element in Vector
		/// </summary>
		/// <param name="value">value to be found</param>
		/// <param name="equalityFunc">opitional paremeter to set user defined equality operator</param>
		/// <returns>Iterator pointing to the found element or end() if not found</returns>
		Iterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>());

		/// <summary>
		/// Finds an element in Vector
		/// </summary>
		/// <param name="value">value to be found</param>
		/// <param name="equalityFunc">opitional paremeter to set user defined equality operator</param>
		/// <returns>ConstIterator pointing to the found element or end() if not found</returns>
		ConstIterator Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>()) const;

		/// <summary>
		/// Removes the first occurrence of an element in Vector
		/// </summary>
		/// <param name="value">value to be removed</param>
		/// <param name="equalityFunc">opitional paremeter to set user defined equality operator</param>
		/// <returns>True if able to find and remove element false if not able to remove element</returns>
		bool Remove(const T& value, std::function<bool(const T&, const T&)> equalityFunc = std::equal_to<T>());

		/// <summary>
		/// Removes the a range of elements from Vector
		/// </summary>
		/// <param name="begin">Inclusive begin of elements to be removed</param>
		/// <param name="end">Exclusive end of elements to be removed</param>
		/// <returns>True if valid indexes and remove elements false if not able to remove elements</returns>
		bool Remove(const Iterator& begin, const Iterator& end);

		/// <summary>
		/// Removes a element from Vector
		/// </summary>
		/// <param name="index"> to be removed</param>
		/// <returns>True if valid indexes and remove elements false if not able to remove elements</returns>
		bool Remove(size_t index);

		Iterator GetIterator(size_t index);

		ConstIterator GetIterator(size_t index) const;

		ConstIterator GetConstIterator(size_t index) const;
	private:
		size_t _capacity{ 0 };
		size_t _size{ 0 };
		T* _data{ nullptr };
	};
}

#include "Vector.inl"