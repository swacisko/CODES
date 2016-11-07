#!/bin/bash
g++ -o generator generator.cpp

rm -r testy
mkdir testy

for i in {1..10}
do
./generator > testy/test$i.in
done

g++ -o test test.cpp

for i in {1..10}
do
./test < testy/test$i.in > testy/test$i.out
echo -e "\n Test nr $i"
cat < testy/test$i.out
done
