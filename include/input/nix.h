#ifndef SNAKE_NIX_H
#define SNAKE_NIX_H

#include <unistd.h>

typedef struct termios term_settings;

void restoreTermState(struct termios *term_settings);

void initTerm(struct termios *term_settings);

char getch(void);

#endif
