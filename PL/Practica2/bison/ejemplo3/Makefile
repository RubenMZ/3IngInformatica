FUENTE = ejemplo3
LEXICO = lexico3

CC = gcc
YFLAGS = -d 
LFLAGS = -lfl -lm  # fl: biblioteca de flex; m: biblioteca matemática

OBJS= $(FUENTE).tab.o lex.yy.o 

$(FUENTE).exe: $(OBJS) 
	$(CC) $(OBJS) $(LFLAGS) -o $(FUENTE).exe 

lex.yy.o:  lex.yy.c $(FUENTE).tab.h 
	$(CC) -c lex.yy.c 

lex.yy.c: $(LEXICO).l $(FUENTE).tab.h 
	flex $(LEXICO).l

$(FUENTE).tab.o: $(FUENTE).tab.c  $(FUENTE).tab.h 
	$(CC) -c $(FUENTE).tab.c

$(FUENTE).tab.c $(FUENTE).tab.h:  $(FUENTE).y
	bison $(YFLAGS) $(FUENTE).y

#Opcion para borrar los ficheros auxiliares y los objetos
clean: 
	rm  -f $(OBJS) $(FUENTE).tab.[ch] lex.yy.c $(FUENTE).exe


