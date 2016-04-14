FUENTE = ejemplo8
LEXICO = lexico8


CC = gcc
YFLAGS = -d -v 
LFLAGS = -lm -lfl 
OBJS= $(FUENTE).tab.o lex.yy.o  init8.o math8.o symbol8.o  code8.o

$(FUENTE)3.exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe

code8.o:  code8.c $(FUENTE).h
	$(CC) -c code8.c

init8.o:  init8.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c init8.c

symbol8.o:  symbol8.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c symbol8.c

math8.o:  math8.c $(FUENTE).h
	$(CC) -c math8.c

lex.yy.o:  lex.yy.c $(FUENTE).tab.h $(FUENTE).h
	$(CC) -c lex.yy.c

lex.yy.c: $(LEXICO).l $(FUENTE).tab.h $(FUENTE).h
	flex $(LEXICO).l

$(FUENTE).tab.o:  $(FUENTE).tab.c $(FUENTE).tab.h $(FUENTE).h
	$(CC) -c $(FUENTE).tab.c

$(FUENTE).tab.c $(FUENTE).tab.h:  $(FUENTE).y $(FUENTE).h 
	bison $(YFLAGS) $(FUENTE).y

#Opcion para borrar los ficheros objetos y auxiliares
clean: 
	rm -f  $(OBJS) $(FUENTE).tab.[ch] lex.yy.c $(FUENTE).exe $(FUENTE).output
