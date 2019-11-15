#include "Interpreter.h"
#include <sstream>
#include "utility.h"
void Interpreter::compile(const char *filename)
{
    std::ifstream in;
    in.open(filename);
    if (in.is_open())
    {
        std::string lex;
        while (in >> lex)
        {
            this->lexQueue.push(lex);
        }
        // Todo: check state
        in.close();

        // Todo: lexer check

        // header
        lexQueue.pop(); // @SIZE
        int width, height;
        width = nextInt();
        height = nextInt();
        executor.initNewBuffer(width, height);

        lexQueue.pop(); // @BACKGROUND
        int r, g, b;
        r = nextInt();
        g = nextInt();
        b = nextInt();
        executor.setBackground(r, g, b);

        lexQueue.pop(); // @POSITION
        int x, y;
        x = nextInt();
        y = nextInt();
        executor.setPenPosition(x, y);

        // body
        while (!lexQueue.empty())
        {
            std::string next = nextSymbol();
            processSymbol(next);
        }
    }
}

int Interpreter::nextInt()
{
    if (lexQueue.empty())
    {
        // Todo: issure error
    }
    int result;
    result = stringToInt(lexQueue.front());
    lexQueue.pop();
    return result;
}

std::string Interpreter::nextSymbol(){
    if (lexQueue.empty())
    {
        // Todo: issure error
    }
    std::string result =lexQueue.front();
    lexQueue.pop();
    return result;
}

void Interpreter::processSymbol(const std::string& symbol){
    if(symbol == "TURN"){

    }
    if(symbol == "MOVE"){
        auto sym = nextSymbol();
        if(isInt(sym)){
            int value = stringToInt(sym);
            executor.move(value);
        }else
        {
            Variable& v = Variable::getVariableByName(sym);
            if(v == Variable::noVar()){
                // Todo: issue error
            }
            executor.move(v);
        }
        
    }
    if(symbol == "DEF"){
        std::string name = nextSymbol();
        int value = nextInt();
        executor.def(name,value );
    }
    if(symbol == "ADD"){
        std::string name = nextSymbol();
        int value = nextInt();
        executor.add(name,value );
    }
    if(symbol == "COLOR"){

    }
    if(symbol == "CLOAK"){
        executor.cloak(v);
    }

    if(symbol == "LOOP"){

    }

    if(symbol == "END"){

    }
}