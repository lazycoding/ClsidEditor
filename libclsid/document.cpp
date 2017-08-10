#include "document.h"
#include "exception.h"
#include "iterator.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "reader.h"
using namespace std;

namespace clsid
{
	Document::Document()
	{
	}
	Document::Document(const Document & source)
	{
		secs_.reserve(source.secs_.size());
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

	void Document::AddSection(const std::string & section_name)
	{
		Section sec(section_name);
		AddSection(sec);
	}
	void Document::AddSection(const Section & sec)
	{
		auto findit = secs_map_.find(sec.Name());
		if (findit==secs_map_.end())
		{
			auto add_it = make_shared<Section>(sec);
			secs_map_.insert(make_pair(sec.Name(), add_it));
			secs_.push_back(add_it);
		}
	}
	void Document::RemoveSection(const std::string & section_name)
	{
		auto findit = secs_map_.find(section_name);
		if (findit != secs_map_.end())
		{			
			secs_map_.erase(section_name);
			secs_.erase(remove_if(secs_.begin(), secs_.end(),
				[&](const shared_ptr<Section>& sec) {
				return sec->Name() == section_name;
			}), secs_.end());
		}
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
		return secs_.size();
	}
	Section & Document::operator[](size_t index)
	{
		if (0 <= index || index < secs_.size())
		{
			return *secs_[index];
		}
		throw out_of_range("out of range");
	}
	const Section & Document::operator[](size_t index) const
	{
		if (0 <= index || index < secs_.size())
		{
			return *secs_[index];
		}
		throw out_of_range("out of range");
	}
	Section & Document::operator[](const std::string & section_name)
	{
		auto find = find_if(secs_.begin(), secs_.end(), [&](const shared_ptr<Section>& sec) { 
			return sec->Name() == section_name; });
		if (find != secs_.end())
		{
			return **find;
		}
		throw out_of_range("not found");

	}
	const Section & Document::operator[](const std::string & section_name) const
	{
		auto find = find_if(secs_.begin(), secs_.end(), [&](const shared_ptr<Section>& sec) {
			return sec->Name() == section_name; });
		if (find != secs_.end())
		{
			return **find;
		}
		throw out_of_range("not found");
	}
	bool Document::Contains(const std::string & section_name) const
	{
		auto it = secs_map_.find(section_name);
		return it != secs_map_.end();
	}
	Document::iterator Document::begin()
	{
		return iterator(*this);
	}
	Document::iterator Document::end()
	{
		return iterator(*this, secs_.size());
	}
	Document::const_iterator Document::begin() const
	{
		return const_iterator(const_cast<Document&>(*this));
	}
	Document::const_iterator Document::end() const
	{
		return const_iterator(const_cast<Document&>(*this), secs_.size());
	}
	Document::const_iterator Document::cbegin() const
	{
		return const_iterator(const_cast<Document&>(*this));
	}
	Document::const_iterator Document::cend() const
	{
		return const_iterator(const_cast<Document&>(*this), secs_.size());
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


