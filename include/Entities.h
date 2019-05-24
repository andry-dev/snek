#ifndef SNAKE_ENTITIES_H
#define SNAKE_ENTITIES_H

#include "Types.h"

typedef int EntityId;

typedef struct
{
    Vec2i position;
    Vec2i direction;
    char symbol;
} Entity;

typedef struct
{
    Entity* body;
    int length;
    int capacity;
} Snake;

typedef struct
{
    Entity* array;
    int length;
    int capacity;
} Foods;

void addSnakePart(Snake* snake);
void addFood(Foods* foods);
void removeFood(Foods* foods, Entity* toRemove);

#endif
