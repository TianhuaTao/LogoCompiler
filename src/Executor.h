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
    friend class Interpreter;
    friend class MoveOp;
    friend class TurnOp;
    friend class AddOp;
    friend class ColorOp;
    friend class EndLoopOp;
    friend class StartLoopOp;
    friend class CloakOp;
    friend class DefOp;
    friend class CallOp;
    friend class FillOp;
    friend class SetPenWidthOp;

private:
    static Executor *globalExe;
    unsigned char *buffer = nullptr;    // pixels

    double logical_pen_x;
    double logical_pen_y;
    int degree = 90; // range [0,359]

    size_t pc; //program counter

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
    int penWidth=1;
    Pixel _noPixel; // a special pixel, all invalid pixels point to this
public:
    Executor();
    ~Executor();
    static Variable &getVariableByNameStatic(std::string name);
    Variable &getVariableByName(std::string name);
    void run();
    void step();

    void initNewBuffer(int width, int height);
    void setBackground(int R, int G, int B);
    void setPenPosition(int x, int y);

    void def(std::string name, int value, int lineno = -1);
    void add(VariableWrapper vw, VariableWrapper value, int lineno = -1);
    void move(std::string varName, int lineno = -1);
    void move(int step,int lineno = -1);
    void cloak(int lineno = -1);
    // void turn(int angle);
    // void turn(std::string varName);
    void turn(VariableWrapper vw, int lineno = -1);
    void setPenColor(VariableWrapper r, VariableWrapper g, VariableWrapper b, int lineno = -1);
    void setPenWidth(VariableWrapper w, int lineno = -1);
    void fill(int lineno=-1);
    void loop(int value, int lineno = -1);
    void endLoop( int lineno = -1);
    void startFuncDef(std::string name, std::vector<VariableWrapper> list, int lineno = -1);
    void endFuncDef( int lineno = -1);
    void drawPixel(int x, int y);
    void writeFile(std::string filename);
    void call(std::string name, std::vector<VariableWrapper> paraList, int lineno = -1);
};

#endif // EXECUTOR_H
