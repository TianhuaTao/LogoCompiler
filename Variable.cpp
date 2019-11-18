#include "Variable.h"

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
bool operator!=(const Variable &lhs, const Variable &rhs)
{
    return !(lhs == rhs);
}
