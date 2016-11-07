#!/bin/bash


g++ polegen.cpp -o gen
g++ pole.cpp -o pole
g++ POL.cpp -o pol

./gen > test.in
echo "Utworzylem test"
time ./pole < test.in > wynik.out

time ./pol < test.in > wynik2.out

diff -w wynik.out wynik2.out
