#ifndef CLSID_OPTION_H__
#define CLSID_OPTION_H__
#include <string>

namespace clsid
{
    class Option
    {
	public:
		Option();

		Option(const std::string& key, const std::string& raw_value);

		Option(const Option& source);

		Option(Option&& source);

		Option& operator=(const Option& source);

		Option& operator=(Option&& source);

		~Option();

		template<typename ValueType> ValueType GetValue() const;
		
		
    private:
        std::string key_;
        std::string raw_;        
    };    
}

#endif //CLSID_OPTION_H__