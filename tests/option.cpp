#include "stdafx.h"
#include "option.h"
using namespace clsid;
TEST(option, ctor_and_copy_assignment)
{
	Option opt1;

	Option opt2(opt1);
	CHECK(opt1 == opt2);

	Option opt3 = opt1;
	CHECK(opt1 == opt3);

	Option opt4(std::move(opt1));
	CHECK(opt1 == opt4);

	Option opt5=std::move(opt1);
	CHECK(opt1 == opt5);
}

