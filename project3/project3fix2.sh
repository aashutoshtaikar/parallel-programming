#!/bin/bash
#number of threads:
for t in 1 2 4 8
do
echo Number of threads:$t
	g++ -DNUMT=$t project3fix2.cpp -o project3fix2 -lm -fopenmp
	./project3fix2
 
done


