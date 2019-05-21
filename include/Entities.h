#ifndef SNAKE_ENTITIES_H
#define SNAKE_ENTITIES_H

#include "Types.h"

typedef int EntityId;

typedef struct
{
    Vec2i position;
    Vec2i direction;
} Entity;

typedef struct
{
    int length;
} Snake;

typedef struct
{
    Entity* arr;
    int capacity;
} EntityArray;

typedef struct
{
    int quantity;
} Foods;

EntityArray initEntities(int num, Snake* snake, Foods* foods);
void addSnakePart(EntityArray* entities, Snake* snake, Entity* newEntity);
void addFood(EntityArray* entities, Foods* foods, Entity* newEntity);
void removeFood(EntityArray* entities, Foods* foods, Entity* toRemove);

#endif
