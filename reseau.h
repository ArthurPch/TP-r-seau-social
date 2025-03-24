#ifndef RESEAU_H
#define RESEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Message {
    char* contenu;
    struct Message* suivant;
} Message;

typedef struct NoeudAmi {
    struct Utilisateur* utilisateur;
    struct NoeudAmi* suivant;
} NoeudAmi;

typedef struct Utilisateur {
    int identifiant;
    char* pseudo;
    Message* premiere_publication;
    Message* derniere_publication;
    NoeudAmi* premier_ami;
    struct Utilisateur* suivant;
    int nb_publications;
    int nb_amis;
} Utilisateur;

typedef struct {
    Utilisateur* premier_utilisateur;
    int nombre_utilisateurs;
} ReseauSocial;

ReseauSocial* initialiser_reseau();
Utilisateur* ajouter_utilisateur(ReseauSocial* reseau, const char* pseudo);
Utilisateur* trouver_utilisateur_par_id(ReseauSocial* reseau, int identifiant);
Utilisateur* trouver_utilisateur_par_pseudo(ReseauSocial* reseau, const char* pseudo);
void ajouter_ami(Utilisateur* utilisateur, Utilisateur* ami);
void publier_message(Utilisateur* utilisateur, const char* contenu);
void afficher_utilisateurs(ReseauSocial* reseau);
void afficher_amis(Utilisateur* utilisateur);
void afficher_publications(Utilisateur* utilisateur);
void liberer_reseau(ReseauSocial* reseau);
void afficher_menu();
void lire_chaine(char* buffer, int taille);
int lire_entier();

#endif