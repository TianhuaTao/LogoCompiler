#include "Pixel.h"
#include "Variable.h"
#include <cmath>
#include<vector>
#include "Op.h"
#include "OpsQueue.h"
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

private:
    unsigned char *buffer = nullptr;
    double logical_pen_x;
    double logical_pen_y;
    int degree = 90;    // range [0,359]
    size_t pc;
    std::vector<OpsQueue *> allOps;
    OpsQueue *current_OpsQueue;
    std::vector<Op *> *current_ops;

    bool clocked = false;
    Pixel penColor;
    Pixel& getBufferPixel(int x, int y);
    int width;
    int height;
    Pixel _noPixel; // a special pixel, all invalid pixels point to this
public:
    Executor();
    ~Executor();
    void run();
    void initNewBuffer(int width, int height);
    void setBackground(int R, int G, int B);
    void setPenPosition(int x, int y);
    void def(std::string name, int value);
    void add(Variable &v, int value);
    void move(const Variable &v);
    void move(int step);
    void cloak();
    void turn(int angle);
    void turn(const Variable &v);
    void setPenColor(int r, int g, int b);
    void loop(int value);
    void endLoop();
    void startFuncDef(std::string name, int argc);
    void drawPixel(int x,int y);
    void writeFile();
};
