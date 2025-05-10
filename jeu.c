#include "jeu.h"

int nb_players(){ // fonction pour le nombre de joueur
    int a;
    a = better_scan_int("Entrez le nombre de joueurs entre 2 et 8 (inclus) \n");
    while(a>8 || a<2 ){
        printf("Mauvaise entrée, respectez l'intervalle svp \n");
        a = better_scan_int("Entrez le nombre de joueurs entre 2 et 8 (inclus) \n ");
    }
    return a;
}

int nombre_cards() { // fonction pour le nombre de cartes par joueur
    int a;
    a = (rand()%5) + 6; // carte entre 6 et 10
    printf("Il y aura %d cartes par joueur. \n", a);
    return a;
}


Party build_players(int *pile_size){ // initialise une party. pile_size: taille de la pioche initaliser a 0.
    Party p; // une partie 
    int nomb_cards;//nb cartes
    int start = 0;

    int *d;// paquet de carte non melangee ensuite seras melanger
    d = malloc(sizeof(int)* 150);
    if(d == NULL){
        printf("erreur allocation dynamique\n"); //on quitte le programme
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
        printf("erreur allocation dynamique \n"); //on quitte le programme
        exit(1);
    }
    p.pile = malloc(sizeof(Card) * 150); // 150 parce que  deck a 150 cartes
    if (p.pile == NULL) {
        printf("erreur allocation dynamique\n");
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

    if (p.nb_players * nomb_cards + *pile_size != 150) {
    printf("Erreur : incohérence du nombre total de cartes.\n");
    exit(15);
    }
    return p;

}


void draw_pile_display(Party p, int *pile_size) { // affichage de la pioche joliment
    if (*pile_size <= 0) {
        printf(" La pioche est vide!\n\n");
    } else {
        printf(" Pioche (top card):\n\n");

        // Haut de la carte
        printf("  _______   \n");

        // Ligne graphique vide
        printf(" |       |  \n");

        // Valeur visible de la carte du dessus
        if(p.pile[*pile_size - 1].value >= -5 && p.pile[*pile_size - 1].value <= 0 ){
            printf(VERT " |  %3d  |  " FIN_COULEUR, p.pile[*pile_size - 1].value);
        }
        else if(p.pile[*pile_size - 1].value >= 1 && p.pile[*pile_size - 1].value <= 5 ){
            printf(BLEU " |  %3d  |  " FIN_COULEUR, p.pile[*pile_size - 1].value);
        }
        else if(p.pile[*pile_size - 1].value >= 6 && p.pile[*pile_size - 1].value <= 10 ){
            printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.pile[*pile_size - 1].value);
        }
        else if(p.pile[*pile_size - 1].value >= 11 && p.pile[*pile_size - 1].value <= 15 ){
            printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.pile[*pile_size - 1].value);
        }

        printf("\n");
        // Bas de la carte
        printf(" |_______|  \n");

        // Nombre de cartes restantes
        printf("  (%d cartes restantes)\n\n", *pile_size);
    }
}




