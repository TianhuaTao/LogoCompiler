#if !defined(UTILITY_MY_H)
#define UTILITY_MY_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

inline bool isInt(std::string symbol) {
    // placeholder
    return false;
}

inline int stringToInt(std::string s) {
    int result;
    std::istringstream(s) >> result;
    return result;
}

inline void issueRuntimeError(std::string err, int lineno=-1) {
    if (lineno == -1) {
        std::cerr << "Runtime Error: " << err << std::endl;
    } else {
        std::cerr << "Runtime Error at line " << lineno << ": " << err << std::endl;
    }
    exit(1);
}
inline void issueRuntimeWarning(std::string err) {
    std::cout << "Runtime warning: " << err << std::endl;
}

inline int max(int a, int b) {
    return a < b ? b : a;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

inline bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
#endif // UTILITY_MY_H
