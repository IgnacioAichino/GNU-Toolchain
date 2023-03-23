CFLAGS= -Wall -Werror -pedantic
OBJ= main.o funtionsPrint.o optionsData.o

execute: $(OBJ) libreriaStatic.a libdinamica.so 
		gcc $(CFLAGS) -L. -o execute $(OBJ) libreriaStatic.a  libdinamica.so -ldl

main.o: main.c  
		gcc $(CFLAGS)  -c main.c 

libdinamica.so: dinamic.o cJSON.o
		gcc $(CFLAGS) -shared -o libdinamica.so dinamic.o cJSON.o

dinamic.o: dinamic.c  libreriaStatic.a cJSON.o
		gcc $(CFLAGS) -fPIC -c dinamic.c 

libreriaStatic.a: cJSON.o
		ar rcs libreriaStatic.a cJSON.o

cJSON.o: cJSON.c cJSON.h
		gcc $(CFLAGS) -c cJSON.c

funtionsPrint.o: funtionsPrint.c 
		gcc $(CFLAGS) -c  funtionsPrint.c 

optionsData.o: optionsData.c 
		gcc $(CFLAGS) -c optionsData.c

clean:
		rm -f execute *.o *a *so