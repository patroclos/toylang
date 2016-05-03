.PHONY: all clean

BIN=parser

all: tokens.cpp parser.cpp $(BIN)

tokens.cpp: tokens.l
	lex -o tokens.cpp tokens.l
parser.cpp: parser.y
	bison -d -o parser.cpp parser.y
$(BIN): *.cpp
	g++ -g -std=c++11 -o $(BIN) *.cpp `llvm-config --libs core jit native --cxxflags --ldflags --system-libs`
clean:
	rm tokens.cpp parser.cpp parser.hpp $(BIN)
