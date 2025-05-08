#include "jeu.h"

int nb_players(){ // fonction pour le nombre de joueur
    int a;
    a = better_scan_int("Enter the number of players in the game between 2 and 8 \n");
    while(a>8 || a<2 ){
        printf("start over you entered the wrong number \n");
        a = better_scan_int("Enter the number of players in the game between 2 and 8: ");
    }
    return a;
}

int nombre_cards() { // fonction pour le nombre de cartes par joueur
    int a;
    a = (rand()%5) + 6; // carte entre 6 et 10
    printf("il y aura %d cartes par joueurs", a);
    return a;
}


Party build_players(int *pile_size){ // initialise une party. pile_size: taille de la pioche initaliser a 0.
    Party p; // une partie 
    int nomb_cards;//nb cartes
    int start = 0;

    int *d;// paquet de carte non melangee ensuite seras melanger
    d = malloc(sizeof(int)* 150);
    if(d == NULL){
        printf("No dynamic space found available\n"); //on quitte le programme
        exit(1);
    }
    
    p.nb_players = nb_players(); // nombre de joueurs
    nomb_cards = nombre_cards(); // nombre de cartes

    //melange les cartes
    deck(d);
    shuffle(d); // paquet de cartes melangé

    // cree les joueurs
    p.players = malloc(sizeof(Player)* p.nb_players);
    if(p.players == NULL){
        printf("No dynamic space found available \n"); //on quitte le programme
        exit(1);
    }
    p.pile = malloc(sizeof(Card) * 150); // 150 parce que  deck a 150 cartes
    if (p.pile == NULL) {
        printf("Memory allocation failed for pile.\n");
        exit(1);
    }
    for(int i =0; i<p.nb_players; i++){
        p.players[i] = build_player(nomb_cards, d,&start);
    }

    p.size_pile = 150 - (p.nb_players * nomb_cards);
    
    for(int i= start; i<150;i++){
        p.pile[*pile_size].value = d[i]; // distribution des cartes 
        p.pile[*pile_size].seeable = 0; // tout cachée
        (*pile_size) ++;
    }
    return p;

}

/*void draw_pile_display(Party p, int * pile_size ){ // affichage de la pioche
    if (*pile_size <= 0) {
        printf("Draw pile is empty!\n");
    }
    else{
        printf("Draw pile: [%d] (%d cards remaining)\n", p.pile[*pile_size - 1].value, *pile_size);
    }
    
}*/

void draw_pile_display(Party p, int *pile_size) { // affichage de la pioche joliment
    if (*pile_size <= 0) {
        printf(" Draw pile is empty!\n\n");
    } else {
        printf(" Draw Pile (top card):\n\n");

        // Haut de la carte
        printf("    _______    \n");

        // Valeur visible de la carte du dessus
        printf("   |  %3d  |   \n", p.pile[*pile_size - 1].value);

        // Ligne graphique vide
        printf("   |       |   \n");

        // Bas de la carte
        printf("   |_______|   \n");

        // Nombre de cartes restantes
        printf("  (%d cards remaining)\n\n", *pile_size);
    }
}




