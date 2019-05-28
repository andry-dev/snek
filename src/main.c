#include "Game.h"
#include "Terminal.h"

#include <stdio.h>
#include "Renderer.h"

#include "Timings.h"

int main(void)
{
    TerminalContext* term = initTerm();
    Vec2i maxScreen = getTermSize(term);
    // Account for rendering
    --maxScreen.x;
    maxScreen.y -= 2;

    Vec2i newDirection;
    Game game = initGame(maxScreen);
    char input;
    newDirection.x = 0;
    newDirection.y = -1;

    Screen screen = initScreen(game.screenCoords, term);

    const double maxfps = 1000.0 * 60.0;

    double lastTime = getCurrentTime();

    // Game loop
    while (1)
    {
        clearScreen(&screen);

        const double current = getCurrentTime();
        const double elapsed = current - lastTime;

        input = getch(term);

        switch (input)
        {
        case 'w':
        case 'W':
            newDirection.x = 0;
            newDirection.y = -1;
            break;

        case 's':
        case 'S':
            newDirection.x = 0;
            newDirection.y = 1;
            break;

        case 'a':
        case 'A':
            newDirection.x = -1;
            newDirection.y = 0;
            break;

        case 'd':
        case 'D':
            newDirection.x = 1;
            newDirection.y = 0;
            break;
        }

        {
            int shouldQuit = querySignals(term);
            if (shouldQuit)
            {
                break;
            }
        }

        if (elapsed < maxfps)
        {
            sleepmillis(maxfps - elapsed);
        }

        moveSnake(&game.snake, newDirection);

        int wallCollision = checkWallCollisions(&game.snake, &game.screenCoords);
        int snakeCollision = checkSelfCollisions(&game.snake);
        if (wallCollision || snakeCollision)
        {
            clearScreen(&screen);
            printf("You lose. SCORE: %d\n", game.scoring);
            break;
        }

        Entity* foodent = checkCollisions(&game.snake, &game.foods);
        if (foodent)
        {
            addSnakePart(&game.snake);
            removeFood(&game.foods, foodent);
            addFood(&game.foods, game.screenCoords);
            ++game.scoring;
        }


        drawScore(&screen, game.scoring);
        draw(&screen, &game.snake, &game.foods);

        lastTime = current;
    }


    deinitTerm(term);
    deinitScreen(&screen);
    deinitGame(&game);

    return 0;
}
