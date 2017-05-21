#!/bin/bash

for x in 1000 10000 20000 40000 60000
do 
echo Arraysize:$x
 
	g++ -DARRAYSIZE=$x simd.p5.cpp -o project5 -lm -fopenmp
	./project5
done
