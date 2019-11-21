#include "Interpreter.h"
#include "symbols.h"
#include "utility.h"
#include <sstream>
Interpreter::Interpreter() {
}

Interpreter::~Interpreter() {
}

int assertSymbolType(Symbol &s, SymbolType type) {
    if (s.getType() == type) {
        return 0;
    }
    std::cerr << "Unexpected symbol: [type="<<s.getType()<<", name=" << s.getName()<<", value="<<s.getValue() <<"]"<< std::endl;
    return -1;
}
void Interpreter::compile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == nullptr) {
        std::cout << "Cannot open the file" << std::endl;
        return;
    }
    extern FILE *yyin;
    yyin = fp;
    yylex();
    fclose(fp);

    std::cout << "symbol queue size: " << lexQueue.size() << std::endl;

    // header
    assertSymbolType(lexQueue.front(), ATSIZE);
    lexQueue.pop(); // @SIZE
    int width, height;
    width = nextInt();
    height = nextInt();
    executor.initNewBuffer(width, height);

    assertSymbolType(lexQueue.front(), ATBACKGROUND);
    lexQueue.pop(); // @BACKGROUND
    int r, g, b;
    r = nextInt();
    g = nextInt();
    b = nextInt();
    executor.setBackground(r, g, b);

    assertSymbolType(lexQueue.front(), ATPOSITION);
    lexQueue.pop(); // @POSITION
    int x, y;
    x = nextInt();
    y = nextInt();
    executor.setPenPosition(x, y);

    // body
    while (!lexQueue.empty()) {
        Symbol s = nextSymbol();
        processSymbol(s);
    }

    executor.run();
    executor.writeFile();
    // std::ifstream in;
    // in.open(filename);
    // if (in.is_open())
    // {
    //     std::string lex;
    //     while (in >> lex)
    //     {
    //         this->lexQueue.push(lex);
    //     }
    //     // Todo: check state
    //     in.close();

    //     // Todo: lexer check

    //     // header
    //     lexQueue.pop(); // @SIZE
    //     int width, height;
    //     width = nextInt();
    //     height = nextInt();
    //     executor.initNewBuffer(width, height);

    //     lexQueue.pop(); // @BACKGROUND
    //     int r, g, b;
    //     r = nextInt();
    //     g = nextInt();
    //     b = nextInt();
    //     executor.setBackground(r, g, b);

    //     lexQueue.pop(); // @POSITION
    //     int x, y;
    //     x = nextInt();
    //     y = nextInt();
    //     executor.setPenPosition(x, y);

    //     // body
    //     while (!lexQueue.empty())
    //     {
    //         std::string next = nextSymbol();
    //         processSymbol(next);
    //     }
    // }
}

int Interpreter::nextInt() {
    if (lexQueue.empty()) {
        issueError("Expecting a value");
    }
    assertSymbolType(lexQueue.front(), INTCONST);
    int result;
    result = lexQueue.front().getValue();
    lexQueue.pop();
    return result;
}

Symbol Interpreter::nextSymbol() {
    if (lexQueue.empty()) {
        issueError("Expecting a symbol");
    }
    Symbol result = lexQueue.front();
    lexQueue.pop();
    return result;
}

void Interpreter::processSymbol(Symbol &symbol) {
    if (symbol.getType() == TURN)
    {
        auto sym = nextSymbol();
        if (sym.getType()==INTCONST)
        {
            executor.turn(sym.getValue());
        }
        else
        {
            assertSymbolType(sym, IDENTIFIER);
            Variable &v = Variable::getVariableByName(sym.getName());
            if (v == Variable::noVar())
            {
                issueError("Variable not found: " + sym.getName());
            }
            executor.turn(v);
        }
    }
    else if (symbol.getType() == MOVE)
    {
        auto sym = nextSymbol();
        if (sym.getType()==INTCONST)
        {
            executor.move(sym.getValue());
        }
        else
        {
            assertSymbolType(sym, IDENTIFIER);
            Variable &v = Variable::getVariableByName(sym.getName());
            if (v == Variable::noVar())
            {
                issueError("Variable not found: " + sym.getName());
            }
            executor.move(v);
        }
    }

    // if (symbol == "DEF")
    // {
    //     std::string name = nextSymbol();
    //     int value = nextInt();
    //     executor.def(name, value);
    // }
    else if (symbol.getType() == ADD) {
        auto sym = nextSymbol();
        assertSymbolType(sym, IDENTIFIER);
        int value = nextInt();

        Variable&v =Variable::getVariableByName(sym.getName());
        if(v == Variable::noVar()){
        issueError("cannot find variable: "+ sym.getName());
    }
        executor.add(v, value);
    } else if (symbol.getType() == COLOR) {
        // std::cout << "symbol:COLOR" << std::endl;
        int r, g, b;
        r = nextInt();
        g = nextInt();
        b = nextInt();
        executor.setPenColor(r, g, b);
    } else if (symbol.getType() == CLOAK) {
        executor.cloak();
    } else if (symbol.getType() == LOOP) {
        int loop = nextInt();
        executor.loop(loop);
    } else if (symbol.getType() == FUNC) {
        auto funcSymbol = nextSymbol();
        assertSymbolType(funcSymbol, IDENTIFIER);
        auto list = getIdentifierList();
        executor.startFuncDef(funcSymbol.getName(), list.size());
        }

    else if (symbol.getType() == CALL) {
        auto funcSymbol = nextSymbol();
        assertSymbolType(funcSymbol, IDENTIFIER);
        auto list = getParaList();
    }
}
std::vector<Symbol> Interpreter::getParaList() {
    std::vector<Symbol> result;
    auto symbol = nextSymbol();
    assertSymbolType(symbol, LPAR);
    symbol = nextSymbol();
    while (symbol.getType() !=RPAR)
    {
        if(symbol.getType()== IDENTIFIER || symbol.getType()== INTCONST){
            result.push_back(symbol);
        }
        symbol = nextSymbol();
        if (symbol.getType() == COMMA){
            symbol = nextSymbol();
        }
    }
    return result;
}
std::vector<Symbol> Interpreter::getIdentifierList() {
    auto list = getParaList();
    for (auto it = list.begin(); it != list.end();it++){
        if(it->getType()!= IDENTIFIER){
            issueError("Symbol " + it->getName() + " is not a valid identifier");
        }
    }
}

void Interpreter::issueError(std::string err) {
    std::cerr << "Error: " << err << std::endl;
}

void Interpreter::issueWarning(std::string err) {
    std::cout << "Warning: " << err << std::endl;
}
