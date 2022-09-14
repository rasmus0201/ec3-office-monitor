#ifndef BUNDSGAARD_HELPERS
#define BUNDSGAARD_HELPERS

#include <string>

namespace Bundsgaard
{
    std::string to_weekdayname(int num)
    {
        switch(num) {
            case 0:
                return std::string("søn");
            case 1:
                return std::string("man");
            case 2:
                return std::string("tirs");
            case 3:
                return std::string("ons");
            case 4:
                return std::string("tors");
            case 5:
                return std::string("fre");
            case 6:
            default:
                return std::string("lør");
        }
    }

    std::string to_monthname(int num)
    {
        switch(num) {
            case 0:
                return std::string("jan");
            case 1:
                return std::string("feb");
            case 2:
                return std::string("mar");
            case 3:
                return std::string("apr");
            case 4:
                return std::string("maj");
            case 5:
                return std::string("jun");
            case 6:
                return std::string("jul");
            case 7:
                return std::string("aug");
            case 8:
                return std::string("sep");
            case 9:
                return std::string("okt");
            case 10:
                return std::string("nov");
            case 11:
            default:
                return std::string("dec");
        }
    }

    std::string pad_left(std::string const& str, size_t s, char padChar = ' ')
    {
        if (str.size() < s) {
            return std::string(s-str.size(), padChar) + str;
        }

        return str;
    }

    std::string pad_right(std::string const& str, size_t s, char padChar = ' ')
    {
        if (str.size() < s) {
            return str + std::string(s-str.size(), padChar);
        }

        return str;
    }
}

#endif
