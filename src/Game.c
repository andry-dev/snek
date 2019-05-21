#include "Game.h"

#include <stdlib.h>

Game initGame(Vec2i screenCoords)
{
    Game game;

    game.screenCoords = screenCoords;
    game.entities.capacity = 20;
    game.entities.arr = malloc(sizeof(Entity) * game.entities.capacity);

    game.snake.length = 8;

    Entity* snakehead = game.entities.arr;
    snakehead->position.x = screenCoords.x / 2;
    snakehead->position.y = screenCoords.y / 2;
    snakehead->direction.x = 0;
    snakehead->direction.y = -1;

    for (int i = 1; i < game.snake.length; ++i)
    {
        Entity* ent = &game.entities.arr[i];
        ent->position.x = snakehead->position.x;
        ent->position.y = snakehead->position.y - i;
        ent->direction.x = 0;
        ent->direction.y = -1;
    }

    return game;
}

int checkWallColisions(EntityArray* entities, Vec2i* maxScreenCoords)
{
    Entity* snakehead = &entities->arr[0];

    int leftcheck = snakehead->position.x <= 0;
    int rightcheck = snakehead->position.x >= maxScreenCoords->x;
    int topcheck = snakehead->position.y <= 0;
    int bottomcheck = snakehead->position.y >= maxScreenCoords->y;

    return leftcheck || rightcheck || topcheck || bottomcheck;
}

void deinitGame(Game* game)
{
    free(game->entities.arr);
}

void moveSnake(EntityArray* entities, Snake* snake, Vec2i direction)
{
    for (int i = snake->length - 1; i > 0; --i)
    {
        Entity* newent = &entities->arr[i];
        Entity* oldent = &entities->arr[i - 1];

        *newent = *oldent;
    }

    Entity* head = &entities->arr[0];

    head->direction = direction;
    head->position.x += direction.x;
    head->position.y += direction.y;
}
