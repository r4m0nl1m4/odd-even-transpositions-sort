#!/bin/bash

# To run on terminal: ./shellscript_start.sh

g++ -O0 -g -W -ansi -pedantic -std=c++11 -o odd-even-transposition-sort-serial odd-even-transposition-sort-serial.c
./odd-even-transposition-sort-serial
mpic++ -g -Wall odd-even-transposition-sort-parallel.cpp -o odd-even-transposition-sort-parallel -lm
mpirun -np 8 --oversubscribe ./odd-even-transposition-sort-parallel