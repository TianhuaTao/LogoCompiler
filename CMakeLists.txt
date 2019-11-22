cmake_minimum_required(VERSION 3.15)
project(LogoCompiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LogoCompiler
        VariableWrapper.cpp
        Function.cpp
        StackFrame.cpp
        Executor.cpp
        FileWriter.cpp
        Interpreter.cpp
        lex.yy.cpp
        main.cpp
        Op.cpp
        symbols.cpp
        Variable.cpp)
