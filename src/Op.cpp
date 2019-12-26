#include "Op.h"
#include "Executor.h"
// #include "OpsQueue.h"
#include "Function.h"
#include "StackFrame.h"
#include "VariableWrapper.h"
#include "utility.h"
#include <cmath>
#include <iostream>
Op::Op() {
}

Op::~Op() {
}

Op::Op(Executor *executor, int lineno) : executor(executor), lineno(lineno) {
    if (lineno == -1) {
        std::cout << "Debug Info: Op lineno is -1" << std::endl;
    }
}

CloakOp::CloakOp(Executor *executor, int lineno) : Op(executor, lineno) {
    if (lineno == -1) {
        std::cout << "Debug Info: lineno is -1" << std::endl;
        std::cout << OpName() << std::endl;
    }
}

CloakOp::~CloakOp() {
}

void CloakOp::exec() {
    if (verbose)
        std::cout << "CLOAK " << std::endl;
    executor->clocked = true;
}

StartLoopOp::StartLoopOp(Executor *executor, int loops, int lineno) : prop_loops(loops), Op(executor, lineno) {
    if (lineno == -1) {
        std::cout << "Debug Info: lineno is -1" << std::endl;
        std::cout << OpName() << std::endl;
    }
}

StartLoopOp::~StartLoopOp() {
}

void StartLoopOp::exec() {
    if (!end) {
        issueRuntimeError("END LOOP not found", getLineNo());
    }

    // will execute only once, just check if loops = 0
    loops = prop_loops;
    if (verbose) {
        std::cout << "LOOP " << loops << std::endl;
    }

    if (loops < 0) {
        issueError("loop value should be non-negative");
    } else if (loops == 0) {
        bool isEndLoop = false;

        while (!isEndLoop && executor->pc < executor->current_ops->size()) {
            executor->pc++;
            // std::cout << "\tPC = " << executor->pc << std::endl;
            std::vector<Op *> *ops = executor->current_ops;
            Op *op = (*ops)[executor->pc];
            isEndLoop = (op == end);
        }
    } else {
        loops--;
    }
}

EndLoopOp::EndLoopOp(Executor *executor, Op *start, int lineno) : Op(executor, lineno), start(start) {
    if (lineno == -1) {
        std::cout << "Debug Info: lineno is -1" << std::endl;
        std::cout << OpName() << std::endl;
    }
}

EndLoopOp::~EndLoopOp() {
}

void EndLoopOp::exec() {
    if (verbose)
        std::cout << "ONE loop finished" << std::endl;

    size_t maybe_pc = executor->pc;
    bool isStartLoop = false;
    Op *op = nullptr;
    while (!isStartLoop) {
        maybe_pc--;
        std::vector<Op *> *ops = executor->current_ops;
        op = (*ops)[maybe_pc];
        isStartLoop = (op == start);
    }
    // std::cout << "\tfound corresponding START LOOP" << std::endl;

    StartLoopOp *sop = dynamic_cast<StartLoopOp *>(op);
    // std::cout << "\t" << sop->getLoopRemain() << " loops left" << std::endl;

    if (sop->getLoopRemain() > 0) {
        sop->minusOneLoop();
        executor->pc = maybe_pc;
    } else {
        // don't need to change pc;
    }
}

MoveOp::~MoveOp() {
}

void MoveOp::exec() {
    int l;
    l = _varWrapper.getValue();
    if (verbose) {
        std::cout << "MOVE " << l << " steps" << std::endl;
        std::cout << "\tlogical_location:[" << executor->logical_pen_x << "," << executor->logical_pen_y << "]" << std::endl;
    }

    if (executor->clocked) {
        double dx, dy;
        dx = l * cos(executor->degree * PI / 180.0);
        dy = l * sin(executor->degree * PI / 180.0);
        executor->logical_pen_x += dx;
        executor->logical_pen_y += dy;
    } else {

        // do some real drawing
        for (int i = 0; i < l; i++) {
            int width = executor->penWidth;
            int physical_pen_x = static_cast<int>(executor->logical_pen_x + 0.5);
            int physical_pen_y = static_cast<int>(executor->logical_pen_y + 0.5);
            for (int x = physical_pen_x - width / 2; x < physical_pen_x + width / 2 + 1; x++) {
                for (int y = physical_pen_y - width / 2; y < physical_pen_y + width / 2 + 1; y++) {
                    executor->drawPixel(x, y);
                }
            }
            executor->logical_pen_x += 1 * cos(executor->degree * PI / 180.0);
            executor->logical_pen_y += 1 * sin(executor->degree * PI / 180.0);
        }
    }
}

TurnOp::~TurnOp() {
}

void TurnOp::exec() {
    int d = varWrapper.getValue();

    if (verbose) {
        std::cout << "TURN " << d << " degree" << std::endl;
    }
    executor->degree -= d;
    if (verbose) {
        std::cout << "\tdegree state: " << executor->degree << std::endl;
    }
    executor->degree = (executor->degree + 360) % 360;
}

