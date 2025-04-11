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
    shuffled[149]=15;
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

Player build_player(Player p, int nb_cards,int *){
    char n[100000];
    printf("type your name (50 charcaters max) :\n");
    scanf("%s",n);
    while(strlen(n)<51){
        printf("You exceeded the max characters allowed, type again :\n");
        scanf("%s",n);
    }
    p.name = malloc(sizeof(char)*strlen(n));
    if(p.name == NULL){
        printf("No dynamic space found available"); //on quitte le programme
        exit(1);
    }
    
}



int main(){
    
}