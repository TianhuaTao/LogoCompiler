#if !defined(OP_H)
#define OP_H

#include "Pixel.h"
#include "Variable.h"
#include "symbols.h"
#include "VariableWrapper.h"
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
    virtual bool isStartLoopOp() { return false; }
    virtual bool isEndLoopOp() { return false; }
    virtual bool isDefOp() { return false; }
};

class MoveOp : public Op {
private:
    // int step;
    // Variable *var = nullptr;        //deprecated
    VariableWrapper _varWrapper;

public:
    // MoveOp(Executor *executor);
    // MoveOp(Executor *executor, int step);
    // MoveOp(Executor *executor, Variable *var);
    MoveOp(Executor *executor, VariableWrapper vw) : Op(executor), _varWrapper(vw) {}

    ~MoveOp();
    virtual void exec();
};

class TurnOp : public Op {
private:
    // int degree;
    // Variable *var = nullptr;
    VariableWrapper varWrapper;

public:
    // TurnOp(Executor *executor, int degree);
    // TurnOp(Executor *executor, Variable *var);
    TurnOp(Executor *executor, VariableWrapper vw) : Op(executor), varWrapper(vw) {}

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
    EndLoopOp(Executor *executor, Op *start);
    virtual void exec();
    ~EndLoopOp();
    virtual bool isEndLoopOp() { return true; }
};

class ColorOp : public Op {
private:
    // Pixel pixel;
    VariableWrapper r;
    VariableWrapper g;
    VariableWrapper b;

public:
    ColorOp(Executor *executor, VariableWrapper r, VariableWrapper g,VariableWrapper b):Op(executor),r(r),g(g),b(b){}
    ~ColorOp();
    virtual void exec();
};

class AddOp : public Op {
private:
    VariableWrapper var;
    VariableWrapper value;

public:
    AddOp(Executor *executor, VariableWrapper vw, VariableWrapper value);
    ~AddOp();
    virtual void exec();
};

class CallOp : public Op {
private:
    std::string name;
    std::vector<VariableWrapper> argList;

public:
    CallOp(Executor *executor, std::string name, std::vector<VariableWrapper> argList) :Op(executor), name(name), argList(argList) {}
    ~CallOp();
    virtual void exec();
};
class DefOp : public Op {
private:
    VariableWrapper varWrapper;
    std::string name;

public:
    DefOp(Executor *executor, std::string name, VariableWrapper vw);
    ~DefOp();
    virtual void exec();
    virtual bool isDefOp() { return true; }
};

#endif // OP_H
