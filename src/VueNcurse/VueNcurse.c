#include "../model/model.h"
#include "VueNcurse.h"
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h> // Pour usleep

void render_grid_N(int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE])
{
    for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++)
        {
            mvaddch(y, x, grid[y][x]);
        }
    }
}

int Ncurse_tron()
{
    // Initialisation de ncurses
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100); // Temps d'attente pour getch() en millisecondes

    // Grille de jeu
    int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE];
    for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++)
        {
            grid[y][x] = 0;
        }
    }

    // Initialisation des joueurs
    Player player1, player2;
    init_player(&player1, 5, 5, 1, 0);
    init_player(&player2, 30, 15, -1, 0);

    // Boucle principale
    bool running = true;
    while (running)
    {
        // Gestion des entrées clavier
        int ch = getch();
        switch (ch)
        {
        // Joueur 1
        case KEY_UP:
        {
            player1.dx = 0;
            player1.dy = -1;
            break;
        }
        case KEY_DOWN:
        {
            player1.dx = 0;
            player1.dy = 1;
            break;
        }
        case KEY_LEFT:
        {
            player1.dx = -1;
            player1.dy = 0;
            break;
        }
        case KEY_RIGHT:
        {
            player1.dx = 1;
            player1.dy = 0;
            break;
        }
        // Joueur 2
        case 'w':
        {
            player2.dx = 0;
            player2.dy = -1;
            break;
        }
        case 's':
        {
            player2.dx = 0;
            player2.dy = 1;
            break;
        }
        case 'a':
        {
            player2.dx = -1;
            player2.dy = 0;
            break;
        }
        case 'd':
        {
            player2.dx = 1;
            player2.dy = 0;
            break;
        }
        }

        // Déplacement des joueurs
        move_player(&player1);
        move_player(&player2);

        // Vérification des collisions
        if (check_collision(&player1, grid) || check_collision(&player2, grid))
        {
            mvprintw(WINDOW_HEIGHT / (2 * GRID_SIZE), WINDOW_WIDTH / (2 * GRID_SIZE) - 5, "Game Over");
            running = false;
            break;
        }

        // Mise à jour de la grille
        grid[player1.y][player1.x] = 1;
        grid[player2.y][player2.x] = 2;

        // Affichage
        clear();
        render_grid_N(grid);
        refresh();

        usleep(100000); // Pause de 100 ms
    }

    // Fin de ncurses
    getch();
    endwin();
    return 0;
}
