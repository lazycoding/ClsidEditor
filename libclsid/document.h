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
        
        void AddSection(const std::string& section_name);
        
        void AddSection(const Section& sec);
        
        void RemoveSection(const std::string& section_name);
        
        void AddOption(const std::string& section_name, const Option& opt);

        //TODO:
        //template<typename ValueType>
        //void AddOption(const std::string& section_name, const std::string& opt_name, ValueType value);        
        
        void RemoveOption(const std::string& section_name, const std::string& opt_name);
        
        size_t Size() const;
        
        Section& operator[](size_t index);
        
        const Section& operator[](size_t index) const;
        
        Section& operator[](const std::string& section_name);
        
        const Section& operator[](const std::string& section_name) const;
        
        bool Contains(const std::string& section_name) const;
        
        iterator begin();
        
        iterator end();
        
        iterator begin() const;
        
        iterator end() const;
        
        const_iterator cbegin() const;
        
        const_iterator cend() const;
        
    private:
        std::vector<Section> secs_;        
		std::map<std::string, Section> secs_map_;
    };
}


#endif //CLSID_DOCUMENT_H__