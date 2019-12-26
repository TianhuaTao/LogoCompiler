#include "symbols.h"
#include "utility.h"
std::queue<Symbol> lexQueue;
Symbol::Symbol(SymbolType st) : type(st) {
    extern int yylineno;
    lineno = yylineno;
}

// The order is important
// should be the same as enum SymbolType
std::string symbolTypeName[] = {
    "MOVE",
    "TURN",
    "LOOP",
    "DEF",
    "CALL",
    "FUNC",
    "ADD",
    "COLOR",
    "CLOAK",
    "ATPOSITION",
    "ATBACKGROUND",
    "ATSIZE",
    "ENDLOOP",
    "ENDFUNC",
    "PENWIDTH",
    "FILL",
    "LPAR",
    "RPAR",
    "IDENTIFIER",
    "INTCONST",
    "MINUS",
    "COMMA"};

Symbol::~Symbol() {
}
Symbol::Symbol(SymbolType st, int value, std::string name) : type(st), value(value), name(name) {
    extern int yylineno;
    lineno = yylineno;
    // std::cout <<"line "<< lineno << std::endl;
}

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
    // std::cout<< "keyword: code = "<<st<< std::endl;
    lexQueue.push(Symbol(st));
    return st;
}
int intConst(const char *s) {
    lexQueue.push(Symbol::intConst(s));
    // std::cout<< "intConst: "<<s<< std::endl;
    return INTCONST;
}
int identifier(const char *s) {
    lexQueue.push(Symbol::identifier(s));
    // std::cout<<"identifier: "<< s<< std::endl;
    return IDENTIFIER;
}
void issueError(const char *text) {
    extern int yylineno;
    std::printf("Error at line %d: %s\n", yylineno, text);
    exit(1);
}

extern "C" {
int yywrap() { return 1; }
}
