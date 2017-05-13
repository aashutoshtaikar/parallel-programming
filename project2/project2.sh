#!/bin/bash

for x in 1 4096 

do
        for y in 1 2 4 8 10 12 16 32
        do
        g++ -DNUMT=$y -Dchunksize=$x project2.cpp -o project2 -lm -fopenmp
        ./project2
        done
done

