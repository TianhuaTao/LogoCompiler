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