#include "document.h"
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
		// TODO: �ڴ˴����� return ���
	}
	Document & Document::operator=(Document && source)
	{
		// TODO: �ڴ˴����� return ���
	}
	void Document::AddSection(const std::string & section_name)
	{
	}
	void Document::AddSection(const Section & sec)
	{
	}
	void Document::RemoveSection(const std::string & section_name)
	{
	}
	void Document::AddOption(const std::string & section_name, const Option & opt)
	{
	}
	void Document::RemoveOption(const std::string & section_name, const std::string & opt_name)
	{
	}
	size_t Document::Size() const
	{
		return size_t();
	}
	Section & Document::operator[](size_t index)
	{
		// TODO: �ڴ˴����� return ���
	}
	const Section & Document::operator[](size_t index) const
	{
		// TODO: �ڴ˴����� return ���
	}
	Section & Document::operator[](const std::string & section_name)
	{
		// TODO: �ڴ˴����� return ���
	}
	const Section & Document::operator[](const std::string & section_name) const
	{
		// TODO: �ڴ˴����� return ���
	}
	bool Document::Contains(const std::string & section_name) const
	{
		return false;
	}
	iterator Document::begin()
	{
		return iterator();
	}
	iterator Document::end()
	{
		return iterator();
	}
	iterator Document::begin() const
	{
		return iterator();
	}
	iterator Document::end() const
	{
		return iterator();
	}
	const_iterator Document::cbegin() const
	{
		return const_iterator();
	}
	const_iterator Document::cend() const
	{
		return const_iterator();
	}
}