#!/bin/bash

for x in 1000 10000 20000 40000 60000
do 
echo Arraysize:$x
	g++ -DARRAYSIZE=$x simd.p5.red.cpp -o project52 -lm -fopenmp
	./project52
done
