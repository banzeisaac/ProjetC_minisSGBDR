#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define MAX_CHAMPS 10
#define MAX_ENREGISTREMENTS 100
#define MAX_NOM 50

typedef enum { ENTIER, CHAINE } Type;

typedef struct {
    char nom[MAX_NOM];
    Type type;
} Champ;

typedef union {
    int entier;
    char chaine[MAX_NOM];
} Valeur;

typedef struct {
    Valeur valeurs[MAX_CHAMPS];
} Enregistrement;

typedef struct {
    char nom[MAX_NOM];
    Champ champs[MAX_CHAMPS];
    Enregistrement enregistrements[MAX_ENREGISTREMENTS];
    int nb_champs;
    int nb_enregistrements;
} BDD;

BDD bdds[MAX_TABLES];
int nb_bdds = 0;

void creer_table() {
    if (nb_bdds >= MAX_TABLES) {
        printf("Nombre maximum de tables atteint.\n");
        return;
    }

    BDD nouvelle_table;
    printf("Entrez le nom de la nouvelle table: ");
    scanf("%s", nouvelle_table.nom);
    nouvelle_table.nb_champs = 0;
    nouvelle_table.nb_enregistrements = 0;

    bdds[nb_bdds++] = nouvelle_table;
    printf("Table '%s' créée avec succès.\n", nouvelle_table.nom);
}

