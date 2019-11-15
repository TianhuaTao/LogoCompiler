#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <sstream>
#include <fstream>

bool isInt(std::string symbol){

}


int stringToInt(std::string s){
    int result;
    std::istringstream(s) >> result;
    return result;
}