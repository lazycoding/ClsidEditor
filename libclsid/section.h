#ifndef CLSID_SECTION_H__
#define CLSID_SECTION_H__
#include "option.h"
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

namespace clsid
{
	template<typename Element> class SectionIterator;

    class Section
    {
	public:
		Section()=delete;

		Section(const std::string& name);

		Section(const Section& source);
		
		Section& operator=(const Section& source);
		
		Section(Section&& source);
		
		Section& operator=(Section&& source);
		
		~Section()=default;

		const std::string& Name() const;

		void AddOption(const Option& opt);

		void RemoveOption(const std::string& opt_name);

		template<typename ValueType>
		void AddOption(const std::string& opt_name, ValueType val);

		size_t Size() const;

		bool Contains(const std::string& opt_name) const;

		friend class SectionIterator<Section>;
		friend class SectionIterator<const Section>;
		using iterator = SectionIterator<Section>;
		using const_iterator = SectionIterator<const Section>;

		iterator begin();

		iterator end();

		const_iterator begin() const;

		const_iterator end() const;

		const_iterator cbegin() const;

		const_iterator cend() const;

		bool operator==(const Section& other);

		bool operator!=(const Section& other);

    private:
        std::vector<std::shared_ptr<Option>> opts_;
		std::map<std::string, std::shared_ptr<Option>> opts_map_;
		std::string name_;
    };    

	template<typename Element> 
	class SectionIterator:public std::iterator<std::random_access_iterator_tag, Element>
	{
	public:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;
		using typename std::iterator<std::random_access_iterator_tag, Element>::pointer;

		SectionIterator() = delete;

		SectionIterator(const SectionIterator&) = default;

		SectionIterator(SectionIterator&& source) = default;

		SectionIterator& operator=(const SectionIterator&) = default;

		SectionIterator& operator=(SectionIterator&&) = default;

		SectionIterator(Section& sect, size_t position):sect_(sect_),position_(position)
		{

		}

		SectionIterator(Section& sect) :SectionIterator(sect, 0) 
		{

		}

		bool operator==(const SectionIterator& other) const
		{
			return &sect_ == &other.sect_ && position_ == other.position_;
		}

		bool operator!=(const SectionIterator& other) const
		{
			return !(*this == other);
		}
		
		bool operator<(const SectionIterator& other) const
		{
			return position_ < other.position_;
		}

		reference operator*()
		{
			return *sect_.opts_.at(position_);
		}

		pointer operator->()
		{
			return &(operator*());
		}

		SectionIterator& operator++() //prefix
		{
			++position_;
			return *this;
		}

		SectionIterator operator++(int)//suffix
		{
			SectionIterator old(*this);
			++position_;
			return old;
		}
	private:
		Section& sect_;
		size_t position_;
	};	
}

#endif //CLSID_SECTION_H__