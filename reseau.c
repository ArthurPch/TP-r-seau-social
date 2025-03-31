#include "reseau.h"

int ajouterUtilisateur(ReseauSocial *reseau, char *nom) {
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

    reseau->nb_utilisateurs++;
    return 1;
}

Utilisateur* trouverUtilisateur(ReseauSocial *reseau, char *nom) {
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        if (strcmp(reseau->utilisateurs[i].nom, nom) == 0) {
            return &reseau->utilisateurs[i];
        }
    }
    return NULL;
}

void ajouterAmi(Utilisateur *utilisateur, char *ami) {
    for (int i = 0; i < utilisateur->nb_amis; i++) {
        if (strcmp(utilisateur->amis[i], ami) == 0) {
            printf("Cet ami existe deja.\n");
            return;
        }
    }

    strcpy(utilisateur->amis[utilisateur->nb_amis], ami);
    utilisateur->nb_amis++;
    printf("%s est maintenant ami avec %s\n", utilisateur->nom, ami);
}

void publierMessage(Utilisateur *utilisateur, char *message) {
    strcpy(utilisateur->posts[utilisateur->nb_posts], message);
    utilisateur->nb_posts++;
    printf("Message publie avec succes !\n");
}

void afficherUtilisateurs(ReseauSocial *reseau) {
    printf("\n--- Liste des utilisateurs ---\n");
    for (int i = 0; i < reseau->nb_utilisateurs; i++) {
        printf("%d. %s\n", reseau->utilisateurs[i].id, reseau->utilisateurs[i].nom);
    }
}

void afficherAmis(Utilisateur *utilisateur) {
    printf("\n--- Amis de %s ---\n", utilisateur->nom);
    for (int i = 0; i < utilisateur->nb_amis; i++) {
        printf("%s\n", utilisateur->amis[i]);
    }
}

void afficherPublications(Utilisateur *utilisateur) {
    printf("\n--- Publications de %s ---\n", utilisateur->nom);
    for (int i = 0; i < utilisateur->nb_posts; i++) {
        printf("%s\n", utilisateur->posts[i]);
    }
}