#include"carte.h"


int* deck(int d[150]) {
    int compteur = 0;
    int valeur;
    int quantite;
    int* doublons = malloc(150 * sizeof(int)); 
    int taille = 0;
    int reponse = 1; // 1 si doublon, 0 sinon
    int a;

    printf("Création du paquet de cartes personnalisé avec 150 cartes imposées\n");

    while (compteur != 150) {
        valeur = better_scan_int("Entrez la valeur que vous voulez entre -5 et 15\n");

        // Vérifie l'intervalle
        while (valeur < -5 || valeur > 15) {
            printf("Vous n'avez pas respecté l'intervalle [-5, 15]\n");
            valeur = better_scan_int("Entrez une valeur correcte entre -5 et 15\n");
        }

        // Vérifie si c’est un doublon
        reponse = 0;
        a = 0;
        while (a < taille) {
            if (doublons[a] == valeur) {
                reponse = 1;
            }
            a++;
        }

        while (reponse == 1) {
            printf("Cette valeur a déjà été saisie !\n");
            valeur = better_scan_int("Entrez une nouvelle valeur entre -5 et 15\n");

            while (valeur < -5 || valeur > 15) {
                printf("Vous n'avez pas respecté l'intervalle [-5, 15]\n");
                valeur = better_scan_int("Entrez une valeur correcte entre -5 et 15\n");
            }

            // Vérifie à nouveau les doublons
            reponse = 0;
            a = 0;
            while (a < taille) {
                if (doublons[a] == valeur) {
                    reponse = 1;
                }
                a++;
            }
        }

        // Ajoute la valeur dans le tableau de doublons
        doublons[taille] = valeur;
        taille++;

        // Demande de la quantité
        quantite = better_scan_int("Entrez la quantité que vous voulez pour cette valeur (1 à 15)\n");
        printf("Il vous reste %d cartes a entree \n",150 -(quantite+compteur));

        while (quantite < 1 || quantite > 15 || compteur + quantite > 150) {
            printf("Quantité invalide ou dépasse le total autorisé de 150 cartes\n");
            printf("Il vous reste %d cartes a entree \n",150 -(quantite+compteur));
            quantite = better_scan_int("Entrez une quantité correcte (1-15, sans dépasser 150 au total)\n");
        }

        // Ajout au deck
        for (int j = 0; j < quantite; j++) {
            d[compteur] = valeur;
            compteur++;
        }
    }

    free(doublons);
    return d;
}


// Mélange en place un tableau de 150 cartes
void shuffle(int* d) {
    for (int i = 149; i > 0; i--) {
        int j = rand() % (i + 1); // indice aléatoire entre 0 et i
        // Échange les valeurs d[i] et d[j]
        int temp = d[i];
        d[i] = d[j];
        d[j] = temp;
    }
}



Player build_player(int nomb_cards, int *deck,int *start){ //deck: le paquet de cartes , start: pointeur qui contient l'indice d'ou on commence a prendre les cartes en gros on a un paquet de cartes et on distribut les cartes dans l'ordre, ex: le premier a les cartes de 1 a 15 le deuxieme de 15 a 30 du coup start c'est le pointeur de l'indice du debut
    Player p;
    int j =0; // indice du paquet du joueurs;
    char n[100];
    better_scan_str("Entrez votre pseudo (50 caracteres max): ", n, 51); // 51 = 50 + '\0'
    p.name = malloc(sizeof(char)*strlen(n) +1 );// +1 pour /0
    if(p.name == NULL){
        printf("erreur allocation dynamique \n"); //on quitte le programme
        exit(1);
    }
    strcpy(p.name, n); // mettre le nom dans la le joueur 
    printf("Bienvenue, %s!\n", p.name);
    p.nb_cards = nomb_cards;
    p.cards = malloc(sizeof(Card)*p.nb_cards);
    if (p.cards == NULL) {
        printf("erreur allocation dynamique \n");
        exit(2);
    }
    for(int i= *start; i<p.nb_cards+ *start;i++){
        p.cards[j].value = deck[i]; // distribution des cartes 
        p.cards[j].seeable = 0; // mettre toute les cartes invisible
        j++;

    }
    *start += p.nb_cards; // avancement du premier indice pour le prochain joueur
    p.discard.value = 0;
    p.discard.seeable = 0;
    p.score = 0;
    return p;
    
}

