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
    int valeur; //valeur de la carte 
    int visible; //valeur visible de la carte (si = 0 la carte est cachée, si 1=visible)
}Card;

typedef struct{
    char *nom; //nom du joueur
    Card *Carte; //tab avec les carte du joueur
    int nb_cartes; //nombre de cartes
    Card defausse; //cartes défaussées
    int score; // score
}Joueur;


int better_scan_int(const char *message);
void better_scan_str(const char *message, char *buffer, int buffer_size);
int* paquet(int d[150]);
void melanger(int* d);
Player construire_joueur(int nombre_cartes, int *pquet, int *commencer);
void affichage_Carte(Joueur p, int fin);
void affichage_defausse(Joueur p);




