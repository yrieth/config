#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <fstream>

namespace yth{
class config{
    private:
    constexpr static char TEMP_NAME[5] = "temp";
    constexpr static char NULL_VALUE[5] = "null";
    std::string configName;

    public:
    config(std::string name);
    void addKey(std::string key, std::string value);
    void addKey(std::string key);
    void removeKey(std::string key);
    void setValue(std::string key, std::string value);
    std::string getValue(std::string key);
};
}


#endif //!CONFIG_HPP

