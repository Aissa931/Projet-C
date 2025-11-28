#include "elements.h"
#include <stdlib.h>
#define FIRE_COOLDOWN 200

// ----------------------------- MISSILES -----------------------------
Missile missiles[MAX_MISSILES];

void init_missile(Joueur *joueur, Missile *missile) {
    missile->rect.h = 10;
    missile->rect.w = 5;
    missile->rect.x = (joueur->rect.x + joueur->rect.w / 2) - missile->rect.w / 2;
    missile->rect.y = joueur->rect.y;
    missile->vitesse = 10;
    missile->actif = 1;
}

void lancer_missile(const Uint8* keystates, Joueur *joueur, Missile missiles[]) {
    static int is_firing = 0;
    static Uint32 dernier_tir = 0;
    Uint32 temps_actuel = SDL_GetTicks();
    if (keystates[SDL_SCANCODE_SPACE]) {
        if (!is_firing && temps_actuel - dernier_tir > FIRE_COOLDOWN) {
            for (int j = 0; j < MAX_MISSILES; j++) {
                if (missiles[j].actif == 0) {
                    init_missile(joueur, &missiles[j]);
                    dernier_tir = temps_actuel;
                    break;
                }
            }
            is_firing = 1;
        } else {
            is_firing = 0;
        }
    }
    for (int k = 0; k < MAX_MISSILES; k++) {
        if (missiles[k].actif == 1) {
            missiles[k].rect.y -= missiles[k].vitesse;
            if (missiles[k].rect.y + missiles[k].rect.h < 0) {
                missiles[k].actif = 0;
            }
        }
    }
}

void missile_render(Joueur *joueur, SDL_Renderer *renderer, Missile missiles[]) {
    SDL_SetRenderDrawColor(renderer, 255, 155, 155, 255);
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].actif == 1) {
            SDL_RenderFillRect(renderer, &missiles[i].rect);
        }
    }
}


// ----------------------------- ENNEMIS ------------------------------

Ennemi ennemis[MAX_ENNEMIS];

void init_ennemis(SDL_Renderer *renderer, Ennemi ennemis[], int nb_ennemis, int frequence) {
    for (int i = 0; i < nb_ennemis; i++) {
        init_ennemi(renderer, &ennemis[i]);
        ennemis[i].code = 1;
    }
}

void init_ennemi(SDL_Renderer *renderer, Ennemi *ennemi) {
    ennemi->rect.h = 20;
    ennemi->rect.w = 20;
    ennemi->rect.x = rand() % (800 - ennemi->rect.w);
    ennemi->rect.y = 0;
    ennemi->vitesse = 5;
    ennemi->code = 1;
}

void ennemis_moove(Ennemi ennemis[], int nb_ennemis) {
    for (int i = 0; i < nb_ennemis; i++) {
        ennemis[i].rect.y += ennemis[i].vitesse;
    }
}

void ennemis_render(SDL_Renderer *renderer, Ennemi ennemis[], int nb_ennemis) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for (int i = 0; i < nb_ennemis; i++) {
        SDL_RenderFillRect(renderer, &ennemis[i].rect);
    }
}


// ---------------------------- COLLISIONS ----------------------------

static int rects_intersect(const SDL_Rect *a, const SDL_Rect *b) {
    return (a->x < b->x + b->w &&
            a->x + a->w > b->x &&
            a->y < b->y + b->h &&
            a->y + a->h > b->y);
}

// Missile touche ennemi -> missile désactivé, ennemi "détruit", score++
void handle_missile_ennemi_collisions(Missile missiles[], Ennemi ennemis[], int *score) {
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (missiles[i].actif == 0) continue;

        for (int j = 0; j < MAX_ENNEMIS; j++) {
            if (ennemis[j].code != 1) continue;

            if (rects_intersect(&missiles[i].rect, &ennemis[j].rect)) {
                missiles[i].actif = 0;
                ennemis[j].code = 0;
                if (score != NULL) {
                    (*score)++;
                }
                break; // ce missile est détruit, on arrête les checks pour lui
            }
        }
    }
}

// Ennemi touche joueur -> ennemi "détruit", vies--
void handle_joueur_ennemi_collisions(Joueur *joueur, Ennemi ennemis[], int *vies) {
    if (joueur == NULL || vies == NULL || *vies <= 0) return;

    for (int j = 0; j < MAX_ENNEMIS; j++) {
        if (ennemis[j].code != 1) continue;

        if (rects_intersect(&joueur->rect, &ennemis[j].rect)) {
            ennemis[j].code = 0;
            (*vies)--;
            // plus tard : invincibilité temporaire, knockback, etc.
        }
    }
}