#include "Interpreter.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    if(argc<2){
        std::cerr<< "Error: No input file."<<std::endl;
        return -1;
    }
    Interpreter i;
    i.compile(argv[1]);
    return 0;
}
