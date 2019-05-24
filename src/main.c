#include "Game.h"
#include "input/Common.h"

#include <stdio.h>
#include "Renderer.h"

#include "Timings.h"

int main(void)
{
    Vec2i maxScreen;
    scanf("%d", &maxScreen.x);
    scanf("%d", &maxScreen.y);
    Vec2i newDirection;
    Game game = initGame(maxScreen);
    char input;
    newDirection.x = 0;
    newDirection.y = -1;

    TerminalContext* term = initTerm();

    Screen screen = initScreen(game.screenCoords, term);

    const double maxfps = 1000.0 * 90.0;

    double lastTime = getCurrentTime();

    // Game loop
    while (1)
    {
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

        if (elapsed < maxfps)
        {
            sleepmillis(maxfps - elapsed);
        }

        moveSnake(&game.snake, newDirection);

        Entity* foodent = checkCollisions(&game.snake, &game.foods);
        if (foodent)
        {
            addSnakePart(&game.snake);
            removeFood(&game.foods, foodent);
            addFood(&game.foods, game.screenCoords);
        }

        int checkCollision = checkWallCollisions(&game.snake, &game.screenCoords);
        if (checkCollision)
        {
            printf("You lose\n");
            break;
        }

        clearScreen(&screen);
        draw(&screen, &game.snake, &game.foods);

        lastTime = current;
    }


    deinitTerm(term);
    deinitScreen(&screen);
    deinitGame(&game);

    return 0;
}
