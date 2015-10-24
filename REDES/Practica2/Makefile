INCLUDES = funcionesServidor.h registro.h estructuras.h 
OBJECTS = bingoServidor.o funcionesServidor.o registro.o
FLAGS = -Wall -g -o

all: bingoCliente bingoServidor clean

bingoCliente: bingoCliente.o
	gcc bingoCliente.o $(FLAGS) bingoCliente

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

clean:
	rm *.o