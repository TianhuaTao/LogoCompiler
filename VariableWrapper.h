#if !defined(VARIABLEWRAPPER_H)
#define VARIABLEWRAPPER_H
#include <string>

class Variable;


class VariableWrapper
{
private:
    Variable *_variable=nullptr;
    int _value = 0;
    std::string varName;
    bool isVar = false;


public:
    VariableWrapper(Variable *var);
    VariableWrapper(int value);
    VariableWrapper(std::string varName);
    ~VariableWrapper();
    bool isLiteral() const { return _variable == 0; }
    bool isVariable() const{
        return _variable != 0;
    }
    std::string getVariableName() const;
    int getValue() const;
};

#endif // VARIABLEWRAPPER_H
