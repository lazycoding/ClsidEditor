#include "reader.h"
#include "document.h"
#include "exception.h"
namespace clsid
{
	Reader::Reader(std::istream & in, Document & doc):in_(in), doc_(doc)
	{
	}
	bool Reader::Parse()
	{
		throw NotImplementedException();
	}
}
