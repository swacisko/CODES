#!/bin/bash



g++ kib.cpp -o kib

for i in {1..100}
do
	./kib < ./kibdir/kib$i.in > wynik.out
	diff -w wynik.out ./kibdir/kib$i.out

done
