#ifndef ELEMENTS_H
#define ELEMENTS_H

#define MAX_MISSILES 10
#define MAX_ENNEMIS 20

#include <SDL2/SDL.h>
#include "player.h"


// ----------------------------- MISSILES -----------------------------
typedef struct {
    SDL_Rect rect;
    int vitesse;
    int actif;
} Missile;

void init_missile(Joueur *joueur, Missile *missile);
void lancer_missile(const Uint8* keystates, Joueur *joueur, Missile *missiles);
void missile_render(Joueur *joueur, SDL_Renderer *renderer, Missile *missile);


// ----------------------------- ENNEMIS ------------------------------
typedef struct {
    SDL_Rect rect;
    int vitesse;
    int code;   // 1 = actif, 0 = détruit/inactif
} Ennemi;

void init_ennemi(SDL_Renderer *renderer, Ennemi *ennemi);
void init_ennemis(SDL_Renderer *renderer, Ennemi ennemis[], int nb_ennemis, int frequence);
void ennemis_moove(Ennemi ennemis[], int nb_ennemis);
void ennemis_render(SDL_Renderer *renderer, Ennemi ennemis[], int nb_ennemis);


// ---------------------------- COLLISIONS ----------------------------
void handle_missile_ennemi_collisions(Missile missiles[], Ennemi ennemis[], int *score);
void handle_joueur_ennemi_collisions(Joueur *joueur, Ennemi ennemis[], int *vies);

#endif