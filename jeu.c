#include "jeu.h"

int nb_players(){ // fonction pour le nombre de joueur
    int a;
    printf("Enter the number of players in the game between 2 and 8 \n");
    scanf("%d",&a);
    while(a>8 || a<2 ){
        printf("start over you entered the wrong number \n");
        scanf("%d",&a);
    }
    return a;
}

int nb_cards(int play){// fonctions pour le nombre de cartes pas joueurs, play est le nombre de joueurs
    int a;
    printf("Enter the number of cards for each player between 2 and 8 \n");
    scanf("%d",&a);
    while(play == 8 && (a>8 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 8 \n");
        scanf("%d",&a);
    }
    while(play == 7 && (a>9 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 9 \n");
        scanf("%d",&a);
    }
    while(play == 6 && (a>10 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 10 \n");
        scanf("%d",&a);
    }
    while(play == 5 && (a>12 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 12\n");
        scanf("%d",&a);
    }
    while(play == 4 && (a>15 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 15 \n");
        scanf("%d",&a);
    }
    while(play == 3 && (a>20 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 20 \n");
        scanf("%d",&a);
    }
    while(play == 2 && (a>25 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 25 \n");
        scanf("%d",&a);
    }
    return a;
}



Party build_players(int *pickaxe_size){ // initialise une party. pickaxe_size: taille de la pioche initaliser a 0.
    Party p; // une partie 
    int nomb_cards;//nb cartes
    int start = 0;

    int *d;// paquet de carte non melangee
    d = malloc(sizeof(int)* 150);
    if(d == NULL){
        printf("No dynamic space found available\n"); //on quitte le programme
        exit(1);
    }
    
    int *deck_; // paquet de carte melangee
    deck_ = malloc(sizeof(int)* 150);
    if(deck_ == NULL){
        printf("No dynamic space found available\n"); //on quitte le programme
        exit(1);
    }

    p.nb_players = nb_players(); // nombre de joueurs
    nomb_cards = nb_cards(p.nb_players); // nombre de cartes

    //melange les cartes
    deck(d);
    deck_ = shuffle(d,deck_); // paquet de cartes melangé

    // cree les joueurs
    p.players = malloc(sizeof(Player)* p.nb_players);
    if(p.players == NULL){
        printf("No dynamic space found available \n"); //on quitte le programme
        exit(1);
    }
    for(int i =0; i<p.nb_players; i++){
        p.players[i] = build_player(nomb_cards, deck_,&start);
    }

    p.size_pickaxe = 150 - (p.nb_players * nomb_cards);
    
    for(int i= start; i<150;i++){
        p.pickaxe[*pickaxe_size].value = deck_[i]; // distribution des cartes 
        p.pickaxe[*pickaxe_size].seeable = 0; // tout cachée
        (*pickaxe_size) ++;
    }
    return p;

}

void draw_pile_display(Party p, int * pickaxe_size){ // affichage de la pioche
    printf("hide the display of the draw pile \n");
    printf("%d \n", p.pickaxe[*pickaxe_size -1].value);
}

void display_party(Party p , int *pickaxe_size){ // que la party commence 
    int choice1; // choix entre piocher ou prendre de la defausse 
    int choice2; // choix1 = 1-> choix entre echanger une carte avec l'une de ses cartes ou refuser et la deposer dans la defausse 
    int choice3; // choix1 = 2 -> choix de la defausse de la personne 
    for(int i=0;i< p.nb_players; i++ ){
        display_card(p.players[i],p.players[i].nb_cards);
        display_discard(p.players[i]);
    }
    printf("If you want to draw a card, enter 1, otherwise if you want to take a card from the discard pile, enter 2 \n");
    scanf("%d",&choice1);
    while(choice1 != 1 && choice1!=2){ 
        printf("false please start again.If you want to draw a card, enter 1, otherwise if you want to take a card from the discard pile, enter 2 \n");
        scanf("%d",&choice1);
    }
    if(choice1 == 1){// si il a choisit de piocher une carte
        draw_pile_display(p,pickaxe_size);
        (*pickaxe_size)--;
        printf("Now enter 1 if you want to exchange your card with one of your cards, or enter 2 if you refuse the card and want to place it in your discard pile. \n");
        scanf("%d",&choice2);
        while(choice2 != 1 && choice2!=2){ 
            printf("false please start again. Now enter 1 if you want to exchange your card with one of your cards, or enter 2 if you refuse the card and want to place it in your discard pile. \n");
            scanf("%d",&choice2);
        }
        if(choice2 == 2){ // si il refuse la carte et veut la mettre dans la defausse 
            p.players[i].discard.values = p.pickaxe[*pickaxe_size -1].value; // i le joueurs pas encore inialiser a faire !!
        }
        else{// si c'est le choix 1 c'est a dire si il veut l'echanger avec l'une de ses cartes perso
          // ... A REMPLIR!!!
        }
    }
    else if(choice1 == 2){// prendre une carte d'une des defausse la sienne ou un autre
        printf("Which card from which player's discard pile do you choose? \n");// choisis la defausse de quelle joueurs il veut prendre 
        scanf("%d",&choice3);
        while(choice3 <2 || choice3>8 ){  // a remplir verifier qu'il a bien choisie un jouer 
            printf("false please start again.Which card from which player's discard pile do you choose? \n");
            scanf("%d",&choice3);
        }
        //echange avec l'une de ses cartes visible et la carte echanger vas sur la defausse 

    }
}


