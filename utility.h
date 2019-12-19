#if !defined(UTILITY_MY_H)
#define UTILITY_MY_H

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <sstream>
#include <fstream>

inline bool isInt(std::string symbol){
    // placeholder
    return false;
}


inline int stringToInt(std::string s){
    int result;
    std::istringstream(s) >> result;
    return result;
}

inline void issueRuntimeError(std::string err) {
    std::cout << err << std::endl;
    exit(1);
}

#endif // UTILITY_MY_H


