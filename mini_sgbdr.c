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

