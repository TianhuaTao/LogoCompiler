#include "Variable.h"

Variable::Variable(std::string name , int initValue):_value(initValue),_name(name), id(nextID++)
{
}

Variable::~Variable()
{
}

int Variable::nextID = 0;

