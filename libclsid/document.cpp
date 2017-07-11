#include "document.h"
#include "exception.h"
#include "iterator.h"

namespace clsid
{
	Document::Document()
	{
	}
	Document::Document(const Document & source)
	{
	}
	Document::Document(Document && source)
	{
	}
	Document & Document::operator=(const Document & source)
	{
		throw NotImplementedException();
	}
	Document & Document::operator=(Document && source)
	{
		throw NotImplementedException();
	}
	bool Document::Load(const char * filepath)
	{
		throw NotImplementedException();
	}
	void Document::AddSection(const std::string & section_name)
	{
		throw NotImplementedException();
	}
	void Document::AddSection(const Section & sec)
	{
		throw NotImplementedException();
	}
	void Document::RemoveSection(const std::string & section_name)
	{
	}
	void Document::AddOption(const std::string & section_name, const Option & opt)
	{
		throw NotImplementedException();
	}
	void Document::RemoveOption(const std::string & section_name, const std::string & opt_name)
	{
		throw NotImplementedException();
	}
	size_t Document::Size() const
	{
		throw NotImplementedException();
	}
	Section & Document::operator[](size_t index)
	{
		throw NotImplementedException();
	}
	const Section & Document::operator[](size_t index) const
	{
		throw NotImplementedException();
	}
	Section & Document::operator[](const std::string & section_name)
	{
		throw NotImplementedException();
	}
	const Section & Document::operator[](const std::string & section_name) const
	{
		throw NotImplementedException();
	}
	bool Document::Contains(const std::string & section_name) const
	{
		throw NotImplementedException();
	}
	Document::iterator Document::begin()
	{
		throw NotImplementedException();
	}
	Document::iterator Document::end()
	{
		throw NotImplementedException();
	}
	Document::iterator Document::begin() const
	{
		throw NotImplementedException();
	}
	Document::iterator Document::end() const
	{
		throw NotImplementedException(); 
	}
	Document::const_iterator Document::cbegin() const
	{
		throw NotImplementedException();
	}
	Document::const_iterator Document::cend() const
	{
		throw NotImplementedException();
	}
}