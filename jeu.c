#include "jeu.h"

int nb_joueur(){ // fonction pour le nombre de joueur
    int a;
    a = better_scan_int("Entrez le nombre de joueurs entre 2 et 8 (inclus) \n");
    while(a>8 || a<2 ){
        printf("Mauvaise entrée, respectez l'intervalle svp \n");
        a = better_scan_int("Entrez le nombre de joueurs entre 2 et 8 (inclus) \n ");
    }
    return a;
}

int nombre_cartes() { // fonction pour le nombre de cartes par joueur
    int a;
    a = (rand()%5) + 6; // carte entre 6 et 10
    printf("Il y aura %d cartes par joueur. \n", a);
    return a;
}


Partie construire_joueur(int *taille_pile){ // initialise une Partie. taille_pile: taille de la pioche initialisée a 0.
    Partie p; // une partie 
    int nomb_cartes;//nb cartes
    int commencer = 0;

    int *d;// paquet de carte non melangé ensuite sera melangé
    d = malloc(sizeof(int)* 150);
    if(d == NULL){
        printf("erreur allocation dynamique\n"); //on quitte le programme
        exit(1);
    }
    
    p.nb_joueur = nb_joueur(); // nombre de joueurs
    nomb_cartes = nombre_cartes(); // nombre de cartes

    //melange les cartes
    paquet(d);
    melanger(d); // paquet de cartes melangé

    // cree les joueurs
    p.joueur = malloc(sizeof(Joueur)* p.nb_joueur);
    if(p.joueur == NULL){
        printf("erreur allocation dynamique \n"); //on quitte le programme
        exit(1);
    }
    p.pile = malloc(sizeof(Carte) * 150); // 150 parce que le paquet a 150 cartes
    if (p.pile == NULL) {
        printf("erreur allocation dynamique\n");
        exit(1);
    }
    for(int i =0; i<p.nb_joueur; i++){
        p.joueur[i] = construire_joueur(nomb_cartes, d,&commencer);
    }

    p.taille_pile = 150 - (p.nb_joueur * nomb_cartes);
    
    for(int i= commencer; i<150;i++){
        p.pile[*taille_pile].valeur = d[i]; // distribution des cartes 
        p.pile[*taille_pile].visible = 0; // tout caché
        (*taille_pile) ++;
    }

    if (p.nb_joueur * nomb_cartes + *taille_pile != 150) {
    printf("Erreur : incohérence du nombre total de cartes.\n");
    exit(15);
    }
    return p;

}


void affichage_pile(Partie p, int *taille_pile) { // affichage de la pioche joliment
    if (*taille_pile <= 0) {
        printf(" La pioche est vide!\n\n");
    } else {
        printf(" Pioche (top Carte):\n\n");

        // Haut de la carte
        printf("  _______   \n");

        // Ligne graphique vide
        printf(" |       |  \n");

        // Valeur visible de la carte du dessus
        if(p.pile[*taille_pile - 1].valeur >= -5 && p.pile[*taille_pile - 1].valeur <= 0 ){
            printf(VERT " |  %3d  |  " FIN_COULEUR, p.pile[*taille_pile - 1].valeur);
        }
        else if(p.pile[*taille_pile - 1].valeur >= 1 && p.pile[*taille_pile - 1].valeur <= 5 ){
            printf(BLEU " |  %3d  |  " FIN_COULEUR, p.pile[*taille_pile - 1].valeur);
        }
        else if(p.pile[*taille_pile - 1].valeur >= 6 && p.pile[*taille_pile - 1].valeur <= 10 ){
            printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.pile[*taille_pile - 1].valeur);
        }
        else if(p.pile[*taille_pile - 1].valeur >= 11 && p.pile[*taille_pile - 1].valeur <= 15 ){
            printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.pile[*taille_pile - 1].valeur);
        }

        printf("\n");
        // Bas de la carte
        printf(" |_______|  \n");

        // Nombre de cartes restantes
        printf("  (%d cartes restantes)\n\n", *taille_pile);
    }
}




