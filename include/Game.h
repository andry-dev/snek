#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Entities.h"


typedef struct
{
    Snake snake;
    Foods foods;

    Vec2i screenCoords;
} Game;

Game initGame(Vec2i screenCoords);
Entity* checkCollisions(Snake* snake, Foods* foods);
int checkWallCollisions(Snake* snake, Vec2i* maxScreenCoords);
void moveSnake(Snake* snake, Vec2i direction);
void deinitGame(Game* game);

#endif
