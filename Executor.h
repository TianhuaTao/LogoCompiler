#include "Pixel.h"
#include "Variable.h"
#include <cmath>
#include<vector>
#include "Op.h"
const double PI = 3.14159265359;
class Executor
{
private:
    char *buffer = nullptr;
    int pen_x;
    int pen_y;
    double angle = PI;
    std::vector<Op*> ops;
public:
    Executor();
    ~Executor();
    void initNewBuffer(int width, int height);
    void setBackground(int R, int G, int B);
    void setPenPosition(int x, int y);
    void def(std::string name, int value);
    void add(std::string name, int value);
    void move(const Variable &v);
    void move(int step);
    void cloak();
    void turn(int angle);
    void turn(const Variable &v);
    void setPenColor(int r, int g, int b);
    void loop(int value);
    void startFuncDef(std::string name, int argc);
    void draw(int pixel);
};
