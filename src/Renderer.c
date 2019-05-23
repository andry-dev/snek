#include "Renderer.h"

#include <stdlib.h>
#include <stdio.h>

#include "Symbols.h"

Screen initScreen(Vec2i screenCoords, TerminalContext* term)
{
    Screen scr;

    scr.screenCoords = screenCoords;
    scr.screenCoords.x += 2; // Accounting for \n
    scr.capacity = scr.screenCoords.x * scr.screenCoords.y;
    scr.framebuffer = malloc(sizeof(char) * scr.capacity);
    scr.term = term;

    return scr;
}

void deinitScreen(Screen* screen)
{
    if (screen->framebuffer)
    {
        free(screen->framebuffer);
    }
}

void clearScreen(Screen* screen)
{
    // hack
    //system("clear");
    //

    clearTerm(screen->term);
    for (int i = 0; i < screen->capacity; ++i)
    {
        screen->framebuffer[i] = symBackground;
    }
}

void draw(Screen* screen, Snake* snake, Foods* foods, EntityArray* entities)
{
    // Left and right walls
    for (int y = 0; y < (screen->screenCoords.y); ++y)
    {
        const int x = screen->screenCoords.x - 2;
        const int leftwall = y * screen->screenCoords.x + 0;
        const int rightwall = y * screen->screenCoords.x + x;

        screen->framebuffer[leftwall] = symVertWall;
        screen->framebuffer[rightwall] = symVertWall;
    }

    // Top and bottom walls
    for (int x = 0; x < (screen->screenCoords.x - 1); ++x)
    {
        const int y = screen->screenCoords.y - 1;
        const int topwall = 0 * screen->screenCoords.x + x;
        const int bottomwall = y * screen->screenCoords.x + x;

        screen->framebuffer[bottomwall] = symHorizWall;
        screen->framebuffer[topwall] = symHorizWall;
    }

    // Render snake on the screen
    for (int i = 0; i < snake->length; ++i)
    {
        Entity* snake = &entities->arr[i];
        Vec2i* snakepos = &snake->position;
        const int ypos = snakepos->y;
        const int coords = ypos * screen->screenCoords.x + snakepos->x;

        if (snakepos->x <= 0 ||
            snakepos->x >= (screen->screenCoords.x - 2) ||
            snakepos->y <= 0 ||
            snakepos->y >= (screen->screenCoords.y))
        {
            continue;
        }

        screen->framebuffer[coords] = snake->symbol;
    }

    for (int i = 0; i < screen->screenCoords.y; ++i)
    {
        const int coords = i * screen->screenCoords.x + (screen->screenCoords.x - 1);
        screen->framebuffer[coords] = '\n';
    }

    printf("%.*s", screen->capacity, screen->framebuffer);
}
