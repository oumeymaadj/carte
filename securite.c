#include "carte.h"  // Inclusion de l'en-tête pour les définitions de types de cartes

// Fonction pour saisir un entier de manière sécurisée
int better_scan_int(const char *message) {
    int var;  // Variable pour stocker l'entier saisi
    int ret_var;  // Variable pour vérifier si scanf a réussi
    do {
        printf("%s", message);  // Affiche le message demandé
        ret_var = scanf("%d", &var);  // Lit un entier avec scanf
        while (getchar() != '\n');  // Vide le tampon de saisie (pour éliminer les caractères restants)
        if (ret_var != 1) {  // Si la saisie n'est pas un entier valide
            printf("Entrée invalide. Veuillez saisir un entier.\n");  // Affiche un message d'erreur
        }
    } while (ret_var != 1);  // Réitère tant que l'entrée n'est pas valide
    return var;  // Retourne l'entier valide saisi
}

// Fonction pour saisir une chaîne de caractères de manière sécurisée
void better_scan_str(const char *message, char *buffer, int buffer_size) {
    int valid = 0;  // Variable pour contrôler si l'entrée est valide
    while (!valid) {  // Tant que l'entrée n'est pas valide, on répète la demande
        printf("%s", message);  // Affiche le message demandé
        if (fgets(buffer, buffer_size, stdin) != NULL) {  // Utilise fgets pour lire une ligne dans le buffer
            size_t len = strlen(buffer);  // Récupère la longueur de la chaîne lue
            if (len > 0 && buffer[len - 1] == '\n') {  // Si la chaîne contient un saut de ligne
                buffer[len - 1] = '\0';  // On enlève le saut de ligne
            } else {  // Si l'entrée dépasse la taille du buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);  // Vide le tampon d'entrée
            }
            valid = 1;  // Si la lecture est correcte, on considère l'entrée comme valide
        } else {
            printf("Erreur de lecture. Veuillez réessayer.\n");  // Si la lecture échoue, on affiche une erreur
            int c;
            while ((c = getchar()) != '\n' && c != EOF);  // Nettoie stdin pour éviter des saisies incorrectes ultérieures
        }
    }
}
