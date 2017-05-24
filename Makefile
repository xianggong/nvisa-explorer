SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
BIN = bin/main

CXX = g++
CXXFLAG = -std=c++11 -Wall -g
LDFLAG = -std=c++11 -Wall -g

all: mkdirs $(BIN) bin/template.cubin pascal

$(BIN): $(OBJ)
	g++ -o $@ $(LDFLAG) $^

obj/%.o: src/%.cpp
	g++ -o $@ $(CXXFLAG) -c $<

bin/template.cubin: src/template.cu
	nvcc -o $@ -arch=sm_60 -cubin $<

.PHONY: mkdirs googletest pascal clean

mkdirs:
	mkdir -p obj bin

pascal:
	make -C pascal

clean:
	rm -fr bin/ obj/
	make -C pascal clean

