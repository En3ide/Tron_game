#ifndef VUESDL_H
#define VUESDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../model/model.h"

// Couleurs primaires
#define WHITE (SDL_Color){255, 255, 255, 255};
#define BLACK (SDL_Color){0, 0, 0, 255};
#define RED (SDL_Color){255, 0, 0, 255};
#define GREEN (SDL_Color){0, 255, 0, 255};
#define BLUE (SDL_Color){0, 0, 255, 255};
#define YELLOW (SDL_Color){255, 255, 0, 255};

// Couleurs claires
#define LIGHT_RED (SDL_Color){255, 128, 128, 255};
#define LIGHT_GREEN (SDL_Color){128, 255, 128, 255};
#define LIGHT_BLUE (SDL_Color){128, 128, 255, 255};
#define LIGHT_YELLOW (SDL_Color){255, 255, 128, 255};
#define LIGHT_WHITE (SDL_Color){240, 240, 240, 255};
#define LIGHT_BLACK (SDL_Color){64, 64, 64, 255};

// Couleurs foncées
#define DARK_RED (SDL_Color){128, 0, 0, 255};
#define DARK_GREEN (SDL_Color){0, 128, 0, 255};
#define DARK_BLUE (SDL_Color){0, 0, 128, 255};
#define DARK_YELLOW (SDL_Color){128, 128, 0, 255};
#define DARK_WHITE (SDL_Color){192, 192, 192, 255};
#define DARK_BLACK (SDL_Color){32, 32, 32, 255};

typedef struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Surface *textSurface;
    SDL_Color Color_Menu;
    SDL_Color Color_Game_Over;
} Game;

/**
 * @brief Fait le rendu de la grille
 *
 * @param renderer Pointeur vers le rendu
 * @param grid Pointeur vers la Grille de jeu
 */
void render_grid(SDL_Renderer *renderer, int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE]);

/**
 * @brief Genere le rendu des joueurs
 *
 * @param renderer Pointeur vers le rendu
 * @param player1  Pointeur sur la structur du joueur 1
 * @param player2  Pointeur sur la structur du joueur 1
 */
void render_players(SDL_Renderer *renderer, Player *player1, Player *player2);

/**
 * @brief Boucle principale de la version SDL du jeu Tron
 *
 * @return int
 */
int Vue_SDL_tron();
#endif