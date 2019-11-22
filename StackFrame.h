#if !defined(STACKFRAME_H)
#define STACKFRAME_H

#include <vector>

#include "Variable.h"
// class OpsQueue;
class Function;
struct StackFrame {
    // OpsQueue *opsQueue;
    Function *function;
    size_t ret_pc;
    std::vector<Variable> localVariables;

    StackFrame(Function * function,size_t pc, std::vector<Variable> args):function(function), ret_pc(pc), localVariables(args){}
    ~StackFrame();
    std::vector<Variable>& getLocalVariables(){return localVariables;}
};


#endif // STACKFRAME_H


