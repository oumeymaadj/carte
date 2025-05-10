#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define FIN_COULEUR   "\033[0m"
#define BLEU    "\033[34m"
#define VERT   "\033[32m"
#define JAUNE "\033[33m"
#define ROUGE     "\033[31m"



typedef struct{
    int value; //valeur de la carte 
    int seeable; //valeur visible de la carte (si = 0 la carte est cachée, si 1=visible)
}Card;

typedef struct{
    char *name; //essayer de faire un tab dynamique
    Card *cards; //tab dynamique pour savoir cbm de cartes on met dedans
    int nb_cards; //nombre de cartes
    Card discard; //cartes défaussées
    int score; // score
}Player;


int better_scan_int(const char *message);
void better_scan_str(const char *message, char *buffer, int buffer_size);
int* deck(int d[150]);
void shuffle(int* d);
Player build_player(int nomb_cards, int *deck, int *start);
void display_card(Player p, int end);
void display_discard(Player p);




