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

#^latgra=21&latmin=22&latseg=12&latsig=N&longra=12&lonmin=12&lonseg=2&lonsig=W&horut=0&anoi=2011&mesi=8&diai=1