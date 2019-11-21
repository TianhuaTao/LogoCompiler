#if !defined(INTERPRETER_H)
#define INTERPRETER_H

#include "Executor.h"
#include "symbols.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
class Interpreter {
private:
    // std::queue<std::string> lexQueue;
    Executor executor;
    int nextInt();
    Symbol nextSymbol();
    void processSymbol(Symbol &symbol);
    std::vector<Symbol> getParaList();
    std::vector<Symbol> getIdentifierList();

public:
    Interpreter();
    ~Interpreter();
    void compile(const char *filename);
    void issueError(std::string err);
    void issueWarning(std::string err);
};

int assertSymbolType(Symbol &s, SymbolType type);

#endif // INTERPRETER_H

