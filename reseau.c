#include "reseau.h"

int ajouter_utilisateur(ReseauSocial *reseau, char *nom) {
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        if (strcmp(reseau->utilisateurs[i].nom, nom) == 0) {
            printf("Ce nom d'utilisateur existe deja.\n");
            return 0;
        }
    }

    Utilisateur *nouveau = &reseau->utilisateurs[reseau->nb_utilisateurs];
    strcpy(nouveau->nom, nom);
    nouveau->id = reseau->nb_utilisateurs + 1;
    nouveau->nb_amis = 0;
    nouveau->nb_posts = 0;

    return reseau->nb_utilisateurs++;
}

Utilisateur* trouver_utilisateur(ReseauSocial *reseau, char *nom) {
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        if (strcmp(reseau->utilisateurs[i].nom, nom) == 0) {
            return &reseau->utilisateurs[i];
        }
    }
    return NULL;
}

void ajouter_ami(Utilisateur *utilisateur, char *ami) {

    for (int i = 0; i < utilisateur->nb_amis; i++) {
        if (strcmp(utilisateur->amis[i], ami) == 0) {
            printf("Cet ami existe deja.\n");
            return;
        }
    }

    strcpy(utilisateur->amis[utilisateur->nb_amis++], ami);
    printf("%s est maintenant ami avec %s\n", utilisateur->nom, ami);
}

void publier_message(Utilisateur *utilisateur, char *message) {

    strcpy(utilisateur->posts[utilisateur->nb_posts++], message);
    printf("Message publie avec succes !\n");
}

void afficher_utilisateurs(ReseauSocial *reseau) {
    printf("\n--- Liste des utilisateurs ---\n");
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        printf("%d. %s\n", reseau->utilisateurs[i].id, reseau->utilisateurs[i].nom);
    }
}

void afficher_amis(Utilisateur *utilisateur) {
    printf("\n--- Amis de %s ---\n", utilisateur->nom);
    for (int i = 0; i < utilisateur->nb_amis; i++) {
        printf("%s\n", utilisateur->amis[i]);
    }
}

void afficher_publications(Utilisateur *utilisateur) {
    printf("\n--- Publications de %s ---\n", utilisateur->nom);
    for (int i = 0; i < utilisateur->nb_posts; i++) {
        printf("%s\n", utilisateur->posts[i]);
    }
}

    