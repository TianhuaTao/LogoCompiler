#if !defined(INTERPRETER_H)
#define INTERPRETER_H

#include "Executor.h"
#include "symbols.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
extern bool verbose;
class Interpreter {
private:
    // std::queue<std::string> lexQueue;
    Executor executor;
    int nextInt();
    VariableWrapper getNextVariableWrapper();
    Symbol nextSymbol();
    void processSymbol(Symbol &symbol);
    std::vector<VariableWrapper> getParaList();
    std::vector<VariableWrapper> getIdentifierList();

public:
    Interpreter();
    ~Interpreter();
    void compile(const char *filename, const char *outName = nullptr);
    void issueError(std::string err,int lineno = -1);
    void issueWarning(std::string err,int lineno = -1);
};

int assertSymbolType(Symbol &s, SymbolType type);

#endif // INTERPRETER_H

