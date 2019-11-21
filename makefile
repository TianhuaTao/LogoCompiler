CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g --std=c++11 
LDFLAGS=-g --std=c++11 
LDLIBS=

SRCS=main.cpp FileWriter.cpp Executor.cpp Op.cpp lex.yy.cpp Interpreter.cpp symbols.cpp OpsQueue.cpp Variable.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: LogoCompiler

LogoCompiler: $(OBJS)
	$(CXX) $(LDFLAGS) -o LogoCompiler $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend