#ifndef CLSID_DOCUMENT_H__
#define CLSID_DOCUMENT_H__
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "section.h"

namespace clsid
{
    template<typename Element> class DocumentIterator;
    
    class Document
    {
    public:
        
        friend class DocumentIterator<Section>;
        friend class DocumentIterator<const Section>;
        using iterator = DocumentIterator<Section>;
        using const_iterator = DocumentIterator<const Section>;
        
        Document();
        
        Document(const Document& source);
        
        Document(Document&& source);
        
        Document& operator=(const Document& source);
        
        Document& operator=(Document&& source);

		bool Load(const char* filepath);

		bool LoadString(const char* clsidstr);

        void AddSection(const std::string& section_name);
        
        void AddSection(const Section& sec);
        
        void RemoveSection(const std::string& section_name);
        
        void AddOption(const std::string& section_name, const Option& opt);
        
        template<typename ValueType>
        void AddOption(const std::string& section_name, const std::string& opt_name, ValueType value);        
        
        void RemoveOption(const std::string& section_name, const std::string& opt_name);
        
        size_t Size() const;
        
        Section& operator[](size_t index);
        
        const Section& operator[](size_t index) const;
        
        Section& operator[](const std::string& section_name);
        
        const Section& operator[](const std::string& section_name) const;
        
        bool Contains(const std::string& section_name) const;
        
        iterator begin();
        
        iterator end();
        
        const_iterator begin() const;
        
		const_iterator end() const;
        
        const_iterator cbegin() const;
        
        const_iterator cend() const;

		bool operator==(const Document& other) const;
        
		bool operator!=(const Document& other) const;

    private:
        std::vector<std::shared_ptr<Section>> secs_;        
		std::map<std::string, std::shared_ptr<Section>> secs_map_;
    };

	template<typename ValueType>
	void Document::AddOption(const std::string & section_name, const std::string & opt_name, ValueType value)
	{
		throw NotImplementedException();
	}

	template<typename Element>
	class DocumentIterator : public std::iterator<std::random_access_iterator_tag, Element>
	{
	public:
		using typename std::iterator<std::random_access_iterator_tag, Element>::reference;
		using typename std::iterator<std::random_access_iterator_tag, Element>::pointer;

		DocumentIterator() = delete;

		DocumentIterator(const DocumentIterator& doc) = default;

		DocumentIterator(DocumentIterator&& doc) = default;

		DocumentIterator& operator=(const DocumentIterator& doc) = default;

		DocumentIterator& operator=(DocumentIterator&& doc) = default;

		DocumentIterator(Document& source) :DocumentIterator(source, 0) 
		{
		}

		DocumentIterator(Document& source, size_t position):container_(source),position_(position)
		{
		}

		DocumentIterator& operator++() //prefix
		{
			++position_;
			return *this;
		}

		DocumentIterator operator++(int)//suffix
		{
			DocumentIterator old(*this);
			++position_;
			return old;
		}

		bool operator!=(const DocumentIterator& other) const
		{
			return !(*this == other);
		}

		bool operator==(const DocumentIterator& other) const
		{
			return &container_ == &other.container_ && position_ == other.position_;
		}

		bool operator<(const DocumentIterator& other) const
		{
			return position_ < other.position_;
		}

		reference operator*()
		{
			return *container_.secs_.at(position_);
		}

		pointer operator->()
		{
			return &(operator*());
		}

	private:
		Document& container_;
		size_t position_;
	};
}



#endif //CLSID_DOCUMENT_H__