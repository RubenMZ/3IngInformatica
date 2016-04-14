FUENTE = ejemplo9
LEXICO = lexico9


CC = gcc
YFLAGS = -d -v 
LFLAGS = -lm -lfl 
OBJS= $(FUENTE).tab.o lex.yy.o  init9.o math9.o symbol9.o  code9.o

$(FUENTE)3.exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe

code9.o:  code9.c $(FUENTE).h
	$(CC) -c code9.c

init9.o:  init9.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c init9.c

symbol9.o:  symbol9.c $(FUENTE).h $(FUENTE).tab.h
	$(CC) -c symbol9.c

math9.o:  math9.c $(FUENTE).h
	$(CC) -c math9.c

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
