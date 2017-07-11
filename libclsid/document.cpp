#include "document.h"
#include "exception.h"
#include "iterator.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "reader.h"
using namespace std;

namespace clsid
{
	Document::Document()
	{
	}
	Document::Document(const Document & source)
	{
		secs_.resize(source.secs_.size());
		for (auto& sec : source.secs_)
		{
			secs_.push_back(make_shared<Section>(*sec));
		}

		for (auto& sec : source.secs_)
		{
			secs_map_.insert(make_pair(sec->Name(), sec));
		}
	}
	Document::Document(Document && source)
	{
		operator=(move(source));
	}
	Document & Document::operator=(const Document & source)
	{
		if (this != &source)
		{
			Document d(source);
			std::swap(*this, d);
		}
		return *this;
	}
	Document & Document::operator=(Document && source)
	{
		if (this != &source)
		{
			secs_ = move(source.secs_);
			secs_map_ = move(source.secs_map_);
		}
		return *this;
	}
	bool Document::Load(const char * filepath)
	{
		std::ifstream in(filepath);
		if (in)
		{
			Reader rd(in, *this);
			return rd.Parse();
		}		
		return false;
	}
	bool Document::LoadString(const char * clsidstr)
	{
		//std::isstream in(filepath);
		std::istringstream in(clsidstr);
		if (in)
		{
			Reader rd(in, *this);
			return rd.Parse();
		}
		return false;
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
	bool Document::operator==(const Document & other) const
	{
		return equal(secs_.begin(), secs_.end(), other.secs_.begin(),
			[](const shared_ptr<Section>& first, const shared_ptr<Section>& second){
			return *first == *second;
		});

	}
	bool Document::operator!=(const Document & other) const
	{
		return !this->operator==(other);
	}
}