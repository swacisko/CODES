#! /bin/bash

g++ Halfprime_numbers.cpp -o Halfprime_numbers
g++ Halprime_numbers_2.cpp -o Halprime_numbers_2


./Halfprime_numbers > wynik.out
./Halprime_numbers_2 > wynik2.out

diff -s wynik.out wynik2.out


