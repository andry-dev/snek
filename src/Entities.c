#include "Entities.h"

#include <stdlib.h>
#include "Utils.h"
#include "Symbols.h"

enum
{
    DEFAULT_RESIZE_HINT = 1
};

static void reallocSnake(Snake* snake, int hint)
{
    if (hint <= DEFAULT_RESIZE_HINT)
    {
        hint = 2;
    }

    snake->body = realloc(snake->body, sizeof(Entity) * snake->capacity * hint);
    snake->capacity = snake->capacity * hint;
}

static void reallocFood(Foods* foods, int hint)
{
    if (hint <= DEFAULT_RESIZE_HINT)
    {
        hint = 2;
    }

    foods->array = realloc(foods->array, sizeof(Entity) * foods->capacity * hint);
    foods->capacity = foods->capacity * hint;
}

void addSnakePart(Snake* snake)
{
    if (snake->length >= snake->capacity)
    {
        reallocSnake(snake, DEFAULT_RESIZE_HINT);
    }

    ++snake->length;
    copySnakeParts(snake);
}

void addFood(Foods* foods, Vec2i screenCoords)
{
    if (foods->length >= foods->capacity)
    {
        reallocFood(foods, DEFAULT_RESIZE_HINT);
    }

    ++foods->length;

    Entity* last = &foods->array[foods->length - 1];
    last->position = generateRandomPosition(screenCoords);
    last->symbol = symFruit;
}

void removeFood(Foods* foods, Entity* toRemove)
{
    if (foods->length == 0)
    {
        return;
    }

    Entity* last = &foods->array[foods->length - 1];

    Entity tmp = *toRemove;
    *toRemove = *last;
    *last = tmp;

    --foods->length;
}
