#!/bin/bash
#number of threads:

echo Number of threads:$1

g++ -DNUMT=$1 CriticalAtomic.cpp -o CriticalAtomic -lm -fopenmp
./CriticalAtomic




