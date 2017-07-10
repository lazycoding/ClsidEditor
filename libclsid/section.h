#ifndef CLSID_SECTION_H__
#define CLSID_SECTION_H__
#include <vector>
#include <memory>
#include "option.h"

namespace clsid
{
    class Section
    {
    private:
        std::vector<std::unique_ptr<Option>> opts_;
    };    
}

#endif //CLSID_SECTION_H__