#!/bin/bash

for x in 4 10 50 70 100 500 700 1000 

do
	for y in 1 2 4 
	do
	g++ -DNUMT=$y -DNUMNODES=$x project1_0.cpp -o project1 -lm -fopenmp   
	./project1 
    	done
done
