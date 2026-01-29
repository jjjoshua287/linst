#include "StringUtils.h"
#include <algorithm>
#include <cctype>

namespace StringUtils {
    // Remove all spaces from string
    std::string normalize(std::string str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        for (char& c : str) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return str;
    }
}