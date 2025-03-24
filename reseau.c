#include "reseau.h"

#include "reseau.h"

Message* creer_message(const char* contenu) {
    Message* nouveau = (Message*)malloc(sizeof(Message));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau->contenu = strdup(contenu);
    nouveau->suivant = NULL;
    return nouveau;
}

Utilisateur* creer_utilisateur(int identifiant, const char* pseudo) {
    Utilisateur* nouveau = (Utilisateur*)malloc(sizeof(Utilisateur));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau->identifiant = identifiant;
    nouveau->pseudo = strdup(pseudo);
    nouveau->premiere_publication = NULL;
    nouveau->derniere_publication = NULL;
    nouveau->premier_ami = NULL;
    nouveau->suivant = NULL;
    nouveau->nb_publications = 0;
    nouveau->nb_amis = 0;
    
    return nouveau;
}

ReseauSocial* initialiser_reseau() {
    ReseauSocial* reseau = (ReseauSocial*)malloc(sizeof(ReseauSocial));
    if (reseau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    reseau->premier_utilisateur = NULL;
    reseau->nombre_utilisateurs = 0;
    
    return reseau;
}

Utilisateur* ajouter_utilisateur(ReseauSocial* reseau, const char* pseudo) {
    Utilisateur* existant = reseau->premier_utilisateur;
    while (existant != NULL) {
        if (strcmp(existant->pseudo, pseudo) == 0) {
            printf("Erreur: Un utilisateur avec le pseudo '%s' existe déjà.\n", pseudo);
            return NULL;
        }
        existant = existant->suivant;
    }
    
    int nouvel_id = reseau->nombre_utilisateurs + 1;
    Utilisateur* nouvel_utilisateur = creer_utilisateur(nouvel_id, pseudo);
    
    nouvel_utilisateur->suivant = reseau->premier_utilisateur;
    reseau->premier_utilisateur = nouvel_utilisateur;
    reseau->nombre_utilisateurs++;
    
    return nouvel_utilisateur;
}

Utilisateur* trouver_utilisateur_par_id(ReseauSocial* reseau, int identifiant) {
    Utilisateur* courant = reseau->premier_utilisateur;
    
    while (courant != NULL) {
        if (courant->identifiant == identifiant) {
            return courant;
        }
        courant = courant->suivant;
    }
    
    return NULL;
}

Utilisateur* trouver_utilisateur_par_pseudo(ReseauSocial* reseau, const char* pseudo) {
    Utilisateur* courant = reseau->premier_utilisateur;
    
    while (courant != NULL) {
        if (strcmp(courant->pseudo, pseudo) == 0) {
            return courant;
        }
        courant = courant->suivant;
    }
    
    return NULL;
}

int est_deja_ami(Utilisateur* utilisateur, Utilisateur* ami) {
    NoeudAmi* courant = utilisateur->premier_ami;
    
    while (courant != NULL) {
        if (courant->utilisateur->identifiant == ami->identifiant) {
            return 1; 
        courant = courant->suivant;
    }
    
    return 0;
    }
}
void ajouter_ami(Utilisateur* utilisateur, Utilisateur* ami) {
    if (utilisateur->identifiant == ami->identifiant) {
        printf("Un utilisateur ne peut pas être ami avec lui-même.\n");
        return;
    }
    
    if (est_deja_ami(utilisateur, ami)) {
        printf("%s est déjà ami avec %s\n", utilisateur->pseudo, ami->pseudo);
        return;
    }
    
    NoeudAmi* nouveau_noeud = (NoeudAmi*)malloc(sizeof(NoeudAmi));
    if (nouveau_noeud == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    
    nouveau_noeud->utilisateur = ami;
    nouveau_noeud->suivant = utilisateur->premier_ami;
    utilisateur->premier_ami = nouveau_noeud;
    utilisateur->nb_amis++;
    
    printf("%s est maintenant ami avec %s\n", utilisateur->pseudo, ami->pseudo);
}

void publier_message(Utilisateur* utilisateur, const char* contenu) {
    Message* nouveau = creer_message(contenu);
    
    if (utilisateur->premiere_publication == NULL) {
        utilisateur->premiere_publication = nouveau;
        utilisateur->derniere_publication = nouveau;
    } else {
        utilisateur->derniere_publication->suivant = nouveau;
        utilisateur->derniere_publication = nouveau;
    }
    
    utilisateur->nb_publications++;
    printf("Publication ajoutée pour %s: \"%s\"\n", utilisateur->pseudo, contenu);
}

void afficher_utilisateurs(ReseauSocial* reseau) {
    Utilisateur* courant = reseau->premier_utilisateur;
    
    printf("\n===== LISTE DES UTILISATEURS (%d) =====\n", reseau->nombre_utilisateurs);
    if (courant == NULL) {
        printf("Aucun utilisateur inscrit\n");
    } else {
        while (courant != NULL) {
            printf("ID: %d, Pseudo: %s, Amis: %d, Publications: %d\n", 
                   courant->identifiant, courant->pseudo, 
                   courant->nb_amis, courant->nb_publications);
            courant = courant->suivant;
        }
    }
    printf("=======================================\n");
}

void afficher_amis(Utilisateur* utilisateur) {
    if (utilisateur == NULL) {
        printf("Utilisateur non trouvé\n");
        return;
    }
    
    NoeudAmi* courant = utilisateur->premier_ami;
    
    printf("\n===== AMIS DE %s (%d) =====\n", utilisateur->pseudo, utilisateur->nb_amis);
    if (courant == NULL) {
        printf("Aucun ami\n");
    } else {
        while (courant != NULL) {
            printf("ID: %d, Pseudo: %s\n", 
                   courant->utilisateur->identifiant, 
                   courant->utilisateur->pseudo);
            courant = courant->suivant;
        }
    }
    printf("=======================\n");
}

void afficher_publications(Utilisateur* utilisateur) {
    if (utilisateur == NULL) {
        printf("Utilisateur non trouvé\n");
        return;
    }
    
    Message* courant = utilisateur->premiere_publication;
    
    printf("\n===== PUBLICATIONS DE %s (%d) =====\n", utilisateur->pseudo, utilisateur->nb_publications);
    if (courant == NULL) {
        printf("Aucune publication\n");
    } else {
        int i = 1;
        while (courant != NULL) {
            printf("%d: %s\n", i++, courant->contenu);
            courant = courant->suivant;
        }
    }
    printf("================================\n");
}

void liberer_message(Message* message) {
    if (message == NULL) return;
    
    free(message->contenu);
    free(message);
}

void liberer_messages(Message* premiere_publication) {
    Message* courant = premiere_publication;
    Message* suivant;
    
    while (courant != NULL) {
        suivant = courant->suivant;
        liberer_message(courant);
        courant = suivant;
    }
}

void liberer_amis(NoeudAmi* premier_ami) {
    NoeudAmi* courant = premier_ami;
    NoeudAmi* suivant;
    
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

void liberer_utilisateur(Utilisateur* utilisateur) {
    if (utilisateur == NULL) return;
    
    free(utilisateur->pseudo);
    liberer_messages(utilisateur->premiere_publication);
    liberer_amis(utilisateur->premier_ami);
    free(utilisateur);
}

void liberer_reseau(ReseauSocial* reseau) {
    Utilisateur* courant = reseau->premier_utilisateur;
    Utilisateur* suivant;
    
    while (courant != NULL) {
        suivant = courant->suivant;
        liberer_utilisateur(courant);
        courant = suivant;
    }
    
    free(reseau);
}

void afficher_menu() {
    printf("\n======= MENU DU RÉSEAU SOCIAL =======\n");
    printf("1. Créer un nouvel utilisateur\n");
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
    char buffer[20];
    lire_chaine(buffer, sizeof(buffer));
    return atoi(buffer);
}



