#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

typedef struct terminal_context_t TerminalContext;

TerminalContext* initTerm();
void deinitTerm(TerminalContext* context);
char getch(TerminalContext* context);
void clearTerm(TerminalContext* context);

#endif
