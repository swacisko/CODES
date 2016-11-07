#!/bin/bash

g++ dod.cpp -o dod

for i in {70..90}
do
	time ./dod < ./Testy/dod$i.in > wynik.out
	diff -b wynik.out ./Testy/dod$i.out

done
