#ifndef SNAKE_TERMINAL_H
#define SNAKE_TERMINAL_H

#include "Entities.h"

typedef struct terminal_context_t TerminalContext;

TerminalContext* initTerm();
void deinitTerm(TerminalContext* context);
Vec2i getTermSize(TerminalContext* context);
char getch(TerminalContext* context);
void drawToTerm(TerminalContext* context, char* buffer, int size);
void clearTerm(TerminalContext* context);
int querySignals(TerminalContext* context);

#endif
