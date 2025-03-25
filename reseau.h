#ifndef RESEAU_H
#define RESEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    int id;
    char nom[100];
    char amis[100];
    int nb_amis;
    char posts[100];
    int nb_posts;
} Utilisateur;

typedef struct {
    Utilisateur utilisateurs[100];
    int nb_utilisateurs;
} ReseauSocial;

int ajouter_utilisateur(ReseauSocial *reseau, char *nom);
Utilisateur* trouver_utilisateur(ReseauSocial *reseau, char *nom);
void ajouter_ami(Utilisateur *utilisateur, char *ami);
void publier_message(Utilisateur *utilisateur, char *message);
void afficher_utilisateurs(ReseauSocial *reseau);
void afficher_amis(Utilisateur *utilisateur);
void afficher_publications(Utilisateur *utilisateur);

#endif