#include "section.h"
#include "exception.h"
using namespace std;

namespace clsid
{
	Section::Section()
	{
	}
	Section::Section(const Section & source)
	{
		opts_.resize(source.opts_.size());
		for (auto& opt : source.opts_)
		{
			opts_.push_back(make_shared<Option>(*opt));
		}

		for (auto& opt : opts_)
		{
			opts_map_.insert(make_pair(opt->Name(), opt));
		}
	}
	Section & Section::operator=(const Section & source)
	{
		if (this != &source)
		{
			Section new_sec(source);
			std::swap(*this, new_sec);
		}
		return *this;
	}
	Section::Section(Section && source)
	{
		this->operator=(move(source));
	}
	Section & Section::operator=(Section && source)
	{
		if(this!=&source)
		{
			opts_ = move(source.opts_);
			opts_map_ = move(source.opts_map_);
		}
		return *this;
	}
	const std::string & Section::Name() const
	{
		return name_;
	}
	void Section::AddOption(const Option & opt)
	{
	}
	void Section::RemoveOption(const std::string & opt_name)
	{
	}
	bool Section::operator==(const Section & other)
	{
		return equal(opts_.begin(), opts_.end(), other.opts_.begin(),
			[](const shared_ptr<Option>& first, const shared_ptr<Option>& second) {
			return *first == *second;
		});
	}
	bool Section::operator!=(const Section & other)
	{
		return !this->operator==(other);
	}
}