#if !defined(FUNCTION_H)
#define FUNCTION_H

#include "utility.h"
#include <string>
#include <vector>
#include "VariableWrapper.h"
class Op;
class Function {
private:
    std::string _name;
    int _argc;
    std::vector<Op *> _ops; // A function is made up of a group of Ops
    std::vector<VariableWrapper> paraList;
public:
    Function(std::string name, std::vector<VariableWrapper> paraList);
    ~Function();
    std::vector<Op *> *getOps() {
        return &_ops;
    }
    std::string getName() const {
        return _name;
    }
    std::vector<VariableWrapper>& getParaList(){
        return paraList;
    }
    // static Function &getFunctionByName(std::string name);
};




#endif // FUNCTION_H

