#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

// Structure qui représente le joueur
/*
typedef struct SDL_Rect {
    int x, y; // Position
    int w, h; // Dimension
}
*/

typedef struct {
    SDL_Rect rect;
    int vitesse;
} Joueur;

// Fonctions liées au joueur
void player_init(Joueur* joueur);
void player_handle_input(Joueur* joueur, const Uint8* keystates);
void player_render(Joueur* joueur, SDL_Renderer* renderer);
void player_in_window(Joueur* joueur);

#endif