void affichage_partie(Partie *p , int *taille_pile, int i ){ // que la Partie commence! i -> c'est l'indice du joueur, turn_index -> l'indice du tour pour la pioche
    int choix_1; // choix1 entre piocher ou prendre de la defausse  
    int choix_2; // choix2 -> choix entre echanger une carte avec l'une de ses cartes ou refuser et la deposer dans la defausse 
    int choix_3; // choix3 -> choix de la defausse de la personne 
    int choix_4; // choix4 = i l'indice de la carte du joueur qu'il veut echanger 
    int var; // variable secondaire juste afin dechanger les cartes entre la defausse et la pioche
    int visible = 0; // variable pour verifier si il y a au moins une defausse visible
    
    //affiche les joueurs

    for(int j=0;j< p->nb_joueur; j++ ){
        display_Carte(p->joueur[j],p->joueur[j].nb_Cartes);
        display_defausse(p->joueur[j]);
    }

    // choix entre pioche ou defausse

    printf("Entrez 1 si vous voulez piocher, sinon entrez 2\n");
    choix_1 = better_scan_int(""); // lecture du choix de l'utilisateur
    while (choix_1 != 1 && choix_1 != 2) { 
        printf("Fausse entrée. Entrez 1 si vous voulez piocher, sinon entrez 2 \n");
        choix_1 = better_scan_int("");
    }
    if(choix_1 == 1){// si il a choisi de piocher une carte
        if(*taille_pile <=0){
            printf("La pioche est vide, on saute votre tour \n");// si la pioche est vide
            return;
        }
        affichage_pile(*p,taille_pile); // affichage de la valeur si elle est visible
        (*taille_pile)--; // j'avance dans la pioche

        printf("Entrez 1 si vous voulez échanger cette carte avec l'une des votres ou 2 si vous la défaussez. \n");
        choix_2 = better_scan_int("");
        while (choix_2 != 1 && choix_2 != 2) {
            printf("Fausse entrée, recommencez.\n");
            printf("Entrez 1 si vous voulez échanger cette carte avec l'une des votres ou 2 si vous la défaussez. \n");
            choix_2 = better_scan_int("");
        }    

        if(choix_2 == 2){ // si il refuse la carte et veut la mettre dans la defausse 
            p->joueur[i].defausse.valeur = p->pile[*taille_pile].valeur; // i le joueur
            p->pile[*taille_pile].visible = 1;
        }
        else if(choix_2 == 1){// si c'est le choix 1 c'est a dire si il veut l'echanger avec l'une de ses cartes perso
            printf("Entrez l'indice de la carte que vous voulez échanger (0-%d) : \n ", p->joueur[i].nb_Cartes-1);
            choix_4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
            while (choix_4 < 0 || choix_4 >= p->joueur[i].nb_Cartes) {
                printf("Indice invalide, recommencez. Entrez l'indice de la carte que vous voulez échanger.\n ");
                choix_4 = better_scan_int("");
            }
            
            var = p->joueur[i].Cartes[choix_4].valeur ; // variable intermediaire
            p->joueur[i].Cartes[choix_4].valeur = p->pile[*taille_pile].valeur; // echanger les cartes, la carte de la pioche a la place de la carte perso 
            p->joueur[i].Cartes[choix_4].visible = 1;
            p->joueur[i].defausse.valeur = var;
            p->joueur[i].defausse.visible = 1;
        }
    }

    else if(choix_1 == 2){// prendre une carte d'une des defausses la sienne ou un autre

        // verifier si une defausse est visible au moins
        for (int j = 0; j < p->nb_joueur; j++) {
            if (p->joueur[j].defausse.visible == 1) {
                visible = 1;
                break;
            }
        }
        if (visible == 0) {
            printf("Aucune défausse visible, vous êtes obligé de piocher.\n");
            return; //return a la place de exit pour seulement arreter la partie du joueur et pas arreter totalement le code
        }

        printf("Choisissez la défausse d'un joueur  (entrez un nombre entre 0 et %d):\n", p->nb_joueur - 1); // choisi la défausse de quel joueur il veut prendre
        choix_3 = better_scan_int("");
        while (choix_3 < 0 || choix_3 >= p->nb_joueur || p->joueur[choix_3].defausse.visible ==0) { // à remplir : vérifier qu'il a bien choisi un joueur
            printf("Fausse entrée, recommencez. Choisissez la défausse d'un joueur  (entrez un nombre entre 0 et %d):\n", p->nb_joueur - 1);
            choix_3 = better_scan_int("");
        }

        printf("Entrez l'indice de la carte que vous voulez échanger (entre 0 et %d):\n", p->joueur[i].nb_Cartes - 1); // échange avec l'une de ses cartes visibles et la carte échangée va sur la défausse
        choix_4 = better_scan_int(""); // je récupère l'indice de la carte qu'il veut échanger
        while (choix_4 < 0 || choix_4 >= p->joueur[i].nb_Cartes) {
            printf("Indice invalide, recommencez. Entrez l'indice de la carte que vous voulez échanger (entre 0 et %d):\n", p->joueur[i].nb_Cartes - 1);
            choix_4 = better_scan_int("");
        }
        var = p->joueur[choix_3].defausse.valeur;
        p->joueur[choix_3].defausse.valeur = p->joueur[i].Cartes[choix_4].valeur;
        p->joueur[choix_3].defausse.visible =1;
        p->joueur[i].Cartes[choix_4].valeur = var;
        p->joueur[i].Cartes[choix_4].visible = 1;
        printf("%s a pris la carte de la défausse de %s et lui a rendu une carte.\n", p->joueur[i].nom, p->joueur[choix_3].nom);   
    }
    // Affichage du joueur qui vient de jiuer 
    printf("\nFin du tour de %s.\n", p->joueur[i].nom);
    printf("-----------------------------\n\n\n\n\n");
}


