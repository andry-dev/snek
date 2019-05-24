#ifndef SNAKE_UTILS_H
#define SNAKE_UTILS_H

#include "Entities.h"

char assignHeadSymbol(Vec2i direction);

char assignBodySymbol(Vec2i direction);

void copySnakeParts(Snake* snake);

Vec2i generateRandomPosition(Vec2i screenCoords);

#endif
