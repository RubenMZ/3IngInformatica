VERSION= 5
FUENTE = ejemplo$(VERSION)
LEXICO = lexico$(VERSION)



CC = gcc
CFLAGS = -c -g
YFLAGS = -d         # Generar el fichero $(FUENTE).tab.h 
LFLAGS = -lm -lfl   # fl: biblioteca de flex; m: biblioteca matemática
OBJS= $(FUENTE).tab.o lex.yy.o  init.o   math.o   symbol.o 

$(FUENTE)3.exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe

init.o:  init.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) $(CFLAGS) init.c

symbol.o:  symbol.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) $(CFLAGS) symbol.c

math.o:  math.c $(FUENTE).h
	$(CC) $(CFLAGS) math.c

lex.yy.o:  lex.yy.c $(FUENTE).tab.h $(FUENTE).h
	$(CC) $(CFLAGS) lex.yy.c

lex.yy.c: $(LEXICO).l $(FUENTE).tab.h $(FUENTE).h
	flex $(LEXICO).l

$(FUENTE).tab.o:  $(FUENTE).tab.c $(FUENTE).tab.h $(FUENTE).h
	$(CC) $(CFLAGS) $(FUENTE).tab.c

$(FUENTE).tab.c $(FUENTE).tab.h:  $(FUENTE).y $(FUENTE).h 
	bison $(YFLAGS) $(FUENTE).y

#Opcion para borrar los ficheros objetos y auxiliares
clean: 
	rm -f  $(OBJS) $(FUENTE).tab.[ch] lex.yy.c $(FUENTE).exe
