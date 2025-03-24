#include "reseau.h"
#include <ctype.h>

int main() {
    ReseauSocial* reseau = initialiser_reseau();
    int choix = -1;
    char entree[1024];

    printf("Bienvenue sur le Reseau Social Minimaliste!\n");

    while (choix != 0) {
        afficher_menu();
        choix = lire_entier();

        switch (choix) {
            case 1: 
                printf("Entrez le pseudo de l'utilisateur: ");
                lire_chaine(entree, sizeof(entree));
                Utilisateur* nouvel_utilisateur = ajouter_utilisateur(reseau, entree);
                if (nouvel_utilisateur) {
                    printf("Utilisateur cree avec succes! ID: %d\n", nouvel_utilisateur->identifiant);
                }
                break;

            case 2: 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(entree, sizeof(entree));
                Utilisateur* utilisateur = isdigit(entree[0]) ? 
                    trouver_utilisateur_par_id(reseau, atoi(entree)) :
                    trouver_utilisateur_par_pseudo(reseau, entree);

                if (!utilisateur) {
                    printf("Utilisateur non trouve.\n");
                    break;
                }

                printf("Entrez l'ID ou le pseudo de l'ami a ajouter: ");
                lire_chaine(entree, sizeof(entree));
                Utilisateur* ami = isdigit(entree[0]) ? 
                    trouver_utilisateur_par_id(reseau, atoi(entree)) :
                    trouver_utilisateur_par_pseudo(reseau, entree);

                if (!ami) {
                    printf("Ami non trouve.\n");
                    break;
                }

                ajouter_ami(utilisateur, ami);
                break;

            case 3: 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(entree, sizeof(entree));
                utilisateur = isdigit(entree[0]) ? 
                    trouver_utilisateur_par_id(reseau, atoi(entree)) :
                    trouver_utilisateur_par_pseudo(reseau, entree);

                if (!utilisateur) {
                    printf("Utilisateur non trouve.\n");
                    break;
                }

                printf("Entrez le message a publier: ");
                lire_chaine(entree, sizeof(entree));
                publier_message(utilisateur, entree);
                break;

            case 4: 
                afficher_utilisateurs(reseau);
                break;

            case 5: 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(entree, sizeof(entree));
                utilisateur = isdigit(entree[0]) ? 
                    trouver_utilisateur_par_id(reseau, atoi(entree)) :
                    trouver_utilisateur_par_pseudo(reseau, entree);

                if (!utilisateur) {
                    printf("Utilisateur non trouve.\n");
                    break;
                }

                afficher_amis(utilisateur);
                break;

            case 6: 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(entree, sizeof(entree));
                utilisateur = isdigit(entree[0]) ? 
                    trouver_utilisateur_par_id(reseau, atoi(entree)) :
                    trouver_utilisateur_par_pseudo(reseau, entree);

                if (!utilisateur) {
                    printf("Utilisateur non trouve.\n");
                    break;
                }

                afficher_publications(utilisateur);
                break;

            case 0:
                printf("Au revoir!\n");
                break;

            default:
                printf("Choix non valide. Veuillez reessayer.\n");
                break;
        }
    }

    liberer_reseau(reseau);
    return 0;
}