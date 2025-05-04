#include "jeu.h"

int main(){
    srand(time(NULL));
    Party p1;
    int pile_size =0;
    int end;
    p1 = build_players(&pile_size);
    end = endgame(p1);
    printf("The game begins!\n");
    while(end == 100){
        for(int index_player=0; index_player<p1.nb_players; index_player++){
            display_party(p1, &pile_size, index_player);
        }
        end = endgame(p1);
    }
    printf("\n%s has revealed all their cards! Everyone else gets one last turn.\n", p1.players[end].name);
    for(int index_player=0; index_player<p1.nb_players; index_player++){ // je refais un tour de jeux sans la personne qui a finis le jeux
        if(index_player != end){
            display_party(p1, &pile_size, index_player);
        }
    }
    printf("\nEnd of the game let's count the scores \n");
    scores(p1);
    printf("\nThanks for playing!\n");
    free_party(p1);
    return 0;
}