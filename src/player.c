#include "player.h"

void player_init(Joueur* joueur) {
    // Dimensionne le joueur et le place au milieu
    joueur->rect.w  =  25;
    joueur->rect.h  =  25;
    joueur->rect.x  = 400;
    joueur->rect.y  = 450;
    joueur->vitesse =   5;
}

void player_handle_input(Joueur* joueur, const Uint8* keystates) {
    // Mettre à jour la position du joueur en fonction des touches appuyées
    if (keystates[SDL_SCANCODE_LEFT]) {
        joueur->rect.x -= joueur->vitesse;
    }
    if (keystates[SDL_SCANCODE_RIGHT]) {
        joueur->rect.x += joueur->vitesse;
    }
    if (keystates[SDL_SCANCODE_UP]) {
        joueur->rect.y -= joueur->vitesse;
    }
    if (keystates[SDL_SCANCODE_DOWN]) {
        joueur->rect.y += joueur->vitesse;
    }
}

void player_render(Joueur* joueur, SDL_Renderer* renderer) {
    // Dessine le joueur sur le renderer
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &joueur->rect);
}

//BDR
void player_in_window(Joueur* joueur) {
    if (joueur->rect.x >= 800 - joueur->rect.w) {joueur->rect.x = 800 - joueur->rect.w;}
    if (joueur->rect.x <= 0) {joueur->rect.x = 0;}
    if (joueur->rect.y >= 900 - joueur->rect.h) {joueur->rect.y = 900 - joueur->rect.h;}
    if (joueur->rect.y <= 0) {joueur->rect.y = 0;}
}