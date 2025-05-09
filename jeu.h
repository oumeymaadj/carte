#include "carte.h"

typedef struct {
    Joueur * joueurs; // joueurs, entre 2 et 8
    int nb_joueurs; // nombre de joueurs
    Carte * pioche; // pioche
    int taille_pioche; // taille de la pioche  
} Partie;

int nb_joueurs(); // fonction pour obtenir le nombre de joueurs
int nombre_cartes(); // fonction pour obtenir le nombre de cartes par joueur
Partie creer_joueurs(int *taille_pioche); // fonction pour initialiser la partie avec les joueurs et la pioche
void afficher_pioche(Partie p, int *taille_pioche); // fonction pour afficher l'état de la pioche
void afficher_partie(Partie *p , int *taille_pioche, int i); // fonction pour afficher l'état actuel de la partie
void liberer_partie(Partie p); // fonction pour libérer la mémoire de la partie
int fin_partie(Partie p, int taille_pioche); // fonction pour détecter la fin de la partie
void scores(Partie p); // fonction pour afficher les scores des joueurs
