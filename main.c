#include "reseau.h"

int main() {
    ReseauSocial* reseau = initialiser_reseau();
    int choix = -1;
    char buffer[1024];
    
    printf("Bienvenue sur le Réseau Social Minimaliste!\n");
    
    while (choix != 0) {
        afficher_menu();
        choix = lire_entier();
        
        switch (choix) {
            case 1: { 
                printf("Entrez le pseudo de l'utilisateur: ");
                lire_chaine(buffer, sizeof(buffer));
                Utilisateur* nouvel_utilisateur = ajouter_utilisateur(reseau, buffer);
                if (nouvel_utilisateur) {
                    printf("Utilisateur créé avec succès! ID: %d\n", nouvel_utilisateur->identifiant);
                }
                break;
            }
            
            case 2: { 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(buffer, sizeof(buffer));
                
                Utilisateur* utilisateur = NULL;
                if (strspn(buffer, "0123456789") == strlen(buffer)) {
                    int id = atoi(buffer);
                    utilisateur = trouver_utilisateur_par_id(reseau, id);
                } else {
                    utilisateur = trouver_utilisateur_par_pseudo(reseau, buffer);
                }
                
                if (utilisateur == NULL) {
                    printf("Utilisateur non trouvé.\n");
                    break;
                }
                
                printf("Entrez l'ID ou le pseudo de l'ami à ajouter: ");
                lire_chaine(buffer, sizeof(buffer));
                
                Utilisateur* ami = NULL;
                if (strspn(buffer, "0123456789") == strlen(buffer)) {
                    int id = atoi(buffer);
                    ami = trouver_utilisateur_par_id(reseau, id);
                } else {
                    ami = trouver_utilisateur_par_pseudo(reseau, buffer);
                }
                
                if (ami == NULL) {
                    printf("Ami non trouvé.\n");
                    break;
                }
                
                ajouter_ami(utilisateur, ami);
                break;
            }
            
            case 3: { 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(buffer, sizeof(buffer));
                
                Utilisateur* utilisateur = NULL;
                if (strspn(buffer, "0123456789") == strlen(buffer)) {
                    int id = atoi(buffer);
                    utilisateur = trouver_utilisateur_par_id(reseau, id);
                } else {
                    utilisateur = trouver_utilisateur_par_pseudo(reseau, buffer);
                }
                
                if (utilisateur == NULL) {
                    printf("Utilisateur non trouvé.\n");
                    break;
                }
                
                printf("Entrez le message à publier: ");
                lire_chaine(buffer, sizeof(buffer));
                
                publier_message(utilisateur, buffer);
                break;
            }
            
            case 4: 
                afficher_utilisateurs(reseau);
                break;
                
            case 5: { 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(buffer, sizeof(buffer));
                
                Utilisateur* utilisateur = NULL;
                if (strspn(buffer, "0123456789") == strlen(buffer)) {
                    int id = atoi(buffer);
                    utilisateur = trouver_utilisateur_par_id(reseau, id);
                } else {
                    utilisateur = trouver_utilisateur_par_pseudo(reseau, buffer);
                }
                
                if (utilisateur == NULL) {
                    printf("Utilisateur non trouvé.\n");
                    break;
                }
                
                afficher_amis(utilisateur);
                break;
            }
            
            case 6: { 
                printf("Entrez l'ID ou le pseudo de l'utilisateur: ");
                lire_chaine(buffer, sizeof(buffer));
                
                Utilisateur* utilisateur = NULL;
                if (strspn(buffer, "0123456789") == strlen(buffer)) {
                    int id = atoi(buffer);
                    utilisateur = trouver_utilisateur_par_id(reseau, id);
                } else {
                    utilisateur = trouver_utilisateur_par_pseudo(reseau, buffer);
                }
                
                if (utilisateur == NULL) {
                    printf("Utilisateur non trouvé.\n");
                    break;
                }
                
                afficher_publications(utilisateur);
                break;
            }

            case 0:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix non valide. Veuillez réessayer.\n");
                break;
        }
    }
    
    liberer_reseau(reseau);
    
    return 0;
}