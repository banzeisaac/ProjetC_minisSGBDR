#include <stdio.h>              // Inclusion de la bibliothèque standard d'entrée/sortie
#include <stdlib.h>             // Inclusion de la bibliothèque standard pour la gestion de la mémoire et autres utilitaires
#include <string.h>             // Inclusion de la bibliothèque pour les fonctions de manipulation de chaînes

#define MAX_TABLES 10           // Définition de la constante pour le nombre maximum de tables
#define MAX_CHAMPS 10           // Définition de la constante pour le nombre maximum de champs par table
#define MAX_ENREGISTREMENTS 100 // Définition de la constante pour le nombre maximum d'enregistrements par table
#define MAX_NOM 50              // Définition de la constante pour la longueur maximale du nom d'une table ou d'un champ

// Définition de l'énumération pour les types de données possibles des champs
typedef enum { ENTIER, CHAINE } Type;

// Définition de la structure pour un champ
typedef struct {
    char nom[MAX_NOM];         // Nom du champ
    Type type;                 // Type du champ (ENTIER ou CHAINE)
} Champ;

// Définition de l'union pour une valeur de champ
typedef union {
    int entier;                // Valeur entière
    char chaine[MAX_NOM];      // Valeur chaîne
} Valeur;

// Définition de la structure pour un enregistrement
typedef struct {
    Valeur valeurs[MAX_CHAMPS]; // Tableau de valeurs de champs
} Enregistrement;

// Définition de la structure pour une table (BDD)
typedef struct {
    char nom[MAX_NOM];                          // Nom de la table
    Champ champs[MAX_CHAMPS];                   // Tableau de champs
    Enregistrement enregistrements[MAX_ENREGISTREMENTS]; // Tableau d'enregistrements
    int nb_champs;                              // Nombre de champs dans la table
    int nb_enregistrements;                     // Nombre d'enregistrements dans la table
} BDD;

BDD bdds[MAX_TABLES];            // Tableau des tables
int nb_bdds = 0;                 // Nombre de tables créées

// Fonction pour créer une nouvelle table
void creer_table() {
    if (nb_bdds >= MAX_TABLES) { // Vérifie si le nombre maximum de tables est atteint
        printf("Nombre maximum de tables atteint.\n");
        return;
    }

    BDD nouvelle_table;          // Crée une nouvelle table
    printf("Entrez le nom de la nouvelle table: ");
    scanf("%s", nouvelle_table.nom);  // Demande le nom de la nouvelle table
    nouvelle_table.nb_champs = 0;     // Initialise le nombre de champs à 0
    nouvelle_table.nb_enregistrements = 0; // Initialise le nombre d'enregistrements à 0

    bdds[nb_bdds++] = nouvelle_table; // Ajoute la nouvelle table au tableau des tables
    printf("Table '%s' créée avec succès.\n", nouvelle_table.nom); // Affiche un message de succès
}

// Fonction pour trouver l'index d'une table par son nom
int trouver_table(char *nom_table) {
    for (int i = 0; i < nb_bdds; i++) {          // Parcourt toutes les tables
        if (strcmp(bdds[i].nom, nom_table) == 0) { // Compare les noms des tables
            return i;                           // Retourne l'index si le nom correspond
        }
    }
    return -1; // Retourne -1 si la table n'est pas trouvée
}

// Fonction pour ajouter des champs à une table
void ajouter_champ(BDD *bdd) {
    if (bdd->nb_champs >= MAX_CHAMPS) {          // Vérifie si le nombre maximum de champs est atteint
        printf("Nombre maximum de champs atteint pour cette table.\n");
        return;
    }

    int nb_champs_a_ajouter;
    printf("Combien de champs voulez-vous ajouter? ");
    scanf("%d", &nb_champs_a_ajouter);           // Demande le nombre de champs à ajouter

    for (int i = 0; i < nb_champs_a_ajouter; i++) {
        Champ nouveau_champ;
        printf("Entrez le nom du champ: ");
        scanf("%s", nouveau_champ.nom);          // Demande le nom du nouveau champ
        printf("Entrez le type du champ (0 pour ENTIER, 1 pour CHAINE): ");
        int type;
        scanf("%d", &type);                      // Demande le type du nouveau champ
        nouveau_champ.type = (type == 0) ? ENTIER : CHAINE; // Définit le type du champ

        bdd->champs[bdd->nb_champs++] = nouveau_champ; // Ajoute le nouveau champ à la table
        printf("Champ '%s' ajouté avec succès.\n", nouveau_champ.nom); // Affiche un message de succès
    }
}

