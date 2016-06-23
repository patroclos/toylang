.PHONY: all clean

BIN=parser

all: tokens.cpp parser.cpp $(BIN)

tokens.cpp: tokens.l node.h
	lex -o tokens.cpp tokens.l
parser.cpp: parser.y node.h
	bison -d -o parser.cpp parser.y
$(BIN): *.cpp codegen.h node.h
	g++ -g -std=c++11 -o $(BIN) *.cpp `llvm-config --libs core jit native bitwriter --cxxflags --ldflags --system-libs`
clean:
	rm tokens.cpp parser.cpp parser.hpp $(BIN)
