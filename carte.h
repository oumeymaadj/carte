#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>


typedef struct{
    int value; //valeur de la carte 
    int seeable; //valeur visible de la carte (si = 0 la carte est cachée, si 1=visible)
}Card;

typedef struct{
    char *name; //essayer de faire un tab dynamique
    Card *cards; //tab dynamique pour savoir cbm de cartes on met dedans
    int nb_cards; //nombre de cartes
    Card discard[50]; //tab avec les cartes défaussées
}Player;

int* deck(int d[150]);
int* shuffle(int d[150], int shuffled[150]);
Player build_player(int nomb_cards, int *deck, int *start);




