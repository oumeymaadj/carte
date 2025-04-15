#include "jeu.h"

int nb_players(){ // fonction pour le nombre de joueur
    int a;
    printf("Enter the number of players in the game between 2 and 8");
    scanf("%d",&a);
    while(a>8 || a<2 ){
        printf("start over you entered the wrong number");
        scanf("%d",&a);
    }
    return a;
}

int nb_cards(int play){// fonctions pour le nombre de cartes pas joueurs, play est le nombre de joueurs
    int a;
    printf("Enter the number of cards for each player between 2 and 8");
    scanf("%d",&a);
    while(play == 8 && (a>8 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 8");
        scanf("%d",&a);
    }
    while(play == 7 && (a>9 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 9");
        scanf("%d",&a);
    }
    while(play == 6 && (a>10 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 10");
        scanf("%d",&a);
    }
    while(play == 5 && (a>12 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 12");
        scanf("%d",&a);
    }
    while(play == 4 && (a>15 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 15");
        scanf("%d",&a);
    }
    while(play == 3 && (a>20 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 20");
        scanf("%d",&a);
    }
    while(play == 2 && (a>25 || a<6)){
        printf("The number of cards does not respect the interval Enter a number between 6 and 25");
        scanf("%d",&a);
    }
    return a;
}



Party build_players(){ // initialise une party
    Party p; // une partie 
    int nomb_cards;//nb cartes
    int start = 0;
    int j=0; // compteur pour la pioche

    int *d;// paquet de carte non melangee
    d = malloc(sizeof(int)* 150);
    if(d == NULL){
        printf("No dynamic space found available"); //on quitte le programme
        exit(1);
    }
    
    int *deck_; // paquet de carte melangee
    deck_ = malloc(sizeof(int)* 150);
    if(deck_ == NULL){
        printf("No dynamic space found available"); //on quitte le programme
        exit(1);
    }

    p.nb_players = nb_players(); // nombre de joueurs
    nomb_cards = nb_cards(p.nb_players); // nombre de cartes

    //melange les cartes
    deck(d);
    *deck_ = shuffle(d,deck_); // paquet de cartes melangé

    // cree les joueurs
    p.players = malloc(sizeof(Player)* p.nb_players);
    if(p.players == NULL){
        printf("No dynamic space found available"); //on quitte le programme
        exit(1);
    }
    for(int i =0; i<p.nb_players; i++){
        p.players[i] = build_player(nomb_cards, deck_,&start);
    }

    p.size_pickaxe = 150 - (p.nb_players * nomb_cards);
    
    for(int i= start; i<150;i++){
        p.pickaxe[j].value = deck_[i]; // distribution des cartes 
        p.pickaxe[j].seeable = 0; // tout cachée
        j++;
    }
    return p;

}

void display_party(Party p){ // que la party commence 
    


}
typedef struct{
    Player *players; //joueurs maximum 8 et minimum 2
    int nb_players; //nombre de joueurs
    Card *pickaxe; // pioche
    int size_pickaxe; //taille de la pioche  
}Party;