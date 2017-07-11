#include "option.h"
#include "exception.h"
using namespace std;

namespace clsid
{
	Option::Option()
	{
	}
	Option::Option(const std::string & key, const std::string & raw_value)
		:name_(key), raw_(raw_value)
	{
	}
	Option::Option(const Option & source):Option(source.name_, source.raw_)
	{
		
	}
	Option::Option(Option && source)
	{
		this->operator=(source);
	}
	Option & Option::operator=(const Option & source)
	{
		if (this != &source)
		{
			name_ = source.name_;
			raw_ = source.raw_;
		}
		return *this;
	}
	Option & Option::operator=(Option && source)
	{
		if (this != &source)
		{
			name_ = std::move(source.name_);
			raw_ = std::move(source.raw_);
		}
		return *this;
	}
	Option::~Option()
	{
	}
	bool Option::operator==(const Option & other)
	{
		if (name_ != other.name_ || raw_ != other.raw_)
		{
			return false;
		}
		return true;
	}
	bool Option::operator!=(const Option & other)
	{
		return !this->operator==(other);
	}

	const std::string& Option::Name() const
	{
		return name_;
	}
}