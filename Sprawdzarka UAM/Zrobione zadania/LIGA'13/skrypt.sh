#!/bin/bash

rm ./liga2013
g++ -o liga2013 liga2013.cpp

rm ./liga_gen
g++ -o liga_gen liga_generator.cpp

rm ./liga_check
g++ -o liga_check liga_check.cpp

./liga_gen > test.in
./liga2013 < test.in > test.out



./liga_check < test.out
