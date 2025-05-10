
# CardYard (Projet CY-Tech MI5 A)

Une application console en C pour jouer au jeu de cartes **CardYard** :
- code final : projet CardYard  
- création, distribution et gestion de cartes  
- tour de jeu interactif avec gestion des joueurs, défausses et pioche  
- possibilité de sauvegarder et charger une partie  
- affichage ergonomique avec couleurs et cadres ASCII

---

## Descriptif des fichiers

### main.c
Point d’entrée principal du programme.  
Gère le menu principal, le lancement d’une nouvelle partie ou le chargement d’une partie existante.

### carte.c / carte.h
Gère la création du deck personnalisé, le mélange des cartes et la création des joueurs.  
Contient aussi les structures `Player` et `Card`.

### jeu.c / jeu.h
Implémente le déroulement complet de la partie :  
distribution des cartes, choix des actions, gestion de la pioche et des défausses, détection de la fin de partie, calcul des scores.

### sauvegarde.c
Permet de sauvegarder l’état complet d’une partie et de la recharger plus tard depuis un fichier `sauvegarde.txt`.

### securite.c
Contient les fonctions sécurisées pour la saisie des entiers et chaînes de caractères (`better_scan_int`, `better_scan_str`).

### Makefile
Automatise la compilation du projet et la génération de l’exécutable `exec` à partir des fichiers `.c`.

---

## Compilation & exécution

1. Ouvrez un terminal à la racine du projet.  
2. Lancez la commande :
   ```bash
   make
   ```
3. Exécutez le programme :
   ```bash
   ./exec
   ```

Amusez-vous !

---

## Trinôme :

Adjaiami Oumeyma  
Ecobichon Antoine  
Gnassounou-Boulay Ethan  
