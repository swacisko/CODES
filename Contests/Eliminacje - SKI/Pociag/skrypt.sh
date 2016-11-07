#!/bin/bash

for i in {1..99}
do
	./pociag < ./in/poc$i.in > wynik.out
	diff -s wynik.out ./out/poc$i.out

done
