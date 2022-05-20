#include "SList.h"

namespace FieaGameEngine
{
	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next):
		Data(data), Next(next)
	{
	}

	template <typename T>
	inline const std::size_t& SList<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	T& SList<T>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access an empty list.");
		}

		return _front->Data;
	}

	template <typename T>
	const T& SList<T>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access an empty list.");
		}

		return _front->Data;
	}

	template <typename T>
	T& SList<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access an empty list.");
		}

		return _back->Data;
	}

	template <typename T>
	const T& SList<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot access an empty list.");
		}

		return _back->Data;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& data)
	{
		Node* tempNode = _front;
		_front = new Node(data, tempNode);
		if (_size == 0)
		{
			_back = _front;
		}
		++_size;
		return Iterator{ *this, _front };
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		if (_size == 0)
		{
			_back = new Node(data, nullptr);
			_front = _back;
		}
		else
		{
			_back->Next = new Node(data, nullptr);
			_back = _back->Next;
		}
		++_size;
		return Iterator{ *this, _back };
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot pop from an empty list.");
		}

		Node* tempNode = _front->Next;
		delete _front;
		_front = tempNode;
		--_size;
		if (_size == 0)
		{
			_back = nullptr;
		}
	}

	template <typename T>
	void SList<T>::PopBack()
	{
		if (_size == 0)
		{
			throw std::runtime_error("Cannot pop from an empty list.");
		}

		if (_front == _back)
		{
			delete _back;
			_back = nullptr;
			_front = nullptr;
			_size = 0;
			return;
		}
		Node* tempNode = _front;
		while (tempNode->Next != _back)
		{
			tempNode = tempNode->Next;
		}
		tempNode->Next = nullptr;
		delete _back;
		_back = tempNode;
		--_size;
	}

	template <typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return (_size == 0);
	}

	template <typename T>
	SList<T>::SList() :
		_front(nullptr), _back(nullptr), _size(0)
	{
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList &other)
	{
		if (this != &other)
		{
			Clear();
			_size = other._size;

			if(other._size > 0)
			{
				_front = new Node(other._front->Data);
				Node* newNode = _front;
				Node* oldNode = other._front->Next;

				while (oldNode != nullptr)
				{
					newNode->Next = new Node(oldNode->Data);
					newNode = newNode->Next;
					oldNode = oldNode->Next;
				}

				_back = newNode;
			}
		}
		return *this;
	}

	template <typename T>
	SList<T>::SList(const SList& other):
		_size(other._size)
	{
		if (other._size == 0)
		{
			_front = nullptr;
			_back = nullptr;
		}
		else
		{
			_front = new Node(other._front->Data);
			Node* newNode = _front;
			Node* oldNode = other._front->Next;

			while (oldNode != nullptr)
			{
				newNode->Next = new Node(oldNode->Data);
				newNode = newNode->Next;
				oldNode = oldNode->Next;
			}

			_back = newNode;
		}
	}

	template <typename T>
	void SList<T>::Clear()
	{
		Node* currentNode = _front;
		while (currentNode != nullptr)
		{
			Node* nextNode = currentNode->Next;
			delete currentNode;
			currentNode = nextNode;
		}
		_front = nullptr;
		_back = nullptr;
		_size = 0;
	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return (_owner != other._owner || _node != other._node);
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& other) const
	{
		return !(*this != other);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment Iterator that does not have a container");
		}

		_node = _node->Next;
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot dereference Iterator that does not have a container");
		}
		if (_node == nullptr)
		{
			throw std::runtime_error("Cannot dereference end() Iterator");
		}
		return _node->Data;
	}

	template <typename T>
	SList<T>::Iterator::Iterator(const SList& owner, Node* node) :
		_owner(&owner), _node(node)
	{
	}

	template <typename T>
	bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return (_owner != other._owner || _node != other._node);
	}

	template <typename T>
	bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(*this != other);
	}

	template <typename T>
	typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment ConstIterator that does not have a container");
		}

		_node = _node->Next;
		return *this;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template <typename T>
	const T& SList<T>::ConstIterator::operator*() const
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot dereference ConstIterator that does not have a container");
		}
		if (_node == nullptr)
		{
			throw std::runtime_error("Cannot dereference end() ConstIterator");
		}
		return _node->Data;
	}

	template <typename T>
	SList<T>::ConstIterator::ConstIterator(const SList& owner, Node* node) :
		_owner(&owner), _node(node)
	{
	}

	template <typename T>
	SList<T>::ConstIterator::ConstIterator(const Iterator& it) :
		_owner(it._owner), _node(it._node)
	{
	}

	template <typename T>
	inline typename SList<T>::Iterator SList<T>::begin()
	{
		return Iterator{ *this, _front };
	}

	template <typename T>
	inline typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator{ *this };
	}

	template <typename T>
	inline typename SList<T>::ConstIterator SList<T>::begin() const
	{
		return ConstIterator{ *this, _front };
	}

	template <typename T>
	inline typename SList<T>::ConstIterator SList<T>::end() const
	{
		return ConstIterator{ *this };
	}

	template <typename T>
	inline typename SList<T>::ConstIterator SList<T>::cbegin() const
	{
		return ConstIterator{ *this, _front };
	}

	template <typename T>
	inline typename SList<T>::ConstIterator SList<T>::cend() const
	{
		return ConstIterator{ *this };
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc) const
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
	typename SList<T>::Iterator SList<T>::Find(const T& value, std::function<bool(const T&, const T&)> equalityFunc)
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
	bool SList<T>::Remove(const T& value, std::function<bool(const T&, const T&)> equalityFunc)
	{
		bool removeElement = false;
		Iterator prevIt;
		for (Iterator it = begin(); it != end(); ++it)
		{
			if (equalityFunc(*it, value))
			{
				if (it._node == _front)
				{
					PopFront();
				}
				else if (it._node == _back)
				{
					PopBack();
				}
				else
				{
					prevIt._node->Next = it._node->Next;
					delete it._node;
					--_size;
				}
				removeElement = true;
				break;
			}
			prevIt = it;
		}
		return removeElement;
	}

	template <typename T>
	void SList<T>::Remove(const typename SList<T>::Iterator& it)
	{
		Iterator prevIt;
		if (it._node == _front)
		{
			PopFront();
		}
		else if (it._node == _back)
		{
			PopBack();
		}
		else
		{
			for (Iterator newIt = begin(); newIt != it; ++newIt)
			{
				prevIt = newIt;
			}
			prevIt._node->Next = it._node->Next;
			delete it._node;
			--_size;
		}
	}

	template <typename T>
	bool SList<T>::InsertAfter(const T& value, const Iterator& it)
	{
		bool insertElement = false;
		if (it._owner == this)
		{
			if (it._node == _back || it._node == nullptr)
			{
				PushBack(value);
			}
			else
			{
				it._node->Next = new Node{ value, it._node->Next };
				++_size;
			}
			insertElement = true;
		}
		return insertElement;
	}


}