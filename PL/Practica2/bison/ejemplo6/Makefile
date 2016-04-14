FUENTE = ejemplo6
LEXICO = lexico6


CC = gcc
YFLAGS = -d -v 
LFLAGS = -lm -lfl 
OBJS= $(FUENTE).tab.o lex.yy.o  init6.o   math6.o   symbol6.o 

$(FUENTE)3.exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe

init6.o:  init6.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c init6.c

symbol6.o:  symbol6.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c symbol6.c

math6.o:  math6.c $(FUENTE).h
	$(CC) -c math6.c

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
	rm -f  $(OBJS) $(FUENTE).tab.[ch] lex.yy.c $(FUENTE).exe  $(FUENTE).output
