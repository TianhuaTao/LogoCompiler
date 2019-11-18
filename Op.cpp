#include "Op.h"
#include "Executor.h"
#include <cmath>
#include <iostream>
Op::Op() {
}

Op::~Op() {
}

Op::Op(Executor *executor) : executor(executor) {
}

cloakOp::cloakOp(Executor *executor) : Op(executor) {
}

cloakOp::~cloakOp() {
}

void cloakOp::exec() {
}

StartLoopOp::StartLoopOp(int loops) {
}

StartLoopOp::~StartLoopOp() {
}

void StartLoopOp::exec() {
}

EndLoopOp::EndLoopOp(Op *start) {
}

EndLoopOp::~EndLoopOp() {
}

void EndLoopOp::exec() {
}

AddOp::AddOp(Variable *v, int value) {
}

AddOp::~AddOp() {
}

void AddOp::exec() {
}

MoveOp::MoveOp(Executor *executor, int step) : Op(executor), step(step) {
}

MoveOp::~MoveOp() {
}

void MoveOp::exec() {
    int l;
    if (var) {
        l = var->getValue();
    } else {
        l = step;
    }
    std::cout << "MOVE " << l << " steps" << std::endl;

    if (executor->clocked) {
        double dx, dy;
        dx = l * cos(executor->degree);
        dx = l * sin(executor->degree);
        executor->logical_pen_x += dx;
        executor->logical_pen_x += dy;
    } else {

        // do some real drawing
        for (int i = 0; i < l; i++) {
            int physical_pen_x = executor->logical_pen_x;
            int physical_pen_y = executor->logical_pen_y;
            executor->drawPixel(physical_pen_x, physical_pen_y);
            executor->logical_pen_x += 1 * cos(executor->degree);
            executor->logical_pen_y += 1 * sin(executor->degree);
        }
    }
}

MoveOp::MoveOp(Executor *executor, Variable *var) {
}

TurnOp::TurnOp(Executor *executor, int degree) : Op(executor), degree(degree) {
}

TurnOp::~TurnOp() {
}

void TurnOp::exec() {
    if (var) {
        int d = var->getValue();
        std::cout << "TURN " << d << " degree" << std::endl;
        executor->degree -= d;
    } else {
        std::cout << "TURN " << degree << " degree" << std::endl;
        executor->degree -= degree;
    }
    executor->degree = executor->degree % 360;
}

TurnOp::TurnOp(Executor *executor, Variable *var) {
}
