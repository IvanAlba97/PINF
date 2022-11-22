#Makefile para cgi de ANdi

OBJETOS=principal.o catalog.o funj2000.o grados.o Interfz.o ocaorsol.o Otrocalc.o  pasomeri.o Polis.o Reduc.o variasfu.o ortocalu.o

CC=g++

CFLAGS=-O -W

all: andi 

andi: ${OBJETOS}
	${CC} -o andi.cgi ${CFLAGS} ${OBJETOS}  

principal: ./kernel/externos.h

#catalog.o: ./kernel/catalog.c

#funj2000.o: ./kernel/funj2000.c

#grados.o: ./kernel/grados.c

#ocaorsol.o: ./kernel/ocaorsol.c

#ortocalu.o: ./kernel/ortocalu.c

#Otrocalc.o: ./kernel/Otrocalc.c

#pasomeri.o: ./kernel/pasomeri.c

#Polis.o:  ./kernel/Polis.c

#Reduc.o: ./kernel/Reduc.c

#variasfu.o: ./kernel/variasfu.c

#Interfz.o:  ./kernel/Interfz.c

#ortocalu,o: ./kernel/ortocalu.c

clean:
	rm -r -f *.o *~ core

