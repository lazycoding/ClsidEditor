#ifndef CLSID_ITERATOR_H__
#define CLSID_ITERATOR_H__
#include <iterator>
namespace clsid
{
	template<typename Element> 
	class DocumentIterator : public std::iterator<std::random_access_iterator_tag, Element>
	{

	};
}
#endif //CLSID_ITERATOR_H__
