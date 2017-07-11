#ifndef CLSID_SECTION_H__
#define CLSID_SECTION_H__
#include <vector>
#include <memory>
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
		
		~Section();

		const std::string& Name() const;

		void AddOption(const Option& opt);

		void RemoveOption(const std::string& opt_name);

		template<typename ValueType>
		void AddOption(const std::string& opt_name, ValueType val);

		using iterator = SectionIterator<Section>;
		using const_iterator = SectionIterator<const Section>;

		iterator begin();

		iterator end();

		iterator begin() const;

		iterator end() const;

		const_iterator cbegin() const;

		const_iterator cend() const;

    private:
        std::vector<std::unique_ptr<Option>> opts_;
    };    

	template<typename Element> 
	class SectionIterator:public std::iterator<std::random_access_iterator_tag, Element>
	{

	};
}

#endif //CLSID_SECTION_H__