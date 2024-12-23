#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../model/model.h"
#include "VueSDL.h"

void GameOver(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Noir
    SDL_RenderClear(game->renderer);                      // Efface le renderer

    // Créer une surface contenant le texte "Jeu en Pause"
    SDL_Surface *textSurface = TTF_RenderText_Solid(game->font, "Game Over", game->color_Game_Over);
    if (!textSurface)
    {
        printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Créer une texture à partir de la surface du texte
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    SDL_FreeSurface(textSurface); // Libérer la surface après avoir créé la texture

    // Définir la position du texte (au centre de l'écran)
    SDL_Rect textRect = {WINDOW_WIDTH / 2 - textSurface->w / 2, WINDOW_HEIGHT / 2 - textSurface->h / 2, textSurface->w, textSurface->h};

    // Afficher la texture à l'écran
    SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);
    // SDL_DestroyTexture(textTexture); // Libérer la texture après l'affichage

    SDL_RenderPresent(game->renderer);
    press_wait();
    SDL_DestroyTexture(textTexture); // Libérer la texture après l'affichage
}

// Fonction de rendu de la grille
void render_grid(Game *game)
{
    for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++)
        {
            if (game->grid[y * (WINDOW_WIDTH / GRID_SIZE) + x] != 0)
            {
                SDL_Rect cell = {x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
                switch (game->grid[y * (WINDOW_WIDTH / GRID_SIZE) + x])
                {
                case 1:
                    SDL_SetRenderDrawColor(game->renderer, 100, 0, 0, 255); // Rouge
                    SDL_RenderFillRect(game->renderer, &cell);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(game->renderer, 0, 0, 100, 255); // Blanc
                    SDL_RenderFillRect(game->renderer, &cell);
                    break;
                default:
                    break;
                }
            }
            /*if (game->grid[y * (WINDOW_WIDTH / GRID_SIZE) + x] != 0) // Afficher seulement les cases occupées
            {
                SDL_Rect cell = {x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255); // Blanc
                SDL_RenderFillRect(game->renderer, &cell);
            }*/
        }
    }
}

void press_wait()
{
    bool wait = true;
    SDL_Event event;
    while (wait)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                wait = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                default:
                    return;
                    break;
                }
            }
        }
    }
}

void Pause(Game *game)
{
    // Si le jeu est en pause, on peut afficher un message de pause
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Noir
    SDL_RenderClear(game->renderer);                      // Efface le renderer

    // Créer une surface contenant le texte "Jeu en Pause"
    SDL_Surface *textSurface = TTF_RenderText_Solid(game->font, "Jeu en Pause", game->color_Menu);
    if (!textSurface)
    {
        printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
    }

    // Créer une texture à partir de la surface du texte
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    SDL_FreeSurface(textSurface); // Libérer la surface après avoir créé la texture

    // Définir la position du texte (au centre de l'écran)
    SDL_Rect textRect = {300, 300, textSurface->w, textSurface->h};

    // Afficher la texture à l'écran
    SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);
    // SDL_DestroyTexture(textTexture); // Libérer la texture après l'affichage

    SDL_RenderPresent(game->renderer);
}

