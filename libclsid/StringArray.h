#pragma once
#include <string>
#include <vector>

namespace clsid
{
	class StringArray
	{
	public:
		StringArray() = default;
		~StringArray() = default;
		StringArray(const StringArray&) = default;
		StringArray(StringArray&&) = default;
		StringArray& operator=(const StringArray&) = default;
		StringArray& operator=(StringArray&&) = default;

		void Append(const std::vector<std::string>& vec);

		void Append(const std::string& str);
	private:
		std::vector<std::string> strings_;
	};
}
