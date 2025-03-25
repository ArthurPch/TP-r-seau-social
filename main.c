#include "reseau.h"

int main() {
    ReseauSocial *reseau=malloc(sizeof(ReseauSocial));
    Utilisateur *utilisateur=malloc(sizeof(Utilisateur));
    printf("Bienvenue sur Indiangram !\n");
    while (1)
    {
    int choix;
    char nom[100];
    char message[500];

    printf("\n--- Menu ---\n");
    printf("1. Creer un utilisateur\n");
    printf("2. Ajouter un ami\n");
    printf("3. Publier un message\n");
    printf("4. Liste des utilisateurs\n");
    printf("5. Voir mes amis\n");
    printf("6. Voir mes publications\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    getchar();
    system("cls");

    switch (choix) {
            case 1:
                printf("Nom de l'utilisateur : ");
                fgets(nom, sizeof(nom), stdin);
                ajouter_utilisateur(reseau, nom);
                break;

            case 2:
                printf("Nom de l'ami : ");
                fgets(nom, sizeof(nom), stdin);
                ajouter_ami(utilisateur, nom);
                break;

            case 3:
                printf("Votre message : ");
                fgets(message, sizeof(message), stdin);
                publier_message(utilisateur, message);
                break;

            case 4:
                afficher_utilisateurs(reseau);
                break;

            case 5:
                afficher_amis(utilisateur);
                break;

            case 6:
                afficher_publications(utilisateur);
                break;

            case 0:
                free(reseau);
                free(utilisateur);
                reseau=NULL;
                utilisateur=NULL;
                printf("Au revoir !\n");
                return 0;

            default:
                printf("Choix invalide.\n");
        }

    }
    
    return 0;
}