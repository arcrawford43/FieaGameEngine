#include "Vector.h"

namespace FieaGameEngine
{
	template <typename T>
	Vector<T>::Vector(std::size_t capacity)
	{
		Reserve(capacity);
	}

	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> list)
	{
		Reserve(list.size());
		for (const T& value : list)
		{
			PushBack(value);
		}
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		free(_data);
	}

	template <typename T>
	Vector<T>::Vector(const Vector& other):
		_capacity(other._capacity), _size(0)
	{
		if (_capacity != 0)
		{
			_data = reinterpret_cast<T*>(malloc(sizeof(T) * _capacity));
		}
		for (const T& value : other)
		{
			PushBack(value);
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& other)
	{
		if (this != &other)
		{
			Clear();
			Reserve(other._capacity);
			for (const T& value : other)
			{
				PushBack(value);
			}
		}
		return *this;
	}

	template <typename T>
	Vector<T>::Vector(Vector&& rhs) noexcept:
		_size(rhs._size), _capacity(rhs._capacity), _data(rhs._data)
	{
		rhs._size = 0;
		rhs._capacity = 0;
		rhs._data = nullptr;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			free(_data);
			_size = rhs._size;
			_capacity = rhs._capacity;
			_data = rhs._data;
			rhs._size = 0;
			rhs._capacity = 0;
			rhs._data = nullptr;
		}
		return *this;
	}

	template <typename T>
	T& Vector<T>::operator[](size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Cannot access out of range element");
		}
		return(_data[index]);
	}

	template <typename T>
	const T& Vector<T>::operator[](size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Cannot access out of range element");
		}
		return(_data[index]);
	}

	template <typename T>
	T& Vector<T>::At(size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Cannot access out of range element");
		}
		return(_data[index]);
	}

	template <typename T>
	const T& Vector<T>::At(size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Cannot access out of range element");
		}
		return(_data[index]);
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (_size > 0)
		{
			_data[_size - 1].~T();
			--_size;
		}
	}
	
	template <typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return (_size == 0);
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access element from empty vector");
		}
		return _data[0];
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access element from empty vector");
		}
		return _data[0];
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access element from empty vector");
		}
		return _data[_size - 1];
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access element from empty vector");
		}
		return _data[_size - 1];
	}

	template <typename T>
	inline std::size_t Vector<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	inline std::size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}

	template <typename T>
	void Vector<T>::Resize(std::size_t size)
	{
		if (size < _size)
		{
			for (std::size_t index = size; index < _size; ++index)
			{
				_data[index].~T();
			}
		}
		else
		{
			Reserve(size);
			for (std::size_t index = _size; index < size; ++index)
			{
				PushBack(T());
			}
		}
		_size = size;
	}

	template <typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return (_owner != other._owner || _index != other._index);
	}

	template <typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return !(*this != other);
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment Iterator that does not have a container");
		}
		if (_index < _owner->_size)
		{
			++_index;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment Iterator that does not have a container");
		}
		if (_index != 0)
		{
			--_index;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator temp = *this;
		operator--();
		return temp;
	}

	template <typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot dereference Iterator that does not have a container");
		}
		if (_index >= _owner->_size)
		{
			throw std::out_of_range("Cannot dereference out of bounds iterator");
		}
		return _owner->_data[_index];
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Vector& owner, std::size_t index) :
		_owner(&owner), _index(index)
	{
	}

	template <typename T>
	bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return (_owner != other._owner || _index != other._index);
	}

	template <typename T>
	bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(*this != other);
	}

	template <typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment ConstIterator that does not have a container");
		}
		if (_index < _owner->_size)
		{
			++_index;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template <typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment ConstIterator that does not have a container");
		}
		if (_index != 0)
		{
			--_index;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator temp = *this;
		operator--();
		return temp;
	}

	template <typename T>
	const T& Vector<T>::ConstIterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot dereference ConstIterator that does not have a container");
		}
		if (_index >= _owner->_size)
		{
			throw std::out_of_range("Cannot dereference out of bounds ConstIterator");
		}
		return _owner->operator[](_index);
	}

	template <typename T>
	Vector<T>::ConstIterator::ConstIterator(const Vector& owner, std::size_t index) :
		_owner(&owner), _index(index)
	{
	}

	template <typename T>
	Vector<T>::ConstIterator::ConstIterator(const Iterator& it) :
		_owner(it._owner), _index(it._index)
	{
	}

	template <typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator{ *this };
	}

	template <typename T>
	inline typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator{ *this, _size };
	}

	template <typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return ConstIterator{ *this };
	}

	template <typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator{ *this, _size };
	}

	template <typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return ConstIterator{ *this, 0 };
	}

	template <typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return ConstIterator{ *this, _size };
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& value)
	{
		if (_size == _capacity)
		{
			if (_capacity == 0)
			{
				_capacity = 1;
			}
			Reserve(_capacity * 2);
		}
		new(_data + _size) T{ value };
		++_size;
		return{ *this, _size - 1 };
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(T&& value)
	{
		if (_size == _capacity)
		{
			if (_capacity == 0)
			{
				Reserve(2);
			}
			else
			{
				Reserve(_capacity * 2);
			}
		}
		new(_data + _size) T{ std::forward<T&&>(value) };
		++_size;
		return{ *this, _size - 1 };
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		for (size_t index = 0; index < _size; ++index)
		{
			operator[](index).~T();
		}
		_size = 0;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc)
	{
		Iterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunc(*it, value))
			{
				break;
			}
		}

		return it;
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc) const
	{
		ConstIterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunc(*it, value))
			{
				break;
			}
		}

		return it;
	}

	template <typename T>
	bool Vector<T>::Remove(const T& value, std::function<bool(const T&, const T&)> equalityFunc)
	{
		bool removeElement = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (removeElement == true)
			{
				operator[](index - 1) = std::move(operator[](index));
			}
			else if (equalityFunc(operator[](index), value))
			{	
				removeElement = true;
			}
		}
		if (removeElement)
		{
			operator[](_size - 1).~T();
			--_size;
		}
		return removeElement;
	}

	template <typename T>
	bool Vector<T>::Remove(const Iterator& begin, const Iterator& end)
	{
		bool removeElement = false;
		if (begin._index < end._index && end._index <= _size)
		{
			size_t numberRemoved = end._index - begin._index;
			removeElement = true;
			for (std::size_t index = begin._index; index < _size - numberRemoved; ++index)
			{
				operator[](index) = std::move(operator[](index + numberRemoved));
			}
			for (std::size_t index = _size - numberRemoved; index < _size; ++index)
			{
				operator[](index).~T();
			}
			_size -= numberRemoved;
		}
		return removeElement;
	}

	template <typename T>
	bool Vector<T>::Remove(size_t index)
	{
		Remove(Iterator(*this, index), Iterator(*this, index + 1));
	}

	template <typename T>
	void Vector<T>::Reserve(std::size_t capacity)
	{
		if (capacity > _capacity)
		{
			T* tempData = reinterpret_cast<T*>(realloc(_data, sizeof(T) * capacity));
			assert(tempData != nullptr);
			_data = tempData;
			_capacity = capacity;
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::GetIterator(size_t index)
	{
		return { *this, index };
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::GetIterator(size_t index) const
	{
		return { *this, index };
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::GetConstIterator(size_t index) const
	{
		return { *this, index };
	}
}
