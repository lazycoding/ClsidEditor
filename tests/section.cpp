#include "stdafx.h"
#include "section.h"
using namespace clsid;

TEST(section, ctor_copy_assignment)
{
	Section s1;
	Section s2(s1);
	CHECK(s1 == s2);
	Section s3 = s1;
	CHECK(s1 == s3);
	Section s4(std::move(s1));
	CHECK(s1 == s4);
	Section s5 = std::move(s1);
	CHECK(s1 == s5);
}