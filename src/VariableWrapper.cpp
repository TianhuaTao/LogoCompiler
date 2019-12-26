
#include "VariableWrapper.h"
#include "Executor.h"
#include "Variable.h"
#include "utility.h"
VariableWrapper::VariableWrapper(int value) : _value(value) {
}
VariableWrapper::~VariableWrapper() {
}

VariableWrapper::VariableWrapper(Variable *var) : _variable(var) {
    isVar = true;
}
VariableWrapper::VariableWrapper(std::string varName) : varName(varName) {
    isVar = true;
}
int VariableWrapper::getValue() const {
    if (isVar) {
        if (_variable) {
            return _variable->getValue();
        } else {
            auto &v = Executor::getVariableByNameStatic(varName);
            if (v == Variable::noVar()) {
                issueRuntimeError("cannot find variable " + varName);
                return v.getValue(); // value is not defined
            } else
                return v.getValue();
        }

    } else {
        return _value;
    }
}

std::string VariableWrapper::getVariableName() const {
    if (isVar) {
        if (_variable) {
            return _variable->getName();
        } else {
            return varName;
        }
    } else {
        return "$NO_NAME$";
    }
}
