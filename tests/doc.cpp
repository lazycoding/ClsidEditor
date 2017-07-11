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