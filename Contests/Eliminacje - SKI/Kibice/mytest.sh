#! /bin/bash


g++ kibgen.cpp -o kibgen
g++ kib.cpp -o kib


./kibgen > mytest.in
echo "Stworzylem test"
#cat mytest.in

time ./kib < mytest.in > mytest.out

#cat mytest.out
