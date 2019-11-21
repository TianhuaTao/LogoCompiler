#include "Variable.h"
#include "utility.h"
Variable noVarInstance("noVar", 0);
std::vector<Variable *> Variable::variableSet;

Variable::Variable(std::string name, int initValue) : _value(initValue), _name(name), id(nextID++) {
    variableSet.push_back(this);
    std::cout << "debug: new Var: " << _name << " value=" << _value << std::endl;
}

Variable::~Variable() {
}

int Variable::nextID = 0;

bool operator==(const Variable &lhs, const Variable &rhs) {
    return lhs.id == rhs.id;
}

Variable &Variable::getVariableByName(std::string name) {
    std::cout << "debug: name=" << name << ", result=";

    Variable *v = nullptr;
    for (auto it = variableSet.rbegin(); it != variableSet.rend(); it++) {
        std::cout << "**********name" << (*it)->getName() << std::endl;
        if ((*it)->getName() == name) {
            v = *it;
            break;
        }
    }
    if (v) {
        std::cout << "found" << std::endl;
        return *v;
    } else {
        std::cout << "not found" << std::endl;
        return noVar();
    }
}
void Variable::deleteVariableByName(std::string name) {
    Variable *v = nullptr;
    auto it = variableSet.rbegin();
    for (; it != variableSet.rend(); it++) {
        if ((*it)->getName() == name) {
            v = *it;
            break;
        }
    }
    if (v) {
        delete v;
        variableSet.erase((it++).base()); // it is reverse iterator
    } else {
        issueRuntimeError("cannot delete variable " + name);
        return;
    }
}

Variable &
Variable::noVar() {
    return noVarInstance;
}

bool operator!=(const Variable &lhs, const Variable &rhs) {
    return !(lhs == rhs);
}

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
            auto &v = Variable::getVariableByName(varName);
            if (v == Variable::noVar()) {
                issueRuntimeError("cannot find variable " + varName);
                return v.getValue();    // value is not defined
            } else
                return v.getValue();
        }

    } else {
        return _value;
    }
}
