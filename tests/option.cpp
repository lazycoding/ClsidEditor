#include "stdafx.h"
#include "option.h"
using namespace clsid;
TEST(option, ctor_and_copy_assignment)
{
	try
	{
		Option opt1("name of option", "value of option");

		Option opt2(opt1);
		CHECK(opt1 == opt2);

		Option opt3 = opt1;
		CHECK(opt1 == opt3);

		Option opt4(std::move(opt1));
		CHECK(opt1 == opt4);

		Option opt5 = std::move(opt1);
		CHECK(opt1 == opt5);
	}
	catch (const std::exception&)
	{
		
	}

}

TEST(option, get_value_type)
{
	CHECK(OptionType::String == GetOptionEnumType<std::string>());
	CHECK(OptionType::Number == GetOptionEnumType<int>());
	CHECK(OptionType::Boolean == GetOptionEnumType<bool>());
	CHECK(OptionType::XmlProp == GetOptionEnumType<XmlProp>());
	CHECK(OptionType::StringArray == GetOptionEnumType<StringArray>());
	CHECK(OptionType::Number == GetOptionEnumType<double>());
	CHECK(OptionType::String == GetOptionEnumType<const char*>());
	CHECK(OptionType::Invalid == GetOptionEnumType<char>());
}