
# Rapport de Projet : CardYard (2024-2025)

## 1. Description de l'équipe

**Membres :**
- Oumeyma : Développement principal, affichage, carte.c
- Antoine : Tests, corrections bugs, affichage couleur, jeu.c, main.c
- Ethan : Makefile, nettoyage du code, sécurisation des entrées

---

## 2. Description du projet

Le projet **CardYard** est un jeu de cartes multijoueur sous forme de programme C, respectant le cahier des charges fourni par le support de TD.

**But du jeu :** Chaque joueur doit minimiser la somme des valeurs de ses cartes à la fin de la partie.

**Règles principales :**
- Chaque joueur possède des cartes cachées + une défausse visible.
- Tour par tour : piocher ou prendre une carte visible d'une défausse.
- Un joueur qui rend toutes ses cartes visibles enclenche la fin de partie.

---

## 3. Organisation et rôles

Nous avons adopté une méthodologie agile avec réunions régulières :

- **Oumeyma** : Conception des fonctions d'affichage, création du deck, gestion des cartes (carte.c)
- **Antoine** : Réglages des bugs, amélioration des couleurs et ergonomie (jeu.c et main.c)
- **Ethan** : Amélioration du Makefile, sécurisation des entrées avec better_scan_int et better_scan_str, nettoyage global du code

**Communication :** GitHub pour la version, Whatsapp pour le suivi.

---

## 4. Journal de bord (extrait)

- **11 avril :** Première réunion, séparation du code en modules. Début des fonctions de création et mélange du deck.
- **Vacances :** Avancées grâce à Oumeyma (affichage pioche, défausse, cartes des joueurs, carte.c finalisé).
- **2 mai :** Travail d'équipe : jeu.c et main.c quasi terminés.
- **8 mai :** Ethan : création des fonctions sécurisées pour scanf.
- **9 mai :** Finalisation : Makefile finalisé par Ethan, corrections de bugs et amélioration affichage par Antoine et Oumeyma. Détection complexe de fin de partie, affichage graphique abandonné.

---

## 5. Problèmes rencontrés et solutions

Au cours du projet, plusieurs difficultés :

- Gestion complexe des pointeurs et allocations dynamiques pour éviter erreurs de segmentation.
- Synchronisation des accès aux structures de données.
- Problème persistant : détection de fin de partie avec parfois un tour supplémentaire.
- Ajustements nécessaires sur le Makefile.

Ces problèmes ont été résolus grâce à un travail d'équipe rigoureux, de nombreux tests et une progression modulaire du développement.

---

## 7. Travail restant / Améliorations possibles

Le principal axe d'amélioration identifié concerne l'affichage :

- Optimiser l'alignement et le rendu des cartes.
- Améliorer la lisibilité et le centrage pour une meilleure expérience utilisateur en terminal.

---

## 8. Conclusion

Le projet est stable et respecte les principales exigences :

**Objectifs atteints :**
- Modularité et clarté du code
- Application robuste, sans crash
- Affichage ergonomique

**Pistes de perfectionnement :**
- Améliorer le confort utilisateur
- Optimiser encore l'affichage

Ce projet a permis de renforcer nos compétences en langage C, en gestion de projet et en travail collaboratif.
