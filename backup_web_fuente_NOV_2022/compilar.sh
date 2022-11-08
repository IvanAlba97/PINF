#!/bin/bash
g++ ./kernel/*.c -c
cp ./kernel/*.o ./enfecha/
cp ./kernel/*.o ./enintervalo/
cd ./enfecha
make
cd ../enintervalo
make
cd ..
rm *.o
