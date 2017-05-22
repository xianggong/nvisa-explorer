all: template.cubin main

template.cubin: template.cu
	nvcc -o $@ -arch=sm_60 -cubin $< -L/home/zhonglia/m2s-gpu/libs -lcudart

main: main.cpp
	g++ -o $@ -std=c++11 -Wall -g $<

