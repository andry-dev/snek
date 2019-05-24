#include "Utils.h"

#include "Symbols.h"

char assignHeadSymbol(Vec2i direction)
{
    char ret = ' ';

    if (direction.x == 1)
    {
        ret = symSnakeHeadRight;
    }
    else if (direction.x == -1)
    {
        ret = symSnakeHeadLeft;
    }
    else if (direction.y == -1)
    {
        ret = symSnakeHeadUp;
    }
    else if (direction.y == 1)
    {
        ret = symSnakeHeadDown;
    }

    return ret;
}

char assignBodySymbol(Vec2i direction)
{
    char ret = ' ';

    if (direction.x == -1 ||
        direction.x == 1)
    {
        ret = symSnakeBodyHoriz;
    }
    else if (direction.y == -1 ||
             direction.y == 1)
    {
        ret = symSnakeBodyVert;
    }

    return ret;
}

void copySnakeParts(Snake* snake)
{
    for (int i = snake->length - 1; i > 0; --i)
    {
        Entity* newent = &snake->body[i];
        Entity* oldent = &snake->body[i - 1];

        *newent = *oldent;

        newent->symbol = assignBodySymbol(newent->direction);
    }
}
