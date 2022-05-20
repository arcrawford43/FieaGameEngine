#include "pch.h"
#include "Datum.h"
#include <assert.h>
#include <stdexcept>
#include "glm/gtx/string_cast.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace FieaGameEngine
{
	const std::size_t Datum::DatumTypeSizes[]
	{
		0, //UNKNOWN
		sizeof(std::int32_t),
		sizeof(float),
		sizeof(glm::vec4),
		sizeof(glm::mat4),
		sizeof(std::string),
		sizeof(Scope*),
		sizeof(RTTI*)
	};

	Datum::~Datum()
	{
		if (_isExternalStorage == false)
		{
			Clear();
			free(_data.vp);
		}
	}

	Datum::Datum(const Datum& other) :
		_type(other._type), _isExternalStorage(other._isExternalStorage)
	{
		if (other._isExternalStorage == true)
		{
			_capacity = _size = other._size;
			_data.vp = other._data.vp;
		}
		else
		{
			if (other._capacity != 0)
			{
				Reserve(other._capacity);
			}

			if (_type == DatumTypes::String)
			{
				for (std::size_t index = 0; index < other._size; ++index)
				{
					PushBack(other.GetString(index));
				}
			}
			else
			{
				std::memcpy(_data.vp, other._data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * other._size);
				_size = other._size;
			}
		}
	}

	Datum& Datum::operator=(const Datum& other)
	{
		if (this != &other)
		{
			if (_isExternalStorage)
			{
				_data.vp = nullptr;
				_size = 0;
			}
			else
			{
				Clear();
			}

			_type = other._type;
			_isExternalStorage = other._isExternalStorage;

			if (other._isExternalStorage == true)
			{
				free(_data.vp);
				_capacity = _size = other._size;
				_data.vp = other._data.vp;
			}
			else
			{
				void* tempData = realloc(_data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * other._capacity);
				assert(tempData != nullptr);
				_data.vp = tempData;
				_capacity = other._capacity;

				if (_type == DatumTypes::String)
				{
					for (std::size_t index = 0; index < other._size; ++index)
					{
						PushBack(other.GetString(index));
					}
				}
				else
				{
					std::memcpy(_data.vp, other._data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * other._size);
					_size = other._size;
				}
			}
		}
		return *this;
	}

	Datum::Datum(Datum&& rhs) noexcept :
		_data(rhs._data), _capacity(rhs._capacity), _size(rhs._size), _type(rhs._type), _isExternalStorage(rhs._isExternalStorage)
	{
		if (_isExternalStorage == false)
		{
			rhs._size = _capacity = 0;
			rhs._data.vp = nullptr;
		}
	}


	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (_isExternalStorage == false)
		{
			Clear();
			free(_data.vp);
		}
		_size = rhs._size;
		_capacity = rhs._capacity;
		_data.vp = rhs._data.vp;
		_isExternalStorage = rhs._isExternalStorage;
		_type = rhs._type;

		if (_isExternalStorage == false)
		{
			rhs._size = _capacity = 0;
			rhs._data.vp = nullptr;
		}

		return *this;
	}

	Datum::Datum(std::int32_t value)
	{
		PushBack(value);
	}

	Datum::Datum(float value)
	{
		PushBack(value);
	}

	Datum::Datum(const glm::vec4& value)
	{
		PushBack(value);
	}

	Datum::Datum(const glm::mat4& value)
	{
		PushBack(value);
	}

	Datum::Datum(const std::string& value)
	{
		PushBack(value);
	}

	Datum::Datum(std::string&& value)
	{
		PushBack(value);
	}

	Datum::Datum(RTTI& value)
	{
		PushBack(value);
	}

	Datum::Datum(RTTI* value)
	{
		PushBack(*value);
	}

	Datum::Datum(Scope& value)
	{
		PushBack(value);
	}

	Datum& Datum::operator=(std::int32_t value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Integer;
		}

		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(float value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Float;
		}

		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Vector;
		}

		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Matrix;
		}

		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(const std::string& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::String;
		}

		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(std::string&& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::String;
		}

		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(RTTI& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Pointer;
		}

		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(RTTI* value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Pointer;
		}

		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(*value);
			break;

		case 1:
			Set(*value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	Datum& Datum::operator=(Scope& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			_type = DatumTypes::Table;
		}

		if (_type != DatumTypes::Table)
		{
			throw std::runtime_error("Cannot call this operator with this type of Datum");
		}

		switch (_size)
		{
		case 0:
			PushBack(value);
			break;

		case 1:
			Set(value);
			break;

		default:
			throw std::runtime_error("Cannot call this operator with size that is greater than 1");
		}

		return *this;
	}

	bool Datum::operator==(const Datum& other) const
	{
		bool isEqual = false;

		if (_type == other._type && _size == other._size)
		{
			if (_type == DatumTypes::String)
			{
				isEqual = true;
				for (std::size_t index = 0; index < _size; ++index)
				{
					if (_data.s[index] != other._data.s[index])
					{
						isEqual = false;
						break;
					}
				}
			}
			else if (_type == DatumTypes::Pointer || _type == DatumTypes::Table)
			{
				isEqual = true;
				for (std::size_t index = 0; index < _size; ++index)
				{
					if (_data.r[index] != other._data.r[index] &&(_data.r[index] == nullptr || other._data.r[index] == nullptr || !_data.r[index]->Equals(other._data.r[index])))
					{
						isEqual = false;
						break;
					}
				}
			}
			else
			{
				isEqual = !std::memcmp(_data.vp, other._data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * _size);
			}
		}
		return isEqual;
	}

	bool Datum::operator!=(const Datum& other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(std::int32_t other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::Integer)
		{
			isEqual = *_data.i == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(std::int32_t other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(float other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::Float)
		{
			isEqual = *_data.f == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(float other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(const glm::vec4& other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::Vector)
		{
			isEqual = *_data.v == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(const glm::vec4& other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(const glm::mat4& other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::Matrix)
		{
			isEqual = *_data.m == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(const glm::mat4& other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(const std::string& other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::String)
		{
			isEqual = *_data.s == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(const std::string& other) const
	{
		return !(*this == other);
	}

	bool Datum::operator==(RTTI* other) const
	{
		bool isEqual = false;

		if (_size == 1 && _type == DatumTypes::Pointer)
		{
			isEqual = *_data.r == other;
		}

		return isEqual;
	}

	bool Datum::operator!=(RTTI* other) const
	{
		return !(*this == other);
	}

	void Datum::Reserve(std::size_t capacity)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot reserve for a Datum with an Unknown type");
		}
		if (capacity > _capacity)
		{
			void* tempData =realloc(_data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * capacity);
			assert(tempData != nullptr);
			_data.vp = tempData;
			_capacity = capacity;
		}
	}

	void Datum::SetType(DatumTypes type)
	{
		if (_type != DatumTypes::Unknown)
		{
			if (_type != type)
			{
				throw std::runtime_error("Cannot change type of datum that is not Unknown");
			}
		}
		else
		{
			if (type == DatumTypes::Unknown)
			{
				throw std::runtime_error("Cannot set type to be Unknown");
			}

			_type = type;
		}
	}

	void Datum::Resize(std::size_t size)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot resize a datum with an Unknown type");
		}

		if (_type == DatumTypes::String)
		{
			while (_size > size)
			{
				PopBack();
			}
		}

		if (size != _capacity)
		{
			void* tempData = realloc(_data.vp, DatumTypeSizes[static_cast<std::size_t>(_type)] * size);
			assert(tempData != nullptr);
			_data.vp = tempData;
			_capacity = size;
		}

		if (_type == DatumTypes::String)
		{
			while (_size < size)
			{
				PushBack("");
			}
		}
		else if(_size < size)
		{
			std::size_t sizeType = DatumTypeSizes[static_cast<std::size_t>(_type)];
			memset(_data.b + (sizeType * (_size)), 0, (size - _size) * sizeType);
		}
		_size = size;
	}

	void Datum::Set(std::int32_t value, std::size_t index)
	{
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum type is not Integer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.i[index] = value;
	}

	void Datum::Set(float value, std::size_t index)
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Datum type is not Float");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.f[index] = value;
	}

	void Datum::Set(const glm::vec4& value, std::size_t index)
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum type is not Vector");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.v[index] = value;
	}

	void Datum::Set(const glm::mat4& value, std::size_t index)
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum type is not Matrix");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.m[index] = value;
	}

	void Datum::Set(const std::string& value, std::size_t index)
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Datum type is not String");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.s[index] = value;
	}

	void Datum::Set(std::string&& value, std::size_t index)
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Datum type is not String");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.s[index] = std::move(value);
	}

	void Datum::Set(RTTI& value, std::size_t index)
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum type is not Pointer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.r[index] = &value;
	}

	void Datum::Set(Scope& value, std::size_t index)
	{
		if (_type != DatumTypes::Table)
		{
			throw std::runtime_error("Datum type is not Table");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}

		_data.t[index] = &value;
	}

	std::int32_t& Datum::GetInteger(std::size_t index)
	{
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum type is not Integer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.i[index];
	}

	std::int32_t Datum::GetInteger(std::size_t index) const
	{
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Datum type is not Integer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.i[index];
	}

	float& Datum::GetFloat(std::size_t index)
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Datum type is not Float");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.f[index];
	}

	float Datum::GetFloat(std::size_t index) const
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Datum type is not Float");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.f[index];
	}

	glm::vec4& Datum::GetVector(std::size_t index)
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum type is not Vector");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.v[index];
	}

	const glm::vec4& Datum::GetVector(std::size_t index) const
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Datum type is not Vector");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.v[index];
	}

	glm::mat4& Datum::GetMatrix(std::size_t index)
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum type is not Matrix");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.m[index];
	}

	const glm::mat4& Datum::GetMatrix(std::size_t index) const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Datum type is not Matrix");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.m[index];
	}

	std::string& Datum::GetString(std::size_t index)
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Datum type is not String");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.s[index];
	}

	const std::string& Datum::GetString(std::size_t index) const
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Datum type is not String");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.s[index];
	}

	RTTI*& Datum::GetPointer(std::size_t index)
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum type is not Pointer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.r[index];
	}

	const RTTI* Datum::GetPointer(std::size_t index) const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Datum type is not Pointer");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.r[index];
	}

	Scope*& Datum::GetTable(std::size_t index)
	{
		if (_type != DatumTypes::Table)
		{
			throw std::runtime_error("Datum type is not Table");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.t[index];
	}

	const Scope* Datum::GetTable(std::size_t index) const
	{
		if (_type != DatumTypes::Table)
		{
			throw std::runtime_error("Datum type is not Table");
		}
		if (_size <= index)
		{
			throw std::out_of_range("Index is not a valid index in Datum");
		}
		return _data.t[index];
	}

	void Datum::PushBack(std::int32_t value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Integer);
		}
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Must be type Integer to insert an integer");
		}
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
		new(_data.i + _size) std::int32_t{ value };
		++_size;
	}

	void Datum::PushBack(float value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Float);
		}
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Must be type Float to insert a float");
		}
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
		new(_data.f + _size) float{ value };
		++_size;
	}

	void Datum::PushBack(const glm::vec4& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Vector);
		}
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Must be type Vector to insert a vec4");
		}
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
		new(_data.v + _size) glm::vec4{ value };
		++_size;
	}

	void Datum::PushBack(const glm::mat4& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Matrix);
		}
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Must be type Matrix to insert a mat4");
		}
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
		new(_data.m + _size) glm::mat4{ value };
		++_size;
	}

	void Datum::PushBack(const std::string& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::String);
		}
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Must be type String to insert a string");
		}
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
		new(_data.s + _size) std::string{ value };
		++_size;
	}

	void Datum::PushBack(std::string&& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::String);
		}
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Must be type String to insert a string");
		}
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
		new(_data.s + _size) std::string{ std::move(value) };
		++_size;
	}

	void Datum::PushBack(RTTI& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Pointer);
		}
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Must be type Pointer to insert a RTTI pointer");
		}
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

		new(_data.r + _size) RTTI*{ &value };
		++_size;
	}

	void Datum::PushBack(Scope& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Table);
		}
		if (_type != DatumTypes::Table)
		{
			throw std::runtime_error("Must be type Table to insert a Scope pointer");
		}
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

		new(_data.r + _size) Scope* { &value };
		++_size;
	}

	void Datum::PopBack()
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot PopBack on Unknown Type");
		}
		if (_size > 0)
		{
			if (_type == DatumTypes::String)
			{
				destroy_at(_data.s + _size - 1);
			}
			--_size;
		}
	}

	std::int32_t& Datum::FrontInteger()
	{
		return GetInteger();
	}

	std::int32_t Datum::FrontInteger() const
	{
		return GetInteger();
	}

	float& Datum::FrontFloat()
	{
		return GetFloat();
	}

	float Datum::FrontFloat() const
	{
		return GetFloat();
	}

	glm::vec4& Datum::FrontVector()
	{
		return GetVector();
	}

	const glm::vec4& Datum::FrontVector() const
	{
		return GetVector();
	}

	glm::mat4& Datum::FrontMatrix()
	{
		return GetMatrix();
	}

	const glm::mat4& Datum::FrontMatrix() const
	{
		return GetMatrix();
	}

	std::string& Datum::FrontString()
	{
		return GetString();
	}

	const std::string& Datum::FrontString() const
	{
		return GetString();
	}

	RTTI*& Datum::FrontPointer()
	{
		return GetPointer();
	}

	const RTTI* Datum::FrontPointer() const
	{
		return GetPointer();
	}

	std::int32_t& Datum::BackInteger()
	{
		return GetInteger(_size - 1);
	}

	std::int32_t Datum::BackInteger() const
	{
		return GetInteger(_size - 1);
	}

	float& Datum::BackFloat()
	{
		return GetFloat(_size - 1);
	}

	float Datum::BackFloat() const
	{
		return GetFloat(_size - 1);
	}

	glm::vec4& Datum::BackVector()
	{
		return GetVector(_size - 1);
	}

	const glm::vec4& Datum::BackVector() const
	{
		return GetVector(_size - 1);
	}

	glm::mat4& Datum::BackMatrix()
	{
		return GetMatrix(_size - 1);
	}

	const glm::mat4& Datum::BackMatrix() const
	{
		return GetMatrix(_size - 1);
	}

	std::string& Datum::BackString()
	{
		return GetString(_size - 1);
	}

	const std::string& Datum::BackString() const
	{
		return GetString(_size - 1);
	}

	RTTI*& Datum::BackPointer()
	{
		return GetPointer(_size - 1);
	}

	const RTTI* Datum::BackPointer() const
	{
		return GetPointer(_size - 1);
	}

	bool Datum::Remove(std::int32_t value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Needs a Integer type Datum to remove an integer");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.i[index] == value)
			{
				std::memcpy(_data.i + index, _data.i + index + 1, (_size - index - 1) * sizeof(std::int32_t));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::Remove(float value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Needs a Float type Datum to remove a float");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.f[index] == value)
			{
				std::memcpy(_data.f + index, _data.f + index + 1, (_size - index - 1) * sizeof(float));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::Remove(const glm::vec4& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Needs a Vector type Datum to remove a vector");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.v[index] == value)
			{
				std::memcpy(_data.v + index, _data.v + index + 1, (_size - index - 1) * sizeof(glm::vec4));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::Remove(const glm::mat4& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Needs a Matrix type Datum to remove a matrix");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.m[index] == value)
			{
				std::memcpy(_data.m + index, _data.m + index + 1, (_size - index - 1) * sizeof(glm::mat4));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::Remove(const std::string& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Needs a String type Datum to remove a string");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.s[index] == value)
			{
				destroy_at(_data.s + index);
				std::memcpy(_data.s + index, _data.s + index + 1, (_size - index - 1) * sizeof(std::string));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::Remove(const RTTI& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Needs a Pointer type Datum to remove a pointer");
		}

		bool didRemove = false;
		for (std::size_t index = 0; index < _size; ++index)
		{
			if (_data.r[index] == &value)
			{
				std::memcpy(_data.r + index, _data.r + index + 1, (_size - index - 1) * sizeof(RTTI*));
				--_size;
				didRemove = true;
				break;
			}
		}
		return didRemove;
	}

	bool Datum::RemoveAt(std::size_t index)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}

		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Cannot remove from a datum with an Unknown type");
		}
		
		bool didRemove = false;
		if (index < _size)
		{
			didRemove = true;
			if (_type == DatumTypes::String)
			{
				destroy_at(_data.s + index);
			}
			std::size_t typeSize = DatumTypeSizes[static_cast<std::size_t>(_type)];
			std::memcpy(_data.b + (index * typeSize), _data.b + ((index + 1) * typeSize), (_size - index - 1) * typeSize);
			--_size;
		}
		return didRemove;
	}

	std::pair<std::size_t, bool> Datum::Find(std::int32_t value) const
	{
		if (_type != DatumTypes::Integer)
		{
			throw std::runtime_error("Needs a Integer type Datum to find an integer");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.i[index] == value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::pair<std::size_t, bool> Datum::Find(float value) const
	{
		if (_type != DatumTypes::Float)
		{
			throw std::runtime_error("Needs a Float type Datum to find a float");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.f[index] == value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::pair<std::size_t, bool> Datum::Find(const glm::vec4& value) const
	{
		if (_type != DatumTypes::Vector)
		{
			throw std::runtime_error("Needs a Vector type Datum to find a vector");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.v[index] == value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::pair<std::size_t, bool> Datum::Find(const glm::mat4& value) const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw std::runtime_error("Needs a Matrix type Datum to find a matrix");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.m[index] == value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::pair<std::size_t, bool> Datum::Find(const std::string& value) const
	{
		if (_type != DatumTypes::String)
		{
			throw std::runtime_error("Needs a String type Datum to find a string");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.s[index] == value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::pair<std::size_t, bool> Datum::Find(const RTTI& value) const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw std::runtime_error("Needs a Pointer type Datum to find a pointer");
		}

		bool didFind = false;
		std::size_t index;
		for (index = 0; index < _size; ++index)
		{
			if (_data.r[index] == &value)
			{
				didFind = true;
				break;
			}
		}
		return { index, didFind };
	}

	std::string Datum::ToString(std::size_t index) const
	{
		std::string str;
		switch (_type)
		{
		case DatumTypes::Integer :
			str = std::to_string(GetInteger(index));
			break;

		case DatumTypes::Float :
			str = std::to_string(GetFloat(index));
			break;

		case DatumTypes::Vector :
			str = glm::to_string(GetVector(index));
			break;

		case DatumTypes::Matrix :
			str = glm::to_string(GetMatrix(index));
			break;

		case DatumTypes::String :
			str = GetString(index);
			break;

		case DatumTypes::Pointer:
		{
			const RTTI* pointer = GetPointer(index);
			if (pointer == nullptr)
			{
				throw std::runtime_error("Cannot dereference nullptr");
			}
			str = pointer->ToString();
			break;
		}

		default :
			throw std::runtime_error("Cannot call ToString on Datum with Unknown type");
		}
		return str;
	}

	void Datum::SetFromString(const std::string& value, std::size_t index)
	{	
		switch (_type)
		{
		case DatumTypes::Integer :
			Set(std::stoi(value), index);
			break;

		case DatumTypes::Float :
			Set(std::stof(value), index);
			break;

		case DatumTypes::Vector :
			float vecArray[4];
			sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &vecArray[0], &vecArray[1], &vecArray[2], &vecArray[3]);
			Set(glm::make_vec4(vecArray), index);
			break;

		case DatumTypes::Matrix :
			float matArray[16];
			sscanf_s(value.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
				&matArray[0], &matArray[1], &matArray[2], &matArray[3], &matArray[4], &matArray[5], &matArray[6], &matArray[7],
				&matArray[8], &matArray[9], &matArray[10], &matArray[11], &matArray[12], &matArray[13], &matArray[14], &matArray[15]);
			Set(glm::make_mat4(matArray), index);
			break;

		case DatumTypes::String :
			Set(value, index);
			break;

		default :
			throw std::runtime_error("Not a valid type to use FromString operations on");
		}
	}

	void Datum::PushBackFromString(const std::string& value)
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Cannot PushBack when using external storage");
		}

		switch (_type)
		{
		case DatumTypes::Integer:
			PushBack(std::stoi(value));
			break;

		case DatumTypes::Float:
			PushBack(std::stof(value));
			break;

		case DatumTypes::Vector:
			float vecArray[4];
			sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &vecArray[0], &vecArray[1], &vecArray[2], &vecArray[3]);
			PushBack(glm::make_vec4(vecArray));
			break;

		case DatumTypes::Matrix:
			float matArray[16];
			sscanf_s(value.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
				&matArray[0], &matArray[1], &matArray[2], &matArray[3], &matArray[4], &matArray[5], &matArray[6], &matArray[7],
				&matArray[8], &matArray[9], &matArray[10], &matArray[11], &matArray[12], &matArray[13], &matArray[14], &matArray[15]);
			PushBack(glm::make_mat4(matArray));
			break;

		case DatumTypes::String:
			PushBack(value);
			break;

		default:
			throw std::runtime_error("Not a valid type to use FromString operations on");
		}
	}

	void Datum::Clear()
	{
		if (_isExternalStorage)
		{
			throw std::runtime_error("Invalid operation on a Datum with external storage");
		}
		if (_type == DatumTypes::String)
		{
			for (std::size_t index = 0; index < _size; ++index)
			{
				destroy_at(_data.s + index);
			}
		}
		_size = 0;
	}

	void Datum::SetStorage(std::int32_t* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Integer);
		_data.i = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(float* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Float);
		_data.f = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(glm::vec4* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Vector);
		_data.v = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(glm::mat4* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Matrix);
		_data.m = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(std::string* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::String);
		_data.s = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(RTTI** data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Pointer);
		_data.r = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(Scope** data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		SetType(DatumTypes::Table);
		_data.t = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	void Datum::SetStorage(void* data, std::size_t size)
	{
		if (_capacity != 0 && _isExternalStorage == false)
		{
			throw std::runtime_error("Cannot change datum with internal storage to become an extneral storage Datum");
		}
		if (data == nullptr)
		{
			throw std::runtime_error("Cannot give a nullptr for external storage");
		}
		_data.vp = data;
		_isExternalStorage = true;
		_size = _capacity = size;
	}

	Scope& Datum::operator[](std::size_t index)
	{ 
		return *GetTable(index); 
	}

}