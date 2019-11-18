#if !defined(SYMBOLS_H)
#define SYMBOLS_H

#include <queue>
#include <string>

extern "C"
{
    int yylex(void);
    
}

enum SymbolType {
    MOVE = 30000,
    TURN,
    LOOP,
    DEF,
    FUNC,
    ADD,
    COLOR,
    ATPOSITION,
    ATBACKGROUND,
    ATSIZE,
    ENDLOOP,
    ENDFUNC,
    LPAR,
    RPAR,
    IDENTIFIER,
    INTCONST,
    MINUS
};

class Symbol
{
private:
    SymbolType type;
    int value;
    std::string name;
public:
    const std::string &getName() const;

public:
    Symbol(SymbolType st);
    Symbol(SymbolType st, int value,std::string name );

    static Symbol identifier(std::string name);
    static Symbol intConst(std::string intStr);
    int getValue()const{return value;}
    int getType()const{return type;}
    ~Symbol();
};

extern std::queue<Symbol> lexQueue;


int keyword(SymbolType st);


int intConst(const char* s);


int identifier(const char* s);


void issueError(const char* text);


#endif // SYMBOLS_H
