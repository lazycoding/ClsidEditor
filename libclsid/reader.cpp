#include "reader.h"
#include "document.h"
#include "exception.h"
#include "string_utils.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

const char* kSectionStart = "[";
const char* kSectionEnd = "]";

namespace clsid
{
	Document Reader::Load(std::istream & stream)
	{
		return InternalLoad(stream);
	}
	Document Reader::Load(const std::string & context)
	{
		istringstream is(context);
		return Load(is);
	}
	Document Reader::LoadFile(const std::string & path)
	{
		ifstream ifs(path);
		if (!ifs.fail())
		{
			return Load(ifs);
		}
		throw ParserException("File reading exception");
	}

	Document Reader::InternalLoad(std::istream & stream)
	{
		using namespace string_utils;
		Document doc;
		shared_ptr<Section> last_section = nullptr;
		string line;
		size_t line_number = 0;

		while (getline(stream, line))
		{
			line_number++;

			line = DeleteComment(line);
			line = TrimLeft(line);

			if (line.empty()) //empty line
			{
				continue;
			}
			else if (StartsWith(line, kSectionStart)) //start of section
			{
				line = TrimRight(line);
				if (EndsWith(line, kSectionEnd))
				{
					if (line.length() == 2)
					{
						throw ParserException("Section name cannot be empty on line" + to_string(line_number));
					}
					
					if (last_section != nullptr)
					{
						doc.AddSection(*last_section);
					}

					string section_name = UnEscape(line.substr(1, line.length() - 2));

					last_section = make_shared<Section>(section_name);
				}
				else
				{
					throw ParserException("Section not ended on line" + to_string(line_number));
				}
			}
			else // option
			{
				size_t opt_delim = find_first_nonescaped(line, '=');
				if (opt_delim == string::npos)
				{
					throw ParserException("Unknown element option expected on line " + to_string(line_number));
				}
				if (last_section==nullptr)
				{
					throw ParserException("Option non in section on line " + to_string(line_number));
				}
				if ((opt_delim + 1) == line.length())
				{
					throw ParserException("Option value cannot be empty on line " + to_string(line_number));
				}

				string opt_name = UnEscape(Trim(line.substr(0, opt_delim)));
				string opt_val = Trim(line.substr(opt_delim + 1));

				if (opt_name.empty())
				{
					throw ParserException("Option name cannot be empty on line " + to_string(line_number));
				}

				Option opt(opt_name);
				if (StartsWith(opt_val, "{") && EndsWith(opt_val, "}")) //stringarray
				{
					opt_val = opt_val.substr(1, opt_val.length() - 2);

					auto items = Split(opt_val, ',');
					StringArray sa;
					for each (auto item in items)
					{
						sa.Append(TrimWith(item, '\"'));
					}
					opt = sa;
				}
				else if (StartsWith(opt_val, "<") && EndsWith(opt_val, ">")) //xmlprop
				{
					opt_val = opt_val.substr(1, opt_val.length() - 2);
					auto items = Split(opt_val, ',');
					if (items.empty())
					{
						items = Split(opt_val, ' ');
					}

					XmlProp xp;
					for each (auto item in items)
					{
						xp.Append(item);
					}
					opt = xp;
				}
				else
				{
					opt_val = TrimWith(opt_val, '\"');
					int opt_number=0;
					if (_stricmp(opt_val.c_str(), "true") == 0)
					{
						opt = true;
					}
					else if (_stricmp(opt_val.c_str(), "false") == 0)
					{
						opt = false;
					}
					else if(TryToNumber(opt_val, &opt_number))
					{
						opt = opt_number;
					}
					else
					{
						opt = opt_val;
					}
				}	

				last_section->AddOption(opt);
			}
		}

		if (last_section != nullptr)
		{
			doc.AddSection(*last_section);
		}

		return doc;
	}
	std::string Reader::DeleteComment(const std::string & content)
	{
		return content.substr(0, find_first_nonescaped(content, '/'));
	}

	std::string Reader::UnEscape(const std::string & str)
	{
		std::string result = str;
		bool escaped = false;

		auto it = result.begin();
		while (it != result.end()) {
			if (escaped) {
				// escaped character, it should remain in string
				escaped = false;
			}
			else if (*it == '\\') {
				// next character will be escaped, so delete escaping character
				escaped = true;
				it = result.erase(it);
				continue;
			}

			// we have while cycle so we have to do this manually
			++it;
		}

		return result;
	}
	size_t Reader::find_first_nonescaped(const std::string & str, char ch)
	{
		size_t result = std::string::npos;
		bool escaped = false;

		for (size_t i = 0; i < str.length(); ++i) {
			if (escaped) {
				// escaped character, do not do anything
				escaped = false;
			}
			else if (str[i] == '\\') {
				// next character will be escaped
				escaped = true;
			}
			else if (str[i] == ch) {
				// we tracked down non escaped character... return it
				result = i;
				break;
			}
		}

		return result;
	}
	bool Reader::TryToNumber(const std::string & str, int* target)
	{
		try
		{			
			*target = std::stol(str);
		}
		catch (const std::invalid_argument &)
		{
			return false;
		}
		return true;
	}
}
