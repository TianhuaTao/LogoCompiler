#include "Op.h"
#include "Executor.h"
#include <cmath>
#include <iostream>
Op::Op()
{
}

Op::~Op()
{
}

Op::Op(Executor *executor) : executor(executor)
{
}

cloakOp::cloakOp(Executor *executor) : Op(executor)
{
    
}

cloakOp::~cloakOp()
{
}

void cloakOp::exec()
{
    executor->clocked = true;
}

StartLoopOp::StartLoopOp(Executor *executor,int loops):Op(executor),loops(loops) {
}

StartLoopOp::~StartLoopOp()
{
}

void StartLoopOp::exec()
{   
    // will execute only once, just check if loops = 0
    if(loops< 0){
        issueError("loop value should be non-negative");
    }
    if(loops==0){
        bool isEndLoop = false;

        while (!isEndLoop && executor->pc< executor->current_ops->size()) {
            executor->pc++;
            std::vector<Op *> *ops = executor->current_ops;
            Op *op = (*ops)[executor->pc];
            isEndLoop = (op== end);
        }

        executor->pc++;
    }
}

EndLoopOp::EndLoopOp(Executor *executor, Op *start) :Op(executor) ,start(start){
}

EndLoopOp::~EndLoopOp()
{
    size_t maybe_pc = executor->pc;
    bool isStartLoop = false;
    Op *op = nullptr;
    while (!isStartLoop) {
        maybe_pc--;
        std::vector<Op *> *ops = executor->current_ops;
        op = (*ops)[executor->pc];
        isStartLoop = (op == start);
    }
    StartLoopOp *sop = dynamic_cast<StartLoopOp *>(op);
    if (sop->getLoopRemain() > 0){
        sop->minusOneLoop();
        executor->pc = maybe_pc;
    }else
    {
        // don't need to change pc;
    }
}

void EndLoopOp::exec()
{

}


MoveOp::MoveOp(Executor *executor, int step) : Op(executor), step(step)
{
}

MoveOp::~MoveOp()
{
}

void MoveOp::exec()
{
    int l;
    if (var)
    {
        l = var->getValue();
    }
    else
    {
        l = step;
    }
    std::cout << "MOVE " << l << " steps" << std::endl;

    if (executor->clocked)
    {
        double dx, dy;
        dx = l * cos(executor->degree * PI / 180.0);
        dx = l * sin(executor->degree * PI / 180.0);
        executor->logical_pen_x += dx;
        executor->logical_pen_x += dy;
    }
    else
    {

        // do some real drawing
        for (int i = 0; i < l; i++)
        {
            int physical_pen_x = executor->logical_pen_x;
            int physical_pen_y = executor->logical_pen_y;
            executor->drawPixel(physical_pen_x, physical_pen_y);
            executor->logical_pen_x += 1 * cos(executor->degree * PI / 180.0);
            executor->logical_pen_y += 1 * sin(executor->degree * PI / 180.0);
        }
    }
}

MoveOp::MoveOp(Executor *executor, Variable *var)
{
}

TurnOp::TurnOp(Executor *executor, int degree) : Op(executor), degree(degree)
{
}

TurnOp::~TurnOp()
{
}

void TurnOp::exec()
{
    if (var)
    {
        int d = var->getValue();
        std::cout << "TURN " << d << " degree" << std::endl;
        executor->degree -= d;
    }
    else
    {
        std::cout << "TURN " << degree << " degree" << std::endl;
        executor->degree -= degree;
    }
    executor->degree = executor->degree % 360;
}

TurnOp::TurnOp(Executor *executor, Variable *var)
{
}

ColorOp::ColorOp(Executor *executor, Pixel p) : Op(executor), pixel(p)
{
}

ColorOp::~ColorOp()
{
}
void ColorOp::exec()
{
    std::cout << "COLOR"
              << "[" << (int)pixel.r << "," << (int)pixel.g << "," << (int)pixel.b << "]" << std::endl;
    executor->penColor = pixel;
    executor->clocked = false;
}

AddOp::AddOp(Executor *executor, Variable &v, int value) : Op(executor), var(v), value(value)
{
}

AddOp::~AddOp()
{
}

void AddOp::exec()
{
    
}

CallOp::CallOp(Executor *executor, std::string name, std::vector<Symbol> paraList) : Op(executor) {
}

CallOp::~CallOp() {
}