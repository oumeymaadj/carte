#include "carte.h"

typedef struct{
    Player * players; //joueurs maximum 8 et minimum 2
    int nb_players; //nombre de joueurs
    Card *pickaxe; // pioche
    int size_pickaxe; //taille de la pioche  
}Party;

int nb_players();
int nb_cards(int play);
Party build_players(int *pickaxe_size);
void draw_pile_display(Party p, int * pickaxe_size );
void display_party(Party p , int *pickaxe_size, int i );
void free_party(Party p);