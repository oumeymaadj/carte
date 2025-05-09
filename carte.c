#include "carte.h"

#include <stdio.h>
#include <stdlib.h>

int* paquet(int p[150]) {
    int compteur = 0;
    int valeur;
    int quantite;
    int* valeurs_utilisées = malloc(150 * sizeof(int)); 
    int taille = 0;
    int doublon = 1; // 1 si doublon, 0 sinon
    int i;

    printf("Création du paquet de cartes personnalisé avec 150 cartes imposées\n");

    while (compteur != 150) {
        valeur = meilleure_saisie_entier("Entrez la valeur que vous voulez entre -5 et 15\n");

        while (valeur < -5 || valeur > 15) {
            printf("Vous n'avez pas respecté l'intervalle [-5, 15]\n");
            valeur = meilleure_saisie_entier("Entrez une valeur correcte entre -5 et 15\n");
        }

        doublon = 0;
        i = 0;
        while (i < taille) {
            if (valeurs_utilisées[i] == valeur) {
                doublon = 1;
            }
            i++;
        }

        while (doublon == 1) {
            printf("Cette valeur a déjà été saisie !\n");
            valeur = meilleure_saisie_entier("Entrez une nouvelle valeur entre -5 et 15\n");

            while (valeur < -5 || valeur > 15) {
                printf("Vous n'avez pas respecté l'intervalle [-5, 15]\n");
                valeur = meilleure_saisie_entier("Entrez une valeur correcte entre -5 et 15\n");
            }

            doublon = 0;
            i = 0;
            while (i < taille) {
                if (valeurs_utilisées[i] == valeur) {
                    doublon = 1;
                }
                i++;
            }
        }

        valeurs_utilisées[taille] = valeur;
        taille++;

        quantite = meilleure_saisie_entier("Entrez la quantité que vous voulez pour cette valeur (1 à 15)\n");

        while (quantite < 1 || quantite > 15 || compteur + quantite > 150) {
            printf("Quantité invalide ou dépasse le total autorisé de 150 cartes\n");
            quantite = meilleure_saisie_entier("Entrez une quantité correcte (1-15, sans dépasser 150 au total)\n");
        }

        for (int j = 0; j < quantite; j++) {
            p[compteur] = valeur;
            compteur++;
        }
    }

    free(valeurs_utilisées);
    return p;
}

void melanger(int* paquet) {
    for (int i = 149; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = paquet[i];
        paquet[i] = paquet[j];
        paquet[j] = temp;
    }
}

Joueur construire_joueur(int nb_cartes, int *paquet, int *debut) {
    Joueur joueur;
    int indice = 0;
    char nom_temp[100];
    meilleure_saisie_chaine("Entrez votre nom (50 caractères max) : ", nom_temp, 51);

    joueur.nom = malloc(sizeof(char) * strlen(nom_temp) + 1);
    if (joueur.nom == NULL) {
        printf("Aucun espace mémoire disponible\n");
        exit(1);
    }
    strcpy(joueur.nom, nom_temp);
    printf("Bienvenue, %s !\n", joueur.nom);

    joueur.nb_cartes = nb_cartes;
    joueur.cartes = malloc(sizeof(Carte) * joueur.nb_cartes);
    if (joueur.cartes == NULL) {
        printf("Échec de l'allocation mémoire pour les cartes.\n");
        exit(2);
    }

    for (int i = *debut; i < joueur.nb_cartes + *debut; i++) {
        joueur.cartes[indice].valeur = paquet[i];
        joueur.cartes[indice].visible = 0;
        indice++;
    }

    *debut += joueur.nb_cartes;
    joueur.defausse.valeur = 0;
    joueur.defausse.visible = 0;
    joueur.score = 0;
    return joueur;
}

void afficher_cartes(Joueur joueur, int fin) {
    printf(" Affichage des cartes du joueur : %s\n\n", joueur.nom);

    for (int i = 0; i < fin; i++) {
        printf("   (%2d)     ", i);
    }
    printf("\n");

    for (int i = 0; i < fin; i++) {
        printf("  _______   ");
    }
    printf("\n");

    for (int i = 0; i < fin; i++) {
        if (joueur.cartes[i].visible == 1)
            printf(" |  %3d  |  ", joueur.cartes[i].valeur);
        else
            printf(" |  ??   |  ");
    }
    printf("\n");

    for (int i = 0; i < fin; i++) {
        printf(" |       |  ");
    }
    printf("\n");

    for (int i = 0; i < fin; i++) {
        printf(" |_______|  ");
    }
    printf("\n\n");
}

void afficher_defausse(Joueur joueur) {
    printf(" Affichage de la défausse du joueur : %s\n\n", joueur.nom);

    printf("     Défausse     \n");
    printf("    _______    \n");

    if (joueur.defausse.visible == 1) {
        printf("   |  %3d  |   \n", joueur.defausse.valeur);
    } else {
        printf("   |  ??   |   \n");
    }

    printf("   |       |   \n");
    printf("   |_______|   \n\n");
}




