#!/bin/bash

  
		for y in 1 2 4 6 8 10 12 14 16
		do
        		gcc -DNUMT=$y openmpsch.c -o openmpsch -lm -fopenmp
        		./openmpsch
		done
       

