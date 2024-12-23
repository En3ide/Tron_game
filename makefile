# Variables
CC = gcc
CFLAGS = -I/usr/include/SDL2 -I./src -I/usr/include/SDL2/SDL_ttf  # Ajoute le chemin des headers de SDL_ttf
LDFLAGS_SDL = -L/usr/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  # Ajoute -lSDL2_ttf pour lier SDL_ttf
LDFLAGS_NCURSE = -lncurses
TARGET_SDL = tron_sdl
TARGET_NCURSE = tron_ncurse

# Sources
SRC_COMMON = ./src/model/model.c
SRC_SDL = ./src/main.c $(SRC_COMMON) ./src/VueSDL/VueSDL.c

# Compilation de toutes les cibles
all: $(TARGET_SDL)

# Compilation SDL
$(TARGET_SDL): $(SRC_SDL)
	$(CC) -o $(TARGET_SDL) $(SRC_SDL) $(CFLAGS) $(LDFLAGS_SDL)

# Compilation ncurses (désactivée pour l'instant)
#$(TARGET_NCURSE): $(SRC_NCURSE)
#	$(CC) -o $(TARGET_NCURSE) $(SRC_NCURSE) $(CFLAGS) $(LDFLAGS_NCURSE)

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGET_SDL)
