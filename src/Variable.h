#if !defined(VARIABLE_H)
#define VARIABLE_H

#include <string>
#include <set>
#include <map>
#include <vector>
class Variable
{
    friend bool operator==(const Variable &lhs, const Variable &rhs);
    typedef int ValueType;

private:
    ValueType _value;
    std::string _name;
    const int id;
    static int nextID;
    bool isConst = false;


public:
    Variable(std::string name, int initValue);
    ~Variable();
    ValueType getValue() const
    {
        return _value;
    }
    void addValue(int value) { _value += value; }
    std::string getName() const { return _name; }
    // static Variable &getVariableByName(std::string name);
    // static void deleteVariableByName(std::string name);
    static  Variable &noVar();
};
extern Variable noVarInstance;

bool operator==(const Variable &lhs, const Variable &rhs);
bool operator!=(const Variable &lhs, const Variable &rhs);



#endif // VARIABLE_H


