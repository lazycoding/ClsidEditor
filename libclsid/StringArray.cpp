#include "StringArray.h"
#include <algorithm>
namespace clsid
{
	void StringArray::Append(const std::vector<std::string>& vec)
	{
		std::copy(vec.begin(), vec.end(), std::back_inserter(strings_));
	}

	void StringArray::Append(const std::string & str)
	{
		strings_.push_back(str);
	}
}