/*void display_card(Player p, int end){ // affuiche un paquet de carte d'un joueur 
    printf("Player Card Display: %s \n", p.name);
    for(int i= 0;i< end ;i++){
        if(p.cards[i].seeable == 1){
            printf("(%d)  [%d] ",i,p.cards[i].value); //affiche l'indice aussi
        }
        else{
            printf("(%d)  [??] ",i); //affiche l'indice aussi
        }
    }
    printf("\n\n");
}*/
void display_card(Player p, int end) { // affiche joliment un paquet de cartes d’un joueur
    printf(" Cartes du joueur: %s\n\n", p.name);

    // Ligne 1 : Indices
    for (int i = 0; i < end; i++) {
        printf("   (%2d)     ", i);
    }
    printf("\n");

    // Ligne 2 : Haut des cartes
    for (int i = 0; i < end; i++) {
        printf("  _______   ");
    }
    printf("\n");

    // Ligne 3 : Visuel vide
    for (int i = 0; i < end; i++) {
        printf(" |       |  ");
    }
    printf("\n");

    // Ligne 4 : Valeur
    for (int i = 0; i < end; i++) {
        if (p.cards[i].seeable == 1){
            if(p.cards[i].value >= -5 && p.cards[i].value <= 0 ){
                printf(VERT " |  %3d  |  " FIN_COULEUR, p.cards[i].value);
            }
            else if(p.cards[i].value >= 1 && p.cards[i].value <= 5 ){
                printf(BLEU " |  %3d  |  " FIN_COULEUR, p.cards[i].value);
            }
            else if(p.cards[i].value >= 6 && p.cards[i].value <= 10 ){
                printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.cards[i].value);
            }
            else if(p.cards[i].value >= 11 && p.cards[i].value <= 15 ){
                printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.cards[i].value);
            }
        }
        else{
            printf(" |  ??   |  ");
        }
    }
    printf("\n");

    // Ligne 5 : Bas des cartes
    for (int i = 0; i < end; i++) {
        printf(" |_______|  ");
    }
    printf("\n\n");
}





/*void display_discard(Player p){ // affiche la defausse du joueurs   
    printf("Player Discard Display: %s \n", p.name);
    if(p.discard.seeable == 1){
        printf("Discard: [%d] \n",p.discard.value);
    }
    else{
        printf("Discard: [??] \n");
    }
}*/
void display_discard(Player p) { // affiche la défausse du joueur joliment
    printf(" Défausse du joueur: %s\n\n", p.name);

    // Ligne 1 : Titre centré
    printf("     Défausse    \n");

    // Ligne 2 : Haut de la carte
    printf("  _______   \n");

    // Ligne 3 : Vide
    printf(" |       |  \n");

    // Ligne 4 : Valeur visible ou cachée
    if (p.discard.seeable == 1) {
        if(p.discard.value >= -5 && p.discard.value <= 0 ){
            printf(VERT " |  %3d  |  " FIN_COULEUR, p.discard.value);
        }
        else if(p.discard.value >= 1 && p.discard.value <= 5 ){
            printf(BLEU " |  %3d  |  " FIN_COULEUR, p.discard.value);
        }
        else if(p.discard.value >= 6 && p.discard.value <= 10 ){
            printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.discard.value);
        }
        else if(p.discard.value >= 11 && p.discard.value <= 15 ){
            printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.discard.value);
        }
    } else {
        printf(" |  ??   |  ");
    }
    printf("\n");
    // Ligne 5 : Bas
    printf(" |_______|  \n\n");
}