void free_Partie(Partie p){
    // Libérer les joueurs
    for (int i = 0; i < p.nb_joueur; i++) {
        free(p.joueur[i].Cartes); // Libérer les cartes du joueur
        free(p.joueur[i].nom);  // Libérer le nom du joueur
    }
    free(p.joueur); // Libérer le tableau de joueurs
    // Libérer la pioche
    free(p.pile);
}

int fin_partie(Partie p, int taille_pile){ // qui detecte la fin de la partie elle renvoie l'indice du joueur qui a fini la partie sinon elle renvoie 100
    int cpt;
    if(taille_pile <= 0){
        printf("La pioche est vide, fin du jeu. \n");
        return 100;
    }
    for(int i=0; i< p.nb_joueur; i++){
        cpt = 0;
        for(int j=0; j<p.joueur[i].nb_Cartes;j++){
            if(p.joueur[i].Cartes[j].visible == 1){
                cpt ++;
            }         
        }
        if(cpt == p.joueur[i].nb_Cartes){
            printf("%s a toutes ses cartes visibles, tous les joueurs jouent un autre tour et la partie se termine \n", p.joueur[i].nom);
            return i;
        } 
    }
    return 100;
}

void scores(Partie p) { // Affiche le(s) joueur(s) avec le meilleur score
    int min = 1000000;          // score minimum  
    int i_min = 0;              // index d’un des gagnants
    int tab[10] = {0};          // indices des gagnants (si égalité) au pire des cas 8 joeurs sont egaux mais j'ai mis 10 au cas ou
    int indice = 0;             // compteur du tableau

    for (int i = 0; i < p.nb_joueur; i++) {
        p.joueur[i].score = 0;
        for (int j = 0; j < p.joueur[i].nb_Cartes; j++) {
            if (p.joueur[i].Cartes[j].visible == 1) {
                p.joueur[i].score += p.joueur[i].Cartes[j].valeur;
            }
        }

        if (p.joueur[i].score < min) {
            min = p.joueur[i].score;
            i_min =i;
            indice =0;
            tab[indice] = i;
            indice ++;
        } 
        else if(p.joueur[i].score == min){
            tab[indice] = i;
            indice ++;
        }
    }

    // Affichage des gagnants
    if (indice == 1) {
        printf("\n Le gagnant est : %s avec %d points!\n", p.joueur[i_min].nom, min);
    } 
    else {
        printf("\n Egalité entre: ");
        for (int i = 0; i < indice; i++) {
            printf("%s \n", p.joueur[tab[i]].nom);
        }
        printf("\n Tous avec un score de : %d points\n", min);
    }

    // Affichage de tous les scores
    printf("\n Scores finaux :\n");
    for (int i = 0; i < p.nb_joueur; i++) {
        printf("- %s : %d points\n", p.joueur[i].nom, p.joueur[i].score);
    }
}


