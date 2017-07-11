#pragma once
#include <iostream>

namespace clsid
{
	class Document;
	class Reader
	{
	public:
		Reader(std::istream& in, Document& doc);
		
		~Reader()=default;

		Reader(const Reader&) = delete;

		Reader(Reader&&) = delete;

		Reader& operator=(const Reader&) = delete;

		Reader& operator=(Reader&&) = delete;

		bool Parse();
	private:
		std::istream& in_;
		Document& doc_;
	};


}