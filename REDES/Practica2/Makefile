INCLUDES = funcionesServidor.h registro.h estructuras.h bingo.h
OBJECTS = bingoServidor.o funcionesServidor.o registro.o bingo.o
FLAGS = -Wall -g -o

all: bingoCliente bingoServidor clean

bingoCliente: bingoCliente.o registro.o bingo.o
	gcc bingoCliente.o bingo.o registro.o $(FLAGS) bingoCliente

bingoServidor: $(INCLUDES) $(OBJECTS)
	gcc $(OBJECTS) $(FLAGS) bingoServidor

bingoCliente.o: bingoCliente.c
	gcc -c bingoCliente.c

bingoServidor.o: bingoServidor.c
	gcc -c bingoServidor.c

funcionesServidor.o: funcionesServidor.c funcionesServidor.h
	gcc -c funcionesServidor.c

registro.o: registro.c registro.h
	gcc -c registro.c

bingo.o: bingo.c bingo.h
	gcc -c bingo.c

clean:
	rm *.o