#ifndef CLSID_SECTION_H__
#define CLSID_SECTION_H__
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iterator>
#include "option.h"

namespace clsid
{
	template<typename Element> class SectionIterator;

    class Section
    {
	public:
		Section();

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

		friend class SectionIterator<Section>;
		friend class SectionIterator<const Section>;
		using iterator = SectionIterator<Section>;
		using const_iterator = SectionIterator<const Section>;

		iterator begin();

		iterator end();

		iterator begin() const;

		iterator end() const;

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

	};	
}

#endif //CLSID_SECTION_H__