#include "pch.h"
#include "Scope.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope(std::size_t capacity) :
		_vector(capacity), _map(capacity)
	{
	}

	Scope::~Scope()
	{
		Orphan();
		Clear();
	}

	Scope::Scope(const Scope& rhs) :
		_map(rhs._map.NumberBuckets()), _vector(rhs._vector.Capacity())
	{
		for (size_t i = 0; i < rhs._vector.Size(); ++i)
		{
			Datum existingDatum = rhs._vector[i]->second;
			Datum& newDatum = Append(rhs._vector[i]->first);
			if (existingDatum.Type() == DatumTypes::Table)
			{
				newDatum.SetType(DatumTypes::Table);
				newDatum.Reserve(existingDatum.Size());
				for (size_t j = 0; j < existingDatum.Size(); ++j)
				{
					Scope* childCopy = existingDatum[j].Clone();
					Adopt(*childCopy, rhs._vector[i]->first);
				}
			}
			else
			{
				newDatum = existingDatum;
			}
		}
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		Clear();
		_vector.Reserve(rhs._vector.Capacity());
		_map.Rehash(rhs._map.NumberBuckets());

		for (size_t i = 0; i < rhs._vector.Size(); ++i)
		{
			Datum existingDatum = rhs._vector[i]->second;
			Datum& newDatum = Append(rhs._vector[i]->first);
			if (existingDatum.Type() == DatumTypes::Table)
			{
				newDatum.SetType(DatumTypes::Table);
				newDatum.Reserve(existingDatum.Size());
				for (size_t j = 0; j < existingDatum.Size(); ++j)
				{
					Scope* childCopy = existingDatum[j].Clone();
					Adopt(*childCopy, rhs._vector[i]->first);
				}
			}
			else
			{
				newDatum = existingDatum;
			}
		}
		return *this;
	}

	Scope::Scope(Scope&& rhs) :
		_map(std::move(rhs._map)), _vector(std::move(rhs._vector)), _parent(rhs._parent)
	{
		for (size_t i = 0; i < _vector.Size(); ++i)
		{
			auto [key, datum] = *_vector[i];
			if (datum.Type() == DatumTypes::Table)
			{
				for (size_t j = 0; j < datum.Size(); ++j)
				{
					datum[j]._parent = this;
				}
			}
		}
		if (_parent != nullptr)
		{
			auto [datumPtr, indexDatum] = _parent->FindContainedScope(&rhs);
			datumPtr->Set(*this, indexDatum);
			rhs._parent = nullptr;
		}
	}

	Scope& Scope::operator=(Scope&& rhs)
	{
		Orphan();
		Clear();
		_map = std::move(rhs._map);
		_vector = std::move(rhs._vector);
		_parent = rhs._parent;

		for (size_t i = 0; i < _vector.Size(); ++i)
		{
			auto [key, datum] = *_vector[i];
			if (datum.Type() == DatumTypes::Table)
			{
				for (size_t j = 0; j < datum.Size(); ++j)
				{
					datum[j]._parent = this;
				}
			}
		}

		if (_parent != nullptr)
		{
			auto [datumPtr, indexDatum] = _parent->FindContainedScope(&rhs);
			datumPtr->Set(*this, indexDatum);
			rhs._parent = nullptr;
		}
		return *this;
	}

	void Scope::Clear()
	{
		for (size_t i = 0; i < _vector.Size(); ++i)
		{
			Datum datum = _vector[i]->second;
			if (datum.Type() == DatumTypes::Table)
			{
				for (size_t j = 0; j < datum.Size(); ++j)
				{
					delete& (datum[j]);
				}
			}
		}
		_vector.Clear();
		_map.Clear();
	}

	Datum* Scope::Find(const std::string& key)
	{
		Datum* pointer = nullptr;
		Hashmap<std::string, Datum>::Iterator it = _map.Find(key);
		if (it != _map.end())
		{
			pointer = &(it->second);
		}
		return pointer;
	}

	const Datum* Scope::Find(const std::string& key) const
	{
		const Datum* pointer = nullptr;
		Hashmap<std::string, Datum>::ConstIterator it = _map.Find(key);
		if (it != _map.end())
		{
			pointer = &(it->second);
		}
		return pointer;
	}

	Datum* Scope::Search(const std::string& key, Scope*& scope)
	{
		Datum* pointer = Find(key);
		if (pointer != nullptr)
		{
			scope = this;
			return (pointer);
		}

		if (_parent == nullptr)
		{
			scope = nullptr;
			return (nullptr);
		}
		
		return (_parent->Search(key, scope));
	}

	const Datum* Scope::Search(const std::string& key, const Scope*& scope) const
	{
		const Datum* pointer = Find(key);
		if (pointer != nullptr)
		{
			scope = this;
			return (pointer);
		}

		if (_parent == nullptr)
		{
			scope = nullptr;
			return (nullptr);
		}

		return (_parent->Search(key, scope));
	}

	Datum* Scope::Search(const std::string& key)
	{
		Scope* scope;
		return Search(key, scope);
	}

	const Datum* Scope::Search(const std::string& key) const
	{
		const Scope* scope;
		return Search(key, scope);
	}

	Datum& Scope::Append(const std::string& key)
	{
		auto insertReturn = _map.Insert(std::make_pair(key, Datum()));
		if (insertReturn.second)
		{
			_vector.PushBack(&*insertReturn.first);
		}
		return insertReturn.first->second;
	}

	Scope& Scope::AppendScope(const std::string& key)
	{
		auto insertReturn = _map.Insert(std::make_pair(key, Datum()));
		if (insertReturn.second)
		{
			_vector.PushBack(&*insertReturn.first);
		}
		if (insertReturn.first->second.Type() != DatumTypes::Table && insertReturn.first->second.Type() != DatumTypes::Unknown)
		{
			throw std::runtime_error("Datum type at this key is not type Table or Unknown");
		}
		Scope* scope = new Scope();
		scope->_parent = this;
		Append(key).PushBack(*scope);
		return *scope;
	}

	void Scope::Adopt(Scope& child, const std::string key)
	{
		if (child.IsAncestorOf(*this))
		{
			throw std::runtime_error("Cannot Adopt a scope that you are a descendant of");
		}
		if (&child == this)
		{
			throw std::runtime_error("Cannot Adopt yourself");
		}
			child.Orphan();
			Append(key).PushBack(child);
			child._parent = this;
	}

	std::pair<Datum*, std::size_t> Scope::FindContainedScope(const Scope* child)
	{
		for (size_t i = 0; i < _vector.Size(); ++i)
		{
			Datum& datum = _vector[i]->second;
			if (datum.Type() == DatumTypes::Table)
			{
				for (size_t j = 0; j < datum.Size(); ++j)
				{
					if (&(datum[j]) == child)
					{
						return { &(datum), j };
					}
				}
			}
		}

		return { nullptr, 0 };
	}

	void Scope::Orphan()
	{
		if (_parent != nullptr)
		{
			auto findResult = _parent->FindContainedScope(this);
			assert(findResult.first != nullptr);
			findResult.first->RemoveAt(findResult.second);
		}
	}

	Scope* Scope::Clone() const
	{
		return new Scope(*this);
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (this == &rhs)
		{
			return true;
		}
		
		if (_vector.Size() != rhs._vector.Size())
		{
			return false;
		}

		for (size_t index = 0; index < _vector.Size(); ++index)
		{
			auto [Key, lhsDatum] = *(_vector[index]);
			auto hashIt = rhs._map.Find(Key);
			if (hashIt == rhs._map.end() || lhsDatum != (*hashIt).second)
			{
				return false;
			}
		}
		return true;
	}

	bool Scope::operator!= (const Scope & rhs) const
	{
		return !operator==(rhs);
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (rhs->Is(Scope::TypeIdClass()))
		{
			return operator==(* reinterpret_cast<const Scope*> (rhs));
		}
		return false;
	}
}