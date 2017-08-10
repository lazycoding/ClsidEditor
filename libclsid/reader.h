#pragma once
#include <iostream>

namespace clsid
{
	class Document;
	class Reader
	{
	public:
		Reader() = delete;
		
		~Reader() = delete;

		Reader(const Reader&) = delete;

		Reader(Reader&&) = delete;

		Reader& operator=(const Reader&) = delete;

		Reader& operator=(Reader&&) = delete;

		static Document Load(std::istream& stream);

		static Document Load(const std::string& context);

		static Document LoadFile(const std::string& path);

	private:
		static Document InternalLoad(std::istream& stream);

		static std::string DeleteComment(const std::string& content);

		static std::string UnEscape(const std::string &str);

		static size_t find_first_nonescaped(const std::string &str, char ch);

		static bool TryToNumber(const std::string& str, int* target);
	};


}