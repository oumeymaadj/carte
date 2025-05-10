#include"jeu.h"

//sauvegarder la partie
void sauvegardePartie(Party p){
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if(fichier == NULL){
        printf("probleme ouverture du fichier \n");
        exit(4);
    }
    // Recupere le nombre de joueur
    fprintf(fichier, "%d\n", p.nb_players);
    for(int i=0; i< p.nb_players; i++){
        //on recupere le nom et le nombre de carte par joueur
        fprintf(fichier, "%s %d \n", p.players[i].name, p.players[i].nb_cards);
        // On recupere les veleurs des cartes et leurs visibilité
        for(int j=0; j<p.players[i].nb_cards; j++){
            fprintf(fichier, "%d %d\n", p.players[i].cards[j].value,p.players[i].cards[j].seeable );
        }
        fprintf(fichier, "%d %d\n",p.players[i].discard.value, p.players[i].discard.seeable );
    }
    // taille de la pioche
    fprintf(fichier, "%d\n", p.size_pile);
    // on recupere la pioche
    for(int i=0; i< p.size_pile; i++){
        fprintf(fichier, "%d %d\n", p.pile[i].value, p.pile[i].seeable);
    }
    fclose(fichier);
    printf("Données sauvegardées avec succès.\n \n");
}



void chargerPartie(Party *p) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Aucune sauvegarde trouvée.\n");
        exit(5);
    }

    // Lire le nombre de joueurs
    fscanf(fichier, "%d", &p->nb_players);

    // Allouer le tableau de joueurs
    p->players = malloc(sizeof(Player) * p->nb_players);
    if (p->players == NULL) {
        printf("Erreur allocation mémoire joueurs\n");
        exit(6);
    }

    // Pour chaque joueur
    for (int i = 0; i < p->nb_players; i++) {
        char buffer[100]; // buffer temporaire pour le nom
        int nb_cards;

        // Lire le nom et le nombre de cartes
        fscanf(fichier, "%s %d", buffer, &nb_cards);

        // Allouer et copier le nom
        p->players[i].name = malloc(strlen(buffer) + 1);
        if (p->players[i].name == NULL) {
            printf("Erreur allocation mémoire nom joueur\n");
            exit(7);
        }
        strcpy(p->players[i].name, buffer);

        // Stocker le nombre de cartes
        p->players[i].nb_cards = nb_cards;

        // Allouer les cartes
        p->players[i].cards = malloc(sizeof(Card) * nb_cards);
        if (p->players[i].cards == NULL) {
            printf("Erreur allocation mémoire cartes joueur\n");
            exit(8);
        }

        // Lire les cartes du joueur
        for (int j = 0; j < nb_cards; j++) {
            fscanf(fichier, "%d %d",
                   &p->players[i].cards[j].value,
                   &p->players[i].cards[j].seeable);
        }

        // Lire la défausse unique du joueur
        fscanf(fichier, "%d %d",
               &p->players[i].discard.value,
               &p->players[i].discard.seeable);

        // Initialiser le score à 0 (il sera recalculé si besoin)
        p->players[i].score = 0;
    }

    // Allouer la pioche
    p->pile = malloc(sizeof(Card) * 150); // taille max de la pioche
    if (p->pile == NULL) {
        printf("Erreur allocation mémoire pioche\n");
        exit(9);
    }

    // Lire la taille de la pioche
    fscanf(fichier, "%d", &p->size_pile);

    // Lire les cartes de la pioche
    for (int i = 0; i < p->size_pile; i++) {
        fscanf(fichier, "%d %d",
               &p->pile[i].value,
               &p->pile[i].seeable);
    }

    fclose(fichier);
    printf("Partie chargée avec succès.\n");
}

