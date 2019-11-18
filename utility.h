#if !defined(UTILITY_MY_H)
#define UTILITY_MY_H

#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <sstream>
#include <fstream>

inline bool isInt(std::string symbol){

}


inline int stringToInt(std::string s){
    int result;
    std::istringstream(s) >> result;
    return result;
}

#endif // UTILITY_MY_H


