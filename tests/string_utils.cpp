#include "stdafx.h"
#include <string>
#include "string_utils.h"
using namespace std;
using namespace clsid;
using namespace string_utils;

TEST(string_utils, trim)
{
	string str = "";
	CHECK("" == Trim(str));

	str = " A";
	CHECK("A" == Trim(str));

	str = "A ";
	CHECK("A" == Trim(str));

	str = " A ";
	CHECK("A" == Trim(str));

	str = " A B ";
	CHECK("A B" == Trim(str));

	str = "          A             ";
	CHECK("A" == Trim(str));

	str = "                       ";
	CHECK("" == Trim(str));

	str = "\r\nA\r\n";
	CHECK("A" == Trim(str));
}

TEST(string_utils, starts_with)
{
	string str = "";
	CHECK(true == StartsWith(str, ""));

	str = " ";
	CHECK(true==StartsWith(str, " "));

	str = "A";
	CHECK(true==StartsWith(str, ""));

	str = "A";
	CHECK(true==StartsWith(str, "A"));

	str = "ABCD";
	CHECK(false==StartsWith(str, "BC"));

	str = "ABCD";
	CHECK(false==StartsWith(str, "BCD"));

	str = " ABCD ";
	CHECK(false==StartsWith(str, "ABCD"));

	str = "ABCD";
	CHECK(false==StartsWith(str, "ABCDEFGH"));

	str = "Hello World!";
	CHECK(true==StartsWith(str, "Hello"));

	str = "Hello World!";
	CHECK(false==StartsWith(str, "World!"));
}

TEST(string_utils, ends_with)
{
	string str = "";
	CHECK(true==EndsWith(str, ""));

	str = " ";
	CHECK(true==EndsWith(str, " "));

	str = "A";
	CHECK(true==EndsWith(str, ""));

	str = "A";
	CHECK(true==EndsWith(str, "A"));

	str = "ABCD";
	CHECK(false==EndsWith(str, "BC"));

	str = "ABCD";
	CHECK(false==EndsWith(str, "ABC"));

	str = " ABCD ";
	CHECK(false==EndsWith(str, "ABCD"));

	str = "ABCD";
	CHECK(false==EndsWith(str, "ABCDEFGH"));

	str = "Hello World!";
	CHECK(true==EndsWith(str, "World!"));

	str = "Hello World!";
	CHECK(false==EndsWith(str, "Hello"));
}