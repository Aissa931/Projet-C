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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        player_handle_input(&joueur, keystates);
        player_in_window(&joueur);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        player_render(&joueur, renderer);
        
        lancer_missile(keystates, &joueur, missiles);
        missile_render(&joueur, renderer, missiles);

        SDL_RenderPresent(renderer);
        
        SDL_Delay(16); // petite pause ~60 FPS
    }

    // 4. Nettoyer avant de quitter
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
