#if !defined(OP_H)
#define OP_H

#include "Variable.h"
#include "Pixel.h"
#include "symbols.h"
class Executor;
class Op
{
private:
protected:
    Executor *executor = nullptr;

public:
    Op();
    Op(Executor *executor);
    virtual ~Op();
    virtual void exec() = 0;
    virtual bool isStartLoopOp() { return false; }
    virtual bool isEndLoopOp() { return false; }
};

class MoveOp : public Op
{
private:
    int step;
    Variable *var = nullptr;

public:
    // MoveOp(Executor *executor);
    MoveOp(Executor *executor, int step);
    MoveOp(Executor *executor, Variable *var);
    ~MoveOp();
    virtual void exec();
};

class TurnOp : public Op
{
private:
    int degree;
    Variable *var = nullptr;

public:
    TurnOp(Executor *executor, int degree);
    TurnOp(Executor *executor, Variable *var);

    ~TurnOp();
    virtual void exec();
};

class cloakOp : public Op
{
private:
public:
    cloakOp(Executor *executor);
    ~cloakOp();
    virtual void exec();
};

class StartLoopOp : public Op {
private:
    const int prop_loops;
    int loops;
    Op *end;
    
public:
    StartLoopOp(Executor *executor, int loops);
    virtual void exec();
    void setEndLoopOp(Op *end) { this->end = end; }
    void minusOneLoop() { loops--; }
    int getLoopRemain() { return loops; }
    ~StartLoopOp();
    virtual bool isStartLoopOp() { return true; }
};

class EndLoopOp : public Op {
private:
    Op *start;

public:
    EndLoopOp(Executor *executor,Op *start);
    virtual void exec();
    ~EndLoopOp();
    virtual bool isEndLoopOp() { return true; }
};

class ColorOp : public Op
{
private:
    Pixel pixel;

public:
    ColorOp(Executor *executor, Pixel p);
    ~ColorOp();
    virtual void exec();
};

class AddOp : public Op
{
private:
    Variable &var;
    int value;

public:
    AddOp(Executor *executor, Variable &v, int value);
    ~AddOp();
    virtual void exec();
};


class CallOp:public Op
{
private:
    
public:
    CallOp(Executor *executor,std::string name, std::vector<Symbol> paraList);
    ~CallOp();
};




#endif // OP_H
