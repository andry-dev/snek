#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H

#include "Types.h"
#include "Entities.h"

typedef struct
{
    char* framebuffer;
    int capacity;
    Vec2i screenCoords;
} Screen;

Screen initScreen(Vec2i screenCoords);
void deinitScreen(Screen* screen);
void draw(Screen* screen, Snake* snake, Foods* foods, EntityArray* entities);
void clearScreen(Screen* screen);

#endif
