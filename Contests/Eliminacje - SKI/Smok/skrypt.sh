#!/bin/bash

for i in {1..50}
do
	./smok < ./Testy/smo$i.in > wynik.out
	diff wynik.out ./Testy/smo$i.out

done
