#include "Game.h"

#include <stdlib.h>
#include <time.h>

#include "Utils.h"
#include "Symbols.h"


Game initGame(Vec2i screenCoords)
{
    Game game;

    game.snake.length = 8;
    game.snake.capacity = 10;
    game.snake.body = malloc(sizeof(Entity) * game.snake.capacity);

    game.foods.length = 2;
    game.foods.capacity = 10;
    game.foods.array = malloc(sizeof(Entity) * game.foods.capacity);

    game.scoring = 0;
    game.screenCoords = screenCoords;

    Entity* snakehead = game.snake.body;
    snakehead->position.x = screenCoords.x / 2;
    snakehead->position.y = screenCoords.y / 2;
    snakehead->direction.x = 0;
    snakehead->direction.y = -1;

    for (int i = 1; i < game.snake.length; ++i)
    {
        Entity* ent = &game.snake.body[i];
        ent->position.x = snakehead->position.x;
        ent->position.y = snakehead->position.y + i;
        ent->direction.x = 0;
        ent->direction.y = -1;
    }

    srand(time(0));

    for (int i = 0; i < game.foods.length; ++i)
    {
        Entity* ent = &game.foods.array[i];

        ent->symbol = symFruit;
        ent->position = generateRandomPosition(screenCoords);
    }

    return game;
}

Entity* checkCollisions(Snake* snake, Foods* foods)
{
    Vec2i* snakepos = &snake->body[0].position;

    for (int i = 0; i < foods->length; ++i)
    {
        Vec2i* foodpos = &foods->array[i].position;

        if ((snakepos->x == foodpos->x) &&
            (snakepos->y == foodpos->y))
        {
            return &foods->array[i];
        }
    }

    return 0;
}

int checkSelfCollisions(Snake* snake)
{
    Vec2i* headpos = &snake->body[0].position;

    for (int i = 1; i < snake->length; ++i)
    {
        Vec2i* partpos = &snake->body[i].position;

        if ((headpos->x == partpos->x) &&
            (headpos->y == partpos->y))
        {
            return 1;
        }
    }

    return 0;
}

int checkWallCollisions(Snake* snake, Vec2i* maxScreenCoords)
{
    Entity* snakehead = &snake->body[0];

    const int leftcheck = snakehead->position.x <= 0;
    const int rightcheck = snakehead->position.x >= maxScreenCoords->x;
    const int topcheck = snakehead->position.y <= 0;
    const int bottomcheck = snakehead->position.y >= (maxScreenCoords->y - 1);

    return leftcheck || rightcheck || topcheck || bottomcheck;
}

void deinitGame(Game* game)
{
    free(game->snake.body);
    free(game->foods.array);
}

void moveSnake(Snake* snake, Vec2i direction)
{
    copySnakeParts(snake);

    Entity* head = &snake->body[0];

    head->direction = direction;
    head->position.x += direction.x;
    head->position.y += direction.y;

    head->symbol = assignHeadSymbol(direction);
}
