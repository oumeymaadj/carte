all: exec

jeu.o: jeu.c jeu.h 
	gcc -c jeu.c -o jeu.o
	
carte.o: carte.c carte.h 
	gcc -c carte.c -o carte.o
	
main.o: main.c 
	gcc -c main.c -o main.o
	
securite.o: securite.c 
	gcc -c securite.c -o securite.o

exec: jeu.o main.o securite.o carte.o
	gcc jeu.o main.o securite.o carte.o -o exec
