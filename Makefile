# Build the P-code compiler from the sources in src/.
# The parser (miny.tab.cpp/.hpp) and lexer (lex.yy.c) are pre-generated,
# so only a C and C++ compiler are needed.

CC  ?= gcc
CXX ?= g++
CFLAGS   ?= -g
CXXFLAGS ?= -g

BIN = pcodeGen
OBJ = build/main.o build/miny.tab.o build/lex.yy.o

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $@ $(OBJ)

build/lex.yy.o: src/lex.yy.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/miny.tab.o: src/miny.tab.cpp src/ast.h | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: src/main.cpp src/main.h src/ast.h src/miny.tab.hpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

# Compile every example and compare it with its expected P-code.
test: $(BIN)
	./tests/run.sh

clean:
	rm -rf build $(BIN) ASTFile.txt outputFile.txt

.PHONY: all test clean
