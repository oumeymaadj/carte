#include "carte.h"

typedef struct{
    Joueur * joueur; //joueurs maximum 8 et minimum 2
    int nb_joueur; //nombre de joueurs
    Carte * pile; // pioche
    int taille_pile; //taille de la pioche  
}Partie;

void sauvegardePartie(Partie p);
void chargerPartie(Partie *p);
int nb_joueur();
int nombre_carte();
Partie initialiser_partie(int *pile_size);
void affichage_pile(Partie p, int * pile_size );
void affichage_partie(Partie *p , int *pile_size, int i );
void free_Partie(Partie p);
int fin_partie(Partie p, int pile_size);
void scores(Partie p);

