#include "jeu.h"

int main(){
    srand(time(NULL));
    Party p1;
    int pile_size =0;
    int end = 100;
    p1 = build_players(&pile_size);
    printf("La partie commence !\n");
    while(end == 100){
        for(int index_player=0; index_player<p1.nb_players; index_player++){
            display_party(&p1, &pile_size, index_player);
        }
        end = endgame(p1,pile_size);
    }
    printf("\n%s a toutes ses cartes visibles, tous les joueurs jouent un autre tour et la partie se termine.\n", p1.players[end].name);
    for(int index_player=0; index_player<p1.nb_players; index_player++){ // je refais un tour de jeux sans la personne qui a finis le jeux
        if(index_player != end){
            display_party(&p1, &pile_size, index_player);
        }
    }
    printf("\nFin de la partie ! Comptons les scores \n");
    scores(p1);
    printf("\nMerci d'avoir joué!\n");
    free_party(p1);
    return 0;
}