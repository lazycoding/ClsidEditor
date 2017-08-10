#pragma once
#include <string>
#include <map>

namespace clsid
{
	class XmlProp
	{
	public:
		void Append(const std::string& prop);
	private:
		std::map<std::string, std::string> props_;
	};
}



