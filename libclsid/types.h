#pragma once
#include "XmlProp.h"
#include "StringArray.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iterator>
#include <algorithm>
namespace clsid
{
	enum class OptionType { Boolean, Number, String, StringArray, XmlProp, Invalid };

	class OptionValueBase
	{
	public:
		virtual ~OptionValueBase() = default;
	};

	template<typename ValueType>
	class OptionValue :public OptionValueBase
	{
	public:
		OptionValue(ValueType val) :value_(val) {}

		virtual ~OptionValue() = default;

		ValueType GetValue() const
		{
			return value_;
		}

		void SetValue(ValueType val)
		{
			value_ = val;
		}

	private:
		ValueType value_;
	};

	template <typename ValueType>
	OptionType GetOptionEnumType()
	{
		using string_t = std::string;

		if (std::is_same<ValueType, bool>::value) {
			return OptionType::Boolean;
		}
		else if (std::is_same<ValueType, int64_t>::value) {
			return OptionType::Number;
		}
		else if (std::is_same<ValueType, uint64_t>::value) {
			return OptionType::Number;
		}
		else if (std::is_same<ValueType, double>::value) {
			return OptionType::Number;
		}
		else if (std::is_same<ValueType, int>::value) {
			return OptionType::Number;
		}
		else if (std::is_same<ValueType, long>::value) {
			return OptionType::Number;
		}
		else if (std::is_same<ValueType, string_t>::value ||
			std::is_same<ValueType, const char*>::value ||
			std::is_same<ValueType, char*>::value)
		{
			return OptionType::String;
		}
		else if (std::is_same<ValueType, StringArray>::value) {
			return OptionType::StringArray;
		}
		else if (std::is_same<ValueType, XmlProp>::value) {
			return OptionType::XmlProp;
		}
		else {
			return OptionType::Invalid;
		}
	}

	namespace convert
	{
		template<typename ActualType, typename ReturnType>
		class Convertor
		{
		public:
			static ReturnType GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				OptionValue<ActualType> *ptr = dynamic_cast<OptionValue<ActualType>*>(&*value);
				if (ptr == nullptr)
				{
					throw BadCastException("Cannot cast to requested type");
				}
				try
				{
					return static_cast<ReturnType>(ptr->GetValue());
				}
				catch (const std::exception& e)
				{
					throw BadCastException(e.what());
				}
			}
		};

		template<typename ActualType>
		class Convertor<ActualType, std::string>
		{
		public:
			static std::string GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				OptionValue<ActualType> *ptr = dynamic_cast<OptionValue<ActualType>*>(&*value);
				if (ptr == nullptr)
				{
					throw BadCastException("Cannot cast to requested type");
				}
				return to_string(ptr->GetValue());
			}
		};

		template<>
		class Convertor<XmlProp, int>
		{
		public:
			static int GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};

		template<>
		class Convertor<XmlProp, bool>
		{
		public:
			static bool GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};

		template<>
		class Convertor<XmlProp, StringArray>
		{
		public:
			static StringArray GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};

		template<>
		class Convertor<StringArray, XmlProp>
		{
		public:
			static XmlProp GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};

		template<>
		class Convertor<StringArray, int>
		{
		public:
			static int GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};

		template<>
		class Convertor<StringArray, bool>
		{
		public:
			static bool GetConvertedValue(const std::unique_ptr<OptionValueBase>& value)
			{
				throw BadCastException("Cannot cast to requested type");
			}
		};
	}
}