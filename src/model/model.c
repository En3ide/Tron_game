#include "model.h"
#include <stdlib.h>
#include <stdbool.h>

void init_player(Player *p, int x, int y, int dx, int dy) {
    p->x = x;
    p->y = y;
    p->ldx = dx;
    p->ldy = dy;
    p->dx = dx;
    p->dy = dy;
}

void move_player(Player *p) {
    p->x += p->dx;
    p->y += p->dy;
}

bool check_collision(Player *p, int grid[WINDOW_HEIGHT / GRID_SIZE][WINDOW_WIDTH / GRID_SIZE]) {
    if (p->x < 0 || p->y < 0 || p->x >= WINDOW_WIDTH / GRID_SIZE || p->y >= WINDOW_HEIGHT / GRID_SIZE) {
        return true;
    }
    if (grid[p->y][p->x] != 0) {
        return true;
    }
    return false;
}
