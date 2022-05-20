#include "pch.h"
#include "Foo.h"

using namespace std;

namespace UnitTests
{
	RTTI_DEFINITIONS(Foo)
		Foo::Foo(int32_t data) :
		mData(new int32_t(data))
	{
	}
	
	Foo::Foo() :
		mData(new int32_t(0))
	{
	}

	Foo::Foo(const Foo& other) :
		mData(new int32_t(*other.mData))
	{
	}

	Foo& Foo::operator=(const Foo& other)
	{
		if (this != &other)
		{
			*mData = *other.mData;
		}

		return *this;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	int32_t& Foo::Data()
	{
		return *mData;
	}

	const int32_t& Foo::Data() const
	{
		return *mData;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		if (mData == rhs.mData)
		{
			return true;
		}

		return (*mData == *rhs.mData);
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}

	std::string Foo::ToString() const
	{
		return to_string(*mData);
	}

	bool Foo::Equals(const RTTI* rhs) const
	{
		return this == rhs;
	}
}