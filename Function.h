#include "utility.h"
class Function
{
private:
    std::string _name;
    int _argc;

public:
    Function(std::string name, int argc);
    ~Function();
    
    static Function &getFunctionByName(std::string name);
};

Function::Function(std::string name, int argc):_name(name), _argc(argc)
{
}

Function::~Function()
{
}
