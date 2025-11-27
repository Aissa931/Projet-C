#ifndef ELEMENTS_H
#define ELEMENTS_H

#define MAX_MISSILES 10
#define MAX_ENNEMIS 20

#include <SDL2/SDL.h>
#include "player.h"

typedef struct {
    SDL_Rect rect;
    int vitesse;
    int actif;
} Missile;

void init_missile(Joueur *joueur, Missile *missile);
void lancer_missile(const Uint8* keystates, Joueur *joueur, Missile *missiles);
void missile_render(Joueur *joueur, SDL_Renderer *renderer, Missile *missile);

typedef struct {
    SDL_Rect rect;
    int vitesse;
    int code;
} Ennemi;

void init_ennemi(SDL_Renderer *renderer, Ennemi *ennemi);
void ennemis_moove(Ennemi ennemis[], int nb_ennemis);
void ennemis_render(SDL_Renderer *renderer, Ennemi ennemis[], int nb_ennemis);

#endif