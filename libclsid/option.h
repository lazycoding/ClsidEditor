#ifndef CLSID_OPTION_H__
#define CLSID_OPTION_H__
#include "exception.h"
#include "string_utils.h"
#include "XmlProp.h"
#include "StringArray.h"
#include "types.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iterator>
#include <algorithm>
namespace clsid
{		
    class Option
    {
	public:
		Option() = delete;

		Option(const std::string& key, const std::string& value = "");

		Option(const Option& source);

		Option(Option&& source);

		Option& operator=(const Option& source);

		Option& operator=(Option&& source);

		~Option();
		
		template<typename ValueType>
		void Set(ValueType val)
		{
			this->operator=(val);
		}

		template<typename ReturnType>
		ReturnType Get()
		{
			if (!value_)
			{
				throw NotFoundException("Not found");
			}

			return ConvertValue<ReturnType>(type_, value_);
		}

		OptionType GetType() const;
		
		bool operator==(const Option& other);
		
		bool operator!=(const Option& other);

		const std::string& Name() const;

		Option& operator=(double num);

		Option& operator=(int num);

		Option& operator=(const char* ch);

		Option& operator=(bool boolean);

		Option& operator=(const std::string& str);

		Option& operator=(const StringArray& vec);

		Option& operator=(const XmlProp& vec);

    private:
		template<typename ValueType>
		void Assign(ValueType val)
		{
			if (GetOptionEnumType<ValueType>() != type_)
			{
				throw std::logic_error("wrong type");
			}
			auto ptr = std::make_unique<OptionValue<ValueType>>(val);
			value_ = std::move(ptr);
		}

		template<typename ValueType>
		void CloneValue(const std::unique_ptr<OptionValueBase>& opt)
		{
			OptionValue<ValueType>* ptr = dynamic_cast<OptionValue<ValueType>*>(&*opt);
			if (ptr!=nullptr)
			{
				auto new_ptr = std::make_unique<OptionValue<ValueType>>(ptr->GetValue());
				value_ = std::move(new_ptr);
			}
		}

		template<typename ValueType>
		bool Compare(const std::unique_ptr<OptionValueBase>& first, const std::unique_ptr<OptionValueBase>& second)
		{
			OptionValue<ValueType>* fst = dynamic_cast<OptionValue<ValueType>*>(&*first);
			OptionValue<ValueType>* sed = dynamic_cast<OptionValue<ValueType>*>(&*second);
			return fst->GetValue() == sed->GetValue();
		}

		template<typename ReturnType>
		ReturnType ConvertValue(OptionType source_type, const std::unique_ptr<OptionValueBase>& value)
		{
			using convert::Convertor;
			switch (source_type)
			{
			case clsid::OptionType::Boolean:
				return Convertor<bool, ReturnType>::GetConvertedValue(value);
				break;
			case clsid::OptionType::Number:
				return Convertor<int, ReturnType>::GetConvertedValue(value);
				break;
			case clsid::OptionType::String:
			{
				OptionValue<string> *ptr = dynamic_cast<OptionValue<string>*>(&*value);
				if (ptr==nullptr)
				{
					throw BadCastException("Cannot cast to requested type");
				}
				try
				{
					return string_utils::ParseString<ReturnType>(ptr->GetValue(), Name());
				}
				catch (const InvalidTypeException& e)
				{
					throw BadCastException(e.what());
				}
			}
				break;
			case clsid::OptionType::StringArray:
				return Convertor<StringArray, ReturnType>::GetConvertedValue(value);
				break;
			case clsid::OptionType::XmlProp:
				return Convertor<XmlProp, ReturnType>::GetConvertedValue(value);
				break;
			case clsid::OptionType::Invalid:				
			default:
				throw InvalidTypeException("Invalid option type");
				break;
			}
		}

        std::string name_;
		OptionType type_;
		std::unique_ptr<OptionValueBase> value_;
    };    
}

#endif //CLSID_OPTION_H__