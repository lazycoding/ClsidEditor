#pragma once
#include <exception>
namespace clsid
{
	class NotImplementedException : public std::exception
	{
	public:
		NotImplementedException():exception("not implemented!")
		{

		}
	};
}