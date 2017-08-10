#include "XmlProp.h"
#include "string_utils.h"
#include "exception.h"
namespace clsid
{
	void XmlProp::Append(const std::string & prop)
	{
		auto kv = string_utils::Split(prop, '=');
		if (kv.size() != 2)
		{
			throw InvalidTypeException("Unexcepted xmlprop value");
		}
		props_[kv[0]] = kv[1];
	}
}

