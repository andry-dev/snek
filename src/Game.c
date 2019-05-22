#include "Game.h"

#include <stdlib.h>

static char assignHeadSymbol(Vec2i direction)
{
    char ret = ' ';

    if (direction.x == 1)
    {
        ret = '>';
    }
    else if (direction.x == -1)
    {
        ret = '<';
    }
    else if (direction.y == -1)
    {
        ret = '^';
    }
    else if (direction.y == 1)
    {
        ret = 'v';
    }

    return ret;
}

static char assignBodySymbol(Vec2i direction)
{
    char ret = ' ';

    if (direction.x == -1 ||
        direction.x == 1)
    {
        ret = '-';
    }
    else if (direction.y == -1 ||
             direction.y == 1)
    {
        ret = '|';
    }

    return ret;
}

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

    const int leftcheck = snakehead->position.x <= 0;
    const int rightcheck = snakehead->position.x >= maxScreenCoords->x;
    const int topcheck = snakehead->position.y <= 0;
    const int bottomcheck = snakehead->position.y >= maxScreenCoords->y;

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

        newent->symbol = assignBodySymbol(newent->direction);
    }

    Entity* head = &entities->arr[0];

    head->direction = direction;
    head->position.x += direction.x;
    head->position.y += direction.y;

    head->symbol = assignHeadSymbol(direction);
}
