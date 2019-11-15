#include <string>
#include <set>
class Variable
{
    friend bool operator==(const Variable &lhs, const Variable &rhs);
    typedef int ValueType;

private:
    ValueType _value;
    std::string _name;
    const int id;
    static int nextID;
    static std::set<std::string, Variable*> variableSet;
public:
    Variable(std::string name, int initValue);
    ~Variable();
    ValueType getValue() const
    {
        return _value;
    }
    static Variable &getVariableByName(std::string name);
    static const Variable &noVar();
};

bool operator==(const Variable &lhs, const Variable &rhs)
{
    return lhs.id == rhs.id;
}
bool operator!=(const Variable &lhs, const Variable &rhs)
{
    return !(lhs == rhs);
}