ColorOp::~ColorOp() {
}
void ColorOp::exec() {
    int rr = r.getValue();
    int gg = g.getValue();
    int bb = b.getValue();
    if (verbose) {
        std::cout << "COLOR"
                  << "[" << rr << "," << gg << "," << bb << "]" << std::endl;
    }
    if (rr > 255 || gg > 255 || bb > 255 || rr < 0 || gg < 0 || bb < 0) {
        issueRuntimeWarning("Color value out of range, value larger than 255 will be set to 255, value smaller than 0 will be set 0");
    }
    rr = min(rr, 255);
    rr = max(rr, 0);
    gg = min(gg, 255);
    gg = max(gg, 0);
    bb = min(bb, 255);
    bb = max(bb, 0);

    Pixel pixel(rr, gg, bb, 1);
    executor->penColor = pixel;
    executor->clocked = false;
    // std::cout << "ColorOp::exec() done" << std::endl;
}

AddOp::AddOp(Executor *executor, VariableWrapper vw, VariableWrapper value, int lineno) : Op(executor, lineno), var(vw), value(value) {
    if (lineno == -1) {
        std::cout << "Debug Info: lineno is -1" << std::endl;
        std::cout << OpName() << std::endl;
    }
}

AddOp::~AddOp() {}

void AddOp::exec() {
    if (verbose) {
        std::cout << "ADD " << var.getVariableName() << " " << value.getValue() << std::endl;
    }
    Variable &v = Executor::getVariableByNameStatic(var.getVariableName());
    if (v == Variable::noVar()) {
    } else {
        v.addValue(value.getValue());
    }
}

CallOp::~CallOp() {}
void CallOp::exec() {
    if (verbose) {
        std::cout << "CALL " << name << " "
                  << "args=[";

        for (auto it = argList.begin(); it != argList.end(); it++) {
            std::cout << it->getValue();
            if (it + 1 != argList.end()) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
    // find ops from allOps, push stack
    Function *func = nullptr;
    for (auto it = executor->allFunctions.begin(); it != executor->allFunctions.end(); it++) {
        if ((*it)->getName() == name) {
            func = *it;
        }
    }
    if (func) {
        //create stack frame
        executor->callStack.push_back(StackFrame(func, executor->pc, std::vector<Variable>()));
        //push args
        std::vector<VariableWrapper> &paraList = func->getParaList();
        if (paraList.size() != argList.size()) {
            issueRuntimeError("arguments do not match", getLineNo());
        }

        for (size_t i = 0; i < argList.size(); i++) {
            auto &frame = executor->callStack[executor->callStack.size() - 1];
            auto &vars = frame.localVariables;
            int argValue = argList[i].getValue();

            std::string paraName = paraList[i].getVariableName();
            vars.push_back(Variable(paraName, argValue));
        }
        executor->current_function = func;
        executor->current_ops = func->getOps();
        executor->pc = -1; // pc will add 1 after CallOp is executed
    } else {
        // func not defined
        issueRuntimeError("function " + name + " not found");
    }
}
DefOp::DefOp(Executor *executor, std::string name, VariableWrapper vw, int lineno) : Op(executor, lineno), name(name), varWrapper(vw) {
}

DefOp::~DefOp() {
}

void DefOp::exec() {
    if (verbose)
        std::cout << "DEF " << name << " " << varWrapper.getValue() << std::endl;
    bool defined = false;
    auto index = executor->callStack.size() - 1; // the index of the last frame
    StackFrame &localStackFrame = executor->callStack[index];
    std::vector<Variable> &localVars = localStackFrame.getLocalVariables();
    // check if a variable called [name] is in localVars
    for (auto it = localVars.begin(); it != localVars.end(); it++) {
        if (it->getName() == name) {
            defined = true;
            break;
        }
    }
    if (!defined) {
        // Variable *v = new Variable(name, varWrapper.getValue());
        localVars.push_back(Variable(name, varWrapper.getValue()));
    } else {
        issueRuntimeError("Variable " + name + " is already defined");
    }
}

SetPenWidthOp::SetPenWidthOp(Executor *executor, VariableWrapper vw, int lineno) : Op(executor, lineno), varWrapper(vw) {
}

SetPenWidthOp::~SetPenWidthOp() {
}

void SetPenWidthOp::exec() {
    int w = varWrapper.getValue();
    if(verbose)
        std::cout << "PENWIDTH " << w << std::endl;
    if (w > 0)
        executor->penWidth = w;
    else {
        issueError("Pen width should be larger than 1");
    }
}

FillOp::FillOp(Executor *executor, int lineno) : Op(executor, lineno) {
}

FillOp::~FillOp() {
}

void FillOp::exec() {
    std::cout << "FILL" << std::endl;
}