#!/bin/bash

if [[ ! -d $1 ]]; then
    if [[ $1 = "" ]]; then
        echo "Es necesario introducir el destino de la compilación."
    else
        echo "El directorio introducido no existe en el sistema."
    fi
    exit 1
fi

cd ./enfecha
make
mv enfecha.cgi ../cgi-bin
mv enfechaluna.cgi ../cgi-bin
cd ../enintervalo
g++ -c principal.c
cp makesol makefile
make
mv andi.cgi ../cgi-bin
cp makeluna makefile
make
mv andiluna.cgi ../cgi-bin

cd ..
if  [[ -w $1 ]]; then
    cp ./cgi-bin/* $1
    chmod +x $1/*
else
    sudo cp ./cgi-bin/* $1
    sudo chmod +x $1/*
fi

