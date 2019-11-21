#include "Executor.h"
#include "FileWriter.h"
#include <iostream>
Executor::Executor() {
    penColor = Pixel(0, 0, 0, 1);
    OpsQueue *globalOps = new OpsQueue("0global");
    current_OpsQueue = globalOps;
    current_ops = current_OpsQueue->getOps();

    allOps.push_back(globalOps);
}

Executor::~Executor() {
}

void Executor::initNewBuffer(int width, int height) {
    delete buffer;
    this->width = width;
    this->height = height;
    buffer = new unsigned char[width * height * sizeof(Pixel)];
}

void Executor::turn(const Variable &v) {
}

void Executor::setBackground(int R, int G, int B) {
    Pixel *pixels = reinterpret_cast<Pixel *>(buffer);
    Pixel fill(R, G, B, 1);
    for (size_t i = 0; i < width * height; i++) {
        pixels[i] = fill;
    }
}

void Executor::setPenPosition(int x, int y) {
    logical_pen_x = x;
    logical_pen_y = y;
}

void Executor::def(std::string name, int value) {
}

void Executor::add(Variable &v, int value) {

    Op *op;
    op = new AddOp(this, v, value);
    current_ops->push_back(op);
}

void Executor::move(const Variable &v) {
}

void Executor::move(int step) {
    Op *op;
    op = new MoveOp(this, step);
    current_ops->push_back(op);
}

void Executor::cloak() {
    Op *op;
    op = new cloakOp(this);
    current_ops->push_back(op);
}

void Executor::turn(int degree) {

    Op *op;
    op = new TurnOp(this, degree);
    current_ops->push_back(op);
}

void Executor::setPenColor(int r, int g, int b) {
    Pixel p(r, g, b, 1);
    Op *op;
    op = new ColorOp(this, p);
    current_ops->push_back(op);
}

void Executor::loop(int value) {
    Op *op;
    op = new StartLoopOp(this, value);
    current_ops->push_back(op);
}

void Executor::endLoop() {
    Op *op;
    Op *start = nullptr;
    int cnt = 1;
    for (auto it = current_ops->rbegin(); it != current_ops->rend(); it++) {
        if ((*it)->isEndLoopOp()) {
            cnt++;
        }
        if ((*it)->isStartLoopOp()) {
            cnt--;
            if (cnt == 0) {
                start = *it;
                
                break;
            }
        }
    }
    if (start) {
        op = new EndLoopOp(this, start);
        dynamic_cast<StartLoopOp *>(start)->setEndLoopOp(op);
        current_ops->push_back(op);
    } else {
        issueError("unexpected END LOOP");
    }
}

void Executor::startFuncDef(std::string name, int argc) {
}

void Executor::run() {
    std::cout << current_ops->size() << " ops to run" << std::endl;

    size_t ops_cnt = current_ops->size();
    pc = 0;
    while (pc != current_ops->size()) {
        std::cout << "pc[" << pc << "]: ";

        (*current_ops)[pc]->exec();
        pc++;
    }
}
void Executor::drawPixel(int x, int y) {
    getBufferPixel(x, y) = penColor;
}

Pixel &Executor::getBufferPixel(int x, int y) {
    // std::cout << "get buffer[" << x << "," << y << "]" << std::endl;
    if (0 <= x && x < width && 0 <= y && y < height) {
        Pixel *p = reinterpret_cast<Pixel *>(buffer);
        p += y * this->width;
        p += x;
        return *p;
    } else {
        return _noPixel;
    }
}

void Executor::writeFile() {
    FileWriter writer;
    std::string filename = "output.bmp";
    auto sz = writer.WriteBMP(filename, this->buffer, width, height);
    std::cout << "write file return value: " << sz << std::endl;
    if (sz) {
        std::cout << "write to file " << filename << std::endl;
    } else {
        std::cerr << "cannot write to file " << filename << std::endl;
    }
}
