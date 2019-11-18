#include "Variable.h"
 Variable noVarInstance("noVar", 0);
Variable::Variable(std::string name , int initValue):_value(initValue),_name(name), id(nextID++)
{
}

Variable::~Variable()
{
}

int Variable::nextID = 0;

bool operator==(const Variable &lhs, const Variable &rhs)
{
    return lhs.id == rhs.id;
}

Variable &Variable::getVariableByName(std::string name) {
    return noVar();
}

 Variable &Variable::noVar() {
    return noVarInstance;
}

bool operator!=(const Variable &lhs, const Variable &rhs)
{
    return !(lhs == rhs);
}
