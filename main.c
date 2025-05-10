#include "jeu.h"

int main(){
    srand(time(NULL));
    Party p1;
    int pile_size =0;
    int end = 100;
    int choix;// choix pour savoir si il veux charger une partie our jouer normalement
    int choix2; // choix de sauvegarde ou non

    printf("Bienvenue sur CardYard !\n");
    printf("1 : Nouvelle partie\n");
    printf("2 : Charger une partie sauvegardée\n");
    choix = better_scan_int("Votre choix : \n");

    while(choix !=1 && choix!=2){
        printf("Erreur veuillez entrez 1 ou 2 seulement (1 pour une nouvelle partie 2 pour charger une ancienne partie) \n");
        choix = better_scan_int("Votre choix : \n");
    }
    if(choix == 2){
        chargerPartie(&p1);
        pile_size = p1.size_pile;
    }
    else if(choix ==1){
        p1 = build_players(&pile_size);
    }

    printf("La partie commence !\n");

    while(end == 100){
        for(int index_player=0; index_player<p1.nb_players; index_player++){
            display_party(&p1, &pile_size, index_player);
        }
        end = endgame(p1,pile_size);

        choix2= better_scan_int("Voulez-vous sauvegarder la partie ? (1 = Oui, 0 = Non) : \n");
        while(choix2 !=1 && choix2!=0){
            printf("Erreur veuillez entrez 1 ou 0 seulement (1 = Oui, 0 = Non) \n");
            choix2= better_scan_int("Voulez-vous sauvegarder la partie ? (1 = Oui, 0 = Non) : \n");
        }
        if(choix2 == 1){
            sauvegardePartie(p1);
        }

    }

    if (end != 100) {
    printf("\n%s a toutes ses cartes visibles, tous les joueurs jouent un autre tour et la partie se termine.\n", p1.players[end].name);
    }

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