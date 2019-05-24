#include "Entities.h"

#include <stdlib.h>
#include "Utils.h"

enum
{
    DEFAULT_RESIZE_HINT = -1
};

static void reallocSnake(Snake* snake, int size, int hint)
{
    if (hint <= DEFAULT_RESIZE_HINT)
    {
        hint = 2;
    }

    snake->body = realloc(snake->body, (snake->capacity + size) * hint);
    snake->capacity = (snake->capacity + size) * hint;
}

static void reallocFood(Foods* foods, int size, int hint)
{
    if (hint <= DEFAULT_RESIZE_HINT)
    {
        hint = 2;
    }

    foods->array = realloc(foods->array, (foods->capacity + size) * hint);
    foods->capacity = (foods->capacity + size) * hint;
}

void addSnakePart(Snake* snake)
{
    if (snake->length >= snake->capacity)
    {
        reallocSnake(snake, 1, DEFAULT_RESIZE_HINT);
    }

    ++snake->length;
    copySnakeParts(snake);
}

void addFood(Foods* foods)
{
    if (foods->length >= foods->capacity)
    {
        
    }

    ++foods->length;
}

void removeFood(Foods* foods, Entity* toRemove)
{

}
