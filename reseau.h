#ifndef RESEAU_H
#define RESEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    int id;
    char nom[100];
    char amis[100][100];
    int nb_amis;
    char posts[100][100];
    int nb_posts;
} Utilisateur;

typedef struct {
    Utilisateur utilisateurs[100];
    int nb_utilisateurs;
} ReseauSocial;

int ajouterUtilisateur(ReseauSocial *reseau, char *nom);
Utilisateur* trouverUtilisateur(ReseauSocial *reseau, char *nom);
void ajouterAmi(Utilisateur *utilisateur, char *ami);
void publierMessage(Utilisateur *utilisateur, char *message);
void afficherUtilisateurs(ReseauSocial *reseau);
void afficherAmis(Utilisateur *utilisateur);
void afficherPublications(Utilisateur *utilisateur);

#endif