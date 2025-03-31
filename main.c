#include "reseau.h"

int main() {
    ReseauSocial *reseau = malloc(sizeof(ReseauSocial));
    reseau->nb_utilisateurs = 0; 
    Utilisateur *utilisateur = NULL;
    int choix;
    char nom[100];
    char nom2[100];
    char message[500];
    
    printf("Bienvenue sur Indiangram !\n");
    do {
        
    
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
            nom[strcspn(nom, "\n")] = '\0'; 
            ajouterUtilisateur(reseau, nom);
            break;
    
        case 2:
            printf("Votre nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';
            utilisateur = trouverUtilisateur(reseau, nom);
            if (!utilisateur) {
                printf("Utilisateur introuvable \n");
                break;
            }
            
            printf("Nom de l'ami : ");
            fgets(nom2, sizeof(nom2), stdin);
            nom2[strcspn(nom2, "\n")] = '\0';
            ajouterAmi(utilisateur, nom2);
            break;
    
        case 3:
            printf("Votre nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';
            utilisateur = trouverUtilisateur(reseau, nom);
            if (!utilisateur) {
                printf("Utilisateur introuvable \n");
                break;
            }
            printf("Votre message : ");
            fgets(message, sizeof(message), stdin);
            message[strcspn(message, "\n")] = '\0';
            publierMessage(utilisateur, message);
            break;
    
        case 4:
            afficherUtilisateurs(reseau);
            break;
    
        case 5:
            printf("Votre nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';
            utilisateur = trouverUtilisateur(reseau, nom);
            if (!utilisateur) {
                printf("Utilisateur introuvable \n");
                break;
            }
            afficherAmis(utilisateur);
            break;
    
        case 6:
            printf("Votre nom : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';
            utilisateur = trouverAtilisateur(reseau, nom);
            if (!utilisateur) {
                printf("Utilisateur introuvable \n");
                break;
            }
            afficherPublications(utilisateur);
            break;
    
        case 0:
            free(reseau);
            printf("A bientot sur Indiangram\n");
            break;
    
        default:
            printf("Choix invalide.\n");
        }
    } while (choix!=0);
    return 0;
}