#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef struct {
    int valeur; // valeur de la carte
    int visible; // 0 = carte cachée, 1 = carte visible
} Carte;

typedef struct {
    char *nom; // nom du joueur (chaîne dynamique)
    Carte *cartes; // tableau dynamique de cartes
    int nb_cartes; // nombre de cartes
    Carte defausse; // carte défaussée
    int score; // score
} Joueur;

int meilleure_saisie_entier(const char *message);
void meilleure_saisie_chaine(const char *message, char *tampon, int taille_tampon);
int* creer_paquet(int p[150]);
void melanger(int* p);
Joueur creer_joueur(int nb_cartes, int *paquet, int *depart);
void afficher_cartes(Joueur j, int fin);
void afficher_defausse(Joueur j);





