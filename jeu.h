#include "carte.h"

typedef struct{
    Player *players; //joueurs maximum 8 et minimum 2
    int nb_players; //nombre de joueurs
    Card *pickaxe; // pioche
    int size_pickaxe; //taille de la pioche  
}Party;
