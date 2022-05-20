#include "Hashmap.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData>
	Hashmap<TKey, TData>::Hashmap(std::size_t numBuckets, HashFunctor hashFunctor, EqualityFunctor equalityFunctor) :
		_hashFunctor(hashFunctor), _equalityFunctor(equalityFunctor), _size(0), _emptyBuckets(numBuckets)
	{
		if (numBuckets > 1)
		{
			_buckets.Resize(numBuckets);
		}
		else
		{
			_buckets.Resize(2);
			_emptyBuckets = 2;
		}
	}

	template <typename TKey, typename TData>
	Hashmap<TKey, TData>::Hashmap(std::initializer_list<PairType> initList, std::size_t numBuckets, HashFunctor hashFunctor, EqualityFunctor equalityFunctor) :
		_hashFunctor(hashFunctor), _equalityFunctor(equalityFunctor), _size(0), _emptyBuckets(numBuckets)
	{
		if (numBuckets > 1)
		{
			_buckets.Resize(numBuckets);
		}
		else
		{
			_buckets.Resize(2);
			_emptyBuckets = 2;
		}

		for (const auto& pair : initList)
		{
			Insert(pair);
		}
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::Iterator::operator!=(const Iterator& other) const
	{
		return(_owner != other._owner || _index != other._index || _chainIterator != other._chainIterator);
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::Iterator::operator==(const Iterator& other) const
	{
		return !(*this != other);
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::Iterator& Hashmap<TKey, TData>::Iterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment Iterator that does not have a container");
		}
		++_chainIterator;
		while (_chainIterator == _owner->_buckets[_index].end())
		{
			if (_index == _owner->_buckets.Size() - 1)
			{
				++_index;
				_chainIterator = SList< std::pair<const TKey, TData>>::Iterator::Iterator();
				break;
			}
			_chainIterator = _owner->_buckets[++_index].begin();
		}
		return *this;
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::Iterator Hashmap<TKey, TData>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	template <typename TKey, typename TData>
	std::pair<const TKey, TData>& Hashmap<TKey, TData>::Iterator::operator*() const
	{
		return *_chainIterator;
	}

	template <typename TKey, typename TData>
	std::pair<const TKey, TData>* Hashmap<TKey, TData>::Iterator::operator->() const
	{
		return &(*_chainIterator);
	}

	template <typename TKey, typename TData>
	Hashmap<TKey, TData>::Iterator::Iterator(Hashmap& owner, size_t index, const typename SList<std::pair<const TKey, TData>>::Iterator& chainIterator) :
		_owner(&owner), _chainIterator(chainIterator), _index(index)
	{
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return(_owner != other._owner || _index != other._index || _chainIterator != other._chainIterator);
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return !(*this != other);
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator& Hashmap<TKey, TData>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
		{
			throw std::runtime_error("Cannot increment ConstIterator that does not have a container");
		}
		++_chainIterator;
		while (_chainIterator == _owner->_buckets[_index].end())
		{
			if (_index == _owner->_buckets.Size() - 1)
			{
				++_index;
				_chainIterator = SList< std::pair<const TKey, TData>>::ConstIterator::ConstIterator();
				break;
			}
			_chainIterator = _owner->_buckets[++_index].begin();
		}
		return *this;
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		operator++();
		return temp;
	}

	template <typename TKey, typename TData>
	const std::pair<const TKey, TData>& Hashmap<TKey, TData>::ConstIterator::operator*() const
	{
		return *_chainIterator;
	}

	template <typename TKey, typename TData>
	const std::pair<const TKey, TData>* Hashmap<TKey, TData>::ConstIterator::operator->() const
	{
		return &(*_chainIterator);
	}

	template <typename TKey, typename TData>
	Hashmap<TKey, TData>::ConstIterator::ConstIterator(const Hashmap& owner, size_t index, const typename SList<std::pair<const TKey, TData>>::ConstIterator& chainIterator) :
		_owner(&owner), _chainIterator(chainIterator), _index(index)
	{
	}

	template <typename TKey, typename TData>
	Hashmap<TKey, TData>::ConstIterator::ConstIterator(const Iterator& it) :
		_owner(it._owner), _index(it._index), _chainIterator(it._chainIterator)
	{
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::Iterator Hashmap<TKey, TData>::begin()
	{
		typename Hashmap<TKey, TData>::Iterator it{ *this, _buckets.Size() };
		if (_size > 0)
		{
			it._index = 0;
			it._chainIterator = _buckets[0].begin();
			for (it._index = 0; it._index < _buckets.Size(); ++it._index)
			{
				if (_buckets[it._index].IsEmpty() == false)
				{
					it._chainIterator = _buckets[it._index].begin();
					break;
				}
			}
		}
		return it;
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::begin() const
	{
		typename Hashmap<TKey, TData>::ConstIterator it{ *this, _buckets.Size() };
		if (_size > 0)
		{
			it._index = 0;
			it._chainIterator = _buckets[0].cbegin();
			for (it._index = 0; it._index < _buckets.Size(); ++it._index)
			{
				if (_buckets[it._index].cbegin() != _buckets[it._index].cend())
				{
					it._chainIterator = _buckets[it._index].cbegin();
				}
			}
		}
		return it;
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::cbegin() const
	{
		typename Hashmap<TKey, TData>::ConstIterator it{ *this, _buckets.Size() };
		if (_size > 0)
		{
			it._index = 0;
			it._chainIterator = _buckets[0].cbegin();
			for (it._index = 0; it._index < _buckets.Size(); ++it._index)
			{
				if (_buckets[it._index].cbegin() != _buckets[it._index].cend())
				{
					it._chainIterator = _buckets[it._index].cbegin();
				}
			}
		}
		return it;
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::Iterator Hashmap<TKey, TData>::end()
	{
		return{ *this, _buckets.Size() };
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::end() const
	{
		return{ *this, _buckets.Size() };
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::cend() const
	{
		return{ *this, _buckets.Size() };
	}

	template <typename TKey, typename TData>
	inline std::size_t Hashmap<TKey, TData>::Hash(const TKey& key) const
	{
		return _hashFunctor(key) % _buckets.Size();
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::Iterator Hashmap<TKey, TData>::Find(const TKey& key)
	{
		std::size_t index = Hash(key);
		for (typename SList<std::pair<const TKey, TData>>::Iterator it = _buckets[index].begin(); it != _buckets[index].end(); ++it)
		{
			if (_equalityFunctor((*it).first, key))
			{
				return { *this, index, it };
			}
		}
		return end();
	}

	template <typename TKey, typename TData>
	typename Hashmap<TKey, TData>::ConstIterator Hashmap<TKey, TData>::Find(const TKey& key) const
	{
		std::size_t index = Hash(key);
		for (typename SList<std::pair<const TKey, TData>>::ConstIterator it = _buckets[index].begin(); it != _buckets[index].end(); ++it)
		{
			if (_equalityFunctor((*it).first, key))
			{
				return { *this, index, it };
			}
		}
		return end();
	}

	template <typename TKey, typename TData>
	std::pair<typename Hashmap<TKey, TData>::Iterator, bool> Hashmap<TKey, TData>::Find(const TKey& key, std::size_t index)
	{
		for (typename SList<std::pair<const TKey, TData>>::Iterator it = _buckets[index].begin(); it != _buckets[index].end(); ++it)
		{
			if (_equalityFunctor((*it).first, key))
			{
				return std::make_pair(Iterator(*this, index, it), true);
			}
		}
		return { end(), false };
	}

	template <typename TKey, typename TData>
	std::pair<typename Hashmap<TKey, TData>::ConstIterator, bool> Hashmap<TKey, TData>::Find(const TKey& key, std::size_t index) const
	{
		for (typename SList<std::pair<const TKey, TData>>::ConstIterator it = _buckets[index].begin(); it != _buckets[index].end(); ++it)
		{
			if (_equalityFunctor((*it).first, key))
			{
				return std::make_pair(ConstIterator(*this, index, it), true);
			}
		}
		return { end(), false };
	}

	template<typename TKey, typename TData>
	std::pair<typename Hashmap<TKey, TData>::Iterator, bool> Hashmap<TKey, TData>::Insert(const PairType& pair)
	{
		std::size_t index = Hash(pair.first);
		std::pair<typename Hashmap<TKey, TData>::Iterator, bool> findPair = Find(pair.first, index);
		
		if (findPair.second == false)
		{
			if (_buckets[index].IsEmpty() == true)
			{
				--_emptyBuckets;
			}
			++_size;
			findPair.second = true;
			findPair.first = { *this, index, _buckets[index].PushFront(pair) };
		}
		else
		{
			findPair.second = false;
		}
		
		return findPair;
	}

	template<typename TKey, typename TData>
	std::pair<typename Hashmap<TKey, TData>::Iterator, bool> Hashmap<TKey, TData>::Insert(PairType&& pair)
	{
		std::size_t index = Hash(pair.first);
		std::pair<typename Hashmap<TKey, TData>::Iterator, bool> findPair = Find(pair.first, index);

		if (findPair.second == false)
		{
			if (_buckets[index].IsEmpty() == true)
			{
				--_emptyBuckets;
			}
			++_size;
			findPair.second = true;
			findPair.first = { *this, index, _buckets[index].PushFront(std::forward<PairType&&>(pair)) };
		}
		else
		{
			findPair.second = false;
		}
		
		return findPair;
	}

	template<typename TKey, typename TData>
	TData& Hashmap<TKey, TData>::operator[](const TKey& key)
	{
		std::pair<typename Hashmap<TKey, TData>::Iterator, bool> insertPair = Insert(std::make_pair(key, TData()));
		typename Hashmap<TKey, TData>::Iterator it = insertPair.first;
		return (*it).second;
	}

	template<typename TKey, typename TData>
	bool Hashmap<TKey, TData>::Remove(const TKey& key)
	{
		std::size_t index = Hash(key);
		std::pair<Iterator, bool > findPair = Find(key, index);

		if (findPair.second == true)
		{
			_buckets[index].Remove(findPair.first._chainIterator);
			--_size;
			if (_buckets[index].IsEmpty())
			{
				++_emptyBuckets;
			}
		}
		return findPair.second;
	}

	template <typename TKey, typename TData>
	inline std::size_t Hashmap<TKey, TData>::Size() const
	{
		return _size;
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::ContainsKey(const TKey& key) const
	{
		return Find(key, Hash(key)).second;
	}

	template <typename TKey, typename TData>
	inline bool Hashmap<TKey, TData>::ContainsKey(const TKey& key, TData& outData)
	{
		auto findResult = Find(key, Hash(key));
		if (findResult.second)
		{
			outData = (*findResult.first).second;
		}
		return findResult.second;
	}

	template <typename TKey, typename TData>
	TData& Hashmap<TKey, TData>::At(const TKey& key)
	{
		Iterator it = Find(key);
		if (it == end())
		{
			throw std::runtime_error("Cannot find the key in the Hashmap");
		}
		return (*it).second;
	}

	template <typename TKey, typename TData>
	const TData& Hashmap<TKey, TData>::At(const TKey& key) const
	{
		ConstIterator it = Find(key);
		if (it == end())
		{
			throw std::runtime_error("Cannot find the key in the Hashmap");
		}
		return (*it).second;
	}

	template <typename TKey, typename TData>
	inline float Hashmap<TKey, TData>::LoadFactor() const
	{
		return { static_cast<float>(_size) / static_cast<float>(_buckets.Size()) };
	}

	template <typename TKey, typename TData>
	inline float Hashmap<TKey, TData>::Capacity() const
	{
		return { 100.0f * ((static_cast<float>(_buckets.Size() - _emptyBuckets)) / static_cast<float>(_buckets.Size())) };
	}

	template <typename TKey, typename TData>
	inline size_t Hashmap<TKey, TData>::NumberBuckets() const
	{
		return _buckets.Size();
	}
	
	template <typename TKey, typename TData>
	void Hashmap<TKey, TData>::Clear()
	{
		for (std::size_t i = 0; i < _buckets.Size(); ++i)
		{
			_buckets[i].Clear();
		}
		_emptyBuckets = _buckets.Size();
		_size = 0;
	}

	template <typename TKey, typename TData>
	void Hashmap<TKey, TData>::Rehash(std::size_t newNumBuckets, std::function<std::size_t(const TKey&)> hashFunctor)
	{
		if (newNumBuckets < 2)
		{
			newNumBuckets = 2;
		}
		Hashmap newHashmap{ newNumBuckets, hashFunctor, _equalityFunctor };
		for (Iterator it = begin(); it != end(); ++it)
		{
			newHashmap.Insert(*it);
		}
		this->operator=(std::move(newHashmap));
	}

	template <typename TKey, typename TData>
	void Hashmap<TKey, TData>::Rehash(std::size_t newNumBuckets)
	{
		if (newNumBuckets < 2)
		{
			newNumBuckets = 2;
		}
		Hashmap newHashmap{ newNumBuckets, _hashFunctor, _equalityFunctor };
		for (Iterator it = begin(); it != end(); ++it)
		{
			newHashmap.Insert(*it);
		}
		this->operator=(std::move(newHashmap));
	}
}