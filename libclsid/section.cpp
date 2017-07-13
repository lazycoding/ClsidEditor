#include "section.h"
#include "exception.h"
#include <algorithm>
using namespace std;

namespace clsid
{
	Section::Section(const std::string& name)
		:name_(name)
	{
	}
	Section::Section(const Section & source):Section(source.name_)
	{
		opts_.reserve(source.opts_.size());
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
		if (this != &source)
		{
			opts_ = move(source.opts_);
			opts_map_ = move(source.opts_map_);
			name_ = source.name_;
		}
		return *this;
	}
	const std::string & Section::Name() const
	{
		return name_;
	}
	void Section::AddOption(const Option & opt)
	{
		auto find = opts_map_.find(opt.Name());
		if (find == opts_map_.end())
		{
			auto toadd = make_shared<Option>(opt);
			opts_map_.insert(make_pair(opt.Name(), toadd));
			opts_.push_back(toadd);
		}
	}
	void Section::RemoveOption(const std::string & opt_name)
	{
		auto find = opts_map_.find(opt_name);
		if (find != opts_map_.end())
		{
			opts_map_.erase(opt_name);
			opts_.erase(remove_if(opts_.begin(), opts_.end(), [&](const shared_ptr<Option>& opt) {
				return opt->Name() == opt_name;
			}), opts_.end());
		}
	}
	Section::iterator Section::begin()
	{
		return iterator(*this);
	}
	Section::iterator Section::end()
	{
		return iterator(*this, opts_.size());
	}
	Section::const_iterator Section::begin() const
	{
		return const_iterator(const_cast<Section&>(*this));
	}
	Section::const_iterator Section::end() const
	{
		return const_iterator(const_cast<Section&>(*this), opts_.size());
	}
	Section::const_iterator Section::cbegin() const
	{
		return const_iterator(const_cast<Section&>(*this));
	}
	Section::const_iterator Section::cend() const
	{
		return const_iterator(const_cast<Section&>(*this), opts_.size());
	}
	bool Section::operator==(const Section & other)
	{
		if (name_ != other.name_)
		{
			return false;
		}
		return equal(opts_.begin(), opts_.end(), other.opts_.begin(),
			[](const shared_ptr<Option>& first, const shared_ptr<Option>& second) {
			return *first == *second;
		});
	}
	bool Section::operator!=(const Section & other)
	{
		return !this->operator==(other);
	}

	size_t Section::Size() const
	{
		return opts_.size();
	}

	bool Section::Contains(const std::string& opt_name) const
	{
		return opts_map_.find(opt_name) != opts_map_.end();
	}

	Option& Section::operator[](int index)
	{
		if (0 <= index && index < opts_.size())
		{
			return *opts_.at(index);
		}
		throw out_of_range("out of range");
	}

	const Option& Section::operator[](int index) const
	{
		if (0 <= index && index < opts_.size())
		{
			return *opts_.at(index);
		}
		throw out_of_range("out of range");
	}

	Option& Section::operator[](const std::string& opt_name)
	{
		shared_ptr<Option> result;
		try
		{
			result = opts_map_.at(opt_name);
		}
		catch (const std::out_of_range&)
		{
			throw out_of_range("not found");
		}
		return *result;
	}

	const Option& Section::operator[](const std::string& opt_name)const
	{
		shared_ptr<Option> result;
		try
		{
			result = opts_map_.at(opt_name);
		}
		catch (const std::out_of_range&)
		{
			throw out_of_range("not found");
		}
		return *result;
	}
}