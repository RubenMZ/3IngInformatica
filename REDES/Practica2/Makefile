all: bingoCliente bingoServidor clean

bingoCliente: bingoCliente.c 
	gcc bingoCliente.c -o bingoCliente

bingoServidor: bingoServidor.c funcionesServidor.c funcionesServidor.h registro.c registro.h estructuras.h
	gcc funcionesServidor.c bingoServidor.c registro.c -o bingoServidor

clean:
	rm *.o