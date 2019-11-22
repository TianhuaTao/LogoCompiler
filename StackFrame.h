#if !defined(STACKFRAME_H)
#define STACKFRAME_H

#include <vector>

#include "Variable.h"
class OpsQueue;
struct StackFrame
{
    OpsQueue *opsQueue;
    size_t pc;
    std::vector<Variable> localVariables;

    StackFrame(OpsQueue * opsQ,size_t pc, std::vector<Variable> args):opsQueue(opsQ), pc(pc), localVariables(args){}
    ~StackFrame();
    std::vector<Variable>& getLocalVariables(){return localVariables;}
};


#endif // STACKFRAME_H


