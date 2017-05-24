SRC = $(wildcard test/src/*.cpp)
OBJ = $(patsubst test/src/%.cpp, test/obj/%.o, $(SRC))
BIN = test/bin/main

CXX = g++
CXXFLAG = -std=c++11 -Wall -g
LDFLAG = -std=c++11 -Wall
INC = -I. -I../googletest/googletest/include
LIB = ../googletest/googletest/make/gtest_main.a -pthread

all: mkdirs googletest $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $@ $(LDFLAG) $^ $(LIB)

test/obj/%.o: test/src/%.cpp isa/%.h
	$(CXX) -o $@ $(CXXFLAG) $(INC) -c $<

.PHONY: mkdirs googletest clean

mkdirs:
	mkdir -p test/bin test/obj

googletest:
	make -C ../googletest/googletest/make

clean:
	rm -fr test/bin test/obj
	make -C ../googletest/googletest/make clean

