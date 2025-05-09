#include "jeu.h"

int nb_joueurs() { // fonction pour le nombre de joueurs
    int a;
    a = meilleure_saisie_entier("Entrez le nombre de joueurs dans la partie entre 2 et 8 \n");
    while (a > 8 || a < 2) {
        printf("Recommencez, vous avez entré un nombre invalide \n");
        a = meilleure_saisie_entier("Entrez le nombre de joueurs dans la partie entre 2 et 8 : ");
    }
    return a;
}

int nombre_cartes() { // fonction pour le nombre de cartes par joueur
    int a;
    a = (rand() % 5) + 6; // cartes entre 6 et 10
    printf("Il y aura %d cartes par joueur\n", a);
    return a;
}

Partie creer_joueurs(int *taille_pioche) { // initialise une partie. taille_pioche : taille de la pioche initialisée à 0.
    Partie partie;
    int nb_cartes;
    int depart = 0;

    int *paquet;
    paquet = malloc(sizeof(int) * 150);
    if (paquet == NULL) {
        printf("Espace mémoire dynamique non disponible\n");
        exit(1);
    }

    partie.nb_joueurs = nb_joueurs(); // nombre de joueurs
    nb_cartes = nombre_cartes(); // nombre de cartes

    // création et mélange du paquet
    creer_paquet(paquet);
    melanger(paquet);

    // création des joueurs
    partie.joueurs = malloc(sizeof(Joueur) * partie.nb_joueurs);
    if (partie.joueurs == NULL) {
        printf("Espace mémoire dynamique non disponible\n");
        exit(1);
    }

    partie.pioche = malloc(sizeof(Carte) * 150);
    if (partie.pioche == NULL) {
        printf("Échec de l'allocation mémoire pour la pioche.\n");
        exit(1);
    }

    for (int i = 0; i < partie.nb_joueurs; i++) {
        partie.joueurs[i] = creer_joueur(nb_cartes, paquet, &depart);
    }

    partie.taille_pioche = 150 - (partie.nb_joueurs * nb_cartes);

    for (int i = depart; i < 150; i++) {
        partie.pioche[*taille_pioche].valeur = paquet[i];
        partie.pioche[*taille_pioche].visible = 0;
        (*taille_pioche)++;
    }

    return partie;
}

void afficher_pioche(Partie partie, int *taille_pioche) {
    if (*taille_pioche <= 0) {
        printf(" La pioche est vide !\n\n");
    } else {
        printf(" Carte au sommet de la pioche :\n\n");
        printf("    _______    \n");
        printf("   |  %3d  |   \n", partie.pioche[*taille_pioche - 1].valeur);
        printf("   |       |   \n");
        printf("   |_______|   \n");
        printf("  (%d cartes restantes)\n\n", *taille_pioche);
    }
}

void afficher_partie(Partie *partie, int *taille_pioche, int i) {
    int choix1, choix2, choix3, choix4, var;

    for (int j = 0; j < partie->nb_joueurs; j++) {
        afficher_cartes(partie->joueurs[j], partie->joueurs[j].nb_cartes);
        afficher_defausse(partie->joueurs[j]);
    }

    printf("Tapez 1 pour piocher une carte, ou 2 pour prendre une carte depuis une défausse\n");
    choix1 = meilleure_saisie_entier("");
    while (choix1 != 1 && choix1 != 2) {
        printf("Erreur. Tapez 1 pour piocher une carte, ou 2 pour prendre une carte depuis une défausse\n");
        choix1 = meilleure_saisie_entier("");
    }

    if (choix1 == 1) {
        if (*taille_pioche <= 0) {
            printf("La pioche est vide. Tour passé.\n");
            return;
        }

        afficher_pioche(*partie, taille_pioche);
        (*taille_pioche)--;

        printf("Tapez 1 pour échanger cette carte avec l'une des vôtres, ou 2 pour la refuser et la mettre dans votre défausse.\n");
        choix2 = meilleure_saisie_entier("");
        while (choix2 != 1 && choix2 != 2) {
            printf("Erreur. Tapez 1 pour échanger ou 2 pour refuser.\n");
            choix2 = meilleure_saisie_entier("");
        }

        if (choix2 == 2) {
            partie->joueurs[i].defausse.valeur = partie->pioche[*taille_pioche].valeur;
            partie->pioche[*taille_pioche].visible = 1;
        } else {
            printf("Entrez l'indice de la carte à échanger (0-%d) :\n", partie->joueurs[i].nb_cartes - 1);
            choix4 = meilleure_saisie_entier("");
            while (choix4 < 0 || choix4 >= partie->joueurs[i].nb_cartes) {
                printf("Indice invalide, essayez encore.\n");
                choix4 = meilleure_saisie_entier("");
            }

            var = partie->joueurs[i].cartes[choix4].valeur;
            partie->joueurs[i].cartes[choix4].valeur = partie->pioche[*taille_pioche].valeur;
            partie->joueurs[i].cartes[choix4].visible = 1;
            partie->joueurs[i].defausse.valeur = var;
            partie->joueurs[i].defausse.visible = 1;
        }
    } else if (choix1 == 2) {
        printf("Choisissez une défausse d’un joueur (entre 0 et %d) :\n", partie->nb_joueurs - 1);
        choix3 = meilleure_saisie_entier("");
        while (choix3 < 0 || choix3 >= partie->nb_joueurs || partie->joueurs[choix3].defausse.visible == 0) {
            printf("Erreur. Choisissez une défausse valide (entre 0 et %d) :\n", partie->nb_joueurs - 1);
            choix3 = meilleure_saisie_entier("");
        }

        printf("Entrez l'indice de la carte à échanger (entre 0 et %d) :\n", partie->joueurs[i].nb_cartes - 1);
        choix4 = meilleure_saisie_entier("");
        while (choix4 < 0 || choix4 >= partie->joueurs[i].nb_cartes) {
            printf("Indice invalide, essayez encore.\n");
            choix4 = meilleure_saisie_entier("");
        }

        var = partie->joueurs[choix3].defausse.valeur;
        partie->joueurs[i].defausse.valeur = partie->joueurs[i].cartes[choix4].valeur;
        partie->joueurs[i].defausse.visible = 1;
        partie->joueurs[i].cartes[choix4].valeur = var;
        partie->joueurs[i].cartes[choix4].visible = 1;
        partie->joueurs[choix3].defausse.visible = 0;
    }

    printf("\nFin du tour de %s.\n", partie->joueurs[i].nom);
    printf("-----------------------------\n\n");
}

void liberer_partie(Partie partie) {
    for (int i = 0; i < partie.nb_joueurs; i++) {
        free(partie.joueurs[i].cartes);
        free(partie.joueurs[i].nom);
    }
    free(partie.joueurs);
    free(partie.pioche);
}

int fin_partie(Partie partie, int taille_pioche) {
    int cpt;
    if (taille_pioche <= 0) {
        printf("Il n'y a plus de pioche, la partie est terminée\n");
        return 100;
    }
    for (int i = 0; i < partie.nb_joueurs; i++) {
        cpt = 0;
        for (int j = 0; j < partie.joueurs[i].nb_cartes; j++) {
            if (partie.joueurs[i].cartes[j].visible == 1) {
                cpt++;
            }
        }
        if (cpt == partie.joueurs[i].nb_cartes) {
            printf("%s a toutes ses cartes visibles, encore un tour et la partie est terminée\n", partie.joueurs[i].nom);
            return i;
        }
    }
    return
