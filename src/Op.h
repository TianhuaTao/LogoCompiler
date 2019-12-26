#if !defined(OP_H)
#define OP_H
#include <iostream>
#include "Pixel.h"
#include "Variable.h"
#include "symbols.h"
#include "VariableWrapper.h"
class Executor;
extern bool verbose;
// short for operation
class Op {
private:
protected:
    Executor *executor = nullptr;
    int lineno;
public:
    Op();
    Op(Executor *executor, int lineno = -1);
    virtual ~Op();
    virtual void exec() = 0;
    virtual bool isStartLoopOp() { return false; }
    virtual bool isEndLoopOp() { return false; }
    virtual bool isDefOp() { return false; }
    virtual int getLineNo() { return lineno; }
    virtual std::string OpName() { return "General Op"; }
};

class MoveOp : public Op {
private:
    VariableWrapper _varWrapper;

public:
    MoveOp(Executor *executor, VariableWrapper vw, int lineno = -1) : Op(executor, lineno), _varWrapper(vw) {
        if (lineno == -1) {
            std::cout << "Debug Info: lineno is -1" << std::endl;
            std::cout << OpName() << std::endl;
        }
    }
    ~MoveOp();
    virtual void exec();
    virtual std::string OpName() { return "MoveOp"; }
};

class TurnOp : public Op {
private:
    VariableWrapper varWrapper;

public:
    TurnOp(Executor *executor, VariableWrapper vw, int lineno = -1) : Op(executor,lineno), varWrapper(vw) {
        if (lineno == -1) {
            std::cout << "Debug Info: lineno is -1" << std::endl;
            std::cout << OpName() << std::endl;
        }
    }
    ~TurnOp();
    virtual void exec();
    virtual std::string OpName() { return "TurnOp"; }
};

class CloakOp : public Op {
private:
public:
    CloakOp(Executor *executor, int lineno = -1);
    ~CloakOp();
    virtual void exec();
    virtual std::string OpName() { return "CloakOp"; }
};

class StartLoopOp : public Op {
private:
    const int prop_loops;
    int loops;
    Op *end =  nullptr;

public:
    StartLoopOp(Executor *executor, int loops, int lineno = -1);
    virtual void exec();
    void setEndLoopOp(Op *end) { this->end = end; }
    void minusOneLoop() { loops--; }
    int getLoopRemain() { return loops; }
    ~StartLoopOp();
    virtual bool isStartLoopOp() { return true; }
    virtual std::string OpName() { return "StartLoopOp"; }
};

class EndLoopOp : public Op {
private:
    Op *start;

public:
    EndLoopOp(Executor *executor, Op *start, int lineno = -1);
    virtual void exec();
    ~EndLoopOp();
    virtual bool isEndLoopOp() { return true; }
};

class ColorOp : public Op {
private:
    VariableWrapper r;
    VariableWrapper g;
    VariableWrapper b;

public:
    ColorOp(Executor *executor, VariableWrapper r, VariableWrapper g, VariableWrapper b, int lineno = -1) : Op(executor, lineno), r(r), g(g), b(b) {
        if (lineno == -1) {
            std::cout << "Debug Info: lineno is -1" << std::endl;
            std::cout << OpName() << std::endl;
        }
    }
    ~ColorOp();
    virtual void exec();
    virtual std::string OpName() { return "ColorOp"; }
};

class AddOp : public Op {
private:
    VariableWrapper var;
    VariableWrapper value;

public:
    AddOp(Executor *executor, VariableWrapper vw, VariableWrapper value, int lineno = -1);
    ~AddOp();
    virtual void exec();
    virtual std::string OpName() { return "AddOp"; }
};

class CallOp : public Op {
private:
    std::string name;
    std::vector<VariableWrapper> argList;

public:
    CallOp(Executor *executor, std::string name, std::vector<VariableWrapper> argList, int lineno = -1) : Op(executor, lineno), name(name), argList(argList) {
        if (lineno == -1) {
            std::cout << "Debug Info: lineno is -1" << std::endl;
            std::cout << OpName() << std::endl;
        }
    }
    ~CallOp();
    virtual void exec();
    virtual std::string OpName() { return "CallOp"; }
};
class DefOp : public Op {
private:
    VariableWrapper varWrapper;
    std::string name;

public:
    DefOp(Executor *executor, std::string name, VariableWrapper vw, int lineno = -1);
    ~DefOp();
    virtual void exec();
    virtual bool isDefOp() { return true; }
    virtual std::string OpName() { return "DefOp"; }
};

class SetPenWidthOp : public Op {
private:
    VariableWrapper varWrapper;
public:
    SetPenWidthOp(Executor *executor, VariableWrapper vw, int lineno = -1);
    ~SetPenWidthOp();
    virtual void exec();
    virtual std::string OpName() { return "SetPenWidthOp"; }
};

class FillOp : public Op {
private:
    
public:
    FillOp(Executor *executor, int lineno = -1);
    ~FillOp();
    virtual void exec();
    virtual std::string OpName() { return "FillOp"; }
};





#endif // OP_H
