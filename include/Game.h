#ifndef GAME_H
#define GAME_H

#include "Entities.h"

typedef struct
{
    EntityArray entities;
    Snake snake;
    Foods foods;

    Vec2i screenCoords;
} Game;

Game initGame(Vec2i screenCoords);
Entity* checkCollisions(EntityArray* entities, Snake* snake, Foods* foods);
int checkWallColisions(EntityArray* entities, Vec2i* maxScreenCoords);
void moveSnake(EntityArray* entities, Snake* snake, Vec2i direction);
void deinitGame(Game* game);

#endif
