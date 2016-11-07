#!/bin/bash

g++ lit.cpp -o lit

for i in {1..10}
do
	./lit < ./in/lit$i.in > wynik.out
	diff -w wynik.out ./out/lit$i.out

done
