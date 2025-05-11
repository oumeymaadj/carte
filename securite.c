#include"carte.h"

int better_scan_int(const char *message) {
    int var;
    int ret_var;
    do {
        printf("%s", message);
        ret_var = scanf("%d", &var);
        while (getchar() != '\n'); // vide le tampon
        if (ret_var != 1) {
            printf("Entrée invalide. Veuillez saisir un entier.\n");
        }
    } while (ret_var != 1);
    return var;
}


void better_scan_str(const char *message, char *buffer, int taille_buffer) {
    int valid = 0;
    while (!valid) {
        printf("%s", message);
        if (fgets(buffer, taille_buffer, stdin) != NULL) {
            // Supprimer le saut de ligne s’il est présent
            taille_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            } else {
                // Si l'utilisateur dépasse la taille du buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
            valid = 1;
        } else {
            printf("Erreur de lecture. Veuillez réessayer.\n");
            // Nettoyer stdin si besoin
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}
