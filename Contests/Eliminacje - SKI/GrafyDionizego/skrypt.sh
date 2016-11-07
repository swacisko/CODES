#!/bin/bash

g++ dio.cpp -o dio
g++ gen.cpp -o gen

./gen > test0.in
echo "Stworzylem test"

time ./dio < test0.in > test0.out


