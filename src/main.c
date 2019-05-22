#include "Game.h"

#include <stdio.h>
#include "Renderer.h"

void printSnake(Game* game)
{
    printf("Coords: %d %d\n", game->screenCoords.x, game->screenCoords.y);
    printf("Head: %d %d\n", game->entities.arr[0].position.x, game->entities.arr[0].position.y);

    printf("Body parts\n");
    for (int i = 1; i < game->snake.length; ++i)
    {
        printf("Body %d: %d %d\n", i, game->entities.arr[i].position.x,
                                      game->entities.arr[i].position.y);
    }
}


int main(void)
{
    Vec2i maxScreen;
    scanf("%d", &maxScreen.x);
    scanf("%d", &maxScreen.y);
    Game game = initGame(maxScreen);

    printSnake(&game);

    Screen screen = initScreen(game.screenCoords);

    // Game loop
    while (1)
    {

        Vec2i newDirection;
        newDirection.x = 0;
        newDirection.y = 0;

        char input = 0;
        scanf("%c\n", &input);

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


        moveSnake(&game.entities, &game.snake, newDirection);

        newDirection.x = 0;
        newDirection.y = 0;

        int checkCollision = checkWallColisions(&game.entities, &game.screenCoords);
        if (checkCollision)
        {
            printf("You lose\n");
            break;
        }

        clearScreen(&screen);
        draw(&screen, &game.snake, &game.foods, &game.entities);
    }


    deinitScreen(&screen);
    deinitGame(&game);

    return 0;
}
