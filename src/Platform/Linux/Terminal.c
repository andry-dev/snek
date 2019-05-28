#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <fcntl.h>

#include "Terminal.h"

#include <signal.h>

struct terminal_context_t
{
    struct termios term;
    struct winsize size;
    sigset_t signals;
};


struct terminal_context_t* initTerm()
{
    struct terminal_context_t* ret = malloc(sizeof(struct terminal_context_t));

    sigemptyset(&ret->signals);
    sigaddset(&ret->signals, SIGINT);
    sigprocmask(SIG_BLOCK, &ret->signals, 0);

    ioctl(0, TIOCGWINSZ, &ret->size);

    printf("\033[2J\033[?25l");

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
    printf("\033[J\033[?25h");

    if (context)
    {
        free(context);
    }
}

char getch(struct terminal_context_t* context)
{
    (void)context;
    char input = 0;
    read(STDIN_FILENO, &input, 1);
    return input;
}

void drawToTerm(struct terminal_context_t* context, char* buffer, int size)
{
    (void)context;
    write(STDOUT_FILENO, buffer, size);
    //printf("%.*s", size, buffer);
}

void clearTerm(struct terminal_context_t* context)
{
    (void)context;
    printf("\033[0;0H");
}

int querySignals(struct terminal_context_t* context)
{
    sigpending(&context->signals);
    if (sigismember(&context->signals, SIGINT))
    {
        return 1;
    }

    return 0;
}
