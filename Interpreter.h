#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Executor.h"
class Interpreter
{
private:
    std::queue<std::string> lexQueue;
    Executor executor;
    int nextInt();
    std::string nextSymbol();
    void processSymbol(const std::string& symbol);
public:
    Interpreter();
    ~Interpreter();
    void compile(const char* filename);
};

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}
