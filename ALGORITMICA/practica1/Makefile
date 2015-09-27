INCLUDE=funciones.hpp metodoInsercionBinaria.hpp metodo.hpp Clock.hpp metodoShell.hpp
OBJECTS=funciones.o metodoInsercionBinaria.o main.o metodoShell.o 

main: $(OBJECTS) $(INCLUDE)
	g++ $(OBJECTS) -g -o main

main.o: main.cpp
	g++ -c main.cpp	

funciones.o: funciones.cpp funciones.hpp
	g++ -c funciones.cpp

metodoInsercionBinaria.o: metodoInsercionBinaria.cpp metodoInsercionBinaria.hpp metodo.hpp
	g++ -c metodoInsercionBinaria.cpp

metodoShell.o: metodoShell.cpp metodoShell.hpp metodo.hpp
	g++ -c metodoShell.cpp