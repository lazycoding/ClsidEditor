#ifndef CLSID_STRING_UTILS_H__
#define CLSID_STRING_UTILS_H__
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iostream>
#include <sstream>

namespace clsid {
	class XmlProp;
	class StringArray;

	namespace string_utils
	{
		std::string TrimLeft(const std::string& str);

		std::string TrimRight(const std::string& str);

		std::string Trim(const std::string& str);

		bool StartsWith(const std::string& str, const std::string& search);

		bool EndsWith(const std::string& str, const std::string& search);

		std::vector<std::string> Split(const std::string &str, char delim);

		std::string TrimWith(const std::string & str, char delim);

		template <typename ReturnType> ReturnType ParseString(const std::string &value, const std::string &option_name)
		{
			throw invalid_type_exception("Invalid option type");
		}

		template <> std::string ParseString<std::string>(const std::string &value, const std::string &);
		
		template <> bool ParseString<bool>(const std::string &value, const std::string &option_name);

		template <> int ParseString<int>(const std::string &value, const std::string &option_name);
	
		namespace clsid_std
		{
			using std::to_string;
		}
	}
}
#endif // !CLSID_STRING_UTILS_H__


