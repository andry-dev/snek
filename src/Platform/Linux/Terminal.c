#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>

#include "Terminal.h"

struct terminal_context_t
{
    struct termios term;
    struct winsize size;
};

struct terminal_context_t* initTerm()
{
    struct terminal_context_t* ret = malloc(sizeof(struct terminal_context_t));

    ioctl(0, TIOCGWINSZ, &ret->size);

    tcgetattr(0, &ret->term);

    struct termios tmp = ret->term;

    tmp.c_lflag &= ~ICANON;
    tmp.c_lflag &= ~ECHO;
    tmp.c_cc[VMIN] = 0;
    tmp.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &tmp);

    return ret;
}

Vec2i getTermSize(struct terminal_context_t* context)
{
    Vec2i ret;

    ret.x = context->size.ws_col;
    ret.y = context->size.ws_row;

    return ret;
}

void deinitTerm(struct terminal_context_t* context)
{
    tcsetattr(0, TCSANOW, &context->term);
    if (context)
    {
        free(context);
    }
}

char getch(TerminalContext* context)
{
    (void)context;
    char input = 0;
    read(STDIN_FILENO, &input, 1);
    return input;
}


void clearTerm(struct terminal_context_t* context)
{
    (void)context;
    printf("\033[2J\033[1;1H");
}
