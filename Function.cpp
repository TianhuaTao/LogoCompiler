#include "Function.h"
#include "VariableWrapper.h"
Function::Function(std::string name, std::vector<VariableWrapper> paraList) : _name(name), paraList(paraList) {
}

Function::~Function() {
}

