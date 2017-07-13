#include "stdafx.h"
#include "document.h"
#include <memory>

using namespace clsid;

TEST(document, ctor_move_assignment)
{
	Document doc1;
	
	Document doc2(doc1);
	CHECK(doc1 == doc2);

	Document doc3 = doc1;
	CHECK(doc1 == doc3);

	Document doc4(std::move(doc1));
	CHECK(doc1 == doc4);

	Document doc5 = std::move(doc1);
	CHECK(doc1 == doc5);
}



TEST(document, add_remove_section)
{
	Document doc;
	doc.AddSection("test");
	CHECK_LONGS_EQUAL(1, doc.Size());
	doc.AddSection(Section("test2"));
	CHECK_LONGS_EQUAL(2, doc.Size());
	CHECK(doc.Contains("test"));
	CHECK(doc.Contains("test2"));
	doc.RemoveSection("test");
	CHECK(!doc.Contains("test"));
	CHECK_LONGS_EQUAL(1, doc.Size());
}


TEST(document, get_section)
{
	Document doc;
	doc.AddSection("test");	
	doc.AddSection("test2");
	
	Section& sec = doc[0];
	CHECK(sec.Name() == "test");
	const Section& sec2 = doc["test2"];
	CHECK(sec2.Name() == "test2");
}

TEST(document, iterator)
{
	Document doc;
	doc.AddSection("test");
	doc.AddSection("test2");

	auto beg = doc.begin();
	CHECK(beg->Name() == "test");
	auto end = doc.end();
	CHECK(end != beg);

	for (auto& sec : doc)
	{
		CHECK(!sec.Name().empty());
	}
}