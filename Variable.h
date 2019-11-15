#include <string>
class Variable
{
    typedef ValueType int;
private:
    ValueType _value;
    std::string _name;
public:
    Variable(std::string name , int initValue);
    ~Variable();
    ValueType getValue() const {
        return _value;
    }
    static Variable& getVariableByName(std::string name);
    static const Variable&  noVar();
};


