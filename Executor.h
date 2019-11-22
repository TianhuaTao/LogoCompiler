#if !defined(EXECUTOR_H)
#define EXECUTOR_H

#include "Op.h"
#include "Pixel.h"
#include "Variable.h"
#include <cmath>
#include <stack>
#include <vector>
#include "StackFrame.h"
class OpsQueue;
class Function;
const double PI = 3.14159265359;
class Executor
{
    friend class MoveOp;
    friend class TurnOp;
    friend class AddOp;
    friend class ColorOp;
    friend class AddOp;
    friend class EndLoopOp;
    friend class StartLoopOp;
    friend class cloakOp;
    friend class DefOp;
    friend class CallOp;

private:
    static Executor *globalExe;
    unsigned char *buffer = nullptr;
    double logical_pen_x;
    double logical_pen_y;
    int degree = 90; // range [0,359]
    size_t pc;
    // std::vector<OpsQueue *> allOps;
    std::vector<Function *> allFunctions;
    // OpsQueue *current_OpsQueue;     // change together
    Function *current_function;
    std::vector<Op *> *current_ops; // change together
    std::vector<StackFrame> callStack;
    bool clocked = false;
    Pixel penColor;
    Pixel &getBufferPixel(int x, int y);
    int width;
    int height;
    Pixel _noPixel; // a special pixel, all invalid pixels point to this
public:
    Executor();
    ~Executor();
    static Variable &getVariableByNameStatic(std::string name);
    Variable &getVariableByName(std::string name);
    void run();
    void initNewBuffer(int width, int height);
    void setBackground(int R, int G, int B);
    void setPenPosition(int x, int y);
    void def(std::string name, int value);
    // void add(Variable &v, int value);
    void add(VariableWrapper vw, VariableWrapper value);

    void move(std::string varName);
    void move(int step);
    void cloak();
    void turn(int angle);
    void turn(std::string varName);
    void turn(VariableWrapper vw);
    // void setPenColor(int r, int g, int b);
    void setPenColor(VariableWrapper r, VariableWrapper g, VariableWrapper b);

    void loop(int value);
    void endLoop();
    void startFuncDef(std::string name, std::vector<VariableWrapper> list);
    void endFuncDef();
    void drawPixel(int x, int y);
    void writeFile();
    void call(std::string name, std::vector<VariableWrapper> paraList);
};

#endif // EXECUTOR_H
