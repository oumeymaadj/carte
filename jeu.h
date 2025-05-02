#include "carte.h"

typedef struct{
    Player * players; //joueurs maximum 8 et minimum 2
    int nb_players; //nombre de joueurs
    Card * pile; // pioche
    int size_pile; //taille de la pioche  
}Party;

int nb_players();
int nb_cards(int play);
Party build_players(int *pile_size);
void draw_pile_display(Party p, int * pile_size );
void display_party(Party p , int *pile_size, int i );
void free_party(Party p);
