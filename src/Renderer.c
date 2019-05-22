#include "Renderer.h"

#include <stdlib.h>
#include <stdio.h>

Screen initScreen(Vec2i screenCoords)
{
    Screen scr;

    scr.screenCoords = screenCoords;
    scr.screenCoords.x += 2; // Accounting for \n
    scr.capacity = scr.screenCoords.x * scr.screenCoords.y;
    scr.framebuffer = malloc(sizeof(char) * scr.capacity);

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
    system("clear");

    for (int i = 0; i < screen->capacity; ++i)
    {
        screen->framebuffer[i] = ' ';
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

        screen->framebuffer[leftwall] = '|';
        screen->framebuffer[rightwall] = '|';
    }

    // Top and bottom walls
    for (int x = 0; x < (screen->screenCoords.x); ++x)
    {
        const int y = screen->screenCoords.y;
        const int topwall = 0 * screen->screenCoords.x + x;
        const int bottomwall = y * screen->screenCoords.x + x;

        screen->framebuffer[bottomwall] = '=';
        screen->framebuffer[topwall] = '=';
    }

    // Render snake on the screen
    for (int i = 0; i < snake->length; ++i)
    {
        Entity* snake = &entities->arr[i];
        Vec2i* snakepos = &snake->position;
        const int ypos = snakepos->y;
        const int coords = ypos * screen->screenCoords.x + snakepos->x;

        screen->framebuffer[coords] = snake->symbol;
    }

    for (int i = 0; i < screen->screenCoords.x; ++i)
    {
        const int coords = i * screen->screenCoords.x + (screen->screenCoords.x - 1);
        screen->framebuffer[coords] = '\n';
    }

    printf("%s", screen->framebuffer);
}