int trouver_table(char *nom_table) {
    for (int i = 0; i < nb_bdds; i++) {
        if (strcmp(bdds[i].nom, nom_table) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_champ(BDD *bdd) {
    if (bdd->nb_champs >= MAX_CHAMPS) {
        printf("Nombre maximum de champs atteint pour cette table.\n");
        return;
    }

    int nb_champs_a_ajouter;
    printf("Combien de champs voulez-vous ajouter? ");
    scanf("%d", &nb_champs_a_ajouter);

    for (int i = 0; i < nb_champs_a_ajouter; i++) {
        Champ nouveau_champ;
        printf("Entrez le nom du champ: ");
        scanf("%s", nouveau_champ.nom);
        printf("Entrez le type du champ (0 pour ENTIER, 1 pour CHAINE): ");
        int type;
        scanf("%d", &type);
        nouveau_champ.type = (type == 0) ? ENTIER : CHAINE;

        bdd->champs[bdd->nb_champs++] = nouveau_champ;
        printf("Champ '%s' ajouté avec succès.\n", nouveau_champ.nom);
    }
}

void inserer_donnees(BDD *bdd) {
    if (bdd->nb_enregistrements >= MAX_ENREGISTREMENTS) {
        printf("Nombre maximum d'enregistrements atteint pour cette table.\n");
        return;
    }

    Enregistrement nouvel_enregistrement;
    for (int i = 0; i < bdd->nb_champs; i++) {
        printf("Entrez la valeur pour le champ '%s': ", bdd->champs[i].nom);
        if (bdd->champs[i].type == ENTIER) {
            scanf("%d", &nouvel_enregistrement.valeurs[i].entier);
        } else {
            scanf("%s", nouvel_enregistrement.valeurs[i].chaine);
        }
    }

    bdd->enregistrements[bdd->nb_enregistrements++] = nouvel_enregistrement;
    printf("Enregistrement ajouté avec succès.\n");
}

void afficher_donnees(BDD *bdd) {
    for (int i = 0; i < bdd->nb_champs; i++) {
        printf("%s\t", bdd->champs[i].nom);
    }
    printf("\n");

    for (int i = 0; i < bdd->nb_enregistrements; i++) {
        for (int j = 0; j < bdd->nb_champs; j++) {
            if (bdd->champs[j].type == ENTIER) {
                printf("%d\t", bdd->enregistrements[i].valeurs[j].entier);
            } else {
                printf("%s\t", bdd->enregistrements[i].valeurs[j].chaine);
            }
        }
        printf("\n");
    }
}

void supprimer_table(int index) {
    for (int i = index; i < nb_bdds - 1; i++) {
        bdds[i] = bdds[i + 1];
    }
    nb_bdds--;
    printf("Table supprimée avec succès.\n");
}

void supprimer_champ(BDD *bdd, int champ_index) {
    for (int i = champ_index; i < bdd->nb_champs - 1; i++) {
        bdd->champs[i] = bdd->champs[i + 1];
    }
    bdd->nb_champs--;
    printf("Champ supprimé avec succès.\n");
}

void mettre_a_jour_champ(BDD *bdd, int champ_index) {
    Champ *champ = &bdd->champs[champ_index];
    printf("Entrez le nouveau nom pour le champ '%s': ", champ->nom);
    scanf("%s", champ->nom);
    printf("Champ mis à jour avec succès.\n");
}

void mettre_a_jour_valeur(BDD *bdd, int champ_index, int enregistrement_index) {
    Enregistrement *enregistrement = &bdd->enregistrements[enregistrement_index];
    printf("Entrez la nouvelle valeur pour le champ '%s': ", bdd->champs[champ_index].nom);
    if (bdd->champs[champ_index].type == ENTIER) {
        scanf("%d", &enregistrement->valeurs[champ_index].entier);
    } else {
        scanf("%s", enregistrement->valeurs[champ_index].chaine);
    }
    printf("Valeur mise à jour avec succès.\n");
}

void mettre_a_jour_donnees(BDD *bdd) {
    int sous_choix;
    printf("1. Modifier un champ\n");
    printf("2. Modifier la valeur d'un champ\n");
    printf("Entrez votre choix: ");
    scanf("%d", &sous_choix);

    if (sous_choix == 1) {
        char nom_champ[MAX_NOM];
        printf("Entrez le nom du champ à modifier: ");
        scanf("%s", nom_champ);
        int champ_index = -1;
        for (int i = 0; i < bdd->nb_champs; i++) {
            if (strcmp(bdd->champs[i].nom, nom_champ) == 0) {
                champ_index = i;
                break;
            }
        }
        if (champ_index != -1) {
            mettre_a_jour_champ(bdd, champ_index);
        } else {
            printf("Champ non trouvé.\n");
        }
    } else if (sous_choix == 2) {
        char nom_champ[MAX_NOM];
        printf("Entrez le nom du champ à mettre à jour: ");
        scanf("%s", nom_champ);
        int champ_index = -1;
        for (int i = 0; i < bdd->nb_champs; i++) {
            if (strcmp(bdd->champs[i].nom, nom_champ) == 0) {
                champ_index = i;
                break;
            }
        }
        if (champ_index != -1) {
            int enregistrement_index;
            printf("Entrez l'index de l'enregistrement à mettre à jour: ");
            scanf("%d", &enregistrement_index);
            if (enregistrement_index >= 0 && enregistrement_index < bdd->nb_enregistrements) {
                mettre_a_jour_valeur(bdd, champ_index, enregistrement_index);
            } else {
                printf("Index d'enregistrement invalide.\n");
            }
        } else {
            printf("Champ non trouvé.\n");
        }
    } else {
        printf("Choix invalide.\n");
    }
}

void trier_donnees(BDD *bdd, char *nom_champ) {
    int champ_index = -1;
    for (int i = 0; i < bdd->nb_champs; i++) {
        if (strcmp(bdd->champs[i].nom, nom_champ) == 0) {
            champ_index = i;
            break;
        }
    }
    if (champ_index == -1) {
        printf("Champ non trouvé.\n");
        return;
    }

    for (int i = 0; i < bdd->nb_enregistrements - 1; i++) {
        for (int j = 0; j < bdd->nb_enregistrements - i - 1; j++) {
            int comparaison;
            if (bdd->champs[champ_index].type == ENTIER) {
                comparaison = bdd->enregistrements[j].valeurs[champ_index].entier > bdd->enregistrements[j + 1].valeurs[champ_index].entier;
            } else {
                comparaison = strcmp(bdd->enregistrements[j].valeurs[champ_index].chaine, bdd->enregistrements[j + 1].valeurs[champ_index].chaine);
            }
            if (comparaison > 0) {
                Enregistrement temp = bdd->enregistrements[j];
                bdd->enregistrements[j] = bdd->enregistrements[j + 1];
                bdd->enregistrements[j + 1] = temp;
            }
        }
    }
    printf("Table triée avec succès.\n");
}

void joindre_tables(BDD *bdd1, BDD *bdd2, char *champ_commun) {
    int champ_index1 = -1, champ_index2 = -1;
    for (int i = 0; i < bdd1->nb_champs; i++) {
        if (strcmp(bdd1->champs[i].nom, champ_commun) == 0) {
            champ_index1 = i;
            break;
        }
    }
    for (int i = 0; i < bdd2->nb_champs; i++) {
        if (strcmp(bdd2->champs[i].nom, champ_commun) == 0) {
            champ_index2 = i;
            break;
        }
    }
    if (champ_index1 == -1 || champ_index2 == -1) {
        printf("Champ commun non trouvé dans l'une ou les deux tables.\n");
        return;
    }

    for (int i = 0; i < bdd1->nb_champs; i++) {
        printf("%s\t", bdd1->champs[i].nom);
    }
    for (int i = 0; i < bdd2->nb_champs; i++) {
        if (i != champ_index2) {
            printf("%s\t", bdd2->champs[i].nom);
        }
    }
    printf("\n");

    for (int i = 0; i < bdd1->nb_enregistrements; i++) {
        for (int j = 0; j < bdd2->nb_enregistrements; j++) {
            int correspondance;
            if (bdd1->champs[champ_index1].type == ENTIER) {
                correspondance = bdd1->enregistrements[i].valeurs[champ_index1].entier == bdd2->enregistrements[j].valeurs[champ_index2].entier;
            } else {
                correspondance = strcmp(bdd1->enregistrements[i].valeurs[champ_index1].chaine, bdd2->enregistrements[j].valeurs[champ_index2].chaine) == 0;
            }
            if (correspondance) {
                for (int k = 0; k < bdd1->nb_champs; k++) {
                    if (k != champ_index1) {
                        if (bdd1->champs[k].type == ENTIER) {
                            printf("%d\t", bdd1->enregistrements[i].valeurs[k].entier);
                        } else {
                            printf("%s\t", bdd1->enregistrements[i].valeurs[k].chaine);
                        }
                    }
                }
                for (int k = 0; k < bdd2->nb_champs; k++) {
                    if (k != champ_index2) {
                        if (bdd2->champs[k].type == ENTIER) {
                            printf("%d\t", bdd2->enregistrements[j].valeurs[k].entier);
                        } else {
                            printf("%s\t", bdd2->enregistrements[j].valeurs[k].chaine);
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}

int main() {
    int choix;
    do {
        printf("\nMenu:\n");
        printf("1. Créer une table\n");
        printf("2. Ajouter un champ à une table\n");
        printf("3. Insérer des données dans une table\n");
        printf("4. Afficher les données d'une table\n");
        printf("5. Supprimer des données\n");
        printf("6. Mettre à jour des données\n");
        printf("7. Trier les données d'une table\n");
        printf("8. Joindre deux tables\n");
        printf("9. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creer_table();
                break;
            case 2: {
                char nom_table[MAX_NOM];
                printf("Entrez le nom de la table à laquelle ajouter des champs: ");
                scanf("%s", nom_table);
                int index = trouver_table(nom_table);
                if (index != -1) {
                    ajouter_champ(&bdds[index]);
                } else {
                    printf("Table non trouvée.\n");
                }
                break;
            }
            case 3: {
                char nom_table[MAX_NOM];
                printf("Entrez le nom de la table dans laquelle insérer des données: ");
                scanf("%s", nom_table);
                int index = trouver_table(nom_table);
                if (index != -1) {
                    inserer_donnees(&bdds[index]);
                } else {
                    printf("Table non trouvée.\n");
                }
                break;
            }
            case 4: {
                char nom_table[MAX_NOM];
                printf("Entrez le nom de la table dont vous voulez afficher les données: ");
                scanf("%s", nom_table);
                int index = trouver_table(nom_table);
                if (index != -1) {
                    afficher_donnees(&bdds[index]);
                } else {
                    printf("Table non trouvée.\n");
                }
                break;
            }
            case 5: {
                int sous_choix;
                printf("1. Supprimer une table\n");
                printf("2. Supprimer un champ d'une table\n");
                printf("Entrez votre choix: ");
                scanf("%d", &sous_choix);
                if (sous_choix == 1) {
                    char nom_table[MAX_NOM];
                    printf("Entrez le nom de la table à supprimer: ");
                    scanf("%s", nom_table);
                    int index = trouver_table(nom_table);
                    if (index != -1) {
                        supprimer_table(index);
                    } else {
                        printf("Table non trouvée.\n");
                    }
                } else if (sous_choix == 2) {
                    char nom_table[MAX_NOM];
                    printf("Entrez le nom de la table: ");
                    scanf("%s", nom_table);
                    int index = trouver_table(nom_table);
                    if (index != -1) {
                        char nom_champ[MAX_NOM];
                        printf("Entrez le nom du champ à supprimer: ");
                        scanf("%s", nom_champ);
                        int champ_index = -1;
                        for (int i = 0; i < bdds[index].nb_champs; i++) {
                            if (strcmp(bdds[index].champs[i].nom, nom_champ) == 0) {
                                champ_index = i;
                                break;
                            }
                        }
                        if (champ_index != -1) {
                            supprimer_champ(&bdds[index], champ_index);
                        } else {
                            printf("Champ non trouvé.\n");
                        }
                    } else {
                        printf("Table non trouvée.\n");
                    }
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            }
            case 6: {
                char nom_table[MAX_NOM];
                printf("Entrez le nom de la table à mettre à jour: ");
                scanf("%s", nom_table);
                int index = trouver_table(nom_table);
                if (index != -1) {
                    mettre_a_jour_donnees(&bdds[index]);
                } else {
                    printf("Table non trouvée.\n");
                }
                break;
            }
            case 7: {
                char nom_table[MAX_NOM];
                printf("Entrez le nom de la table à trier: ");
                scanf("%s", nom_table);
                int index = trouver_table(nom_table);
                if (index != -1) {
                    char nom_champ[MAX_NOM];
                    printf("Entrez le nom du champ pour le tri: ");
                    scanf("%s", nom_champ);
                    trier_donnees(&bdds[index], nom_champ);
                } else {
                    printf("Table non trouvée.\n");
                }
                break;
            }
            case 8: {
                char nom_table1[MAX_NOM], nom_table2[MAX_NOM], champ_commun[MAX_NOM];
                printf("Entrez le nom de la première table: ");
                scanf("%s", nom_table1);
                printf("Entrez le nom de la deuxième table: ");
                scanf("%s", nom_table2);
                printf("Entrez le nom du champ commun: ");
                scanf("%s", champ_commun);
                int index_table1 = trouver_table(nom_table1);
                int index_table2 = trouver_table(nom_table2);
                if (index_table1 != -1 && index_table2 != -1) {
                    joindre_tables(&bdds[index_table1], &bdds[index_table2], champ_commun);
                } else {
                    printf("Une ou les deux tables non trouvées.\n");
                }
                break;
            }
            case 9:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choix != 9);
    return 0;
}
