#include "stdafx.h"
#include "section.h"
using namespace clsid;

TEST(section, ctor_copy_assignment)
{
	Section s1("test");
	Section s2(s1);
	CHECK(s1 == s2);
	Section s3 = s1;
	CHECK(s1 == s3);
	Section s4(std::move(s1));
	CHECK(s1 == s4);
	Section s5 = std::move(s1);
	CHECK(s1 == s5);
}

TEST(section, add_remove_option)
{
	Section s("test");
	s.AddOption(Option("boolean", "true"));
	s.AddOption(Option("string", "xxxxx"));
	s.AddOption(Option("number", "15"));
	s.AddOption(Option("array", "{\"a1\",\"a2\"}"));
	s.AddOption(Option("xmlprop", "<x=\"y\", z=\"a\">"));
	
	CHECK_LONGS_EQUAL(5, s.Size());

	s.RemoveOption("boolean");

	CHECK_LONGS_EQUAL(4, s.Size());	
}
