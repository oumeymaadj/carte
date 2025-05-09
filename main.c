#include "jeu.h"

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires
    Partie p1;          // Déclaration de la structure Partie
    int taille_pioche = 0;  // Initialisation de la taille de la pioche
    int fin = 100;      // Variable pour vérifier si la partie est terminée
    p1 = creer_joueurs(&taille_pioche);  // Création des joueurs et de la pioche
    printf("La partie commence !\n");

    while (fin == 100) {  // Tant que la partie n'est pas terminée
        for (int index_joueur = 0; index_joueur < p1.nb_joueurs; index_joueur++) {
            afficher_partie(&p1, &taille_pioche, index_joueur);  // Afficher l'état actuel de la partie pour chaque joueur
        }
        fin = fin_partie(p1, taille_pioche);  // Vérifier si la partie est terminée
    }

    // Affichage du message de fin de partie
    printf("\n%s a révélé toutes ses cartes ! Tous les autres joueurs ont un dernier tour.\n", p1.joueurs[fin].nom);

    // Refait un dernier tour de jeu sans la personne qui a terminé
    for (int index_joueur = 0; index_joueur < p1.nb_joueurs; index_joueur++) {
        if (index_joueur != fin) {  // Si ce n'est pas le joueur qui a fini
            afficher_partie(&p1, &taille_pioche, index_joueur);  // Afficher l'état de la partie
        }
    }

    // Affichage des scores à la fin de la partie
    printf("\nFin de la partie, comptons les scores.\n");
    scores(p1);  // Affichage des scores des joueurs

    printf("\nMerci d'avoir joué !\n");
    liberer_partie(p1);  // Libération de la mémoire allouée pour la partie
    return 0;  // Fin du programme
}