void Menu(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Noir
    SDL_RenderClear(game->renderer);                      // Efface le renderer

    // Créer une surface contenant le texte "Jeu en Pause"
    SDL_Surface *textSurface = TTF_RenderText_Solid(game->font, "Jouer", game->color_Game_Over);
    if (!textSurface)
    {
        printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    // Créer une texture à partir de la surface du texte
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    SDL_FreeSurface(textSurface); // Libérer la surface après avoir créé la texture

    // Définir la position du texte (au centre de l'écran)
    SDL_Rect textRect = {WINDOW_WIDTH / 2 - textSurface->w / 2, WINDOW_HEIGHT / 2 - textSurface->h / 2, textSurface->w, textSurface->h};

    // Afficher la texture à l'écran
    SDL_RenderCopy(game->renderer, textTexture, NULL, &textRect);
    // SDL_DestroyTexture(textTexture); // Libérer la texture après l'affichage

    SDL_RenderPresent(game->renderer);
    press_wait();
}

// Fonction de rendu des joueurs
void render_players(Game *game)
{
    // joueur 1 rouge
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255); // Rouge
    SDL_Rect p1 = {game->player1->x * GRID_SIZE, game->player1->y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(game->renderer, &p1);

    // joueur 2 bleu
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255); // Bleu
    SDL_Rect p2 = {game->player2->x * GRID_SIZE, game->player2->y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(game->renderer, &p2);
}

// Fonction principale du jeu
int Vue_SDL_tron()
{
    Game *game = (Game *)malloc(sizeof(Game));
    game->color_Game_Over = RED;
    game->color_Menu = WHITE;
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1; // Quitte si SDL échoue à s'initialiser
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("Erreur d'initialisation SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre et du renderer
    game->window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (game->window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1; // Quitte si la fenêtre n'est pas créée
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        TTF_Quit();
        SDL_Quit();
        return 1; // Quitte si le renderer n'est pas créé
    }

    // Charger une police
    game->font = TTF_OpenFont("./src/VueSDL/Enterpriser.ttf", 24); // Remplace par le chemin de ta police
    if (!game->font)
    {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(game->renderer);
        SDL_DestroyWindow(game->window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Menu(game);
    //  Grille et joueurs
    game->grid = malloc(WINDOW_HEIGHT / GRID_SIZE * WINDOW_WIDTH / GRID_SIZE * sizeof(int));
    game->player1 = new (Player);
    game->player2 = new (Player);
    init_player(game->player1, 10, 10, 1, 0);  // Initialisation de player1
    init_player(game->player2, 30, 15, -1, 0); // Initialisation de player2

    bool running = true;
    bool pause = false;
    SDL_Event event;

    // Boucle de jeu
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    game->player1->dx = 0;
                    game->player1->dy = -1;
                    break;
                case SDLK_DOWN:
                    game->player1->dx = 0;
                    game->player1->dy = 1;
                    break;
                case SDLK_LEFT:
                    game->player1->dx = -1;
                    game->player1->dy = 0;
                    break;
                case SDLK_RIGHT:
                    game->player1->dx = 1;
                    game->player1->dy = 0;
                    break;
                case SDLK_w:
                    game->player2->dx = 0;
                    game->player2->dy = -1;
                    break;
                case SDLK_s:
                    game->player2->dx = 0;
                    game->player2->dy = 1;
                    break;
                case SDLK_a:
                    game->player2->dx = -1;
                    game->player2->dy = 0;
                    break;
                case SDLK_d:
                    game->player2->dx = 1;
                    game->player2->dy = 0;
                    break;
                case SDLK_SPACE:
                    pause = !pause;
                    if (pause)
                    {
                        printf("Jeu en pause\n");
                    }
                    else
                    {
                        printf("Jeu repris\n");
                    }
                }
            }
        }
        if (!pause)
        {
            move_player(game->player1);
            move_player(game->player2);

            // vérifie si il y a un face à face
            if (check_collision(game->player1, game->grid) && check_collision(game->player2, game->grid))
            {
                printf("Bien jouer pour le face à face !!!!");
                running = false;
                GameOver(game);
            }
            else
            {

                // Vérifie si le joueur 1 a perdu
                if (check_collision(game->player1, game->grid))
                {
                    printf("Joueur 1 perdu !!!!\n");
                    running = false;
                    GameOver(game);
                }

                // Vérification si le joueur 2 a perdu
                if (check_collision(game->player2, game->grid))
                {
                    printf("Joueur 2 perdu !!!!\n");
                    running = false;
                    GameOver(game);
                }
            }
            // Mise à jour de la grille avec les positions des joueurs
            game->grid[game->player1->y * (WINDOW_WIDTH / GRID_SIZE) + game->player1->x] = 1;
            game->grid[game->player2->y * (WINDOW_WIDTH / GRID_SIZE) + game->player2->x] = 2;

            // Effacement de l'écran
            SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Noir
            SDL_RenderClear(game->renderer);

            // Rendu de la grille et des joueurs
            render_grid(game);
            render_players(game);

            SDL_RenderPresent(game->renderer);
            SDL_Delay(100); // Attente pour ralentir le jeu
        }
        else
        {
            Pause(game);
        }
    }

    // Libération des ressources
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    return 0;
}
