#pragma once
#include <exception>
#include <string>
namespace clsid
{
	class Exception : public std::exception
	{		
	public:
		Exception():std::exception("Generic exception")
		{

		}

		Exception(const std::string& what) :what_(what)
		{

		}

		virtual ~Exception()
		{

		}

		virtual char const* what() const noexcept
		{
			return what_.c_str();
		}

	protected:
		std::string what_;
	};

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException():Exception("Not implemented!")
		{

		}
	};

	class BadCastException : public Exception
	{
	public:
		BadCastException(const std::string& message):Exception(message)
		{

		}

		BadCastException(const std::string& from, const std::string& to)
			:Exception("Bad conversion from: " + from + " to: " + to)
		{

		}
	};

	class ParserException : public Exception
	{
	public:
		ParserException(const std::string& message):Exception(message)
		{

		}
	};

	class InvalidTypeException : public Exception
	{
	public:
		InvalidTypeException(const std::string& message):Exception(message)
		{

		}
	};

	class NotFoundException : public Exception
	{
	public:
		NotFoundException(const std::string& message):Exception(message)
		{

		}
	};
}