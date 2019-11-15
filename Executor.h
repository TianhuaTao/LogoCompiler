#include "Pixel.h"
#include "Variable.h"
class Executor
{
private:
    char* buffer = nullptr;
public:
    Executor();
    ~Executor();
    void initNewBuffer(int width, int height);
    void setBackground(int R, int G, int B);
    void setPenPosition(int x, int y);
    void def(std::string name, int value);
    void add(std::string name, int value);
    void move(const Variable& v);
    void move(int step);
    void cloak();
};

