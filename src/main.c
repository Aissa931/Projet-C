#include <SDL2/SDL.h>
#include <stdio.h>
#include "player.h"
#include "elements.h"

int main(int argc, char* argv[])
{
    // 1. Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return 1;
    }

    // 2. Créer une fenêtre
    SDL_Window* window = SDL_CreateWindow(
        "Mon premier jeu SDL",       // Titre
        SDL_WINDOWPOS_CENTERED,      // Position X
        SDL_WINDOWPOS_CENTERED,      // Position Y
        800, 900,                    // Largeur, Hauteur
        0                            // Options
    );

    if (window == NULL) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 3. Boucle principale (on attend que l'utilisateur ferme la fenêtre)
    int running = 1;
    SDL_Event event;

    Joueur joueur;
    player_init(&joueur);

    Missile missiles[MAX_MISSILES] = {};

    // Tableau de missiles
    Missile missiles[MAX_MISSILES] = {0};

    // Tableau d'ennemis
    Ennemi ennemis[MAX_ENNEMIS];
    int nb_ennemis = MAX_ENNEMIS;
    init_ennemis(renderer, ennemis, nb_ennemis, 0);

    // Score et points de vie du joueur
    int score = 0;
    int vies  = 3;

    while (running) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Mise à jour du joueur
    player_handle_input(&joueur, keystates);
    player_in_window(&joueur);

    // Mise à jour des missiles (tir + déplacement)
    lancer_missile(keystates, &joueur, missiles);

    // Mise à jour des ennemis (déplacement)
    ennemis_moove(ennemis, nb_ennemis);

    // Gestion des collisions
    handle_missile_ennemi_collisions(missiles, ennemis, &score);
    handle_joueur_ennemi_collisions(&joueur, ennemis, &vies);

    // Condition de fin de partie
    if (vies <= 0) {
        printf("Game Over ! Score final : %d\n", score);
        running = 0;
    }

    // Rendu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player_render(&joueur, renderer);
    missile_render(&joueur, renderer, missiles);
    ennemis_render(renderer, ennemis, nb_ennemis);

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}


    // 4. Nettoyer avant de quitter
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
