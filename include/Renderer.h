#ifndef SNAKE_RENDERER_H
#define SNAKE_RENDERER_H

#include "Types.h"
#include "Entities.h"
#include "input/Common.h"


typedef struct
{
    char* framebuffer;
    int capacity;
    Vec2i screenCoords;
    TerminalContext* term;
} Screen;

Screen initScreen(Vec2i screenCoords, TerminalContext* term);
void deinitScreen(Screen* screen);
void draw(Screen* screen, Snake* snake, Foods* foods, EntityArray* entities);
void clearScreen(Screen* screen);

#endif
