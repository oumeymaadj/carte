#include"carte.h"


int* paquet(int d[150]) {
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

        // Ajout au paquet
        for (int j = 0; j < quantite; j++) {
            d[compteur] = valeur;
            compteur++;
        }
    }

    free(doublons);
    return d;
}


// Mélange en place un tableau de 150 cartes
void melanger(int* d) {
    for (int i = 149; i > 0; i--) {
        int j = rand() % (i + 1); // indice aléatoire entre 0 et i
        // Échange les valeurs d[i] et d[j]
        int temp = d[i];
        d[i] = d[j];
        d[j] = temp;
    }
}



Joueur construire_joueur(int nombre_cartes, int *paquet,int *commencer){ //paquet: le paquet de cartes , commencer: pointeur qui contient l'indice d'ou on commence a prfinre les cartes en gros on a un paquet de cartes et on distribut les cartes dans l'ordre, ex: le premier a les cartes de 1 a 15 le deuxieme de 15 a 30 du coup commencer c'est le pointeur de l'indice du debut
    Joueur p;
    int j =0; // indice du paquet du joueurs;
    char n[100];
    better_scan_str("Entrez votre pseudo (50 caracteres max): ", n, 51); // 51 = 50 + '\0'
    p.nom = malloc(sizeof(char)*strlen(n) +1 );// +1 pour /0
    if(p.nom == NULL){
        printf("erreur allocation dynamique \n"); //on quitte le programme
        exit(1);
    }
    strcpy(p.nom, n); //copie le contenu de la chaîne n (le pseudo entré par l'utilisateur) dans p.nom
    printf("Bienvenue, %s!\n", p.nom);
    p.nb_cartes = nombre_cartes;
    p.Cartes = malloc(sizeof(Carte)*p.nb_cartes);
    if (p.Cartes == NULL) {
        printf("erreur allocation dynamique \n");
        exit(2);
    }
    for(int i= *commencer; i<p.nb_cartes+ *commencer;i++){
        p.Cartes[j].valeur = paquet[i]; // distribution des cartes 
        p.Cartes[j].visible = 0; // mettre toute les cartes invisible
        j++;

    }
    *commencer += p.nb_cartes; // avancement du premier indice pour le prochain joueur
    p.defausse.valeur = 0;
    p.defausse.visible = 0;
    p.score = 0;
    return p;
    
}


void affichage_Carte(Joueur p, int fin) { // affiche joliment un paquet de cartes d’un joueur
    printf(" Cartes du joueur: %s\n\n", p.nom);

    // Ligne 1 : Indices
    for (int i = 0; i < fin; i++) {
        printf("   (%2d)     ", i);
    }
    printf("\n");

    // Ligne 2 : Haut des cartes
    for (int i = 0; i < fin; i++) {
        printf("  _______   ");
    }
    printf("\n");

    // Ligne 3 : Visuel vide
    for (int i = 0; i < fin; i++) {
        printf(" |       |  ");
    }
    printf("\n");

    // Ligne 4 : Valeur
    for (int i = 0; i < fin; i++) {
        if (p.Cartes[i].visible == 1){
            if(p.Cartes[i].valeur >= -5 && p.Cartes[i].valeur <= 0 ){
                printf(VERT " |  %3d  |  " FIN_COULEUR, p.Cartes[i].valeur);
            }
            else if(p.Cartes[i].valeur >= 1 && p.Cartes[i].valeur <= 5 ){
                printf(BLEU " |  %3d  |  " FIN_COULEUR, p.Cartes[i].valeur);
            }
            else if(p.Cartes[i].valeur >= 6 && p.Cartes[i].valeur <= 10 ){
                printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.Cartes[i].valeur);
            }
            else if(p.Cartes[i].valeur >= 11 && p.Cartes[i].valeur <= 15 ){
                printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.Cartes[i].valeur);
            }
        }
        else{
            printf(" |  ??   |  ");
        }
    }
    printf("\n");

    // Ligne 5 : Bas des cartes
    for (int i = 0; i < fin; i++) {
        printf(" |_______|  ");
    }
    printf("\n\n");
}



void affichage_defausse(Joueur p) { // affiche la défausse du joueur joliment
    printf(" Défausse du joueur: %s\n\n", p.nom);

    // Ligne 1 : Titre centré
    printf("     Défausse    \n");

    // Ligne 2 : Haut de la carte
    printf("  _______   \n");

    // Ligne 3 : Vide
    printf(" |       |  \n");

    // Ligne 4 : Valeur visible ou cachée
    if (p.defausse.visible == 1) {
        if(p.defausse.valeur >= -5 && p.defausse.valeur <= 0 ){
            printf(VERT " |  %3d  |  " FIN_COULEUR, p.defausse.valeur);
        }
        else if(p.defausse.valeur >= 1 && p.defausse.valeur <= 5 ){
            printf(BLEU " |  %3d  |  " FIN_COULEUR, p.defausse.valeur);
        }
        else if(p.defausse.valeur >= 6 && p.defausse.valeur <= 10 ){
            printf(JAUNE " |  %3d  |  " FIN_COULEUR, p.defausse.valeur);
        }
        else if(p.defausse.valeur >= 11 && p.defausse.valeur <= 15 ){
            printf(ROUGE " |  %3d  |  " FIN_COULEUR, p.defausse.valeur);
        }
    } else {
        printf(" |  ??   |  ");
    }
    printf("\n");
    // Ligne 5 : Bas
    printf(" |_______|  \n\n");
}


