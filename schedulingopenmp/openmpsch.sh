#!/bin/bash

for z in static dynamic
do
	echo $z
        for x in 1 4096
        do
		for y in 1 2 4 6 8 10 12 14 16
		do
        		gcc -DNUMT=$y -DTYPE=$z -DCHUNKSIZE=$x openmpsch.c -o openmpsch -lm -fopenmp
        		./openmpsch
		done
        done
done

