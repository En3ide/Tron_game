#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../model/model.h"

void GameOver(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255); // Noir
    SDL_RenderClear(game->renderer);                      // Efface le renderer

    // Créer une surface contenant le texte "Jeu en Pause"
    SDL_Surface *textSurface = TTF_RenderText_Solid(game->font, "Game Over", RED);
    if (!textSurface)
    {
        printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
        return EXIT_FAILURE;
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

// Fonction de rendu de la grille
void render_grid(SDL_Renderer *renderer, int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE])
{
    for (int y = 0; y < WINDOW_HEIGHT / GRID_SIZE; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH / GRID_SIZE; x++)
        {
            if (grid[y][x] != 0) // Afficher seulement les cases occupées
            {
                SDL_Rect cell = {x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
                SDL_RenderFillRect(renderer, &cell);
            }
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

// Fonction de rendu des joueurs
void render_players(SDL_Renderer *renderer, Player *player1, Player *player2)
{
    // joueur 1 rouge
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
    SDL_Rect p1 = {player1->x * GRID_SIZE, player1->y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(renderer, &p1);

    // joueur 2 bleu
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Bleu
    SDL_Rect p2 = {player2->x * GRID_SIZE, player2->y * GRID_SIZE, GRID_SIZE, GRID_SIZE};
    SDL_RenderFillRect(renderer, &p2);
}

// Fonction principale du jeu
int Vue_SDL_tron()
{
    SDL_Color WHITE = WHITE;
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
    SDL_Window *window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1; // Quitte si la fenêtre n'est pas créée
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1; // Quitte si le renderer n'est pas créé
    }

    // Charger une police
    TTF_Font *font = TTF_OpenFont("./src/VueSDL/Enterpriser.ttf", 24); // Remplace par le chemin de ta police
    if (!font)
    {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer une surface contenant le texte
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Hello, SDL!", WHITE);
    if (!textSurface)
    {
        printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    wait(1000);
    // Grille et joueurs
    int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE] = {0};
    Player player1, player2;
    init_player(&player1, 10, 10, 1, 0);  // Initialisation de player1
    init_player(&player2, 30, 15, -1, 0); // Initialisation de player2

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
                    player1.dx = 0;
                    player1.dy = -1;
                    break;
                case SDLK_DOWN:
                    player1.dx = 0;
                    player1.dy = 1;
                    break;
                case SDLK_LEFT:
                    player1.dx = -1;
                    player1.dy = 0;
                    break;
                case SDLK_RIGHT:
                    player1.dx = 1;
                    player1.dy = 0;
                    break;
                case SDLK_w:
                    player2.dx = 0;
                    player2.dy = -1;
                    break;
                case SDLK_s:
                    player2.dx = 0;
                    player2.dy = 1;
                    break;
                case SDLK_a:
                    player2.dx = -1;
                    player2.dy = 0;
                    break;
                case SDLK_d:
                    player2.dx = 1;
                    player2.dy = 0;
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
            move_player(&player1);
            move_player(&player2);

            // vérifie si il y a un face à face
            if (check_collision(&player1, grid) && check_collision(&player2, grid))
            {
                printf("Bien jouer pour le face à face !!!!");
                running = false;
                press_wait();
            }
            else
            {

                // Vérifie si le joueur 1 a perdu
                if (check_collision(&player1, grid))
                {
                    printf("Joueur 1 perdu !!!!\n");
                    running = false;
                }

                // Vérification si le joueur 2 a perdu
                if (check_collision(&player2, grid))
                {
                    printf("Joueur 2 perdu !!!!\n");
                    running = false;
                }
            }
            // Mise à jour de la grille avec les positions des joueurs
            grid[player1.y][player1.x] = 1;
            grid[player2.y][player2.x] = 2;

            // Effacement de l'écran
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
            SDL_RenderClear(renderer);

            // Rendu de la grille et des joueurs
            render_grid(renderer, grid);
            render_players(renderer, &player1, &player2);

            SDL_RenderPresent(renderer);
            SDL_Delay(100); // Attente pour ralentir le jeu
        }
        else
        {
            // Si le jeu est en pause, on peut afficher un message de pause
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
            SDL_RenderClear(renderer);                      // Efface le renderer

            // Créer une surface contenant le texte "Jeu en Pause"
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Jeu en Pause", WHITE);
            if (!textSurface)
            {
                printf("Erreur de création de la surface du texte : %s\n", TTF_GetError());
                running = false;
            }

            // Créer une texture à partir de la surface du texte
            SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface); // Libérer la surface après avoir créé la texture

            // Définir la position du texte (au centre de l'écran)
            SDL_Rect textRect = {300, 300, textSurface->w, textSurface->h};

            // Afficher la texture à l'écran
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            // SDL_DestroyTexture(textTexture); // Libérer la texture après l'affichage

            SDL_RenderPresent(renderer);
        }
    }

    // Libération des ressources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
