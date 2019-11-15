#include "Interpreter.h"
#include <sstream>
#include "utility.h"

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}
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
        issueError("Expecting a value");
    }
    int result;
    result = stringToInt(lexQueue.front());
    lexQueue.pop();
    return result;
}

std::string Interpreter::nextSymbol()
{
    if (lexQueue.empty())
    {
        issueError("Expecting a symbol");
    }
    std::string result = lexQueue.front();
    lexQueue.pop();
    return result;
}

void Interpreter::processSymbol(const std::string &symbol)
{
    if (symbol == "TURN")
    {
        auto sym = nextSymbol();
        if (isInt(sym))
        {
            int value = stringToInt(sym);
            executor.turn(value);
        }
        else
        {
            Variable &v = Variable::getVariableByName(sym);
            if (v == Variable::noVar())
            {
                issueError("Variable not found: " + sym);
            }
            executor.turn(v);
        }
    }
    if (symbol == "MOVE")
    {
        auto sym = nextSymbol();
        if (isInt(sym))
        {
            int value = stringToInt(sym);
            executor.move(value);
        }
        else
        {
            Variable &v = Variable::getVariableByName(sym);
            if (v == Variable::noVar())
            {
                issueError("Variable not found: " + sym);
            }
            executor.move(v);
        }
    }
    if (symbol == "DEF")
    {
        std::string name = nextSymbol();
        int value = nextInt();
        executor.def(name, value);
    }
    if (symbol == "ADD")
    {
        std::string name = nextSymbol();
        int value = nextInt();
        executor.add(name, value);
    }
    if (symbol == "COLOR")
    {
        int r, g, b;
        r = nextInt();
        g = nextInt();
        b = nextInt();
        executor.setPenColor(r, g, b);
    }
    if (symbol == "CLOAK")
    {
        executor.cloak();
    }

    if (symbol == "LOOP")
    {
        int loop = nextInt();
    }
    if (symbol == "FUNC")
    {
    }
    if (symbol == "END")
    {
        auto sym = nextSymbol();
    }

    if (symbol == "CALL")
    {
        auto funcName = nextSymbol();
    }
}