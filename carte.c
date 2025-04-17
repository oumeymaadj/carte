#include"carte.h"

int scanfbutbetter(){
    ///recuperer dans un td jsp lequel
}

int* deck(int d[150]){// cree un paquet de cartes avec les conditions ATTENTION ils sont dans l'odre
    int c= 0;
    for(int i=0;i<5;i++){
        *(d+c)= -2;
        c++;
    }
    for(int i=5;i<15;i++){
        *(d+c)= -1;
        c++;
    }
    for(int i=15;i<30;i++){
        *(d+c)= 0;
        c++;
    }
    for(int i=1;i<=12;i++){
        for(int j=1;j<=10;j++){
            *(d+c)= i;
            c++;
        }
    }
    return d;
}

int* shuffle(int d[150], int shuffled[150]){// shuffled tableaux vide qui seras retourner avec le paquet de cartes melangee
    int k =1; //booleens qui permet de verifier si l'indice a deja ete pris(1 si il n'est pas dedans 0 sinon)
    int nb; //indice aléatoire qu'on va prendre du tab d
    int j=0;
    int takenindeces[150] ={0}; //tab avec indices deja pris du tableau d
    while(j<150){
        k=1;
        do{
            nb = rand()%150;
            for(int i=0;i<j;i++){
                if(nb == takenindeces[i]){
                    k=0;
                    break;
                }
            }
        }while(k==0);
        takenindeces[j]=nb;
        shuffled[j]=d[nb];
        j++;
    }
    return shuffled; 
}



Player build_player(int nomb_cards, int *deck,int *start){ //deck: le paquet de cartes , start: pointeur qui contient l'indice d'ou on commence a prendre les cartes en gros on a un paquet de cartes et on distribut les cartes dans l'ordre, ex: le premier a les cartes de 1 a 15 le deuxieme de 15 a 30 du coup start c'est le pointeur de l'indice du debut
    Player p;
    int j =0; // indice du paquet du joueurs;
    char n[100000];
    printf("type your name (50 charcaters max) :\n");
    scanf("%s",n);
    while(strlen(n) > 50 ){
        printf("You exceeded the max characters allowed, type again :\n");
        scanf("%s",n);
    }
    p.name = malloc(sizeof(char)*strlen(n) +1 );// +1 pour /0
    if(p.name == NULL){
        printf("No dynamic space found available \n"); //on quitte le programme
        exit(1);
    }
    strcpy(p.name, n);
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
    return p;
    
}

void display_card(Player p, int end){ // affuiche un paquet de carte d'un joueur 
    printf("Player Card Display: %s \n", p.name);
    for(int i= 0;i< end ;i++){
        if(p.cards[i].seeable == 1){
            printf("%d \n",p.cards[i].value);
        }
        else{
            printf("??? \n");
        }
    }
}

void display_discard(Player p){ // affiche la defausse du joueurs   
    printf("Player Discard Display: %s \n", p.name);
    if(p.discard.seeable == 1){
        printf("%d \n",p.discard.value);
    }
    else{
        printf("??? \n");
    }
}

int main(){
    
}