#if !defined(OP_H)
#define OP_H

#include "Variable.h"
class Executor;
class Op {
private:
protected:
    Executor *executor = nullptr;

public:
    Op();
    Op(Executor *executor);
    virtual ~Op();
    virtual void exec() = 0;
};

class MoveOp : public Op {
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

class TurnOp : public Op {
private:
    int degree;
    Variable *var = nullptr;

public:
    TurnOp(Executor *executor, int degree);
    TurnOp(Executor *executor, Variable *var);

    ~TurnOp();
    virtual void exec();
};

class cloakOp : public Op {
private:
public:
    cloakOp(Executor *executor);
    ~cloakOp();
    virtual void exec();
};

class StartLoopOp {
private:
public:
    StartLoopOp(int loops);
    virtual void exec();
    ~StartLoopOp();
};

class EndLoopOp {
private:
public:
    EndLoopOp(Op *start);
    virtual void exec();
    ~EndLoopOp();
};

class AddOp {
private:
public:
    AddOp(Variable *v, int value);
    ~AddOp();
    virtual void exec();
};

#endif // OP_H
