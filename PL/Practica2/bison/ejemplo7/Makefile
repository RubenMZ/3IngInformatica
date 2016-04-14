FUENTE = ejemplo7
LEXICO = lexico7


CC = gcc
YFLAGS = -d -v
LFLAGS = -lm -lfl 
OBJS= $(FUENTE).tab.o lex.yy.o  init7.o   math7.o   symbol7.o  code7.o

$(FUENTE)3.exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe

code7.o:  code7.c $(FUENTE).h
	$(CC) -c code7.c

init7.o:  init7.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c init7.c

symbol7.o:  symbol7.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c symbol7.c

math7.o:  math7.c $(FUENTE).h
	$(CC) -c math7.c

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


