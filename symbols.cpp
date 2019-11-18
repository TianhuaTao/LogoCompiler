#include "symbols.h"
#include "utility.h"
std::queue<Symbol> lexQueue;
Symbol::Symbol(SymbolType st) : type(st) {
}

Symbol::~Symbol() {
}
Symbol::Symbol(SymbolType st, int value, std::string name) : type(st), value(value), name(name) {}

Symbol Symbol::identifier(std::string name) {
    return Symbol(IDENTIFIER, 0, name);
}

Symbol Symbol::intConst(std::string intStr) {
    int value = stringToInt(intStr);
    return Symbol(INTCONST, value, std::string());
}

const std::string &Symbol::getName() const {
    return name;
}

int keyword(SymbolType st) {
    std::cout<< "keyword: code = "<<st<< std::endl;

    lexQueue.push(Symbol(st));
    return st;
}
int intConst(const char *s) {
    lexQueue.push(Symbol::intConst(s));
    std::cout<< "intConst: "<<s<< std::endl;
    return INTCONST;
}
int identifier(const char *s) {
    lexQueue.push(Symbol::identifier(s));
    std::cout<<"identifier: "<< s<< std::endl;
    return IDENTIFIER;
}
void issueError(const char *text) {
    std::printf("Error: %s\n", text);
}



extern "C"
{
    int yywrap(){return 1;}
}
// int main(int argc, char const *argv[])
// {
//     yylex();
//     std::cout<< "queue size: "<<lexQueue.size()<< std::endl;
//     return 0;
// }

