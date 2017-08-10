#include "stdafx.h"
#include "reader.h"
#include "document.h"
using namespace clsid;

TEST(reader, load)
{
	std::string str = "[section]\nopt1=\"TRUE\"\nopt2=15";
	Document doc = Reader::Load(str);

	CHECK(doc["section"]["opt1"].Get<bool>() == true);
	CHECK_LONGS_EQUAL(15, doc["section"]["opt2"].Get<int>());
}