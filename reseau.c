#include "reseau.h"

ReseauSocial* initialiser_reseau() {
    ReseauSocial* reseau = malloc(sizeof(ReseauSocial));
    if (!reseau) {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    reseau->premier_utilisateur = NULL;
    reseau->nombre_utilisateurs = 0;
    return reseau;
}

Utilisateur* ajouter_utilisateur(ReseauSocial* reseau, const char* pseudo) {
    int nouvel_id = reseau->nombre_utilisateurs + 1;
    Utilisateur* nouvel_utilisateur = malloc(sizeof(Utilisateur));
    if (!nouvel_utilisateur) {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }

    nouvel_utilisateur->identifiant = nouvel_id;
    nouvel_utilisateur->pseudo = strdup(pseudo);
    nouvel_utilisateur->premiere_publication = NULL;
    nouvel_utilisateur->derniere_publication = NULL;
    nouvel_utilisateur->premier_ami = NULL;
    nouvel_utilisateur->suivant = reseau->premier_utilisateur;
    nouvel_utilisateur->nb_publications = 0;
    nouvel_utilisateur->nb_amis = 0;

    reseau->premier_utilisateur = nouvel_utilisateur;
    reseau->nombre_utilisateurs++;

    return nouvel_utilisateur;
}

Utilisateur* trouver_utilisateur_par_id(ReseauSocial* reseau, int identifiant) {
    Utilisateur* courant = reseau->premier_utilisateur;
    while (courant) {
        if (courant->identifiant == identifiant) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

Utilisateur* trouver_utilisateur_par_pseudo(ReseauSocial* reseau, const char* pseudo) {
    Utilisateur* courant = reseau->premier_utilisateur;
    while (courant) {
        if (strcmp(courant->pseudo, pseudo) == 0) {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}

void ajouter_ami(Utilisateur* utilisateur, Utilisateur* ami) {
    if (!utilisateur || !ami || utilisateur == ami) {
        printf("Ajout d'ami impossible.\n");
        return;
    }

    NoeudAmi* nouveau_ami = malloc(sizeof(NoeudAmi));
    if (!nouveau_ami) {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }

    nouveau_ami->utilisateur = ami;
    nouveau_ami->suivant = utilisateur->premier_ami;
    utilisateur->premier_ami = nouveau_ami;
    utilisateur->nb_amis++;

    // Ajout réciproque
    NoeudAmi* nouvel_ami_reciproque = malloc(sizeof(NoeudAmi));
    nouvel_ami_reciproque->utilisateur = utilisateur;
    nouvel_ami_reciproque->suivant = ami->premier_ami;
    ami->premier_ami = nouvel_ami_reciproque;
    ami->nb_amis++;

    printf("%s et %s sont maintenant amis !\n", utilisateur->pseudo, ami->pseudo);
}

void publier_message(Utilisateur* utilisateur, const char* contenu) {
    if (!utilisateur) {
        printf("Utilisateur introuvable.\n");
        return;
    }

    Message* nouveau_message = malloc(sizeof(Message));
    if (!nouveau_message) {
        fprintf(stderr, "Erreur d'allocation memoire\n");
        exit(EXIT_FAILURE);
    }

    nouveau_message->contenu = strdup(contenu);
    nouveau_message->suivant = NULL;

    if (!utilisateur->premiere_publication) {
        utilisateur->premiere_publication = nouveau_message;
    } else {
        utilisateur->derniere_publication->suivant = nouveau_message;
    }

    utilisateur->derniere_publication = nouveau_message;
    utilisateur->nb_publications++;

    printf("Message publie avec succes !\n");
}

void afficher_utilisateurs(ReseauSocial* reseau) {
    if (!reseau->premier_utilisateur) {
        printf("Aucun utilisateur inscrit.\n");
        return;
    }

    Utilisateur* courant = reseau->premier_utilisateur;
    printf("\nListe des utilisateurs :\n");
    while (courant) {
        printf("- ID: %d, Pseudo: %s (Amis: %d, Publications: %d)\n",
               courant->identifiant, courant->pseudo, courant->nb_amis, courant->nb_publications);
        courant = courant->suivant;
    }
}

void afficher_amis(Utilisateur* utilisateur) {
    if (!utilisateur || !utilisateur->premier_ami) {
        printf("Aucun ami trouve.\n");
        return;
    }

    printf("\nAmis de %s :\n", utilisateur->pseudo);
    NoeudAmi* courant = utilisateur->premier_ami;
    while (courant) {
        printf("- %s\n", courant->utilisateur->pseudo);
        courant = courant->suivant;
    }
}

void afficher_publications(Utilisateur* utilisateur) {
    if (!utilisateur || !utilisateur->premiere_publication) {
        printf("Aucune publication trouvee.\n");
        return;
    }

    printf("\nPublications de %s :\n", utilisateur->pseudo);
    Message* courant = utilisateur->premiere_publication;
    while (courant) {
        printf("- %s\n", courant->contenu);
        courant = courant->suivant;
    }
}

void liberer_reseau(ReseauSocial* reseau) {
    if (!reseau) return;

    Utilisateur* courant = reseau->premier_utilisateur;
    while (courant) {
        Utilisateur* temp = courant;

        // Libérer les publications
        Message* msg = courant->premiere_publication;
        while (msg) {
            Message* tmp_msg = msg;
            msg = msg->suivant;
            free(tmp_msg->contenu);
            free(tmp_msg);
        }

        // Libérer la liste d'amis
        NoeudAmi* ami = courant->premier_ami;
        while (ami) {
            NoeudAmi* tmp_ami = ami;
            ami = ami->suivant;
            free(tmp_ami);
        }

        // Libérer l'utilisateur
        free(temp->pseudo);
        courant = courant->suivant;
        free(temp);
    }

    free(reseau);
}

void afficher_menu() {
    printf("\n======= MENU DU RESEAU SOCIAL =======\n");
    printf("1. Creer un nouvel utilisateur\n");
    printf("2. Ajouter un ami\n");
    printf("3. Publier un message\n");
    printf("4. Afficher tous les utilisateurs\n");
    printf("5. Afficher les amis d'un utilisateur\n");
    printf("6. Afficher les publications d'un utilisateur\n");
    printf("0. Quitter\n");
    printf("Votre choix: ");
}

void lire_chaine(char* buffer, int taille) {
    fgets(buffer, taille, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

int lire_entier() {
    char entree[20];
    lire_chaine(entree, sizeof(entree));
    return atoi(entree);
}
