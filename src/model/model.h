#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>

// definie les taille de l'interface et de la fenetre
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRID_SIZE 20
/**
 * Structure représentant un joueur.
 */
typedef struct
{
    int x, y;     // Position actuelle du joueur dans la grille
    int ldx, ldy; // Dernière direction prise
    int dx, dy;   // Direction actuelle
} Player;

/**
 * Initialise un joueur avec une position et une direction données.
 * @param p Pointeur vers la structure du joueur
 * @param x Position initiale en x
 * @param y Position initiale en y
 * @param dx Direction initiale en x (-1, 0 ou 1)
 * @param dy Direction initiale en y (-1, 0 ou 1)
 */
void init_player(Player *p, int x, int y, int dx, int dy);

/**
 * Déplace le joueur selon sa direction actuelle.
 * @param p Pointeur vers la structure du joueur
 */
void move_player(Player *p);

/**
 * Vérifie si le joueur est en collision avec un obstacle ou sort des limites.
 * @param p Pointeur vers la structure du joueur
 * @param grid Grille de jeu contenant les obstacles
 * @return true si une collision est détectée, false sinon
 */
bool check_collision(Player *p, int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE]);

#endif // MODEL_H
