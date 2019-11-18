#if !defined(OP_H)
#define OP_H

#include "Variable.h"

class Op
{
private:
    
public:
    Op();
    virtual ~Op();
    virtual void exec() = 0;
};




class cloakOp:public Op
{
private:
    
public:
    cloakOp();
    ~cloakOp();
};


class StartLoopOp
{
private:
    
public:
    StartLoopOp(int loops);
    ~StartLoopOp();
};



class EndLoopOp
{
private:
    
public:
    EndLoopOp(Op* start);
    ~EndLoopOp();
};




class AddOp
{
private:
    
public:
    AddOp(Variable* v, int value);
    ~AddOp();
};


#endif // OP_H


