#Makefile para cgi de ANdi

OBJETOSL=princ_luna.o catalog.o funj2000.o grados.o Interfz.o ocaorsol.o Otrocalc.o  pasomeri.o Polis.o Reduc.o variasfu.o ortocalu.o
OBJETOS=principal.o catalog.o funj2000.o grados.o Interfz.o ocaorsol.o Otrocalc.o  pasomeri.o Polis.o Reduc.o variasfu.o ortocalu.o
CC=g++

CFLAGS=-O -W

all: enfechaluna enfecha

enfecha: ${OBJETOS}
	${CC} -Wall -pedantic -o enfecha.cgi ${CFLAGS} ${OBJETOS}  

principal.o: principal.c ../kernel/externos.h

enfechaluna: ${OBJETOS}
	${CC} -Wall -pedantic -o enfechaluna.cgi ${CFLAGS} ${OBJETOSL}  

princ_luna.o: principal.c ../kernel/externos.h
    
#catalog.o: ../kernel/catalog.c

#funj2000.o: ../kernel/funj2000.c

#grados.o: ../kernel/grados.c

#ocaorsol.o: ../kernel/ocaorsol.c

#ortocalu.o: ../kernel/ortocalu.c

#Otrocalc.o: ../kernel/Otrocalc.c

#pasomeri.o: ../kernel/pasomeri.c

#Polis.o:  ../kernel/Polis.c

#Reduc.o: ../kernel/Reduc.c

#variasfu.o: ../kernel/variasfu.c

#Interfz.o:  ../kernel/Interfz.c

#ortocalu,o: ../kernel/ortocalu.c

clean:
	rm -r -f *.o *~ core

