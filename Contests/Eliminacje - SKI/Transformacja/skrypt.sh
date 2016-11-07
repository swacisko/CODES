#!/bin/bash

g++ trans.cpp -o trans

for i in {1..120}
do
	./trans < ./big/tra$i.in > wynik.out
	diff wynik.out ./big/tra$i.out

done
