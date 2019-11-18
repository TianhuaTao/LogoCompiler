#include "Executor.h"

Executor::Executor()
{
}

Executor::~Executor()
{
}

void Executor::initNewBuffer(int width, int height){
    delete buffer;
    buffer = new char[width* height* sizeof(Pixel)];
}

void Executor::turn(const Variable &v) {

}

void Executor::setBackground(int R, int G, int B) {

}

void Executor::setPenPosition(int x, int y) {

}

void Executor::def(std::string name, int value) {

}

void Executor::add(std::string name, int value) {

}

void Executor::move(const Variable &v) {

}

void Executor::move(int step) {

}

void Executor::cloak() {

}

void Executor::turn(int angle) {

}

void Executor::setPenColor(int r, int g, int b) {

}

void Executor::loop(int value) {

}

void Executor::startFuncDef(std::string name, int argc) {

}

void Executor::draw(int pixel) {

}
