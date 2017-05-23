#!/bin/bash

for a in 1000 10000 20000 40000 60000 80000 100000 200000 400000 600000 800000 1000000 4000000 8000000 10000000 20000000
do 
echo Arraysize:$a 
 
	g++ -DARRAYSIZE=$a simd.p5.cpp -o project5 -lm -fopenmp
	./project5 
done
