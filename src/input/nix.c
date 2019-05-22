#include <unistd.h>
#include <termios.h>
#include <stdio.h>

void restoreTermState(struct termios *term_settings)
{
    tcsetattr(0, TCSANOW, term_settings);
}

void initTerm(struct termios *term_settings)
{
    struct termios newterm;
    tcgetattr(0, term_settings);

    newterm = *term_settings;
    newterm.c_lflag &= ~ICANON;
    newterm.c_lflag &= ~ECHO;
    newterm.c_cc[VMIN] = 0;
    newterm.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &newterm);
}

char getch(void)
{
    char input = 0;
    read(STDIN_FILENO, &input, 1);
    return input;
}
