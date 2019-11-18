#include "Executor.h"
#include <iostream>
#include "FileWriter.h"
Executor::Executor() {
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
    penColor = Pixel(R, G, B, 1);
}

void Executor::setPenPosition(int x, int y) {
    logical_pen_x = x;
    logical_pen_y = y;
}

void Executor::def(std::string name, int value) {
}

void Executor::add(std::string name, int value) {
}

void Executor::move(const Variable &v) {
}

void Executor::move(int step) {
    Op *op;
    op = new MoveOp(this, step);
    ops.push_back(op);
}

void Executor::cloak() {
    Op *op;
    op = new cloakOp(this);
    ops.push_back(op);
}

void Executor::turn(int degree) {

    Op *op;
    op = new TurnOp(this, degree);
    ops.push_back(op);
}

void Executor::setPenColor(int r, int g, int b) {
}

void Executor::loop(int value) {
}

void Executor::startFuncDef(std::string name, int argc) {
}

// void Executor::draw(int pixel) {
// }

void Executor::run() {
    std::cout << ops.size() << " ops to run" << std::endl;

    size_t ops_cnt = ops.size();
    size_t pc = 0;
    while (pc != ops.size()) {
        std::cout << "pc[" << pc << "]: ";

        ops[pc]->exec();
        pc++;
    }
}
void Executor::drawPixel(int x, int y) {
    getBufferPixel(x,y) = penColor;
}

Pixel &Executor::getBufferPixel(int x, int y) {
    Pixel *p = reinterpret_cast<Pixel *>(buffer);
    p += y * this->height;
    p += x;
    return *p;
}

void Executor::writeFile() {
    FileWriter writer;
    std::string filename = "output.bmp";
    auto sz = writer.WriteBMP(filename, this->buffer,width * height * sizeof(Pixel));
    if(sz ==width * height * sizeof(Pixel) ){
        std::cout<< "write to file "<< filename<<std::endl;
    } else{
        std::cerr<< "cannot write to file "<< filename<<std::endl;
    }
}
