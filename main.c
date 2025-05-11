#include "jeu.h"

int main(){
    srand(time(NULL));
    Partie p1;
    int pile_size =0;
    int fin = 100;
    int choix;// choix pour savoir si il veux charger une partie our jouer normalement
    int choix2; // choix de sauvegarde ou non

    printf("Bienvenue sur CardYard !\n");
    printf("1 : Nouvelle partie\n");
    printf("2 : Charger une partie sauvegardée\n");
    choix = better_scan_int("Votre choix : \n");

    while(choix !=1 && choix!=2){
        printf("Erreur veuillez entrez 1 ou 2 seulement (1 pour une nouvelle partie / 2 pour charger une ancienne partie) \n");
        choix = better_scan_int("Votre choix : \n");
    }
    if(choix == 2){
        chargerPartie(&p1);
        pile_size = p1.taille_pile;
    }
    else if(choix ==1){
        p1 = initialiser_partie(&pile_size);
    }

    printf("La partie commence !\n");

    while(fin == 100){
        for(int indice_joueur=0; indice_joueur<p1.nb_joueur; indice_joueur++){
            affichage_partie(&p1, &pile_size, indice_joueur);
        }
        fin = fin_partie(p1,pile_size);

        choix2= better_scan_int("Voulez-vous sauvegarder la partie ? (1 = Oui, 0 = Non) : \n");
        while(choix2 !=1 && choix2!=0){
            printf("Erreur veuillez entrez 1 ou 0 seulement (1 = Oui, 0 = Non) \n");
            choix2= better_scan_int("Voulez-vous sauvegarder la partie ? (1 = Oui, 0 = Non) : \n");
        }
        if(choix2 == 1){
            sauvegardePartie(p1);
        }
    }

    for(int indice_joueur=0; indice_joueur<p1.nb_joueur; indice_joueur++){ // je refais un tour de jeux sans la personne qui a finis le jeux
        if(indice_joueur != fin){
            affichage_partie(&p1, &pile_size, indice_joueur);
        }
    }
    
    printf("\nFin de la partie ! Comptons les scores \n");
    scores(p1);
    printf("\nMerci d'avoir joué!\n");
    free_Partie(p1);
    return 0;
}
