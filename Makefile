all: build/babel

CFLAGS := -g -std=c++17 -fno-omit-frame-pointer -c

babel.o: babel.cc
	g++ $(CFLAGS) babel.cc -o babel.o

lex.yy.o: lex.yy.cpp
	g++ $(CFLAGS) lex.yy.cpp -o lex.yy.o

syntax_analyzer.tab.o: syntax_analyzer.tab.cpp
	g++ $(CFLAGS) syntax_analyzer.tab.cpp -o syntax_analyzer.tab.o

ast.o: ast.cpp
	g++ $(CFLAGS) ast.cpp -o ast.o

IR.o: IR.cpp
	g++ $(CFLAGS) IR.cpp -o IR.o

Dominators.o: Dominators.cc
	g++ $(CFLAGS) Dominators.cc -o Dominators.o

Mem2Reg.o: Mem2Reg.cc
	g++ $(CFLAGS) Mem2Reg.cc -o Mem2Reg.o

LoopSearch.o: LoopSearch.cc
	g++ $(CFLAGS) LoopSearch.cc -o LoopSearch.o

LoopInvHoist.o: LoopInvHoist.cc
	g++ $(CFLAGS) LoopInvHoist.cc -o LoopInvHoist.o

arm.o: arm.cpp
	g++ $(CFLAGS) arm.cpp -o arm.o

RemoveRedundantLoad.o: RemoveRedundantLoad.cpp
	g++ $(CFLAGS) RemoveRedundantLoad.cpp -o RemoveRedundantLoad.o

build/babel: babel.o lex.yy.o syntax_analyzer.tab.o ast.o IR.o Dominators.o Mem2Reg.o LoopSearch.o LoopInvHoist.o arm.o RemoveRedundantLoad.o
	g++ -std=c++17 babel.o lex.yy.o syntax_analyzer.tab.o ast.o IR.o Dominators.o Mem2Reg.o LoopSearch.o LoopInvHoist.o arm.o RemoveRedundantLoad.o -o build/babel
