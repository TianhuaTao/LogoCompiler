#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include "Executor.h"
#include "symbols.h"
class Interpreter
{
private:
    // std::queue<std::string> lexQueue;
    Executor executor;
    int nextInt();
    Symbol nextSymbol();
    void processSymbol(Symbol& symbol);
public:
    Interpreter();
    ~Interpreter();
    void compile(const char* filename);
    void issueError(std::string err);
    void issueWarning(std::string err);
};


int assertSymbolType(Symbol& s, SymbolType type);