#include"jeu.h"

//sauvegarder la partie
void sauvegardePartie(Partie p){
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if(fichier == NULL){
        printf("probleme ouverture du fichier \n");
        exit(4);
    }
    // Recupere le nombre de joueur
    fprintf(fichier, "%d\n", p.nb_joueurs);
    for(int i=0; i< p.nb_joueurs; i++){
        //on recupere le nom et le nombre de carte par joueur
        fprintf(fichier, "%s %d \n", p.joueurs[i].nom, p.joueurs[i].nb_cartes);
        // On recupere les veleurs des cartes et leurs visibilité
        for(int j=0; j<p.joueurs[i].nb_cartes; j++){
            fprintf(fichier, "%d %d\n", p.joueurs[i].cartes[j].valeur,p.joueurs[i].cartes[j].visible );
        }
        fprintf(fichier, "%d %d\n",p.joueurs[i].defausse.valeur, p.joueurs[i].defausse.visible );
    }
    // taille de la pioche
    fprintf(fichier, "%d\n", p.taille_pile);
    // on recupere la pioche
    for(int i=0; i< p.taille_pile; i++){
        fprintf(fichier, "%d %d\n", p.pile[i].valeur, p.pile[i].visible);
    }
    fclose(fichier);
    printf("Données sauvegardées avec succès.\n \n");
}



void chargerPartie(Partie *p) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Aucune sauvegarde trouvée.\n");
        exit(5);
    }

    // Lire le nombre de joueurs
    fscanf(fichier, "%d", &p->nb_joueurs);

    // Allouer le tableau de joueurs
    p->joueurs = malloc(sizeof(Player) * p->nb_joueurs);
    if (p->joueurs == NULL) {
        printf("Erreur allocation mémoire joueurs\n");
        exit(6);
    }

    // Pour chaque joueur
    for (int i = 0; i < p->nb_joueurs; i++) {
        char buffer[100]; // buffer temporaire pour le nom
        int nb_cartes;

        // Lire le nom et le nombre de cartes
        fscanf(fichier, "%s %d", buffer, &nb_cartes);

        // Allouer et copier le nom
        p->joueurs[i].nom = malloc(strlen(buffer) + 1);
        if (p->joueurs[i].nom == NULL) {
            printf("Erreur allocation mémoire nom joueur\n");
            exit(7);
        }
        strcpy(p->joueurs[i].nom, buffer);

        // Stocker le nombre de cartes
        p->joueurs[i].nb_cartes = nb_cartes;

        // Allouer les cartes
        p->joueurs[i].cartes = malloc(sizeof(Carte) * nb_cartes);
        if (p->joueurs[i].cartes == NULL) {
            printf("Erreur allocation mémoire cartes joueur\n");
            exit(8);
        }

        // Lire les cartes du joueur
        for (int j = 0; j < nb_cartes; j++) {
            fscanf(fichier, "%d %d",
                   &p->joueurs[i].cartes[j].valeur,
                   &p->joueurs[i].cartes[j].visible);
        }

        // Lire la défausse unique du joueur
        fscanf(fichier, "%d %d",
               &p->joueurs[i].defausse.valeur,
               &p->joueurs[i].defausse.visible);

        // Initialiser le score à 0 (il sera recalculé si besoin)
        p->joueurs[i].score = 0;
    }

    // Allouer la pioche
    p->pile = malloc(sizeof(Carte) * 150); // taille max de la pioche
    if (p->pile == NULL) {
        printf("Erreur allocation mémoire pioche\n");
        exit(9);
    }

    // Lire la taille de la pioche
    fscanf(fichier, "%d", &p->taille_pile);

    // Lire les cartes de la pioche
    for (int i = 0; i < p->taille_pile; i++) {
        fscanf(fichier, "%d %d",
               &p->pile[i].valeur,
               &p->pile[i].visible);
    }

    fclose(fichier);
    printf("Partie chargée avec succès.\n");
}

