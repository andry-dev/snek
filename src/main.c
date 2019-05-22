#include "Game.h"
#include "input/nix.h"

#include <unistd.h>
#include <termios.h>
#include <stdio.h>

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
    struct termios term_settings;
    Vec2i maxScreen;
    scanf("%d", &maxScreen.x);
    scanf("%d", &maxScreen.y);
    Vec2i newDirection;
    Game game = initGame(maxScreen);
    char input;
    newDirection.x = 0;
    newDirection.y = -1;
    initTerm(&term_settings); // Switches to no echo, unbuffered mode

    printSnake(&game);
    
    // Game loop
    while (1)
    {
        input = getch();

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

        printSnake(&game);

        int checkCollision = checkWallColisions(&game.entities, &game.screenCoords);
        if (checkCollision)
        {
            printf("You lose\n");
            break;
        }
    }

    restoreTermState(&term_settings); // Restores initial tty settings
    deinitGame(&game);

    return 0;
}
