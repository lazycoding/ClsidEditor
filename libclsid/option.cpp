#include "option.h"
#include "exception.h"

using namespace std;

namespace clsid
{
	Option::Option(const std::string & key, const std::string & value)
		:name_(key), type_(OptionType::String)
	{
		Assign<string>(value);
	}
	Option::Option(const Option & source)
	{
		this->operator=(source);
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
			type_ = source.type_;
			switch (type_)
			{
			case OptionType::Boolean: CloneValue<bool>(source.value_); break;
			case OptionType::Number: CloneValue<long>(source.value_); break;
			case OptionType::String: CloneValue<string>(source.value_); break;
			case OptionType::StringArray: CloneValue<StringArray>(source.value_); break;
			case OptionType::XmlProp: CloneValue<XmlProp>(source.value_); break;
			case OptionType::Invalid:
			default:
				throw InvalidTypeException("Invalid option type");
				break;
			}
			
		}
		return *this;
	}
	Option & Option::operator=(Option && source)
	{
		if (this != &source)
		{
			name_ = source.name_;
			value_ = std::move(source.value_);
		}
		return *this;
	}
	Option::~Option()
	{
	}
	OptionType Option::GetType() const
	{
		return type_;
	}
	bool Option::operator==(const Option & other)
	{
		if (name_ != other.name_)
		{
			return false;
		}
		//TODO: compare value with same type
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

	Option & Option::operator=(double num)
	{	
		type_ = OptionType::Number;		
		Assign<double>(num);
		return *this;
	}

	Option& Option::operator=(int num)
	{
		type_ = OptionType::Number;
		Assign<int>(num);
		return *this;
	}

	Option & Option::operator=(bool boolean)
	{
		type_ = OptionType::Boolean;
		Assign<bool>(boolean);
		return *this;
	}

	Option & Option::operator=(const std::string & str)
	{
		type_ = OptionType::String;
		Assign<string>(str);
		return *this;
	}

	Option& Option::operator=(const char* ch)
	{
		type_ = OptionType::String;
		Assign<string>(std::string(ch));
		return *this;
	}

	Option & Option::operator=(const StringArray& vec)
	{
		type_ = OptionType::StringArray;
		Assign<StringArray>(vec);
		return *this;
	}

	Option& Option::operator=(const XmlProp& prop)
	{
		type_ = OptionType::XmlProp;
		Assign<XmlProp>(prop);
		return *this;
	}

}