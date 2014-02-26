#ifndef GAME_H
#define GAME_H

#include "wall.h"
#include "landscape.h"
#include "heli.h"
#include "backend.h"

typedef struct Game Game;

Game* game_init();
void game_run(Game *game);

#endif // GAME_H

