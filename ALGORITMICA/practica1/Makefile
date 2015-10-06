INCLUDE=funciones.hpp metodoInsercionBinaria.hpp metodo.hpp Clock.hpp metodoShell.hpp ajuste.hpp
OBJECTS=funciones.o metodoInsercionBinaria.o main.o metodoShell.o  ajuste.o

main: $(OBJECTS) $(INCLUDE)
	g++ $(OBJECTS) -Wall -o3 -g -o main

main.o: main.cpp
	g++ -c main.cpp	

funciones.o: funciones.cpp funciones.hpp
	g++ -c funciones.cpp

metodoInsercionBinaria.o: metodoInsercionBinaria.cpp metodoInsercionBinaria.hpp metodo.hpp
	g++ -c metodoInsercionBinaria.cpp

metodoShell.o: metodoShell.cpp metodoShell.hpp metodo.hpp
	g++ -c metodoShell.cpp

ajuste.o: ajuste.cpp ajuste.hpp
	g++ -c ajuste.cpp

clean:
	rm *.o