void display_party(Party *p , int *pile_size, int i ){ // que la party commence! i -> c'est l'indice du joueur, turn_index -> l'indice du tour pour la pioche
    int choice1; // choix1 entre piocher ou prendre de la defausse  
    int choice2; // choix2 -> choix entre echanger une carte avec l'une de ses cartes ou refuser et la deposer dans la defausse 
    int choice3; // choix3 -> choix de la defausse de la personne 
    int choice4; // choix4 = i l'indice de la carte du joueur qu'il veut echanger 
    int var; // variable secondaire juste afin dechanger les cartes entre la defausse et la pioche
    
    //affiche les joueurs

    for(int j=0;j< p->nb_players; j++ ){
        display_card(p->players[j],p->players[j].nb_cards);
        display_discard(p->players[j]);
    }

    // choix entre pioche ou defausse

    printf("If you want to draw a card, enter 1, otherwise if you want to take a card from the discard pile, enter 2 \n");
    choice1 = better_scan_int(""); // lecture du choix de l'utilisateur
    while (choice1 != 1 && choice1 != 2) { 
        printf("false please start again. If you want to draw a card, enter 1, otherwise if you want to take a card from the discard pile, enter 2 \n");
        choice1 = better_scan_int("");
    }
    if(choice1 == 1){// si il a choisit de piocher une carte
        if(*pile_size <=0){
            printf("Draw pile is empty. Turn skipped \n");// si la pioche est vide
            return;
        }
        draw_pile_display(*p,pile_size); // affichage de la valeur si elle est visible
        (*pile_size)--; // j'avance dans la pioche

        printf("Now enter 1 if you want to exchange your card with one of your cards, or enter 2 if you refuse the card and want to place it in your discard pile. \n");
        choice2 = better_scan_int("");
        while (choice2 != 1 && choice2 != 2) {
            printf("False, please start again.\n");
            printf("Now enter 1 if you want to exchange your card with one of your cards, or enter 2 if you refuse the card and want to place it in your discard pile. \n");
            choice2 = better_scan_int("");
        }    

        if(choice2 == 2){ // si il refuse la carte et veut la mettre dans la defausse 
            p->players[i].discard.value = p->pile[*pile_size].value; // i le joueur
            p->pile[*pile_size].seeable = 1;
        }
        else if(choice2 == 1){// si c'est le choix 1 c'est a dire si il veut l'echanger avec l'une de ses cartes perso
            printf("Enter the index of the card you want to exchange (0-%d) : \n ", p->players[i].nb_cards-1);
            choice4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
            while (choice4 < 0 || choice4 >= p->players[i].nb_cards) {
                printf("The index is not valid, please try again. Enter the index of the card you want to exchange.\n ");
                choice4 = better_scan_int("");
            }
            
            var = p->players[i].cards[choice4].value ; // variable intermediaire
            p->players[i].cards[choice4].value = p->pile[*pile_size].value; // echangerles cartes, la cartes de la pioche a la place de la carte perso 
            p->players[i].cards[choice4].seeable = 1;
            p->players[i].discard.value = var;
            p->players[i].discard.seeable = 1;
        }
    }

    else if(choice1 == 2){// prendre une carte d'une des defausse la sienne ou un autre
        printf("Choose a player's discard pile (enter a number between 0 and %d):\n", p->nb_players - 1); // choisis la défausse de quel joueur il veut prendre
        choice3 = better_scan_int("");
        while (choice3 < 0 || choice3 >= p->nb_players || p->players[choice3].discard.seeable ==0) { // à remplir : vérifier qu'il a bien choisi un joueur
            printf("False, please start again. Choose a player's discard pile (enter a number between 0 and %d):\n", p->nb_players - 1);
            choice3 = better_scan_int("");
        }

        printf("Enter the index of the card you want to exchange (between 0 and %d):\n", p->players[i].nb_cards - 1); // échange avec l'une de ses cartes visibles et la carte échangée va sur la défausse
        choice4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
        while (choice4 < 0 || choice4 >= p->players[i].nb_cards) {
            printf("The index is not valid, please try again. Enter the index of the card you want to exchange (between 0 and %d):\n", p->players[i].nb_cards - 1);
            choice4 = better_scan_int("");
        }
        var = p->players[choice3].discard.value;
        p->players[i].discard.value = p->players[i].cards[choice4].value;
        p->players[i].discard.seeable = 1;
        p->players[i].cards[choice4].value = var;
        p->players[i].cards[choice4].seeable = 1;
        p->players[choice3].discard.seeable =0;

    }
    // Affichage du joueur qui vient de jiuer 
    printf("\nEnd of %s's turn.\n", p->players[i].name);
    printf("-----------------------------\n\n");
}

void free_party(Party p){
    // Libérer les joueurs
    for (int i = 0; i < p.nb_players; i++) {
        free(p.players[i].cards); // Libérer les cartes du joueur
        free(p.players[i].name);  // Libérer le nom du joueur
    }
    free(p.players); // Libérer le tableau de joueurs
    // Libérer la pioche
    free(p.pile);
}

int endgame(Party p, int pile_size){ // qui detecte la fin de la partie elle renvoie l'indice du joueur qui a finis la partie sinon elle renvoie 100
    int cpt;
    if(pile_size <= 0){
        printf("There is no more draw pile, the game is over \n");
        return 100;
    }
    for(int i=0; i< p.nb_players; i++){
        cpt = 0;
        for(int j=0; j<p.players[i].nb_cards;j++){
            if(p.players[i].cards[j].seeable == 1){
                cpt ++;
            }         
        }
        if(cpt == p.players[i].nb_cards){
            printf("%s has all his cards visible one more turn and the game is over \n", p.players[i].name);
            return i;
        } 
    }
    return 100;
}

void scores(Party p) { // Affiche le(s) joueur(s) avec le meilleur score
    int max = 1000000;          // score minimum flemme de changer la variable 
    int i_max = 0;              // index d’un des gagnants
    int tab[10] = {0};          // indices des gagnants (si égalité) au pire des cas 8 joeurs sont egaux mais j'ai mis 10 au cas ou
    int indice = 0;             // compteur du tableau

    for (int i = 0; i < p.nb_players; i++) {
        p.players[i].score = 0;
        for (int j = 0; j < p.players[i].nb_cards; j++) {
            if (p.players[i].cards[j].seeable == 1) {
                p.players[i].score += p.players[i].cards[j].value;
            }
        }

        if (p.players[i].score < max) {
            max = p.players[i].score;
            i_max =i;
            indice =0;
            tab[indice] = i;
            indice ++;
        } 
        else if(p.players[i].score == max){
            tab[indice] = i;
            indice ++;
        }
    }

    // Affichage des gagnants
    if (indice == 1) {
        printf("\n The winner is: %s with %d points!\n", p.players[i_max].name, max);
    } 
    else {
        printf("\n It's a tie between: ");
        for (int i = 0; i < indice; i++) {
            printf("%s \n", p.players[tab[i]].name);
        }
        printf("\nAll with a score of: %d points\n", max);
    }

    // Affichage de tous les scores
    printf("\n Final scores:\n");
    for (int i = 0; i < p.nb_players; i++) {
        printf("- %s : %d points\n", p.players[i].name, p.players[i].score);
    }
}


