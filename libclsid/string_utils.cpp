#include "string_utils.h"
#include "exception.h"

namespace clsid
{
	namespace string_utils
	{
		std::string TrimLeft(const std::string & str)
		{
			auto front = std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); });
			return std::string(front, str.end());
		}
		std::string TrimRight(const std::string & str)
		{
			auto back = std::find_if(str.rbegin(), str.rend(), [](int ch) {return !std::isspace(ch); }).base();
			return std::string(str.begin(), back);
		}
		std::string Trim(const std::string & str)
		{
			auto front = std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); });
			auto back = std::find_if(str.rbegin(), str.rend(), [](int ch) {return !std::isspace(ch); }).base();
			if (back <= front)
			{
				return "";
			}
			return std::string(front, back);
		}

		std::string TrimWith(const std::string & str, char delim)
		{
			auto front = std::find_if(str.begin(), str.end(), [&](int ch) { return ch != (int)delim; });
			auto back = std::find_if(str.rbegin(), str.rend(), [&](int ch) {return ch != (int)delim; }).base();
			if (back <= front)
			{
				return "";
			}
			return std::string(front, back);
		}

		bool StartsWith(const std::string & str, const std::string & search)
		{
			auto search_length = search.length();
			if (search_length > str.length())
			{
				return false;
			}
			for (size_t i = 0; i < search_length; i++)
			{
				if (search[i] != str[i])
					return false;
			}
			return true;
		}
		bool EndsWith(const std::string & str, const std::string & search)
		{
			auto search_length = search.length();
			auto str_length = str.length();
			if (search_length > str_length)
			{
				return false;
			}
			auto start_pos = str_length - search_length;
			for (size_t i = 0; i < search_length; i++)
			{
				//if (search[search_length - 1 - i] != str[str_length - 1 - i])
				if(search[i] != str[start_pos + i])
					return false;
			}
			return true;
		}

		std::vector<std::string> Split(const std::string &str, char delim)
		{
			std::vector<std::string> result;
			std::stringstream stream(str);
			std::string item;

			while (std::getline(stream, item, delim)) {
				result.push_back(item);
			}
			return result;
		}

		template <> std::string ParseString<std::string>(const std::string &value, const std::string &)
		{
			return value;
		}

		template <> bool ParseString<bool>(const std::string &value, const std::string &option_name)
		{
			if (_stricmp(value.c_str(), "false")==0) {
				return false;
			}
			else if (_stricmp(value.c_str(), "true")==0) {
				return true;
			}
			else {
				throw InvalidTypeException(
					"Option '" + option_name + "' parsing failed: String '" + value + "' is not valid boolean type.");
			}
		}

		template <> int ParseString<int>(const std::string &value, const std::string &option_name)
		{
			try {
				return std::stol(value);
			}
			catch (std::exception &e) {
				throw InvalidTypeException("Option '" + option_name + "' parsing failed: " + e.what());
			}
		}
	}
}