void display_party(Party *p , int *pile_size, int i ){ // que la party commence! i -> c'est l'indice du joueur, turn_index -> l'indice du tour pour la pioche
    int choice1; // choix1 entre piocher ou prendre de la defausse  
    int choice2; // choix2 -> choix entre echanger une carte avec l'une de ses cartes ou refuser et la deposer dans la defausse 
    int choice3; // choix3 -> choix de la defausse de la personne 
    int choice4; // choix4 = i l'indice de la carte du joueur qu'il veut echanger 
    int var; // variable secondaire juste afin dechanger les cartes entre la defausse et la pioche
    int visible = 0; // variable pour verifier si il y a au moins une defausse visible
    
    //affiche les joueurs

    for(int j=0;j< p->nb_players; j++ ){
        display_card(p->players[j],p->players[j].nb_cards);
        display_discard(p->players[j]);
    }

    // choix entre pioche ou defausse

    printf("Entrez 1 si vous voulez piocher, sinon entrez 2\n");
    choice1 = better_scan_int(""); // lecture du choix de l'utilisateur
    while (choice1 != 1 && choice1 != 2) { 
        printf("Fausse entrée. Entrez 1 si vous voulez piocher, sinon entrez 2 \n");
        choice1 = better_scan_int("");
    }
    if(choice1 == 1){// si il a choisit de piocher une carte
        if(*pile_size <=0){
            printf("La pioche est vide, on saute votre tour \n");// si la pioche est vide
            return;
        }
        draw_pile_display(*p,pile_size); // affichage de la valeur si elle est visible
        (*pile_size)--; // j'avance dans la pioche

        printf("Entrez 1 si vous voulez échanger cette carte avec l'une des votres ou si vous la défaussez. \n");
        choice2 = better_scan_int("");
        while (choice2 != 1 && choice2 != 2) {
            printf("Fausse entrée, recommencez.\n");
            printf("Entrez 1 si vous voulez échanger cette carte avec l'une des votres ou si vous la défaussez. \n");
            choice2 = better_scan_int("");
        }    

        if(choice2 == 2){ // si il refuse la carte et veut la mettre dans la defausse 
            p->players[i].discard.value = p->pile[*pile_size].value; // i le joueur
            p->pile[*pile_size].seeable = 1;
        }
        else if(choice2 == 1){// si c'est le choix 1 c'est a dire si il veut l'echanger avec l'une de ses cartes perso
            printf("Entrez l'indice de la carte que vous voulez échanger (0-%d) : \n ", p->players[i].nb_cards-1);
            choice4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
            while (choice4 < 0 || choice4 >= p->players[i].nb_cards) {
                printf("Indice invalide, recommencez. Entrez l'indice de la carte que vous voulez échanger.\n ");
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

        // verifier si une defausse est visible au moins
        for (int j = 0; j < p->nb_players; j++) {
            if (p->players[j].discard.seeable == 1) {
                visible = 1;
                break;
            }
        }
        if (visible == 0) {
            printf("Aucune défausse visible, vous êtes obligé de piocher.\n");
            return; //return a la place de exit pour seulement arreter la partie du joueur et pas arreter totalement le code
        }

        printf("Choisissez la défausse d'un joueur  (entrez un nombre entre 0 et %d):\n", p->nb_players - 1); // choisis la défausse de quel joueur il veut prendre
        choice3 = better_scan_int("");
        while (choice3 < 0 || choice3 >= p->nb_players || p->players[choice3].discard.seeable ==0) { // à remplir : vérifier qu'il a bien choisi un joueur
            printf("Fausse entrée, recommencez. Choisissez la défausse d'un joueur  (entrez un nombre entre 0 et %d):\n", p->nb_players - 1);
            choice3 = better_scan_int("");
        }

        printf("Entrez l'indice de la carte que vous voulez échanger (entre 0 et %d):\n", p->players[i].nb_cards - 1); // échange avec l'une de ses cartes visibles et la carte échangée va sur la défausse
        choice4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
        while (choice4 < 0 || choice4 >= p->players[i].nb_cards) {
            printf("Indice invalide, recommencez. Entrez l'indice de la carte que vous voulez échanger (entre 0 et %d):\n", p->players[i].nb_cards - 1);
            choice4 = better_scan_int("");
        }
        var = p->players[choice3].discard.value;
        p->players[choice3].discard.value = p->players[i].cards[choice4].value;
        p->players[choice3].discard.seeable =1;
        p->players[i].cards[choice4].value = var;
        p->players[i].cards[choice4].seeable = 1;
        printf("%s a pris la carte de la défausse de %s et lui a rendu une carte.\n", p->players[i].name, p->players[choice3].name);   
    }
    // Affichage du joueur qui vient de jiuer 
    printf("\nFin du tour de %s.\n", p->players[i].name);
    printf("-----------------------------\n\n\n\n\n");
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
        printf("La pioche est vide, fin du jeu. \n");
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
            printf("%s a toutes ses cartes visibles, tous les joueurs jouent un autre tour et la partie se termine \n", p.players[i].name);
            return i;
        } 
    }
    return 100;
}

void scores(Party p) { // Affiche le(s) joueur(s) avec le meilleur score
    int min = 1000000;          // score minimum  
    int i_min = 0;              // index d’un des gagnants
    int tab[10] = {0};          // indices des gagnants (si égalité) au pire des cas 8 joeurs sont egaux mais j'ai mis 10 au cas ou
    int indice = 0;             // compteur du tableau

    for (int i = 0; i < p.nb_players; i++) {
        p.players[i].score = 0;
        for (int j = 0; j < p.players[i].nb_cards; j++) {
            if (p.players[i].cards[j].seeable == 1) {
                p.players[i].score += p.players[i].cards[j].value;
            }
        }

        if (p.players[i].score < min) {
            min = p.players[i].score;
            i_min =i;
            indice =0;
            tab[indice] = i;
            indice ++;
        } 
        else if(p.players[i].score == min){
            tab[indice] = i;
            indice ++;
        }
    }

    // Affichage des gagnants
    if (indice == 1) {
        printf("\n Le gagnant est : %s avec %d points!\n", p.players[i_min].name, min);
    } 
    else {
        printf("\n Egalité entre: ");
        for (int i = 0; i < indice; i++) {
            printf("%s \n", p.players[tab[i]].name);
        }
        printf("\n Tous avec un score de : %d points\n", min);
    }

    // Affichage de tous les scores
    printf("\n Scores finaux :\n");
    for (int i = 0; i < p.nb_players; i++) {
        printf("- %s : %d points\n", p.players[i].name, p.players[i].score);
    }
}


