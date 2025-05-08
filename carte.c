#include"carte.h"

int* deck(int d[150]){// cree un paquet de cartes avec les conidition de variantes nous avons ajoutez un nombre de cartes de 150 imposer
    int compteur= 0;
    int valeur;
    int quantite;
    printf("Creation du paquet de cartes personnaliser avec 150 cartes imposer \n");
    while(compteur != 150){
        // demande la valeur
        valeur = better_scan_int("Entrez la valeur que vous voulez entre -5 et 15 \n");
        while(valeur<-5 || valeur>15){
            printf("Vous n'avez pas respecter l'intervalle \n");
            valeur = better_scan_int("Entrez la valeur que vous voulez entre -5 et 15\n");
        }
        // demande la quantite
        quantite =  better_scan_int("Entrez la quantite que vous voulez pour cette valeur \n");
        while(quantite +compteur > 150 || quantite < 1 || quantite > 15){
            printf("Erreur de saisie respectant les normes \n");
            quantite = better_scan_int("Entrez la quantite que vous voulez pour cette valeur en respectant la limite max et l'intervalle -5 et 15 !!! \n");          
        }
        for(int j =0; j< quantite; j++){
            d[compteur]= valeur;
            compteur++;
        }

    }
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
    better_scan_str("Type your name (50 characters max): ", n, 51); // 51 = 50 + '\0'
    p.name = malloc(sizeof(char)*strlen(n) +1 );// +1 pour /0
    if(p.name == NULL){
        printf("No dynamic space found available \n"); //on quitte le programme
        exit(1);
    }
    strcpy(p.name, n); // mettre le nom dans la le joueur 
    printf("Welcome, %s!\n", p.name);
    p.nb_cards = nomb_cards;
    p.cards = malloc(sizeof(Card)*p.nb_cards);
    if (p.cards == NULL) {
        printf("Memory allocation failed for cards.\n");
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
    printf("🧑 Player Card Display: %s\n\n", p.name);

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

    // Ligne 3 : Valeur
    for (int i = 0; i < end; i++) {
        if (p.cards[i].seeable == 1)
            printf(" |  %3d  |  ", p.cards[i].value);
        else
            printf(" |  ??   |  ");
    }
    printf("\n");

    // Ligne 4 : Visuel vide
    for (int i = 0; i < end; i++) {
        printf(" |       |  ");
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
    printf("🗑️  Player Discard Display: %s\n\n", p.name);

    // Ligne 1 : Titre centré
    printf("     Discard     \n");

    // Ligne 2 : Haut de la carte
    printf("    _______    \n");

    // Ligne 3 : Valeur visible ou cachée
    if (p.discard.seeable == 1) {
        printf("   |  %3d  |   \n", p.discard.value);
    } else {
        printf("   |  ??   |   \n");
    }

    // Ligne 4 : Vide
    printf("   |       |   \n");

    // Ligne 5 : Bas
    printf("   |_______|   \n\n");
}



