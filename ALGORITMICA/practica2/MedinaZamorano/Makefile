INCLUDE=funciones.hpp Clock.hpp ajuste.hpp matriz.hpp determinanteRecursivo.hpp determinanteIterativo.hpp
OBJECTS= main.o ajuste.o

all: main clean

main: $(OBJECTS) $(INCLUDE)
	g++ $(OBJECTS) -Wall -g -o main

main.o: main.cpp 
	g++ -c main.cpp	

ajuste.o: ajuste.cpp ajuste.hpp
	g++ -c ajuste.cpp

clean:
	rm *.o