#if !defined(SYMBOLS_H)
#define SYMBOLS_H

#include <queue>
#include <string>

extern "C"
{
    int yylex(void);
    
}
const int SYMBOL_TYPE_START_NO = 30000;
enum SymbolType {
    MOVE = SYMBOL_TYPE_START_NO,
    TURN,
    LOOP,
    DEF,
    CALL,
    FUNC,
    ADD,
    COLOR,
    CLOAK,
    ATPOSITION,
    ATBACKGROUND,
    ATSIZE,
    ENDLOOP,
    ENDFUNC,
    PENWIDTH,
    FILL,
    LPAR,
    RPAR,
    IDENTIFIER,
    INTCONST,
    MINUS,
    COMMA
};

extern std::string symbolTypeName[];

inline std::string getSymbolTypeName(int type){
    return symbolTypeName[type - SYMBOL_TYPE_START_NO];
}

class Symbol {
private:
    SymbolType type;
    int value;
    std::string name;
    int lineno;

public:
    const std::string &getName() const;
    const int &getLineno() const{
        return lineno;
    }

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
